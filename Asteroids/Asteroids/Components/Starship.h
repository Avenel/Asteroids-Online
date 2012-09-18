#pragma once
#include "Unit.h"

class Starship : public Unit
{
public:
	Starship();
	~Starship(void);

	sf::Packet getPacket(int clientId, int id);
	void refresh(sf::Packet packet);
};

