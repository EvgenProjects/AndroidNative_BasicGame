#include <android/native_window.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "my_game.h"
#include "my_game_assets.h"

MyGame::MyGame(AAssetManager* pAssetManager)
{
	m_pAssetManager = pAssetManager;
    m_isButtonPressed = false;
    m_2DcameraPosition.x = 0;
    m_2DcameraPosition.y = 0;
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
    m_2DcameraPosition.y -= 0.008;

    for (int i=0; i<m_arrEnemyAirPlane.size(); i++)
        m_arrEnemyAirPlane[i].MoveByOffset(0, -0.004);

    if (m_isButtonPressed)
    {
        if (m_ptInDevicePixelWhenTouched.x < m_Graphic.GetWidth()/2.0f)
            m_MyAirPlane.MoveByOffset(-0.008, 0);
        else
            m_MyAirPlane.MoveByOffset(0.008, 0);
    }
}

void MyGame::OnDraw()
{
    m_Graphic.DrawBackground(0.72f, 0.87f, 0.55f, 1);

    // no move
    glLoadIdentity();
    glTranslatef(0, 0, 0);
    m_MyAirPlane.Draw();

    // move camera
    glLoadIdentity();
    glTranslatef(m_2DcameraPosition.x, m_2DcameraPosition.y, 0);

    for (int i=0; i<m_arrEnemyAirPlane.size(); i++)
        m_arrEnemyAirPlane[i].Draw();

    for (int i=0; i<m_arrBackgroundObject.size(); i++)
        m_arrBackgroundObject[i].Draw();

    m_Graphic.DrawGraphicEnd();
}

void MyGame::OnKillWindow()
{
    m_Graphic.CloseGraphic();
}

void MyGame::OnCreateWindow(ANativeWindow *pWindow)
{
    m_Graphic.InitGraphic(pWindow);

    m_2DcameraPosition.x = 0;
    m_2DcameraPosition.y = 0;

    m_MyAirPlane = TEMPLATE_MyAirPlane.CreateByTemplate(XY(0.5, 0.8), 0.2, 0.1);
    m_arrEnemyAirPlane.push_back(TEMPLATE_EnemyAirPlane.CreateByTemplate(XY(0.1, -1.4), 0.2, 0.1));
    m_arrEnemyAirPlane.push_back(TEMPLATE_EnemyAirPlane.CreateByTemplate(XY(0.15, -1.8), 0.2, 0.1));

    m_arrBackgroundObject.push_back(TEMPLATE_Lake.CreateByTemplate(XY(0.4, -1.3), 0.5, 0.5));
    m_arrBackgroundObject.push_back(TEMPLATE_Tree.CreateByTemplate(XY(0.88, -0.9), 0.08, 0.06));
    m_arrBackgroundObject.push_back(TEMPLATE_Tree.CreateByTemplate(XY(0.9, -1.2), 0.08, 0.06));
    m_arrBackgroundObject.push_back(TEMPLATE_Tree.CreateByTemplate(XY(0.3, -1.3), 0.08, 0.06));
}