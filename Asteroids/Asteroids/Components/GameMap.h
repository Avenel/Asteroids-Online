#pragma once
#include "Unit.h"

class GameMap : public Unit
{
public:
	GameMap(void);
	~GameMap(void);

	sf::Packet getPacket(int clientId, int id);
	void refresh(sf::Packet packet);

private:

};

