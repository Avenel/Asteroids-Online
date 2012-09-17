#pragma once
#include "Unit.h"

class Asteroid : public Unit
{
public:
	Asteroid(void);
	~Asteroid(void);

	sf::Packet getPacket();
};

