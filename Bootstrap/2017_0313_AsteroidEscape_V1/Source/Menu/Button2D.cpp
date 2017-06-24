#include "Button2D.h"

Button2D::Button2D()
{
}


Button2D::~Button2D()
{
}
//All renders get called between begin and end in the Draw() function
void Button2D::display(aie::Renderer2D * a_r2d)
{
	//Image (with or without tint)
	a_r2d->setRenderColour(m_renderColor);
	a_r2d->drawSprite(m_img, m_bb.x, m_bb.y, m_bb.width, m_bb.height);
	a_r2d->setRenderColour(WHITE); //Reset renderer color to default (white)
	//Text
	a_r2d->setRenderColour(ORANGE);
	a_r2d->drawText(m_font, &m_txt[0u], m_bb.x - (m_bb.width / 2) + BTN_TXT_X_OFFSET, m_bb.y - BTN_TXT_Y_OFFSET); //Convert string to constant char and draw in the middle (For bootstrap things draw from the center!)
}

void Button2D::onFocus()
{
	//Play hover sound (if there is one)
	if (m_focusSnd != nullptr) {
		if (m_playHover) {
			// Stop other hover sound from playing before playing again
			if (m_focusSnd->getIsPlaying())
				m_focusSnd->stop();
			m_focusSnd->setGain(MENU_VOLUME);
			m_focusSnd->play();
			m_playHover = false;    //Stop infinite looping
		}
	}
	//Change rendercolor to indicate selection
	m_renderColor = DEFAULT_BTN_TINT;
}

void Button2D::loseFocus() {
	m_playHover = true;       //The next time this button comes into focus we can play the hover sound
}

