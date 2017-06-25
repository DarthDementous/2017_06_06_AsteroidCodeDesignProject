#include <PauseState.h>
#include <_2017_0313_test2DprojApp.h>
#include <GameStateManager.h>

PauseState::PauseState(_2017_0313_test2DprojApp* a_app) : IGameState(static_cast<aie::Application *>(a_app)) {
	Initialise();
}

void PauseState::Initialise()
{
	/// Static cast to application with proper members. ~Implementation courtesy of Jack McCall
	APP = static_cast<_2017_0313_test2DprojApp*>(m_app);	//EXPENSIVE: Have this operation performed as little as possible.
}

void PauseState::Startup()
{
}

void PauseState::Update(float deltaTime) {
	aie::Input *input = aie::Input::getInstance();

	// If un-paused, resume game and leave pause state.
	if (input->wasKeyPressed(aie::INPUT_KEY_P)) {
		APP->GetStateManager()->ResumeStates();
		APP->GetStateManager()->PopState();
	}
}

void PauseState::Draw()
{
	APP->GetRenderer()->drawText(APP->m_fontList[TITLE_TXT].get(), "PAUSED", float(APP->getWindowWidth() / 2), float(APP->getWindowHeight() - 20));
}

void PauseState::Shutdown()
{
}
