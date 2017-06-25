#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Vector2.h"
#include "Settings.h"
#include "Menu2D.h"
#include <Asteroid.h>
#include <vector>
#include <Map.hpp>
#include <LinkedList.hpp>
#include <memory>
#include <Player.h>

class GameStateManager;

using std::vector;

class _2017_0313_test2DprojApp : public aie::Application {
public:
	///Constructors
	_2017_0313_test2DprojApp();
	virtual ~_2017_0313_test2DprojApp() = default;
	
	///Getters
	// Return raw-pointers because memory is application's responsibility
	aie::Renderer2D* GetRenderer() { return m_2dRenderer.get(); }	
	GameStateManager* GetStateManager() { return m_stateManager.get(); }

	///Initialization/De-initialization
	virtual bool startup();
	virtual void shutdown();
	
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
public:
	///Variables
	//Maps
	
	//AIE
	std::unique_ptr<aie::Renderer2D>				m_2dRenderer;      //Unique pointer, only one 2dRenderer for the game
	
	//Timers
	float m_asteroidTimeInterval;
	float m_bulletTimeInterval;
	float m_timer;
	int m_score;
	
	//Menu stuff
	std::shared_ptr<Menu2D> m_mainMenu;
	std::shared_ptr<Menu2D> m_endMenu;
	
	//Game objects
	LinkedList <std::shared_ptr<Asteroid>>	m_Asteroids;
	LinkedList <std::shared_ptr<Bullet>>	m_Bullets;

	std::shared_ptr<Player> m_Player;

	Map<textureID, std::shared_ptr<aie::Texture>>	m_textureList;   //We want to assign the same texture to multiple things, therefore shared pointer
	Map<fontID, std::shared_ptr<aie::Font>>			m_fontList;
	Map<audioID, std::shared_ptr<aie::Audio>>		m_audioList;
	int maxAsteroids = MIN_ASTEROIDS;

	// State Manager
	std::shared_ptr<GameStateManager> m_stateManager;

	///Methods
	//Button functions
	void startFunc();
	void restartFunc();
	void quitFunc();
};
