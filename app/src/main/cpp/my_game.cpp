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
    m_2DcameraPosition.x = 0;
    m_2DcameraPosition.y = 0;
    m_2DcameraAngle = 0;
}

void MyGame::OnActiveFocus()
{
}

void MyGame::OnLostFocus()
{
}

bool MyGame::OnHandleTouch(AInputEvent* pEvent, bool isMotion, bool isTouchDown, bool isTouchUp, float xDevicePixel, float yDevicePixel)
{
    if (isMotion && isTouchDown)
    {
        m_isButtonPressed = true;
        m_ptInDevicePixelWhenTouched = XY(xDevicePixel, yDevicePixel);
        return true;
    }
    else if (isMotion && isTouchUp)
    {
        m_isButtonPressed = false;
        return true;
    }
	return false; // event not handled
}

void MyGame::OnNextTick()
{
    m_2DcameraPosition.y += m_moveStep;
    if (m_isButtonPressed)
    {
        if (m_ptInDevicePixelWhenTouched.x < m_Graphic.GetWidth()/2.0f)
            m_MyAirPlane.MoveByOffset(m_moveStep, 0);
        else
            m_MyAirPlane.MoveByOffset(-m_moveStep, 0);
    }
}

void MyGame::OnDraw()
{
    m_Graphic.DrawBackground(0.72f, 0.87f, 0.55f, 1);

    // no move
    glLoadIdentity();
    glRotatef(m_2DcameraAngle, 0, 0, 1);
    glTranslatef(0, 0, 0);
    m_MyAirPlane.Draw();

    // move camera
    glLoadIdentity();
    glRotatef(m_2DcameraAngle, 0, 0, 1);
    glTranslatef(m_2DcameraPosition.x, m_2DcameraPosition.y, 0);
    m_Lake1.Draw();
    m_EnemyAirPlane.Draw();

    m_Graphic.DrawGraphicEnd();
}

void MyGame::OnKillWindow()
{
    m_Graphic.CloseGraphic();
}

void MyGame::OnCreateWindow(ANativeWindow *pWindow)
{
    m_Graphic.InitGraphic(pWindow);

    m_moveStep = -0.008;
    m_2DcameraPosition.x = 0;
    m_2DcameraPosition.y = 0;

    m_MyAirPlane.CreateByTemplate(g_MyAirPlane, XY(0.5, 0.8), 0.2, 0.1);
    m_Lake1.CreateByTemplate(g_Lake, XY(0.4, -1.3), 0.5, 0.7);
    m_EnemyAirPlane.CreateByTemplate(g_EnemyAirPlane, XY(0.2, -0.8), 0.2, 0.1);
}