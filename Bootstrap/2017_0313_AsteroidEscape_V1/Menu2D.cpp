#include "Menu2D.h"

Menu2D::Menu2D() {

}
Menu2D::~Menu2D() {

}
void Menu2D::addButton(Button2D* a_btn)
{
	m_btns.push_back(a_btn);
}

void Menu2D::displayAll(aie::Renderer2D* a_r2d)
{
	//Title (only draw if it's there!)
	if (m_titleImg != nullptr) {
		a_r2d->drawSprite(m_titleImg, m_menuBB.x + (m_menuBB.width / 2), m_menuBB.y + (m_menuBB.height - m_titleImg->getHeight())); //Draw vertically in middle and down horizontally according to its height
	}
	//Menu image (only draw if it's there!)
	if (m_menuImg != nullptr) {
		a_r2d->drawSprite(m_menuImg, m_menuBB.x + (m_menuBB.width / 2), m_menuBB.y + (m_menuBB.height / 2), m_menuBB.width, m_menuBB.height, 0, 1);   //Draw behind everything else
	}
	//Buttons
	for (Button2D* btn : m_btns) {
		btn->display(a_r2d);
	}
}

void Menu2D::update(float a_deltaTime, aie::Input* a_input)
{
	//Play music (if there is some)
	if (m_bgSnd != nullptr) {
		static bool playOnce = true;
		if (m_loop == false && playOnce == true) {   //Not looping, play once
			m_bgSnd->play();
			playOnce = false; //Prevent from playing again
		}
		else if (m_loop == true) {   //Looping, always play
			m_bgSnd->play();
		}
	}
	//Get mouse info
	COORD pt = { -1, -1 };  //Initialize off the screen
	a_input->getMouseXY(&pt.x, &pt.y); //Set coord to current mouse pos
	//Cycle through all buttons and check if mouse is in bounding box
	for (Button2D* btn : m_btns) {
		//In focus
		if (btn->getBB().Contains(pt)) {
			btn->onFocus();
			//Clicked
			if (a_input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT)) {        //Up functions get called continously, use down instead
				//Play click sound (if there is one)
				if (btn->getClickSnd() != nullptr) {
					// Stop sound from playing before playing again
					if (btn->getClickSnd()->getIsPlaying())
						btn->getClickSnd()->stop();
					btn->getClickSnd()->setGain(MENU_VOLUME);
					btn->getClickSnd()->play();
				}
				//Do linked click function
				btn->onClick();
			}
		} else {
			btn->loseFocus();  //We've left the button, lose focus
			btn->setDisplayColor(WHITE); //Draw in default color if not in focus
		}
	}
}

void Menu2D::endMusic() {
	//Don't stop nothing
	if (m_bgSnd != nullptr) {
		m_bgSnd->stop();
	}
}