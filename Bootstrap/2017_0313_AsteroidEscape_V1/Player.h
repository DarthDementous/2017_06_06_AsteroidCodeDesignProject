#pragma once
#include "Entity2D.h"
#include <LinkedList.hpp>
#include <Bullet.h>

class _2017_0313_test2DprojApp;

class Player :
	public Entity2D
{
public:
	// Take in application pointer to pass in to component
	Player(short a_health, float a_speed, short a_dmg, aie::Texture* a_img, _2017_0313_test2DprojApp* a_app);
	///Methods
	void update(float a_deltaTime) override;
	void updateShoot(float a_deltaTime);       //Check if we can shoot
	void updateInput(float a_deltaTime, aie::Input* a_input);    //Need to update according to player input as well
	
	void render(aie::Renderer2D* a_r2d) override;

	//Getters
	bool isAlive() { return m_alive; }
	bool isShooting() { return m_shooting; }
	bool canShoot() { return m_canShoot; }

	//Setters
	void setShoot(bool a_shootStatus) { m_canShoot = a_shootStatus; }
	void setTimer(float a_timer) { m_shotTimer = a_timer; }
private:
	///Variables
	bool m_alive;
	bool m_shooting, m_canShoot;
	float m_shotDelay;        //How long between shots
	float m_shotTimer;        //Timer for firing gun
};

