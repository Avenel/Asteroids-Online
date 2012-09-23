#pragma once

#include "Unit.h"

class GameState : public Unit
{
public:
	GameState(void);
	~GameState(void);

	void addDataToPacket(sf::Packet* packet);
	void refresh(sf::Packet packet);
};

