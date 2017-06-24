#include "EntityMaker.h"
///Asteroid
Asteroid::Asteroid(short a_health, float a_speed, short a_dmg, aie::Texture* a_img)
{
	m_health = a_health;
	m_speed = a_speed;
	m_dmg = a_dmg;
	m_img = a_img;
	m_depth = (float)(rand() % (9 + 1));    //Generate random depth between 1 and 10
}

void Asteroid::update(float a_deltaTime) {
	// Coming down
	float newSpeed = m_speed * ((W_HEIGHT - m_pos.y) + (m_health + 1)) / 100.f;   //The lower we are, the faster we fall
	Vector2 velocity = { 0, -(newSpeed * a_deltaTime) };   
	//Asteroid exceeds bottom, mark for deletion and negate velocity
	Vector2 wishPos = Vector2{ m_pos.x, (m_pos.y + velocity.y) };
	if (wishPos.y < 0 - m_health) {
		velocity = Vector2{ 0, 0 };
		m_health = 0;
	}
	m_pos += velocity;   //Add velocity to current position
	//Update bounding box
	m_bb = BoundingBox{ m_pos.x, m_pos.y, m_health * 2, m_health * 2 };
}
Asteroid::~Asteroid() {

}
///Player
Player::Player(short a_health, float a_speed, short a_dmg, aie::Texture* a_img)
{
	m_health = a_health;
	m_speed = a_speed;
	m_dmg = a_dmg;
	m_img = a_img;
	m_alive = true;  //The player is alive...for now.
	m_shooting = false;  //The player can't be shooting...yet.
	m_canShoot = true;   //They can fire straight away! 
	m_shotDelay = BULLET_RATE;
	m_shotTimer = m_shotDelay;
	m_pos = PLAYER_STARTPOS;
}

void Player::update(float a_deltaTime) {
	//Check if dead
	if (m_health == 0) {
		m_alive = false;
	}
	//Check if we can shoot
	updateShoot(a_deltaTime);
}
void Player::updateShoot(float a_deltaTime) {
	m_shotTimer += a_deltaTime;

	if (m_shotTimer < m_shotDelay) return; // Hasn't reached timer, can not shoot
	m_shotTimer = 0.f;        //Reset timer
	m_canShoot = true;
}
void Player::updateInput(float a_deltaTime, aie::Input* a_input) {
	///Movement
	Vector2 velocity = Vector2{ 0, 0 };
	//The smaller we are the faster we move
	float newSpeed = m_speed + ((PLAYER_HEALTH - m_health) * 5);      //When health is max, m_speed is = default speed
	if (a_input->isKeyDown(aie::INPUT_KEY_A) || a_input->isKeyDown(aie::INPUT_KEY_LEFT))
		velocity += { -(newSpeed*a_deltaTime), 0 };
	if (a_input->isKeyDown(aie::INPUT_KEY_D) || a_input->isKeyDown(aie::INPUT_KEY_RIGHT))
		velocity += { (newSpeed*a_deltaTime), 0 };
	if (a_input->isKeyDown(aie::INPUT_KEY_W) || a_input->isKeyDown(aie::INPUT_KEY_UP))
		velocity += { 0, (newSpeed*a_deltaTime) };
	if (a_input->isKeyDown(aie::INPUT_KEY_S) || a_input->isKeyDown(aie::INPUT_KEY_DOWN))
		velocity += { 0, -(newSpeed*a_deltaTime) };
	//If we're outside the game bounds, cancel velocity
	Vector2 wishPos = m_pos + velocity;
	if (wishPos.x + m_health > W_WIDTH || wishPos.x - m_health < 0 || wishPos.y + m_health > W_HEIGHT || wishPos.y - m_health < 0) {
		velocity = Vector2{ 0, 0 };
	}
	//Add new velocity to player position
	m_pos += velocity;
	///Shooting
	if (a_input->isKeyDown(aie::INPUT_KEY_SPACE)) {
		m_shooting = true;      //The player wants to shoot
	}
	if (a_input->isKeyUp(aie::INPUT_KEY_SPACE)) {
		m_shooting = false;     //The player is no longer shooting
	}
}

Player::~Player() {

}
///Bullet
Bullet::Bullet(short a_health, float a_speed, aie::Texture* a_img) {
	m_health = a_health;
	m_speed = a_speed;
	m_img = a_img;
}

void Bullet::update(float a_deltaTime) {
	// Coming up
	Vector2 velocity = { 0, (m_speed * a_deltaTime)};   //Travel at a constant speed
	Vector2 wishPos = Vector2{ m_bb.x, m_bb.y + velocity.y };
	//If bullet reaches top, negate velocity and mark for deletion
	if (wishPos.y - m_bb.height > W_HEIGHT) {
		velocity = Vector2{ 0, 0 };
		m_health = 0;
	}
	m_bb.y += velocity.y;   //Add Y velocity to current position
}

Bullet::~Bullet() {

}
///Entity Factory
std::unique_ptr<Asteroid> EntityMaker::createAsteroid(aie::Texture* a_img)
{
	return std::unique_ptr<Asteroid>(new Asteroid(AST_HEALTH, AST_SPEED, AST_DMG, a_img));
}

std::unique_ptr<Asteroid> EntityMaker::createComet(aie::Texture* a_img)
{
	return std::unique_ptr<Asteroid>(new Asteroid(CMT_HEALTH, CMT_SPEED, CMT_DMG, a_img));
}

std::unique_ptr<Asteroid> EntityMaker::createMeteor(aie::Texture* a_img)
{
	return std::unique_ptr<Asteroid>(new Asteroid(MTR_HEALTH, MTR_SPEED, MTR_DMG, a_img));
}

std::unique_ptr<Player> EntityMaker::createPlayer(aie::Texture* a_img)
{
	return std::unique_ptr<Player>(new Player(PLAYER_HEALTH, PLAYER_SPEED, PLAYER_DMG, a_img));
}


std::unique_ptr<Bullet> EntityMaker::createBullet(aie::Texture* a_img)
{
	return std::unique_ptr<Bullet>(new Bullet(BULLET_HEALTH, BULLET_SPEED, a_img));
}
