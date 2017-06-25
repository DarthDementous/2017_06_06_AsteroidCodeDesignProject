#pragma once
#include <memory>
#include <IGameState.h>
#include <LinkedList.hpp>

class IComponent;

class _2017_0313_test2DprojApp;
namespace aie {
	class Font;
	class Renderer2D;
}

class PlayState :
	public IGameState
{
public:
	PlayState(_2017_0313_test2DprojApp* a_app);

	~PlayState();

	void AddComponent(IComponent* a_comp) { m_components.PushBack(a_comp); }

	virtual void Initialise();

	virtual void Startup();

	virtual void Update(float deltaTime);

	virtual void Draw();

	virtual void Shutdown();
private:
	_2017_0313_test2DprojApp* APP = nullptr; // Actual version of application using state manager that equals a static cast of Application
	float elapsedTime;
	float framesPerSecond;

	LinkedList<IComponent*> m_components;
};

