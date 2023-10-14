#include <android_native_app_glue.h>
#include <android/sensor.h>
#include <cassert>

#include "my_game.h"

// my settings
class MySettings
{
	// fields
	public: constexpr static const float TURN_TIMES_IN_SECONDS = 0.02f; // 50 times per second
	public: bool m_IsPause = false;
	public: bool m_IsGraphicInited = false;
	public: MyGame MyGame;

	// local variables
	private: struct timespec _currentTime;
	private: struct timespec _lastTime;

	// constructor
	public: MySettings(AAssetManager* pAssetManager) : MyGame(pAssetManager)
	{
		_currentTime.tv_sec = 0;
		_currentTime.tv_nsec = 0;
		_lastTime.tv_sec = 0;
		_lastTime.tv_nsec = 0;
	}

	public: bool IsNextGameTick()
	{
		// get current time
		_currentTime.tv_sec = _currentTime.tv_nsec = 0;
		clock_gettime(CLOCK_MONOTONIC, &_currentTime);

		// is ellapsed time
		if ( ((_currentTime.tv_sec - _lastTime.tv_sec) + (_currentTime.tv_nsec - _lastTime.tv_nsec) / 1000000000.f) >= TURN_TIMES_IN_SECONDS )
		{
			// set last time
			_lastTime.tv_sec = _currentTime.tv_sec;
			_lastTime.tv_nsec = _currentTime.tv_nsec;
			return true;
		}
		return false;
	}
};

/**
 * touch events:
 */
int32_t engine_handle_input(struct android_app* app, AInputEvent* pEvent)
{
	MySettings* pMySettings = (MySettings*)app->userData;
	return pMySettings->MyGame.OnHandleTouch(pEvent);
}

/**
 * application events: application on focus, lost focus, window create, window close
 */
void engine_handle_cmd(struct android_app* app, int32_t cmd)
{
	MySettings* pMySettings = (MySettings*)app->userData;

	switch (cmd) {
		case APP_CMD_SAVE_STATE:
			break;

		case APP_CMD_INIT_WINDOW:
			if (pMySettings->m_IsGraphicInited)
			{
				pMySettings->MyGame.CreateSurfaceFromWindow_OpenGL(app->window);
				pMySettings->MyGame.MakeCurrent_Display_Surface_Context_OpenGL();
			}
			else
			{
				pMySettings->m_IsGraphicInited = pMySettings->MyGame.InitGraphic_OpenGL(app->window);
			}
			break;

		case APP_CMD_TERM_WINDOW:
			{
				// The window is being hidden or closed, clean it up.
				pMySettings->MyGame.KillSurface_OpenGL();
				break;
			}

		case APP_CMD_GAINED_FOCUS:
		{
			pMySettings->m_IsPause = false;
			pMySettings->MyGame.OnActiveFocus();
			break;
		}

		case APP_CMD_LOST_FOCUS:
		{
			pMySettings->m_IsPause = true;
			pMySettings->MyGame.OnLostFocus();
			break;
		}

		default:
			break;
	}
}

/**
 * This is the main entry point of a native application that is using android_native_app_glue.
 * It runs in its own thread, with its own event loop for receiving input events and draw scene.
 */
void android_main(struct android_app* pAndroidApp)
{
	MySettings mySettings(pAndroidApp->activity->assetManager);

	pAndroidApp->userData = &mySettings;
	pAndroidApp->onAppCmd = engine_handle_cmd;
	pAndroidApp->onInputEvent = engine_handle_input;

	// events.
	int ident;
	int events;
	struct android_poll_source* source;

	// loop waiting for stuff to do.
	while (true)
	{
		// If -1, we will block forever waiting for events.
		// If 0, we loop until all events are read, then continue to draw the next frame of animation.
		if ((ident = ALooper_pollOnce(0 /* -1 0 */, nullptr, &events,(void**)&source)) >= 0)
		{
			// Process this event.
			if (source != nullptr) {
				source->process(pAndroidApp, source);
			}

			// stop application
			if (pAndroidApp->destroyRequested != 0)
			{
				mySettings.MyGame.CloseGraphic_OpenGL();
				return;
			}
		}

		if (!mySettings.m_IsPause && mySettings.m_IsGraphicInited)
		{
			// draw scene
			mySettings.MyGame.DrawGraphic_OpenGL();

			 // next tick
			if (mySettings.IsNextGameTick())
			{
				mySettings.MyGame.OnNextTick();
			}
		}
	}
}