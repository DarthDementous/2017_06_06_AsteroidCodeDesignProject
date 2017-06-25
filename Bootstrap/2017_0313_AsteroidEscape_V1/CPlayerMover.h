#pragma once
#include <IComponent.hpp>

class Player;

/**
*	@brief Component that handles movement of player.
*/
class CPlayerMover :
	public IComponent
{
public:
	CPlayerMover(Player* a_player) : PLAYER(a_player) {}

	virtual void Update(float dt);
private:
	Player* PLAYER = nullptr;					// Hold on to pointer to parented entity
};

