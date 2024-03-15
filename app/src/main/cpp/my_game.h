#include <android/input.h>
#include <android/asset_manager.h>
#include <EGL/egl.h>
#include "graphic.h"

class MyGame
{
    // constructor
    public: MyGame(AAssetManager* pAssetManager);

    // fields
    protected: AAssetManager* m_pAssetManager;
    protected: MyGraphic m_Graphic;
    protected: bool m_isButtonPressed;
    protected: XY m_ptInDevicePixelWhenTouched;
    protected: float m_moveStep;

    // my game
    protected: MyObject m_MyAirPlane;
    protected: MyObject m_Lake1;
    protected: XY m_2DcameraPosition;
    protected: float m_2DcameraAngle;
    // events
    public: void OnActiveFocus();
    public: void OnLostFocus();
    public: bool OnHandleTouch(AInputEvent* pEvent, bool isMotion, bool isTouchDown, bool isTouchUp, float xDevicePixel, float yDevicePixel);
    public: void OnNextTick();
    public: void OnCreateWindow(ANativeWindow* pWindow);
    public: void OnKillWindow();
    public: void OnDraw();
};

