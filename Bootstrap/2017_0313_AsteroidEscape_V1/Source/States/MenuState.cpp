#include <MenuState.h>
#include <_2017_0313_test2DprojApp.h>

#include <ResourceManager.h>
#include <Font.h>

MenuState::MenuState(_2017_0313_test2DprojApp* a_app) : IGameState(static_cast<aie::Application *>(a_app)) {
	Initialise();
}

void MenuState::Initialise()
{
	//Main Menu
	elapsedTime = 0;

	// Static cast to application with proper members. ~Implementation courtesy of Jack McCall
	APP = static_cast<_2017_0313_test2DprojApp*>(m_app);	//EXPENSIVE: Have this operation performed as little as possible.
	
}

void MenuState::Update(float deltaTime)
{
	elapsedTime += deltaTime;
}

void MenuState::Draw()
{
	char buffer[32];
	sprintf_s(buffer, "%3.2f", elapsedTime);

	APP->GetRenderer()->drawText(APP->m_fontList[TITLE_TXT].get(), buffer, 10, 50);
	APP->GetRenderer()->drawText(APP->m_fontList[TITLE_TXT].get(), "Menu State", 10, 10);
}
