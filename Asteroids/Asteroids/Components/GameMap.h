#pragma once
#include "Unit.h"

class GameMap : public Unit
{
public:
	GameMap(void);
	~GameMap(void);

	void addDataToPacket(sf::Packet* packet);
	void refresh(sf::Packet *packet);

private:

};

