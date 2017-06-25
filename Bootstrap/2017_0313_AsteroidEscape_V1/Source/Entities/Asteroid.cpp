#include <Asteroid.h>
#include <Renderer2D.h>
#include <_2017_0313_test2DprojApp.h>

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
	
	//Asteroid exceeds bottom, remove from linked list
	Vector2 wishPos = Vector2{ m_pos.x, (m_pos.y + velocity.y) };
	
	//if (wishPos.y < 0 - m_health) {
	//	
	//}

	m_pos += velocity;   //Add velocity to current position
	
	//Update bounding box
	m_bb = BoundingBox{ m_pos.x, m_pos.y, m_health * 2, m_health * 2 };
}

void Asteroid::render(aie::Renderer2D* a_r2d) {
	a_r2d->drawSprite(
		getImg(), getPos().x, getPos().y,
		getRadius() * 2, getRadius() * 2,		//Get width and height from diameter
		0, getDepth()							// Account for overlapping
	);
}