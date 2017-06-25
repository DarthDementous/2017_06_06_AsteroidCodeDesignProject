#include <CWeapon.h>
#include <Player.h>
#include <_2017_0313_test2DprojApp.h>
#include <memory>
#include <EntityMaker.h>

void CWeapon::Update(float dt)
{
	// Do we create another bullet? (Check if the player wants to shoot)
	if (PLAYER->isShooting()) {
		wishBullet(dt);
	}

	for (auto iter = APP->m_Bullets.begin(); iter != APP->m_Bullets.end(); ++iter) {
		std::shared_ptr<Bullet> blt = iter.GetLink()->GetValue();
		
		blt->update(dt);

		//If bullet reaches top or is dead, remove from the linked list
		if (blt->getBB().y > W_HEIGHT || blt->getHealth() == 0) {
			iter = APP->m_Bullets.Erase(APP->m_Bullets.FindIter(blt));
		}
	}
}

void CWeapon::wishBullet(float a_deltaTime) {
	// Can we shoot a bullet? If not, return
	if (!PLAYER->canShoot()) {
		return;
	}

	// Bullet sound (stop it if its already playing before playing new one)
	if (APP->m_audioList[BULLET_FIRE]->getIsPlaying()) {
		APP->m_audioList[BULLET_FIRE]->stop();
	}
	APP->m_audioList[BULLET_FIRE]->play();

	//Create bullet
	std::shared_ptr<Bullet> blt = EntityMaker::createBullet(APP->m_textureList[BULLET_SPRITE].get());

	//Place bullet just above player
	BoundingBox position = BoundingBox{PLAYER->getPos().x, PLAYER->getPos().y + PLAYER->getRadius(), BULLET_WIDTH, BULLET_HEIGHT };
	blt->setBB(position);

	//Add it to vector
	APP->m_Bullets.PushBack(blt);

	// Reset shoot status
	PLAYER->setShoot(false);   //Stop from being able to fire straight after
	PLAYER->setTimer(0.f);     //Reset timer instantly to avoid multi-fire bug
}

void CWeapon::Render(aie::Renderer2D * a_r2d)
{
	for (auto blt : APP->m_Bullets) {
		blt->render(a_r2d);
	}
}


