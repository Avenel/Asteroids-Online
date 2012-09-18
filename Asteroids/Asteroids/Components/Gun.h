#pragma once
#include "Unit.h"

class Gun : public Unit
{
public:
	Gun(void);
	~Gun(void);

	sf::Packet getPacket();
	void refresh(sf::Packet packet);
};

