#include <android/native_window.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "my_game.h"
#include "my_game_assets.h"

MyGame::MyGame(AAssetManager* pAssetManager)
{
	m_pAssetManager = pAssetManager;
    m_isButtonPressed = false;
    m_moveStep = 0;
}

void MyGame::OnActiveFocus()
{
}

void MyGame::OnLostFocus()
{
}

bool MyGame::OnHandleTouch(AInputEvent* pEvent)
{
    if (m_Graphic.GetWidth()>0 && m_Graphic.GetHeight()>0 && AInputEvent_getType(pEvent) == AINPUT_EVENT_TYPE_MOTION) {

        if ((AMOTION_EVENT_ACTION_MASK & AMotionEvent_getAction(pEvent)) == AMOTION_EVENT_ACTION_DOWN)
        {
            m_isButtonPressed = true;
            m_ptWhenTouched = XY(
                    (float)AMotionEvent_getX(pEvent, 0) / (float)m_Graphic.GetWidth(), // normalize to [0, 1]
                    (float)AMotionEvent_getY(pEvent, 0) / (float)m_Graphic.GetHeight() // normalize to [0, 1]
            );

            return true;
        }
        else if ((AMOTION_EVENT_ACTION_MASK & AMotionEvent_getAction(pEvent)) == AMOTION_EVENT_ACTION_UP)
        {
            m_isButtonPressed = false;
        }
        return true;
    }
	return false; // event not handled
}

void MyGame::OnNextTick()
{
    m_Lake1.MoveByOffset(0, -m_moveStep);
    if (m_isButtonPressed)
    {
        if (m_ptWhenTouched.x < 0.5)
            m_MyAirPlane.MoveByOffset(-m_moveStep, 0);
        else
            m_MyAirPlane.MoveByOffset(m_moveStep, 0);
    }
}

void MyGame::OnDraw()
{
    m_Graphic.DrawBackground(0.72f, 0.87f, 0.55f, 1);

    m_MyAirPlane.Draw();
    m_Lake1.Draw();

    m_Graphic.DrawGraphicEnd();
}

void MyGame::OnKillWindow()
{
    m_Graphic.CloseGraphic();
}

void MyGame::OnCreateWindow(ANativeWindow *pWindow)
{
    m_Graphic.InitGraphic(pWindow);

    m_moveStep = 0.008;

    m_MyAirPlane.CreateByTemplate(g_MyAirPlane, XY(0.5, 0.8), 0.2, 0.1);
    m_Lake1.CreateByTemplate(g_Lake, XY(0.4, -1.3), 0.5, 0.7);
}