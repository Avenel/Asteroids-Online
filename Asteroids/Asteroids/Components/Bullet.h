#pragma once
#include "Unit.h"

class Bullet : public Unit
{
public:
	Bullet(void);
	~Bullet(void);

	void addDataToPacket(sf::Packet* packet);
	void refresh(sf::Packet packet);

	void setRangeRemaining(float rangeRemaining);
	float getRangeRemaining();

private:
	float rangeRemaining;
};
