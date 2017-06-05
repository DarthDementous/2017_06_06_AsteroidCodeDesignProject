#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Vector2.h"
#include "Settings.h"
#include "Menu2D.h"
#include "EntityMaker.h"
#include <vector>
#include <map>
#include <memory>

using std::vector;

class _2017_0313_test2DprojApp : public aie::Application {
public:
	///Constructors
	_2017_0313_test2DprojApp();
	virtual ~_2017_0313_test2DprojApp() = default;
	///Initialization/De-initialization
	virtual bool startup();
	void initializeMenus();
	virtual void shutdown();
	void resetGame();
	///Update
	virtual void update(float deltaTime);
	void checkCollisions(float a_deltaTime);
	template<typename T>
	void cleanUp(vector<T> &a_vec);
	///Draw
	virtual void draw();
	///Mechanics
	void wishAsteroid(float deltaTime);
	void wishBullet(float deltaTime);
private:
	///Variables
	//Maps
	//AIE
	std::unique_ptr<aie::Renderer2D> m_2dRenderer;      //Unique pointer, only one 2dRenderer for the game
	//Timers
	float m_asteroidTimeInterval;
	float m_bulletTimeInterval;
	float m_timer;
	int m_score;
	//Menu stuff
	std::unique_ptr<Menu2D> m_mainMenu;
	std::unique_ptr<Menu2D> m_endMenu;
	//Game objects
	vector <std::unique_ptr<Asteroid>> m_Asteroids;
	vector <std::unique_ptr<Bullet>> m_Bullets;
	std::unique_ptr<Player> m_Player;
	std::map<textureID, std::shared_ptr<aie::Texture>>  m_textureList;   //We want to assign the same texture to multiple things, therefore shared pointer
	std::map<fontID, std::shared_ptr<aie::Font>>		m_fontList;
	std::map<audioID, std::shared_ptr<aie::Audio>>      m_audioList;
	int maxAsteroids = MIN_ASTEROIDS;
	///Methods
	//Button functions
	void startFunc();
	void quitFunc();
};
template<typename T>
void _2017_0313_test2DprojApp::cleanUp(vector<T> &a_vec) {
	///Get rid of dead entities
	SelectionSort(a_vec);          
	//Keep erasing until there's no dead entities left at the beginning of the list (check from top)
	for (size_t i = 0; i < a_vec.size(); ++i) {
		if (a_vec[i]->getHealth() == 0) {
			a_vec.erase(a_vec.begin() + i);
		}
	}
}