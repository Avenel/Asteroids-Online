#pragma once
#include "Unit.h"

class GunControl : public Unit
{
public:
	GunControl(void);
	~GunControl(void);

	sf::Packet* getPacket(int clientId, int id);
	void refresh(sf::Packet packet);
};

