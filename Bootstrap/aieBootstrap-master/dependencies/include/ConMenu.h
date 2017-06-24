#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include "window.h"



using std::string;
using std::vector;

///Prototyping
class ConButton;             /*Forward declaration, not actually being used.

							 All classes need to know the exact size of custom datatypes being used, hence includes. However,
							 if everything is a pointer to a custom class this needs to be used instead because the compiler knows
							 all pointers are the same size.*/
class ConMenu
{
public:  

	///Constructors and initialization
	ConMenu();
	ConMenu(vector<ConButton*> &a_buttons, COORD a_drawPos, short a_buttonIncrement) :
		m_buttons(a_buttons), m_drawPos(a_drawPos), m_buttonIncrement(a_buttonIncrement) {
		//Generate bounding boxes from menu elements
		createBoundingBoxes();
	};
	ConMenu(vector<string> &a_title, eColor a_titleColor, COORD a_titlePos, vector<ConButton*> &a_buttons, COORD a_drawPos, short a_buttonIncrement) : 
		m_title(a_title), m_titleColor(a_titleColor), m_titlePos(a_titlePos), m_buttons(a_buttons), m_drawPos(a_drawPos), m_buttonIncrement(a_buttonIncrement) {
		//Generate bounding boxes from menu elements
		createBoundingBoxes();
	};
	~ConMenu();
	///Methods
	template <typename T> void display(T *a_board);              //Draw all elements in the menu to the board
	void createBoundingBoxes();  //Based off current position of menu and elements in the menu
	void checkInput(COORD a_pt);
protected:
	///Variables
	COORD m_drawPos;               //Where to draw menu from
	short m_menuWidth = 0;
	short m_menuHeight = 0;
private:
	///Variables
	COORD m_titlePos;              //Where to draw title from
	eColor m_titleColor;
	vector<string> m_title;

	//Keep a vector of pointers so we're not parsing in the actual objects
	vector<ConButton*> m_buttons;
	short m_buttonIncrement;         //How far apart to draw the buttons

	Rect m_menuBB;                     //Bounding box for entire menu
};

template <typename T>
void ConMenu::display(T *a_board)
{
	//Draw the title if initialized
	if (m_title.size() != 0) {
		a_board->DrawShape(m_titlePos.X, m_titlePos.Y, m_title, m_titleColor);
	}
	//Draw the buttons
	for (ConButton *btn : m_buttons) {
		btn->display(a_board);
	}
}

