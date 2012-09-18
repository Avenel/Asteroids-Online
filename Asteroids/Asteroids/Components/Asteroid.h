#pragma once
#include "Unit.h"

class Asteroid : public Unit
{
public:
	Asteroid(void);
	~Asteroid(void);

	sf::Packet* getPacket(int clientId, int id);
	void refresh(sf::Packet packet);
};

