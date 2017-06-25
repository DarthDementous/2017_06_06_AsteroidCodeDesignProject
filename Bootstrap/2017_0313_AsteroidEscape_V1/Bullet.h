#pragma once
#include "Entity2D.h"

class Bullet :
	public Entity2D
{
public:
	Bullet(short a_health, float a_speed, aie::Texture* a_img);
	
	void update(float a_deltaTime);
	void render(aie::Renderer2D* a_r2d);


	void setBB(BoundingBox a_bb) { m_bb = a_bb; }
	BoundingBox getBB() { return m_bb; }
private:
	///Variables
	BoundingBox m_bb;
};

