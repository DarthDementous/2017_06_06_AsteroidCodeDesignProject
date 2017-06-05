#pragma once
#include "Entity2D.h"
class Asteroid :
	public Entity2D
{
public:
	Asteroid(short a_health, float a_speed, short a_dmg, aie::Texture* a_img);
	~Asteroid();
	///Methods
	void update(float a_deltaTime) override;
	//Getters
	BoundingBox getBB() { return m_bb; }
	float getDepth() { return m_depth; }
	//Setters
	void setDepth(float a_depth) { m_depth = a_depth; }
private:
	///Unique variables
	BoundingBox m_bb;
	float m_depth;     //Random depth to avoid overlapping
};

class Player :
	public Entity2D
{
public:
	Player(short a_health, float a_speed, short a_dmg, aie::Texture* a_img);
	~Player();
	///Methods
	void update(float a_deltaTime) override;
	void updateShoot(float a_deltaTime);       //Check if we can shoot
	void updateInput(float a_deltaTime, aie::Input* a_input);    //Need to update according to player input as well
	//Getters
	bool isAlive() { return m_alive; }
	bool isShooting() { return m_shooting; }
	bool canShoot() { return m_canShoot;  }
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

class Bullet :
	public Entity2D
{
public:
	Bullet(short a_health, float a_speed, aie::Texture* a_img);
	~Bullet();
	void update(float a_deltaTime); //Bullets are created AFTER player input and are then out of control

	void setBB(BoundingBox a_bb) { m_bb = a_bb; }
	BoundingBox getBB() { return m_bb; }
private:
	///Variables
	BoundingBox m_bb;
};
///Use this as factory to call constructors
class EntityMaker
{
public:
	//Creators
	static std::unique_ptr<Asteroid> createAsteroid(aie::Texture* a_img);
	static std::unique_ptr<Asteroid> createComet(aie::Texture* a_img);
	static std::unique_ptr<Asteroid> createMeteor(aie::Texture* a_img);
	static std::unique_ptr<Player>   createPlayer(aie::Texture* a_img);
	static std::unique_ptr<Bullet>   createBullet(aie::Texture* a_img);
};