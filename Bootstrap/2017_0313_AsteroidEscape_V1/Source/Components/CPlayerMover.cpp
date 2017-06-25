#include "CPlayerMover.h"
#include <Input.h>
#include <Settings.h>
#include <Entity2D.h>
#include <Player.h>

void CPlayerMover::Update(float dt)
{
	aie::Input* input = aie::Input::getInstance();

	Vector2 velocity = Vector2{ 0, 0 };
	
	//The smaller we are the faster we move
	float newSpeed = PLAYER->getSpeed() + ((PLAYER_HEALTH - PLAYER->getHealth()) * 5);      //When health is max, m_speed is = default speed

	if (input->isKeyDown(aie::INPUT_KEY_A) || input->isKeyDown(aie::INPUT_KEY_LEFT))
		velocity += { -(newSpeed*dt), 0 };
	if (input->isKeyDown(aie::INPUT_KEY_D) || input->isKeyDown(aie::INPUT_KEY_RIGHT))
		velocity += { (newSpeed*dt), 0 };
	if (input->isKeyDown(aie::INPUT_KEY_W) || input->isKeyDown(aie::INPUT_KEY_UP))
		velocity += { 0, (newSpeed*dt) };
	if (input->isKeyDown(aie::INPUT_KEY_S) || input->isKeyDown(aie::INPUT_KEY_DOWN))
		velocity += { 0, -(newSpeed*dt) };

	//If we're outside the game bounds, cancel velocity
	Vector2 wishPos = PLAYER->getPos() + velocity;

	if (wishPos.x + PLAYER->getHealth() > W_WIDTH || 
		wishPos.x - PLAYER->getHealth() < 0 || 
		wishPos.y + PLAYER->getHealth() > W_HEIGHT || 
		wishPos.y - PLAYER->getHealth() < 0) {
		velocity = Vector2{ 0, 0 };
	}

	//Add new velocity to player position
	PLAYER->setPos(velocity);
}
