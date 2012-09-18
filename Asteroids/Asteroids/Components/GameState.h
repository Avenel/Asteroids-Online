#pragma once

#include "Unit.h"

class GameState : public Unit
{
public:
	GameState(void);
	~GameState(void);

	sf::Packet getPacket(int clientId, int id);
	void refresh(sf::Packet packet);
};

