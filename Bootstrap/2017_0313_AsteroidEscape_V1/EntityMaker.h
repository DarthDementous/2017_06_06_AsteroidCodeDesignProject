#pragma once
#include <memory>
#include <Asteroid.h>
#include <Player.h>
#include <Bullet.h>

class _2017_0313_test2DprojApp;

///Use this as factory to call constructors
class EntityMaker
{
public:
	//Creators
	static std::shared_ptr<Asteroid> createAsteroid(aie::Texture* a_img);
	static std::shared_ptr<Asteroid> createComet(aie::Texture* a_img);
	static std::shared_ptr<Asteroid> createMeteor(aie::Texture* a_img);
	static std::shared_ptr<Player>   createPlayer(aie::Texture* a_img, _2017_0313_test2DprojApp* a_app);
	static std::shared_ptr<Bullet>   createBullet(aie::Texture* a_img);
};