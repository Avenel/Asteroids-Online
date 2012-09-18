#pragma once
#include "Unit.h"

class GunControl : public Unit
{
public:
	GunControl(void);
	~GunControl(void);

	sf::Packet getPacket();
	void refresh(sf::Packet packet);
};

