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
    protected: Graphic m_Graphic;
    protected: bool m_isButtonPressed;
    protected: XY m_ptWhenTouched;
    protected: float m_moveStep;

    // my game
    public: void CreateMyAirPlane(float xCenter, float yCenter);
    public: void CreateEnemyAirPlane(float xCenter, float yCenter);
    public: void CreateLake(float xCenter, float yCenter, float width, float height);
    protected: My2DObject m_AirPlane;
    protected: My2DObject m_Lakes;
    protected: My2DObject m_EnemyAirPlane;

    // events
    public: void OnActiveFocus();
    public: void OnLostFocus();
    public: bool OnHandleTouch(AInputEvent* pEvent);
    public: void OnNextTick();
    public: void OnCreateWindow(ANativeWindow* pWindow);
    public: void OnKillWindow();
    public: void OnDraw();
};

