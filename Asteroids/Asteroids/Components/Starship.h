#pragma once
#include "Unit.h"

class Starship : public Unit
{
public:
	Starship();
	~Starship(void);

	sf::Packet getPacket();
	void refresh(sf::Packet packet);
};

