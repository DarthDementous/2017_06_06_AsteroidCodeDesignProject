#include <CAsteroidDeployer.h>
#include <_2017_0313_test2DprojApp.h>

void CAsteroidDeployer::Update(float dt)
{
	// Do we create an asteroid?
	APP->wishAsteroid(dt);

	// Update
	for (auto iter = APP->m_Asteroids.begin(); iter != APP->m_Asteroids.end(); ++iter) {
		std::shared_ptr<Asteroid> ast = iter.GetLink()->GetValue();

		ast->update(dt);

		//If asteroid reaches bottom or is dead, remove from the linked list
		if (ast->getPos().y < 0 || ast->getHealth() == 0) {
			iter = APP->m_Asteroids.Erase(APP->m_Asteroids.FindIter(ast));
		}
	}

	// Check if we should increase asteroids produced
	if (APP->m_Player->getHealth() < 25.f) {
		APP->maxAsteroids = MAX_ASTEROIDS;
	}
}

void CAsteroidDeployer::Render(aie::Renderer2D * a_r2d)
{
	for (auto ast : APP->m_Asteroids) {
		ast->render(a_r2d);
	}
}
