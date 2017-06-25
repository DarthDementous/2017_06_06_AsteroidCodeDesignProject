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
#include <GameStateManager.h>
#include <MainMenuState.h>
#include <EndMenuState.h>
#include <PlayState.h>
#include <PauseState.h>
#include <SplashState.h>
#include <EntityMaker.h>

///Constructors
_2017_0313_test2DprojApp::_2017_0313_test2DprojApp() {
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
	m_textureList[SPLASH] = ResourceManager::loadResource<aie::Texture>("./GameData/Art/splash.png");
	m_textureList[TITLE] = ResourceManager::loadResource<aie::Texture>("./GameData/Art/title.png");
	m_textureList[BTN] = ResourceManager::loadResource<aie::Texture>("./GameData/Art/button_base.png");
	m_textureList[M_BG] = ResourceManager::loadResource<aie::Texture>("./GameData/Art/menu.png");
	//Sprites
	m_textureList[PLAYER_SPRITE] = ResourceManager::loadResource<aie::Texture>("./GameData/Art/ship_player.png");
	m_textureList[BULLET_SPRITE] = ResourceManager::loadResource<aie::Texture>("./GameData/Art/pew_laser.png");

	m_textureList[AST_SPRITE] = ResourceManager::loadResource<aie::Texture>("./GameData/Art/asteroid_generic.png");
	m_textureList[CMT_SPRITE] = ResourceManager::loadResource<aie::Texture>("./GameData/Art/asteroid_comet.png");
	m_textureList[MTR_SPRITE] = ResourceManager::loadResource<aie::Texture>("./GameData/Art/asteroid_meteor.png");
	//Game
	m_textureList[G_BG] = ResourceManager::loadResource<aie::Texture>("./GameData/Art/background.png");
	///Fonts
	m_fontList[TITLE_TXT] = ResourceManager::loadResource<aie::Font>("./font/techno_hideo.ttf", 14);
	m_fontList[BTN_TXT] = ResourceManager::loadResource<aie::Font>("./font/techno_hideo.ttf", 14);
	m_fontList[DEBUG_TXT] = ResourceManager::loadResource<aie::Font>("./font/consolas_bold.ttf", 56);
	///Audio
	m_audioList[MENU_MUS] = ResourceManager::loadResource<aie::Audio>("./GameData/Music/Main_Menu.wav");
	m_audioList[MENU_MUS]->setGain(MENU_VOLUME);
	m_audioList[MENU_MUS]->setLooping(true);
	m_audioList[BTN_HVR] = ResourceManager::loadResource<aie::Audio>("./GameData/Sound/menu_over.wav");
	m_audioList[BTN_CLICK] = ResourceManager::loadResource<aie::Audio>("./GameData/Sound/menu_click.wav");;
	m_audioList[GAME_MUS_INTRO] = ResourceManager::loadResource<aie::Audio>("./GameData/Music/Action-Intro_converted.wav");
	m_audioList[GAME_MUS_INTRO]->setGain(MENU_VOLUME);
	m_audioList[GAME_MUS_LOOP] = ResourceManager::loadResource<aie::Audio>("./GameData/Music/Action-Loop.wav");
	m_audioList[GAME_MUS_LOOP]->setGain(MENU_VOLUME);
	m_audioList[GAME_MUS_LOOP]->setLooping(true);
	m_audioList[GAME_END_STING] = ResourceManager::loadResource<aie::Audio>("./GameData/Music/Death_Sting.wav");
	m_audioList[GAME_END_STING]->setGain(MENU_VOLUME);
	m_audioList[BULLET_FIRE] = ResourceManager::loadResource<aie::Audio>("./GameData/Sound/pew_laser.wav");
	m_audioList[BULLET_FIRE]->setGain(BULLET_VOLUME);
	m_audioList[HIT] = ResourceManager::loadResource<aie::Audio>("./GameData/Sound/pew_hit.wav");
	m_audioList[HIT]->setGain(BULLET_VOLUME);

	///Player
	m_Player = EntityMaker::createPlayer(m_textureList[PLAYER_SPRITE].get(), this);
	
	///State Manager
	m_stateManager = std::unique_ptr<GameStateManager>(new GameStateManager());
	
	// Load states
	m_stateManager->PushState("SPLASH", new SplashState(this));
	m_stateManager->PushState("MAIN_MENU", new MainMenuState(this));
	m_stateManager->PushState("PLAY", new PlayState(this));
	m_stateManager->PushState("PAUSE", new PauseState(this));
	m_stateManager->PushState("END_MENU", new EndMenuState(this));

	// Start off in main menu state
	m_stateManager->SetState("SPLASH");

	return true;
}

///De-initialization
void _2017_0313_test2DprojApp::shutdown() {
	//Delete non-smart pointers
}

///Button functions
//Start the game
void _2017_0313_test2DprojApp::startFunc() {
	m_stateManager->PopState();									// Pop main menu state
	m_stateManager->SetState("PLAY");
}

void _2017_0313_test2DprojApp::restartFunc() {
	// Remove end menu state AND play state, and reset play state.
	m_stateManager->PopState();
	m_stateManager->PopState();

	m_stateManager->SetState("PLAY");
}

void _2017_0313_test2DprojApp::quitFunc() {
	exit(EXIT_SUCCESS);
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
	if (currentTime < m_asteroidTimeInterval || m_Asteroids.GetSize() > (size_t)maxAsteroids) return;   //Haven't reached interval or we've reached our maximum asteroids
	currentTime = 0.f;       //Reset timer
	int asteroidType = rand() % 3;  //Generate random number between 0-3 to determine what type of asteroid to make
	std::shared_ptr<Asteroid> ast;
	
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
	m_Asteroids.PushBack(ast);
}
///Update
void _2017_0313_test2DprojApp::update(float deltaTime) {
	// input example
	aie::Input* input = aie::Input::getInstance();

	// State Manager
	m_stateManager->Update(deltaTime);

}

void _2017_0313_test2DprojApp::checkCollisions(float a_deltaTime) {
	bool collision = false;

	//Anything colliding with the asteroids
	for (auto ast : m_Asteroids) {
		//Player (check if we've intersected)
		if (ast->getPos().findDistance(m_Player->getPos()) < (ast->getRadius() + m_Player->getRadius())) {
			//Mark asteroid for deletion
			ast->takeDamage((short)(ast->getHealth()));

			//Damage player
			m_Player->takeDamage(ast->getDmg());
			collision = true;
		}

		//Bullets (check for intersection).
		for (auto blt : m_Bullets) {
			if (blt->getBB().IntersectsWith(ast->getBB())) {
				//Mark bullet for deletion
				blt->takeDamage(short(blt->getHealth()));

				//Damage asteroid with player's attack
				ast->takeDamage(m_Player->getDmg());
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

	// State Manager
	m_stateManager->Draw();

	// done drawing sprites, push to the screen
	m_2dRenderer->end();
}
