#include <android/native_window.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include "graphic.h"

Graphic::Graphic()
{
	m_Width = 0;
	m_Height = 0;
	m_isGraphicInited = false;
}

void Graphic::DrawBackground(float red, float green, float blue, float alpha)
{
	if (m_Display == EGL_NO_DISPLAY || m_Surface == EGL_NO_SURFACE || m_Context == EGL_NO_CONTEXT)
		return;

    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphic::DrawGraphicEnd()
{
	if (m_Display == EGL_NO_DISPLAY || m_Surface == EGL_NO_SURFACE || m_Context == EGL_NO_CONTEXT)
		return;

	eglSwapBuffers(m_Display, m_Surface);
}

void Graphic::CreateSurfaceFromWindow(ANativeWindow* pWindow)
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

void Graphic::InitGraphic(ANativeWindow* pWindow)
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

void Graphic::CloseGraphic()
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

// my 2D primitive
void My2DPrimitive::SetMode(int drawMode)
{
	m_DrawMode = drawMode;
}

void My2DPrimitive::Add(float x, float y, RGBA color)
{
	// convert from 0..1 to -1 ... 1
	m_arrPosition.push_back(XYZ{.x=(x*2.f-1.f), .y=2.f*(1.f-y)-1.f, .z=0});
	m_arrColor.push_back(color);
}

void My2DPrimitive::RemoveAll()
{
	m_arrPosition.clear();
	m_arrColor.clear();
}

void My2DPrimitive::Draw()
{
	int countOfPointsToDraw = m_arrPosition.size();

	// point (x,y,z)
	glVertexPointer(3, // it is count of fields: x,y,z
					GL_FLOAT,
					sizeof(XYZ),
					(GLvoid*)m_arrPosition.data()
	);

	// color (r,g,b,alpha)
	glColorPointer(4, // it is count of fields: red,green,blue, alpha
				   GL_FLOAT,
				   sizeof(RGBA),
				   (GLvoid*) ((char*)m_arrColor.data())
	);

	glDrawArrays(m_DrawMode, 0 /*first index to draw*/, countOfPointsToDraw);
}

void My2DPrimitive::MoveByOffset(float xOffset, float yOffset)
{
	for (int i=0; i<m_arrPosition.size(); i++) {
		m_arrPosition[i].x += xOffset;
		m_arrPosition[i].y += yOffset;
	}
}

/////////
void My2DObject::Add2DPrimitive(My2DPrimitive primitive)
{
	m_arr2DPrimitive.push_back(primitive);
}
void My2DObject::RemoveAll()
{
	m_arr2DPrimitive.clear();
}
void My2DObject::Draw()
{
	for (int i=0; i<m_arr2DPrimitive.size(); i++)
		m_arr2DPrimitive[i].Draw();
}

void My2DObject::MoveByOffset(float xOffset, float yOffset)
{
	for (int i=0; i<m_arr2DPrimitive.size(); i++)
		m_arr2DPrimitive[i].MoveByOffset(xOffset, yOffset);
}