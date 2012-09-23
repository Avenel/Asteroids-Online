#pragma once
#include "Unit.h"

class Asteroid : public Unit
{
public:
	Asteroid(void);
	~Asteroid(void);

	void addDataToPacket(sf::Packet* packet);
	void refresh(sf::Packet packet);
};

