#pragma once
#include <Audio.h>
#include <Renderer2D.h>
#include <Texture.h>
#include <string>
#include <functional>
#include "Settings.h"

using std::string;

class Button2D
{
public:
	///Constructors
	Button2D();
	Button2D(const char* a_txt, aie::Font *a_font, std::function<void()> a_link, float a_x = 0, float a_y = 0, float a_width = 0, float a_height = 0,   //Take default width and height from image if 0,0 
		aie::Texture* a_img = nullptr, aie::Audio* a_clickSnd = nullptr, aie::Audio* a_focusSnd = nullptr) :
		m_txt(a_txt), m_font(a_font), onClick(a_link), m_bb(BoundingBox{ a_x, a_y, a_width, a_height }), 
		m_img(a_img), m_clickSnd(a_clickSnd), m_focusSnd(a_focusSnd), m_playHover(true) {}
	~Button2D();
	///Methods
	void display(aie::Renderer2D* a_r2d);
	//Setters
	void setDisplayColor(unsigned int a_renderColor) { m_renderColor = a_renderColor; }
	//Getters
	BoundingBox getBB() { return m_bb;  }
	aie::Audio* getClickSnd() { return m_clickSnd; }
	//Function
	std::function<void()> onClick;        //Use standard function instead of function pointer to accept it as parameter and bind it to what is being passed in
	void onFocus();
	void loseFocus();
private:
	///Variables
	//Sprites
	aie::Texture* m_img;            //Pointer to image in case we want to change from the default
	//Positions
	BoundingBox m_bb;                      //Track boundary and position
	//Audio (passed in externally, don't handle clean up)
	aie::Audio* m_clickSnd;           //Play on click
	aie::Audio* m_focusSnd;           //Play on mouse over button
	bool m_playHover;                 //Do we play the hover sound?
	//Text
	aie::Font* m_font;      
	string m_txt;
	unsigned int m_renderColor;        //Render in regular color by default but allow to be tinted
};

