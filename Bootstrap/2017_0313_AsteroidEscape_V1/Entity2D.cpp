#include "Entity2D.h"

void Entity2D::takeDamage(short a_dmg)
{
	//Take damage and shrink only if this will not kill us
	if (m_health - a_dmg > 0) {
		m_health -= a_dmg;
		return;
	}
	//Dead
	m_health = 0;
}
