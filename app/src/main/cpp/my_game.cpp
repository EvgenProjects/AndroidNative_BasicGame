#include <android/native_window.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "my_game.h"

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
    m_Lakes.MoveByOffset(0, -m_moveStep);

    m_EnemyAirPlane.MoveByOffset(0, -m_moveStep*1.5);

    if (m_isButtonPressed)
    {
        if (m_ptWhenTouched.x < 0.5)
            m_AirPlane.MoveByOffset(-m_moveStep, 0);
        else
            m_AirPlane.MoveByOffset(m_moveStep, 0);
    }
}

void MyGame::OnDraw()
{
    m_Graphic.DrawBackground(0.72f, 0.87f, 0.55f, 1);

    m_EnemyAirPlane.Draw();
    m_AirPlane.Draw();
    m_Lakes.Draw();

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

    CreateEnemyAirPlane(0.2, -1.7);
    CreateEnemyAirPlane(0.5, -1.2);
    CreateEnemyAirPlane(0.3, -3.7);

    CreateMyAirPlane(0.5, 0.8);

    CreateLake(0.4, -0.3, 0.5, 0.4);
    CreateLake(0.1, -2.1, 0.7, 0.5);
    CreateLake(0.5, -4, 0.5, 0.7);
    CreateLake(0.4, -7, 0.7, 0.5);
}

void MyGame::CreateLake(float xCenter, float yCenter, float width, float height)
{
    My2DPrimitive primitive2D;

    RGBA colorBlue = {0.0f, 0.0f, 1.0f, 1.0f};
    RGBA colorLightBlue = {0.3f, 0.3f, 0.5f, 1.0f};

    // lake
    primitive2D.RemoveAll();
    primitive2D.Add(xCenter - width / 2.f, yCenter - height / 2.f, colorBlue);
    primitive2D.Add(xCenter + width / 2.f, yCenter - height / 2.f, colorLightBlue);
    primitive2D.Add(xCenter - width / 2.f, yCenter + height / 2.f, colorLightBlue);
    primitive2D.Add(xCenter + width / 2.f, yCenter + height / 2.f, colorLightBlue);
    primitive2D.SetMode(GL_TRIANGLE_STRIP);
    m_Lakes.Add2DPrimitive(primitive2D);
}

void MyGame::CreateMyAirPlane(float xCenter, float yCenter)
{
    My2DPrimitive primitive2D;

    float wingW = 0.3;
    float wingH = 0.02;
    float wingA = 0.01;

    float backWingW = 0.10;
    float backWingH = 0.018;
    float backWingHOffset = 0.066;

    float bodyW1 = 0.054;
    float bodyW2 = 0.03;
    float bodyH = 0.12;
    float bodyHOffset = 0.02;
    float bodyHeadRadius = 0.01;

    RGBA color1 = {0.9f, 0.9f, 0.9f, 1.0f};
    RGBA color2 = {0.3f, 0.3f, 0.3f, 0.6f};

    // body
    primitive2D.RemoveAll();
    primitive2D.Add(xCenter + bodyW2 / 2.f,    yCenter + bodyH / 2.f+bodyHOffset, color1);
    primitive2D.Add(xCenter - bodyW2 / 2.f,    yCenter + bodyH / 2.f+bodyHOffset, color1);
    primitive2D.Add(xCenter + bodyW1 / 2.f,    yCenter - bodyH / 2.f+bodyHOffset, color2);
    primitive2D.Add(xCenter - bodyW1 / 2.f,    yCenter - bodyH / 2.f+bodyHOffset, color2);
    primitive2D.Add(xCenter,                   yCenter - bodyH / 2.f+bodyHOffset-(bodyHeadRadius), color2);
    primitive2D.SetMode(GL_TRIANGLE_STRIP);
    m_AirPlane.Add2DPrimitive(primitive2D);

    // left wing
    primitive2D.RemoveAll();
    primitive2D.Add(xCenter - wingW / 2.f, yCenter - wingH / 2.f, color2);
    primitive2D.Add(xCenter + 0,           yCenter - wingH / 2.f, color2);
    primitive2D.Add(xCenter - wingW / 2.f, yCenter + wingH / 2.f, color1);
    primitive2D.Add(xCenter + 0,           yCenter + wingH / 2.f + wingA, color1);
    primitive2D.SetMode(GL_TRIANGLE_STRIP);
    m_AirPlane.Add2DPrimitive(primitive2D);

    // right wing
    primitive2D.RemoveAll();
    primitive2D.Add(xCenter + wingW / 2.f, yCenter - wingH / 2.f, color2);
    primitive2D.Add(xCenter + 0,           yCenter - wingH / 2.f, color2);
    primitive2D.Add(xCenter + wingW / 2.f, yCenter + wingH / 2.f, color1);
    primitive2D.Add(xCenter + 0,           yCenter + wingH / 2.f + wingA, color1);
    primitive2D.SetMode(GL_TRIANGLE_STRIP);
    m_AirPlane.Add2DPrimitive(primitive2D);

    // back wing
    primitive2D.RemoveAll();
    primitive2D.Add(xCenter - backWingW / 2.f, yCenter - backWingH / 2.f + backWingHOffset, color2);
    primitive2D.Add(xCenter + backWingW / 2.f, yCenter - backWingH / 2.f + backWingHOffset, color2);
    primitive2D.Add(xCenter - backWingW / 2.f, yCenter + backWingH / 2.f + backWingHOffset, color1);
    primitive2D.Add(xCenter + backWingW / 2.f, yCenter + backWingH / 2.f + backWingHOffset, color1);
    primitive2D.SetMode(GL_TRIANGLE_STRIP);
    m_AirPlane.Add2DPrimitive(primitive2D);
}

void MyGame::CreateEnemyAirPlane(float xCenter, float yCenter)
{
    My2DPrimitive primitive2D;

    float wingW = 0.25;
    float wingH = 0.015;
    float wingA = 0.0075;

    float backWingW = 0.075;
    float backWingH = 0.0135;
    float backWingHOffset = 0.054;

    float bodyW1 = 0.033;
    float bodyW2 = 0.025;
    float bodyH = 0.09;
    float bodyHOffset = 0.015;
    float bodyHeadRadius = 0.0075;

    RGBA color1 = {0.9f, 0.2f, 0.4f, 1.0f};
    RGBA color2 = {0.5f, 0.2f, 0.1f, 0.6f};

    // body
    primitive2D.RemoveAll();
    primitive2D.Add(xCenter + bodyW2 / 2.f,    yCenter - bodyH / 2.f-bodyHOffset, color1);
    primitive2D.Add(xCenter - bodyW2 / 2.f,    yCenter - bodyH / 2.f-bodyHOffset, color1);
    primitive2D.Add(xCenter + bodyW1 / 2.f,    yCenter + bodyH / 2.f-bodyHOffset, color2);
    primitive2D.Add(xCenter - bodyW1 / 2.f,    yCenter + bodyH / 2.f-bodyHOffset, color2);
    primitive2D.Add(xCenter,                   yCenter + bodyH / 2.f-bodyHOffset+(bodyHeadRadius), color2);
    primitive2D.SetMode(GL_TRIANGLE_STRIP);
    m_EnemyAirPlane.Add2DPrimitive(primitive2D);

    // left wing
    primitive2D.RemoveAll();
    primitive2D.Add(xCenter - wingW / 2.f, yCenter + wingH / 2.f, color2);
    primitive2D.Add(xCenter + 0,           yCenter + wingH / 2.f, color2);
    primitive2D.Add(xCenter - wingW / 2.f, yCenter - wingH / 2.f, color1);
    primitive2D.Add(xCenter + 0,           yCenter - wingH / 2.f - wingA, color1);
    primitive2D.SetMode(GL_TRIANGLE_STRIP);
    m_EnemyAirPlane.Add2DPrimitive(primitive2D);

    // right wing
    primitive2D.RemoveAll();
    primitive2D.Add(xCenter + wingW / 2.f, yCenter + wingH / 2.f, color2);
    primitive2D.Add(xCenter + 0,           yCenter + wingH / 2.f, color2);
    primitive2D.Add(xCenter + wingW / 2.f, yCenter - wingH / 2.f, color1);
    primitive2D.Add(xCenter + 0,           yCenter - wingH / 2.f - wingA, color1);
    primitive2D.SetMode(GL_TRIANGLE_STRIP);
    m_EnemyAirPlane.Add2DPrimitive(primitive2D);

    // back wing
    primitive2D.RemoveAll();
    primitive2D.Add(xCenter - backWingW / 2.f, yCenter + backWingH / 2.f - backWingHOffset, color2);
    primitive2D.Add(xCenter + backWingW / 2.f, yCenter + backWingH / 2.f - backWingHOffset, color2);
    primitive2D.Add(xCenter - backWingW / 2.f, yCenter - backWingH / 2.f - backWingHOffset, color1);
    primitive2D.Add(xCenter + backWingW / 2.f, yCenter - backWingH / 2.f - backWingHOffset, color1);
    primitive2D.SetMode(GL_TRIANGLE_STRIP);
    m_EnemyAirPlane.Add2DPrimitive(primitive2D);
}