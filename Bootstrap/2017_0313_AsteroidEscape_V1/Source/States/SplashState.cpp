#include <SplashState.h>
#include <_2017_0313_test2DprojApp.h>
#include <GameStateManager.h>

#define LOADING_SPEED 500.f			// How much to increase loading bar width per frame
#define LOADING_END 1000.f			// Maximum width loading bar can reach before loading is done

SplashState::SplashState(_2017_0313_test2DprojApp* a_app) : IGameState(static_cast<aie::Application *>(a_app)) {
	Initialise();
}

void SplashState::Initialise()
{
	/// Static cast to application with proper members. ~Implementation courtesy of Jack McCall
	APP = static_cast<_2017_0313_test2DprojApp*>(m_app);	//EXPENSIVE: Have this operation performed as little as possible.
}

void SplashState::Startup() {

}

void SplashState::Update(float deltaTime) {
	loadingBarExtents.x += LOADING_SPEED * deltaTime;

	// Reached end of loading, de-activate splash state and activate menu
	if (loadingBarExtents.x > LOADING_END) {
		APP->GetStateManager()->PopState();
		APP->GetStateManager()->SetState("MAIN_MENU");
	}
}

void SplashState::Draw()
{
	Vector2 middle = { float(APP->getWindowWidth() / 2), float(APP->getWindowHeight() / 2) };

	APP->GetRenderer()->drawSprite(
		APP->m_textureList[SPLASH].get(), (W_WIDTH / 2), (W_HEIGHT / 2), W_WIDTH, W_HEIGHT, 0, 100	//Draw behind everything
	);
	APP->GetRenderer()->drawText(APP->m_fontList[TITLE_TXT].get(), "LOADING", middle.x - 50, middle.y);

	APP->GetRenderer()->setRenderColour(0, 0.5f, 0);
	APP->GetRenderer()->drawBox(middle.x, middle.y - 40, loadingBarExtents.x, loadingBarExtents.y);
	APP->GetRenderer()->setRenderColour(0, 0, 0);
}

void SplashState::Shutdown() {

}