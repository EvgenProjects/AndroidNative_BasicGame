#include <android/native_window.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "my_game.h"

MyGame::MyGame(AAssetManager* pAssetManager)
{
    m_Width = 0;
    m_Height = 0;
    m_pAssetManager = pAssetManager;
}

void MyGame::OnActiveFocus()
{
}

void MyGame::OnLostFocus()
{
}

bool MyGame::OnHandleTouch(AInputEvent* pEvent)
{
    return false; // event not handled
}

void MyGame::OnNextTick()
{
}

// open GL
void MyGame::DrawGraphic_OpenGL()
{
    // green color
    glClearColor(0.0f, 0.95f, 0.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    eglSwapBuffers(m_Display, m_Surface);
}

bool MyGame::InitGraphic_OpenGL(ANativeWindow* pWindow)
{
    const EGLint attribs[] = {EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, // new lines !!!!!
                              EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                              EGL_BLUE_SIZE,    8,
                              EGL_GREEN_SIZE,   8,
                              EGL_RED_SIZE,     8,
                              EGL_NONE};
    EGLint w, h, format;
    EGLint numConfigs;
    EGLConfig config = nullptr;
    EGLSurface surface;
    EGLContext context;

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, nullptr, nullptr);

    eglChooseConfig(display, attribs, &config, 1, &numConfigs);

    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    surface = eglCreateWindowSurface(display, config, pWindow, NULL);

    EGLint contextAttribs[] =
            {
                    EGL_CONTEXT_CLIENT_VERSION, 2,
                    EGL_NONE
            };
    context = eglCreateContext(display, config, NULL, contextAttribs);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
        return false;

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    m_Display = display;
    m_Context = context;
    m_Surface = surface;
    m_Width = w;
    m_Height = h;

    // Open GL states
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    return true;
}

void MyGame::CloseGraphic_OpenGL()
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