#pragma once
#include "Unit.h"

class Item : public Unit
{
public:
	Item(void);
	~Item(void);

	sf::Packet getPacket();
	void refresh(sf::Packet packet);
};

