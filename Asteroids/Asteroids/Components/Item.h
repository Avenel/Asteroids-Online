#pragma once
#include "Unit.h"

class Item : public Unit
{
public:
	Item(void);
	~Item(void);

	sf::Packet* getPacket(int clientId, int id);
	void refresh(sf::Packet packet);
};

