#pragma once
#include <IComponent.hpp>
#include <LinkedList.hpp>
#include <Bullet.h>
#include <memory>

class Player;
class Bullet;
class _2017_0313_test2DprojApp;

/**
*	@brief Component that handles everything to do with the player's laser gun.
*/
class CWeapon :
	public IComponent
{
public:
	CWeapon(Player* a_entity, _2017_0313_test2DprojApp* a_app) : PLAYER(a_entity), APP(a_app) {}
	
	virtual void Update(float dt);
	virtual void Render(aie::Renderer2D* a_r2d);
private:
	void wishBullet(float dt);

	Player* PLAYER				  = nullptr;
	_2017_0313_test2DprojApp* APP = nullptr;
};

