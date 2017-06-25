#include "Bullet.h"
#include <Renderer2D.h>

Bullet::Bullet(short a_health, float a_speed, aie::Texture* a_img) {
	m_health = a_health;
	m_speed = a_speed;
	m_img = a_img;
}

void Bullet::update(float a_deltaTime) {
	// Coming up
	Vector2 velocity = { 0, (m_speed * a_deltaTime) };   //Travel at a constant speed
	Vector2 wishPos = Vector2{ m_bb.x, m_bb.y + velocity.y };


	m_bb.y += velocity.y;   //Add Y velocity to current position
}

void Bullet::render(aie::Renderer2D* a_r2d) {
	a_r2d->drawSprite(
		getImg(), getBB().x, getBB().y, getBB().width, getBB().height
	);
}
