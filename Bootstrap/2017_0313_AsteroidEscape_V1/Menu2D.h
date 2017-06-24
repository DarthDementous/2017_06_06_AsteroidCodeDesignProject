#pragma once
#include <LinkedList.hpp>
#include <Texture.h>
#include <Renderer2D.h>
#include <Audio.h>
#include <Input.h>
#include "Settings.h"
#include "Button2D.h"

using std::vector;

class Menu2D
{
public:
	Menu2D();
	Menu2D(aie::Audio* a_bgSnd = nullptr, bool a_loop = true, aie::Texture* a_titleImg = nullptr, aie::Texture* a_menuImg = nullptr, float a_x = 0, float a_y = 0, float a_width = W_WIDTH, float a_height = W_HEIGHT) :
		m_bgSnd(a_bgSnd), m_loop(a_loop), m_titleImg(a_titleImg), m_menuImg(a_menuImg), m_menuBB(BoundingBox{ a_x, a_y, a_width, a_height }) {}
	~Menu2D();

	///Methods
	void addButton(Button2D* a_btn);               //Keep button vector private
	void displayAll(aie::Renderer2D* a_r2d);       //Render all menu items
	void update(float a_deltaTime, aie::Input* a_input);                //Check for user input on buttons
	void endMusic();                                //Stop playing the music when we leave the menu
    //Conditions
	bool Active = false;                      //Whether to draw or not
private:
	///Variables
	//Sprites
	aie::Texture* m_titleImg;             //Sprite for menu title
	aie::Texture* m_menuImg;           //Sprite for menu background
	aie::Texture* m_btnImg;            //Default sprite for buttons
	//Positions
	BoundingBox m_menuBB;                   //Keep track of x, y and bounding box
	//Sound
	aie::Audio* m_bgSnd;              //Play while menu is active
	bool m_loop;                      //Loop the background sound, true by default
	//Elements
	LinkedList<Button2D*> m_btns;         //Linked list of pointers to menu buttons
};

