#include <android/input.h>
#include <android/asset_manager.h>
#include <EGL/egl.h>

class MyGame
{
    // constructor
    public: MyGame(AAssetManager* pAssetManager);

    // fields
    protected: AAssetManager* m_pAssetManager;
    protected: EGLDisplay m_Display;
    protected: EGLSurface m_Surface;
    protected: EGLContext m_Context;
    protected: int32_t m_Width;
    protected: int32_t m_Height;

    // events
    public: void OnActiveFocus();
    public: void OnLostFocus();
    public: bool OnHandleTouch(AInputEvent* pEvent);
    public: void OnNextTick();

    // OpenGL
    public: bool InitGraphic_OpenGL(ANativeWindow* pWindow);
    public: void CloseGraphic_OpenGL();
    public: void DrawGraphic_OpenGL();
};

