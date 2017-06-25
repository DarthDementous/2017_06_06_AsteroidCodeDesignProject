#include "EntityMaker.h"


///Entity Factory
std::shared_ptr<Asteroid> EntityMaker::createAsteroid(aie::Texture* a_img)
{
	return std::shared_ptr<Asteroid>(new Asteroid(AST_HEALTH, AST_SPEED, AST_DMG, a_img));
}

std::shared_ptr<Asteroid> EntityMaker::createComet(aie::Texture* a_img)
{
	return std::shared_ptr<Asteroid>(new Asteroid(CMT_HEALTH, CMT_SPEED, CMT_DMG, a_img));
}

std::shared_ptr<Asteroid> EntityMaker::createMeteor(aie::Texture* a_img)
{
	return std::shared_ptr<Asteroid>(new Asteroid(MTR_HEALTH, MTR_SPEED, MTR_DMG, a_img));
}

std::shared_ptr<Player> EntityMaker::createPlayer(aie::Texture* a_img, _2017_0313_test2DprojApp* a_app)
{
	return std::shared_ptr<Player>(new Player(PLAYER_HEALTH, PLAYER_SPEED, PLAYER_DMG, a_img, a_app));
}


std::shared_ptr<Bullet> EntityMaker::createBullet(aie::Texture* a_img)
{
	return std::shared_ptr<Bullet>(new Bullet(BULLET_HEALTH, BULLET_SPEED, a_img));
}
