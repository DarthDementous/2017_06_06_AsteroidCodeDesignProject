#include <PlayState.h>
#include <_2017_0313_test2DprojApp.h>
#include <GameStateManager.h>
#include <EntityMaker.h>
#include <CAsteroidDeployer.h>

PlayState::PlayState(_2017_0313_test2DprojApp* a_app) : IGameState(static_cast<aie::Application *>(a_app)) {
	Initialise();
}

PlayState::~PlayState() {
	for (auto comp : m_components) {
		delete comp;
	}
}

void PlayState::Initialise()
{
	/// Static cast to application with proper members. ~Implementation courtesy of Jack McCall
	APP = static_cast<_2017_0313_test2DprojApp*>(m_app);	//EXPENSIVE: Have this operation performed as little as possible.

	AddComponent(new CAsteroidDeployer(APP));
}

void PlayState::Startup()
{
#ifdef _DEBUG
	elapsedTime = 0;
#endif

	/// Initialise music
	//Play the game intro
	APP->m_audioList[GAME_MUS_INTRO]->play();

	/// Initialise game environment
	//Reset entities
	APP->m_Asteroids.Erase(APP->m_Asteroids.begin(), APP->m_Asteroids.end());
	APP->m_Bullets.Erase(APP->m_Bullets.begin(), APP->m_Bullets.end());

	//Reset player
	APP->m_Player = EntityMaker::createPlayer(APP->m_textureList[PLAYER_SPRITE].get(), APP);
}

void PlayState::Update(float deltaTime)
{
#ifdef _DEBUG
	elapsedTime += deltaTime;
	framesPerSecond = deltaTime * 100000;				// Convert to seconds
#endif

	aie::Input* input = aie::Input::getInstance();

	// If paused, pause game and activate pause state.
	if (input->wasKeyPressed(aie::INPUT_KEY_P)) {    // wasKeyPressed = Check only spans one frame and doesn't carry over into next update loop
		APP->GetStateManager()->PauseStates();
		APP->GetStateManager()->SetState("PAUSE");
	}

	// Update components
	for (auto comp : m_components) {
		comp->Update(deltaTime);
	}

#pragma region Music
	//Change to loop when intro is finished
	if (!APP->m_audioList[GAME_MUS_INTRO]->getIsPlaying()) {
		APP->m_audioList[GAME_MUS_LOOP]->play();
	}
#pragma endregion

#pragma region Collisions
	APP->checkCollisions(deltaTime);
#pragma endregion
	
#pragma region Player (check after collisions in case player has died)
	APP->m_Player->update(deltaTime);
	APP->m_Player->updateInput(deltaTime, input);
#pragma endregion
	
#pragma region Game Over
	if (!APP->m_Player->isAlive()) {
		APP->GetStateManager()->PauseStates();						// Freeze game
		APP->GetStateManager()->SetState("END_MENU");
	}
#pragma endregion

}

void PlayState::Draw()
{
#ifdef _DEBUG
	char buffer[32];
	sprintf_s(buffer, "%3.2f", elapsedTime);

	APP->GetRenderer()->drawText(APP->m_fontList[TITLE_TXT].get(), buffer, 10, 50);
	APP->GetRenderer()->drawText(APP->m_fontList[TITLE_TXT].get(), "Play State", 10, 10);

	char fps[32];
	sprintf_s(fps, "FPS: %2.2f", framesPerSecond);

	APP->GetRenderer()->drawText(APP->m_fontList[DEBUG_TXT].get(), fps, float(APP->getWindowWidth() - 350), float(APP->getWindowHeight() - 40));
#endif

	// Draw components
	for (auto comp : m_components) {
		comp->Render(APP->GetRenderer());
	}

#pragma region Player
	APP->m_Player->render(APP->GetRenderer());
#pragma endregion

#pragma region Background
	APP->GetRenderer()->drawSprite(
		APP->m_textureList[G_BG].get(), (W_WIDTH / 2), (W_HEIGHT / 2), W_WIDTH, W_HEIGHT, 0, 100	//Draw behind everything
	);
#pragma endregion

}

void PlayState::Shutdown()
{
	//If intro is still playing end that, otherwise end the loop.
	if (APP->m_audioList[GAME_MUS_INTRO]->getIsPlaying()) {
		APP->m_audioList[GAME_MUS_INTRO]->stop();
	}
	else {
		APP->m_audioList[GAME_MUS_LOOP]->stop();
	}
}
