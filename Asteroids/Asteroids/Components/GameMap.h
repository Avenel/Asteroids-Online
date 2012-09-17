#pragma once
#include "Unit.h"

class GameMap : public Unit
{
public:
	GameMap(void);
	~GameMap(void);

	sf::Packet getPacket();
private:

};

