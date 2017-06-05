#pragma once

#include "ConMenu.h"

///Co-written by Sebastian Toy and Jack McCall
using std::string;

class ConButton : public ConMenu {
public:
	///Constructors
	//Construct and initialize variables
	ConButton();
	ConButton(short a_width, short a_height, string text, std::function<void()> a_link, eColor a_textColor = WHITE, eColor a_borderColor = WHITE) :
		 m_width(a_width), m_height(a_height), m_btnText(text), onClick(a_link), m_textColor(a_textColor), m_borderColor(a_borderColor) {}
	~ConButton();
	///Methods
	bool isPressed(COORD a_pt);             //Check if button is in pressed state
	template <typename T> void display(T *a_board);							//Draw the button to the board
	void setBoundingBox(short a_currentDrawPos, COORD a_drawPos); /*Creating bounding box based off button position 
																    and menu draw position*/
	Rect getBoundingBox();
	short getWidth();
	short getHeight();
	///Functions
	std::function<void()> onClick;        //Use standard function instead of function pointer to accept it as parameter
private:
	///Variables
	string m_btnText;
	eColor m_textColor;
	eColor m_borderColor;

	short m_width;
	short m_height;
	Rect m_bb;
};

template <typename T>
void ConButton::display(T *a_board)
{
	a_board->DrawBorder(m_bb, m_borderColor);
	if (m_btnText != " ") {
		a_board->DrawTextLine(m_bb.x + 2, m_bb.y + 1, m_textColor, Window::toChar(m_btnText), 100);
	}
}


