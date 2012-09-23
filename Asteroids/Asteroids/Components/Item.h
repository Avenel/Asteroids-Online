#pragma once
#include "Unit.h"

class Item : public Unit
{
public:
	Item(void);
	~Item(void);

	void addDataToPacket(sf::Packet* packet);
	void refresh(sf::Packet packet);
};

