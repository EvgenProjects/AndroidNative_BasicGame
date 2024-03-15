#include <android/native_window.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include "graphic.h"

MyGraphic::MyGraphic()
{
	m_Width = 0;
	m_Height = 0;
	m_isGraphicInited = false;
}

void MyGraphic::DrawBackground(float red, float green, float blue, float alpha)
{
	if (m_Display == EGL_NO_DISPLAY || m_Surface == EGL_NO_SURFACE || m_Context == EGL_NO_CONTEXT)
		return;

    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MyGraphic::DrawGraphicEnd()
{
	if (m_Display == EGL_NO_DISPLAY || m_Surface == EGL_NO_SURFACE || m_Context == EGL_NO_CONTEXT)
		return;

	eglSwapBuffers(m_Display, m_Surface);
}

void MyGraphic::CreateSurfaceFromWindow(ANativeWindow* pWindow)
{
	const EGLint attribs[] = {EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
							  EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
							  EGL_BLUE_SIZE, 8,
							  EGL_GREEN_SIZE, 8,
							  EGL_RED_SIZE, 8,
							  EGL_NONE};
	EGLint format;
	EGLint numConfigs;

	eglChooseConfig(m_Display, attribs, &m_configOpenGL, 1, &numConfigs);

	eglGetConfigAttrib(m_Display, m_configOpenGL, EGL_NATIVE_VISUAL_ID, &format);

	m_Surface = eglCreateWindowSurface(m_Display, m_configOpenGL, pWindow, NULL);
}

void MyGraphic::InitGraphic(ANativeWindow* pWindow)
{
	if (m_isGraphicInited)
	{
		CreateSurfaceFromWindow(pWindow);
        eglMakeCurrent(m_Display, m_Surface, m_Surface, m_Context);
		return;
	}

	// init Display
	m_Display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(m_Display, nullptr, nullptr);

	// init Surface
	CreateSurfaceFromWindow(pWindow);

	// init Context
	EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 1/*openGL version 1*/ ,EGL_NONE };
	m_Context = eglCreateContext(m_Display, m_configOpenGL, NULL, contextAttribs);

	if (eglMakeCurrent(m_Display, m_Surface, m_Surface, m_Context) == EGL_FALSE)
		return;

	EGLint w, h;
	eglQuerySurface(m_Display, m_Surface, EGL_WIDTH, &w);
	eglQuerySurface(m_Display, m_Surface, EGL_HEIGHT, &h);

	m_Width = w;
	m_Height = h;

	// Open GL states
	//glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	// for alpha color (transparency)
	glEnable( GL_BLEND );
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enable draw lines and colors
    glEnableClientState(GL_VERTEX_ARRAY);// allow to use glVertexPointer
    glEnableClientState(GL_COLOR_ARRAY); // allow to use glColorPointer

	m_isGraphicInited = true;
}

void MyGraphic::CloseGraphic()
{
	if (m_Display != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(m_Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

		if (m_Context != EGL_NO_CONTEXT) {
			eglDestroyContext(m_Display, m_Context);
		}

		if (m_Surface != EGL_NO_SURFACE) {
			eglDestroySurface(m_Display, m_Surface);
		}

		eglTerminate(m_Display);
	}

	m_Display = EGL_NO_DISPLAY;
	m_Context = EGL_NO_CONTEXT;
	m_Surface = EGL_NO_SURFACE;
}

// my polygon
MyPolygon::MyPolygon()
{
	m_DrawMode = 0;
}
MyPolygon::MyPolygon(int drawMode, std::vector<XYZ_RGBA> arrPoint)
{
	m_DrawMode = drawMode;
	for (int i=0; i<arrPoint.size(); i++)
		m_arrPositionColor.push_back(arrPoint[i]);
}

void MyPolygon::Draw()
{
	int countOfPointsToDraw = m_arrPositionColor.size();

	// point (x,y,z)
	glVertexPointer(3, // it is count of fields: x,y,z
					GL_FLOAT,
					sizeof(XYZ_RGBA),
					(GLvoid*)m_arrPositionColor.data()
	);

	// color (r,g,b,alpha)
	glColorPointer(4, // it is count of fields: red,green,blue, alpha
				   GL_FLOAT,
				   sizeof(XYZ_RGBA),
				   (GLvoid*) ((char*)m_arrPositionColor.data()+sizeof(XYZ))
	);

	glDrawArrays(m_DrawMode, 0 /*first index to draw*/, countOfPointsToDraw);
}

void MyPolygon::MoveByOffset(float xOffset, float yOffset)
{
	for (int i=0; i<m_arrPositionColor.size(); i++) {
		m_arrPositionColor[i].position.x += xOffset;
		m_arrPositionColor[i].position.y += yOffset;
	}
}

/////////
MyObject::MyObject()
{

}
MyObject::MyObject(std::vector<MyPolygon> arrPolygon)
{
	for (int i=0; i<arrPolygon.size(); i++)
		m_arrPolygon.push_back(arrPolygon[i]);
}

void MyObject::Draw()
{
	for (int i=0; i<m_arrPolygon.size(); i++)
		m_arrPolygon[i].Draw();
}

void MyObject::MoveByOffset(float xOffset, float yOffset)
{
	for (int i=0; i<m_arrPolygon.size(); i++)
		m_arrPolygon[i].MoveByOffset(xOffset, yOffset);
}

void MyObject::CreateByTemplate(const MyObject& objTemplate, XY realPos, float realWidth, float realHeight)
{
	m_arrPolygon.clear();

	float minX = 0, maxX = 0;
	float minY = 0, maxY = 0;
	for (int iPolygon=0; iPolygon<objTemplate.m_arrPolygon.size(); iPolygon++)
	{
		MyPolygon myPolygon = objTemplate.m_arrPolygon[iPolygon];
		for (int i=0; i<myPolygon.ItemsCount(); i++)
		{
			XYZ_RGBA& rItem = myPolygon.GetItem(i);
			if (rItem.position.x<minX)
				minX = rItem.position.x;
			if (rItem.position.x>maxX)
				maxX = rItem.position.x;
			if (rItem.position.x<minY)
				minY = rItem.position.y;
			if (rItem.position.x>maxY)
				maxY = rItem.position.y;
		}
		m_arrPolygon.push_back(myPolygon);
	}
	float imgWidth = maxX-minX;
	if (imgWidth<=0)
		return;

	float imgHeight = maxY-minY;
	if (imgHeight<=0)
		return;

	for (int iPolygon=0; iPolygon<objTemplate.m_arrPolygon.size(); iPolygon++)
	{
		MyPolygon myPolygon = objTemplate.m_arrPolygon[iPolygon];

		// convert each point
		for (int i=0; i<myPolygon.ItemsCount(); i++)
		{
			XYZ_RGBA& rItem = myPolygon.GetItem(i);
			XY pt = XY (
					realPos.x + realWidth * rItem.position.x / imgWidth,
					realPos.y + realHeight * rItem.position.y / imgHeight);

			// convert from 0..1 to -1 ... 1
			rItem.position.x = pt.x*2.f-1.f;
			rItem.position.y = 2.f*(1.f-pt.y)-1.f;
		}
		m_arrPolygon.push_back(myPolygon);
	}
}
