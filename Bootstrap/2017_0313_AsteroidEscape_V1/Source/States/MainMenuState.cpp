#include <MainMenuState.h>
#include <_2017_0313_test2DprojApp.h>

MainMenuState::MainMenuState(_2017_0313_test2DprojApp* a_app) : IGameState(static_cast<aie::Application *>(a_app)) {
	Initialise();
}

void MainMenuState::Initialise()
{
	/// Static cast to application with proper members. ~Implementation courtesy of Jack McCall
	APP = static_cast<_2017_0313_test2DprojApp*>(m_app);	//EXPENSIVE: Have this operation performed as little as possible.

#ifdef _DEBUG
	elapsedTime = 0;
#endif

#pragma region Main Menu
	///Main Menu
	APP->m_mainMenu = std::unique_ptr<Menu2D>(
		new Menu2D(APP->m_audioList[MENU_MUS].get(), true, APP->m_textureList[TITLE].get(), APP->m_textureList[M_BG].get())
		); //.get() returns raw pointer
	
		   /// Main Menu Buttons
	// Play
	APP->m_mainMenu->addButton(new Button2D("Play Game", APP->m_fontList[BTN_TXT].get(),
		// Bind button function to an instance of application in order to pass in as a std::function
		std::bind(&_2017_0313_test2DprojApp::startFunc, APP), W_WIDTH / 2, W_HEIGHT / 2, DEFAULT_BTN_WIDTH, DEFAULT_BTN_HEIGHT,
		APP->m_textureList[BTN].get(), APP->m_audioList[BTN_CLICK].get(), APP->m_audioList[BTN_HVR].get())
	);

	// Quit
	APP->m_mainMenu->addButton(new Button2D("Quit Game", APP->m_fontList[BTN_TXT].get(),
		std::bind(&_2017_0313_test2DprojApp::quitFunc, APP), W_WIDTH / 2, (W_HEIGHT / 2) - BTN_Y_INCREMENT, DEFAULT_BTN_WIDTH, DEFAULT_BTN_HEIGHT,
		APP->m_textureList[BTN].get(), APP->m_audioList[BTN_CLICK].get(), APP->m_audioList[BTN_HVR].get())
	);
#pragma endregion

}

void MainMenuState::Startup()
{
}

void MainMenuState::Update(float deltaTime)
{
#ifdef _DEBUG
	elapsedTime += deltaTime;
#endif

	aie::Input* input = aie::Input::getInstance();

	APP->m_mainMenu->update(deltaTime, input);
}

void MainMenuState::Draw()
{
#ifdef _DEBUG
	char buffer[32];
	sprintf_s(buffer, "%3.2f", elapsedTime);

	APP->GetRenderer()->drawText(APP->m_fontList[TITLE_TXT].get(), buffer, 10, 50);
	APP->GetRenderer()->drawText(APP->m_fontList[TITLE_TXT].get(), "Menu State", 10, 10);
#endif

	APP->m_mainMenu->displayAll(APP->GetRenderer());
}

void MainMenuState::Shutdown()
{
	// End music before activating next state
	APP->m_mainMenu->endMusic();
}
