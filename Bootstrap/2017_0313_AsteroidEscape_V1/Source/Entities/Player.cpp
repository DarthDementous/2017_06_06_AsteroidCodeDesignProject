#include "Player.h"
#include <CPlayerMover.h>
#include <CWeapon.h>
#include <_2017_0313_test2DprojApp.h>
#include <assert.h>

Player::Player(short a_health, float a_speed, short a_dmg, aie::Texture* a_img, _2017_0313_test2DprojApp* a_app)
{
	m_health = a_health;
	m_speed = a_speed;
	m_dmg = a_dmg;
	m_img = a_img;
	m_alive = true;				//The player is alive...for now.
	m_shooting = false;			//The player can't be shooting...yet.
	m_canShoot = true;			//They can fire straight away! 
	m_shotDelay = BULLET_RATE;
	m_shotTimer = m_shotDelay;
	m_pos = PLAYER_STARTPOS;

	// Components
	AddComponent(new CWeapon(this, a_app));
	AddComponent(new CPlayerMover(this));
}

void Player::update(float a_deltaTime) {
	//Check if dead
	if (m_health == 0) {
		m_alive = false;
	}
	
	//Check if we can shoot
	updateShoot(a_deltaTime);

	//Update components
	for (auto comp : m_components) {
		comp->Update(a_deltaTime);
	}
}
void Player::updateShoot(float a_deltaTime) {
	m_shotTimer += a_deltaTime;

	if (m_shotTimer < m_shotDelay) return;	// Hasn't reached timer, can not shoot
	m_shotTimer = 0.f;						//Reset timer
	m_canShoot = true;
}

void Player::updateInput(float a_deltaTime, aie::Input* a_input) {
	///Shooting
	if (a_input->isKeyDown(aie::INPUT_KEY_SPACE)) {
		m_shooting = true;      //The player wants to shoot
	}
	if (a_input->isKeyUp(aie::INPUT_KEY_SPACE)) {
		m_shooting = false;     //The player is no longer shooting
	}
}

void Player::render(aie::Renderer2D* a_r2d) {
	//Don't draw if he's supposed to be dead!
	if (m_health != 0) {
		a_r2d->drawSprite(
			getImg(), getPos().x, getPos().y,
			getRadius() * 2, getRadius() * 2		//Get width and height from diameter (radius * 2)
		);
	}

	//Draw components
	for (auto comp : m_components) {
		comp->Render(a_r2d);
	}
}
