#pragma once
#include <memory>
#include <IGameState.h>
#include <Settings.h>

class _2017_0313_test2DprojApp;
namespace aie {
	class Font;
	class Renderer2D;
}

class SplashState :
	public IGameState
{
public:
	SplashState(_2017_0313_test2DprojApp* a_app);

	virtual void Initialise();

	virtual void Startup();

	virtual void Update(float deltaTime);

	virtual void Draw();

	virtual void Shutdown();
private:
	_2017_0313_test2DprojApp* APP = nullptr; // Actual version of application using state manager that equals a static cast of Application

	Vector2 loadingBarExtents = { 0, 60 };				 // Keep track of loading bar size
};

