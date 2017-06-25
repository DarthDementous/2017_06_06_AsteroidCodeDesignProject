#pragma once

#include "Entity2D.h"

class Asteroid :
	public Entity2D
{
public:
	Asteroid(short a_health, float a_speed, short a_dmg, aie::Texture* a_img);
	
	///Methods
	void update(float a_deltaTime) override;
	void render(aie::Renderer2D* a_r2d) override;
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