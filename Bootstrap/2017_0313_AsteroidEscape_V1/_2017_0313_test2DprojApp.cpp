#include "_2017_0313_test2DprojApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "ResourceManager.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <functional>

///Constructors
_2017_0313_test2DprojApp::_2017_0313_test2DprojApp() {
	m_Asteroids.clear();
	m_gameOver = false;
	m_asteroidTimeInterval = 1.f;                   // time (seconds) between creating asteroids
	m_bulletTimeInterval = 0.1f;       //Time (seconds) between creating bullets
	m_score = 0;
}
///Initialization
bool _2017_0313_test2DprojApp::startup() {
	///Resource manager to inform what hasn't loaded and return with an error - CRITICAL for lots of sprites
	m_2dRenderer = std::unique_ptr<aie::Renderer2D>(new aie::Renderer2D());
	///Textures
	//Menu
	m_textureList[TITLE] = ResourceManager::loadResource<aie::Texture>("./Asteroid Fall/Art/title.png");
	m_textureList[BTN] = ResourceManager::loadResource<aie::Texture>("./Asteroid Fall/Art/button_base.png");
	m_textureList[M_BG] = ResourceManager::loadResource<aie::Texture>("./Asteroid Fall/Art/menu.png");
	//Sprites
	m_textureList[PLAYER_SPRITE] = ResourceManager::loadResource<aie::Texture>("./Asteroid Fall/Art/ship_player.png");
	m_textureList[BULLET_SPRITE] = ResourceManager::loadResource<aie::Texture>("./Asteroid Fall/Art/pew_laser.png");

	m_textureList[AST_SPRITE] = ResourceManager::loadResource<aie::Texture>("./Asteroid Fall/Art/asteroid_generic.png");
	m_textureList[CMT_SPRITE] = ResourceManager::loadResource<aie::Texture>("./Asteroid Fall/Art/asteroid_comet.png");
	m_textureList[MTR_SPRITE] = ResourceManager::loadResource<aie::Texture>("./Asteroid Fall/Art/asteroid_meteor.png");
	//Game
	m_textureList[G_BG] = ResourceManager::loadResource<aie::Texture>("./Asteroid Fall/Art/background.png");
	///Fonts
	m_fontList[TITLE_TXT] = ResourceManager::loadResource<aie::Font>("./font/techno_hideo.ttf", 14);
	m_fontList[BTN_TXT] = ResourceManager::loadResource<aie::Font>("./font/techno_hideo.ttf", 14);
	///Audio
	m_audioList[MENU_MUS] = ResourceManager::loadResource<aie::Audio>("./Asteroid Fall/Music/Main_Menu.wav");
	m_audioList[MENU_MUS]->setGain(MENU_VOLUME);
	m_audioList[MENU_MUS]->setLooping(true);
	m_audioList[BTN_HVR] = ResourceManager::loadResource<aie::Audio>("./Asteroid Fall/Sound/menu_over.wav");
	m_audioList[BTN_CLICK] = ResourceManager::loadResource<aie::Audio>("./Asteroid Fall/Sound/menu_click.wav");;
	m_audioList[GAME_MUS_INTRO] = ResourceManager::loadResource<aie::Audio>("./Asteroid Fall/Music/Action-Intro_converted.wav");
	m_audioList[GAME_MUS_INTRO]->setGain(MENU_VOLUME);
	m_audioList[GAME_MUS_LOOP] = ResourceManager::loadResource<aie::Audio>("./Asteroid Fall/Music/Action-Loop.wav");
	m_audioList[GAME_MUS_LOOP]->setGain(MENU_VOLUME);
	m_audioList[GAME_MUS_LOOP]->setLooping(true);
	m_audioList[GAME_END_STING] = ResourceManager::loadResource<aie::Audio>("./Asteroid Fall/Music/Death_Sting.wav");
	m_audioList[GAME_END_STING]->setGain(MENU_VOLUME);
	m_audioList[BULLET_FIRE] = ResourceManager::loadResource<aie::Audio>("./Asteroid Fall/Sound/pew_laser.wav");
	m_audioList[BULLET_FIRE]->setGain(BULLET_VOLUME);
	m_audioList[HIT] = ResourceManager::loadResource<aie::Audio>("./Asteroid Fall/Sound/pew_hit.wav");
	m_audioList[HIT]->setGain(BULLET_VOLUME);
	///Menus
	initializeMenus();
	///Player
	m_Player = EntityMaker::createPlayer(m_textureList[PLAYER_SPRITE].get());
	return true;
}
void _2017_0313_test2DprojApp::initializeMenus()
{
	//Main Menu
	m_mainMenu = std::unique_ptr<Menu2D>(new Menu2D(m_audioList[MENU_MUS].get(), true, m_textureList[TITLE].get(), m_textureList[M_BG].get())); //.get() returns raw pointer

	m_mainMenu->addButton(new Button2D("Play Game", m_fontList[BTN_TXT].get(),
		std::bind(&_2017_0313_test2DprojApp::startFunc, this), W_WIDTH / 2, W_HEIGHT / 2, DEFAULT_BTN_WIDTH, DEFAULT_BTN_HEIGHT,
		m_textureList[BTN].get(), m_audioList[BTN_CLICK].get(), m_audioList[BTN_HVR].get()));
	m_mainMenu->addButton(new Button2D("Quit Game", m_fontList[BTN_TXT].get(),
		std::bind(&_2017_0313_test2DprojApp::quitFunc, this), W_WIDTH / 2, (W_HEIGHT / 2) - BTN_Y_INCREMENT, DEFAULT_BTN_WIDTH, DEFAULT_BTN_HEIGHT,
		m_textureList[BTN].get(), m_audioList[BTN_CLICK].get(), m_audioList[BTN_HVR].get()));
	m_mainMenu->Active = true;        //Activate the menu
	//End Menu
	m_endMenu = std::unique_ptr<Menu2D>(new Menu2D(nullptr));
	m_endMenu->addButton(new Button2D("Restart", m_fontList[BTN_TXT].get(),
		std::bind(&_2017_0313_test2DprojApp::startFunc, this), W_WIDTH / 2, W_HEIGHT / 2, DEFAULT_BTN_WIDTH, DEFAULT_BTN_HEIGHT,
		m_textureList[BTN].get(), m_audioList[BTN_CLICK].get(), m_audioList[BTN_HVR].get()));
	m_endMenu->addButton(new Button2D("Quit", m_fontList[BTN_TXT].get(),
		std::bind(&_2017_0313_test2DprojApp::quitFunc, this), W_WIDTH / 2, (W_HEIGHT / 2) - BTN_Y_INCREMENT, DEFAULT_BTN_WIDTH, DEFAULT_BTN_HEIGHT,
		m_textureList[BTN].get(), m_audioList[BTN_CLICK].get(), m_audioList[BTN_HVR].get()));
}
///De-initialization
void _2017_0313_test2DprojApp::shutdown() {
	//Delete non-unique pointers
}
void _2017_0313_test2DprojApp::resetGame() {
	//Clear vectors
	m_Asteroids.clear();
	m_Bullets.clear();
	//Reset player
	m_Player = EntityMaker::createPlayer(m_textureList[PLAYER_SPRITE].get());
}
///Button functions
//Start the game
void _2017_0313_test2DprojApp::startFunc() {
	m_mainMenu->Active = false;
	m_mainMenu->endMusic();
	m_endMenu->Active = false;
	m_endMenu->endMusic();
	resetGame();
	//Play the game intro
	m_audioList[GAME_MUS_INTRO]->play();
}
void _2017_0313_test2DprojApp::quitFunc() {
	exit(EXIT_SUCCESS);
}
//Return to main menu
///Mechanics
void _2017_0313_test2DprojApp::wishBullet(float a_deltaTime) {
	// Can we shoot a bullet?
	if (m_Player->canShoot()) {
		m_Player->setShoot(false);   //Stop from being able to fire straight after
		m_Player->setTimer(0.f);     //Reset timer instantly to avoid multi-fire bug
		// Stop other bullet sound before playing again
		if (m_audioList[BULLET_FIRE]->getIsPlaying())
			m_audioList[BULLET_FIRE]->stop();
		m_audioList[BULLET_FIRE]->play();
		//Create bullet
		std::unique_ptr<Bullet> blt = EntityMaker::createBullet(m_textureList[BULLET_SPRITE].get());
		//Place bullet just above player
		BoundingBox position = BoundingBox{ m_Player->getPos().x, m_Player->getPos().y + m_Player->getRadius(), BULLET_WIDTH, BULLET_HEIGHT };
		blt->setBB(position);
		//Add it to vector
		m_Bullets.push_back(std::move(blt));        //We're moving the memory of the unique pointer into the vector so we can access it later
	}
}
//Create asteroid after exceeding timer and pause it if ball has been reached
void _2017_0313_test2DprojApp::wishAsteroid(float a_deltaTime) {
	static float currentTime, stopCreateTime, addTime;             //Current timer, when to stop and reset timer, how much to add to timer
	currentTime += a_deltaTime;
	const float decreaseInterval = 2.f;                            //How quickly we count down

	addTime += a_deltaTime;
	if (addTime > decreaseInterval) {
		addTime = 0;
		// Lower the time of the next comet
		m_asteroidTimeInterval = std::max(0.2f, m_asteroidTimeInterval - 0.2f);                //Decrease time but never go past 0.2
	}
	// Choose min of 0 or decrease time until next asteroid batch
	stopCreateTime = std::max(0.f, stopCreateTime - a_deltaTime);
	if (stopCreateTime) return;

	// Should we create another asteroid?
	if (currentTime < m_asteroidTimeInterval || m_Asteroids.size() > (size_t)maxAsteroids) return;   //Haven't reached interval or we've reached our maximum asteroids
	currentTime = 0.f;       //Reset timer
	int asteroidType = rand() % 3;  //Generate random number between 0-3 to determine what type of asteroid to make
	std::unique_ptr<Asteroid> ast;
	// What type of asteroid do we have?
	if (asteroidType == ASTEROID) {
		 ast = EntityMaker::createAsteroid(m_textureList[AST_SPRITE].get());
	}
	else if (asteroidType == COMET) {
		ast = EntityMaker::createComet(m_textureList[CMT_SPRITE].get());
	} else {
		ast = EntityMaker::createMeteor(m_textureList[MTR_SPRITE].get());
	}
	// Put it in a random x position
	ast->setPos(Vector2{ (float)(rand() % W_WIDTH), W_HEIGHT + ast->getRadius() });
	//Add it to the vector
	m_Asteroids.push_back(std::move(ast));
}
///Update
void _2017_0313_test2DprojApp::update(float deltaTime) {
	// input example
	aie::Input* input = aie::Input::getInstance();
	///Menus
	if (m_mainMenu->Active) {
		m_mainMenu->update(deltaTime, input);
	}
	if (m_endMenu->Active) {
		m_endMenu->update(deltaTime, input);
	}
	//Only update the game if the menus are not active
	if (!m_mainMenu->Active && !m_endMenu->Active) {
		///Music
		//Change to loop when intro is finished
		if (!m_audioList[GAME_MUS_INTRO]->getIsPlaying()) {
			m_audioList[GAME_MUS_LOOP]->play();
		}
		///Collisions
		checkCollisions(deltaTime);
		///Asteroids
		// Do we create an asteroid?
		wishAsteroid(deltaTime);
		// Only if there are asteroids
		if (!m_Asteroids.empty()) {
			// Update
			for (uInt i = 0; i < m_Asteroids.size(); i++) {
				m_Asteroids[i]->update(deltaTime);
			}
		}
		///Player (check after collisions)
		//Check if player is dead
		m_Player->update(deltaTime);
		//Check input
		m_Player->updateInput(deltaTime, input);
		///Bullets
		// Do we create another bullet? (Check if the player wants to shoot)
		if (m_Player->isShooting()) {
			wishBullet(deltaTime);
		}
		//Only if there are bullets
		if (!m_Bullets.empty()) {
			//Update
			for (size_t i = 0; i < m_Bullets.size(); i++) {
				m_Bullets[i]->update(deltaTime);
			}
		}
		///Clean up (if there are entities to clean up!)
		if (!m_Asteroids.empty()) {
			cleanUp(m_Asteroids);
		}
		if (!m_Bullets.empty()) {
			cleanUp(m_Bullets);
		}
		///Check if we should increase asteroids produced
		if (m_Player->getHealth() < 25.f) {
			maxAsteroids = MAX_ASTEROIDS;
		}
		///Check game over
		if (!m_Player->isAlive()) {
			//Stop game music
			m_audioList[GAME_MUS_INTRO]->stop();
			m_audioList[GAME_MUS_LOOP]->stop();
			//Play death sound
			m_audioList[GAME_END_STING]->play();
			//Activate end menu
			m_endMenu->Active = true;
		}
	}
}
void _2017_0313_test2DprojApp::checkCollisions(float a_deltaTime) {
	bool collision = false;
	//Anything colliding with the asteroids (can't use for each since its a unique pointer, unique pointers must remain in the array)
	for (size_t i = 0; i < m_Asteroids.size(); i++) {
		//Player (check if we've intersected)
		if (m_Asteroids[i]->getPos().findDistance(m_Player->getPos()) < (m_Asteroids[i]->getRadius() + m_Player->getRadius())) {
			//Mark asteroid for deletion
			m_Asteroids[i]->takeDamage((short)(m_Asteroids[i]->getHealth()));
			//Damage player
			m_Player->takeDamage(m_Asteroids[i]->getDmg());
			collision = true;
		}
		//Bullets (check for intersection). DO NOT HAVE THE ITERATOR AS THE SAME VARIABLE AS ASTEROIDS BECAUSE ITS NESTED.
		for (size_t x = 0; x < m_Bullets.size(); x++) {
			if (m_Bullets[x]->getBB().IntersectsWith(m_Asteroids[i]->getBB())) {
				//Mark bullet for deletion
				m_Bullets[x]->takeDamage(short(m_Bullets[x]->getHealth()));
				//Damage asteroid with player's attack
				m_Asteroids[i]->takeDamage(m_Player->getDmg());
				collision = true;
			}
		}
	}
	//Play collision sound
	if (collision) {
		// Stop other bullet sound before playing again
		if (m_audioList[HIT]->getIsPlaying()) {
			m_audioList[HIT]->stop();
		}
		m_audioList[HIT]->play();
	}
}
///Draw
void _2017_0313_test2DprojApp::draw() {
	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	///Menus
	if (m_mainMenu->Active) {
		m_mainMenu->displayAll(m_2dRenderer.get());
	}
	if (m_endMenu->Active) {
		m_endMenu->displayAll(m_2dRenderer.get());
	}
	//Main menu is not active, draw game stuff
	if (!m_mainMenu->Active) {
		//Asteroids (account for overlapping)
		for (uInt i = 0; i < m_Asteroids.size(); ++i) {
			m_2dRenderer->drawSprite(
				m_Asteroids[i]->getImg(), m_Asteroids[i]->getPos().x, m_Asteroids[i]->getPos().y, m_Asteroids[i]->getRadius() * 2, m_Asteroids[i]->getRadius() * 2, 0, m_Asteroids[i]->getDepth()
			);  //Get width and height from radius
		}
		//Bullets
		for (uInt i = 0; i < m_Bullets.size(); ++i) {
			m_2dRenderer->drawSprite(
				m_Bullets[i]->getImg(), m_Bullets[i]->getBB().x, m_Bullets[i]->getBB().y, m_Bullets[i]->getBB().width, m_Bullets[i]->getBB().height
			);  //Get width and height from radius
		}
		//The player (don't draw if he's supposed to be dead!)
		if (m_Player->getHealth() != 0) {
			m_2dRenderer->drawSprite(
				m_Player->getImg(), m_Player->getPos().x, m_Player->getPos().y, m_Player->getRadius() * 2, m_Player->getRadius() * 2
			);  //Get width and height from diameter (radius * 2)
		}
		//Background
		m_2dRenderer->drawSprite(
			m_textureList[G_BG].get(), (W_WIDTH / 2), (W_HEIGHT / 2), W_WIDTH, W_HEIGHT, 0, 100 //Draw behind everything
		);
	}
	// done drawing sprites, push to the screen
	m_2dRenderer->end();
}
