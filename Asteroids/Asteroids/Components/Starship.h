#pragma once
#include "Unit.h"

class Starship : public Unit
{
public:
	Starship();
	~Starship(void);

	void addDataToPacket(sf::Packet* packet);
	void refresh(sf::Packet packet);
};

