#include <EndMenuState.h>

#include <_2017_0313_test2DprojApp.h>

EndMenuState::EndMenuState(_2017_0313_test2DprojApp* a_app) : IGameState(static_cast<aie::Application *>(a_app)) {
	Initialise();
}

void EndMenuState::Initialise() {

	/// Static cast to application with proper members. ~Implementation courtesy of Jack McCall
	APP = static_cast<_2017_0313_test2DprojApp*>(m_app);	//EXPENSIVE: Have this operation performed as little as possible.

#ifdef _DEBUG
	elapsedTime = 0;
#endif

#pragma region End Menu
	/// End Menu
	APP->m_endMenu = std::unique_ptr<Menu2D>(new Menu2D(nullptr));

	/// End Menu Buttons
	// Restart
	APP->m_endMenu->addButton(new Button2D("Restart", APP->m_fontList[BTN_TXT].get(),
		std::bind(&_2017_0313_test2DprojApp::restartFunc, APP), W_WIDTH / 2, W_HEIGHT / 2, DEFAULT_BTN_WIDTH, DEFAULT_BTN_HEIGHT,
		APP->m_textureList[BTN].get(), APP->m_audioList[BTN_CLICK].get(), APP->m_audioList[BTN_HVR].get())
	);

	// Quit
	APP->m_endMenu->addButton(new Button2D("Quit", APP->m_fontList[BTN_TXT].get(),
		std::bind(&_2017_0313_test2DprojApp::quitFunc, APP), W_WIDTH / 2, (W_HEIGHT / 2) - BTN_Y_INCREMENT, DEFAULT_BTN_WIDTH, DEFAULT_BTN_HEIGHT,
		APP->m_textureList[BTN].get(), APP->m_audioList[BTN_CLICK].get(), APP->m_audioList[BTN_HVR].get())
	);
#pragma endregion

}

void EndMenuState::Startup()
{
	// Stop all sounds
	for (auto pair : APP->m_audioList) {
		aie::Audio* snd = pair.m_val.get();

		if (snd->getIsPlaying()) {
			snd->stop();
		}
	}

	// Play the sting
	APP->m_audioList[GAME_END_STING]->play();
}

void EndMenuState::Update(float deltaTime)
{
#ifdef _DEBUG
	elapsedTime += deltaTime;
#endif

	aie::Input* input = aie::Input::getInstance();

	APP->m_endMenu->update(deltaTime, input);
}

void EndMenuState::Draw()
{
#ifdef _DEBUG
	char buffer[32];
	sprintf_s(buffer, "%3.2f", elapsedTime);

	APP->GetRenderer()->drawText(APP->m_fontList[TITLE_TXT].get(), buffer, 10, 50);
	APP->GetRenderer()->drawText(APP->m_fontList[TITLE_TXT].get(), "End Menu State", 10, 10);
#endif

	APP->m_endMenu->displayAll(APP->GetRenderer());
}

void EndMenuState::Shutdown()
{
	// End music before activating next state
	APP->m_endMenu->endMusic();
}

