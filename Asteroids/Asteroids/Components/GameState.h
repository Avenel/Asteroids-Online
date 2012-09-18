#pragma once

#include "Unit.h"

class GameState : public Unit
{
public:
	GameState(void);
	~GameState(void);

	sf::Packet getPacket();
	void refresh(sf::Packet packet);
};

