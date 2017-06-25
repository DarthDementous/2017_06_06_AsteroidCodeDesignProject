#pragma once
#include "Vector2.h"
#include "Settings.h"
#include <Texture.h>
#include <Input.h>
#include <memory>
#include <LinkedList.hpp>

namespace aie {
	class Renderer2D;
}

class IComponent;

/**
*	@brief Base-class for all game objects. Utilises component design pattern.
*/
class Entity2D
{
public:
	///Virtual functions that everything will use differently: e.g. virtual int attack() = 0;
	virtual void update(float a_deltaTime) = 0;
	virtual void render(aie::Renderer2D* a_r2d) = 0;
	
	///Methods that everything will use the same way
	void AddComponent(IComponent* a_comp) {
		m_components.PushBack(a_comp);
	}

	~Entity2D();

	//Setters
	void setHealth(short a_health) { m_health = a_health; }
	void setPos(Vector2 a_pos) { m_pos += a_pos; }
	void setID(short a_ID) { m_ID = a_ID; }
	void setRadius(float a_radius) { m_health = a_radius; }
	//Getters
	float getHealth() { return m_health; }
	short getDmg() { return m_dmg; }
	Vector2 getPos() { return m_pos; }
	float getSpeed() { return m_speed; }
	float getRadius() { return m_health; }     //These are the same thing
	short getID() { return m_ID; }
	aie::Texture* getImg() { return m_img; }
	//Methods
	void takeDamage(short a_dmg);
protected:
	///Entity variables
	float m_health;			//Also acts as radius
	short m_dmg;
	Vector2 m_pos;
	float m_speed;			//Base speed
	aie::Texture* m_img;
	short m_ID;

	LinkedList<IComponent*> m_components;
};
