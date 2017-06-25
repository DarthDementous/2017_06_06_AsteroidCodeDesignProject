#pragma once
#include <IComponent.hpp>

class _2017_0313_test2DprojApp;

/**
*	@brief Component that handles deployment of asteroids.
*/
class CAsteroidDeployer :
	public IComponent
{
public:
	CAsteroidDeployer(_2017_0313_test2DprojApp* a_app) : APP(a_app) {}

	virtual void Update(float dt);
	virtual void Render(aie::Renderer2D* a_r2d);
private:
	_2017_0313_test2DprojApp* APP = nullptr;					// Hold on to pointer to application
};

