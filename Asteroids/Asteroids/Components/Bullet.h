#pragma once
#include "Unit.h"

class Bullet : public Unit
{
public:
	Bullet(void);
	~Bullet(void);

	sf::Packet getPacket(int clientId, int id);
	void refresh(sf::Packet packet);

	void setRangeRemaining(float rangeRemaining);
	float getRangeRemaining();

private:
	float rangeRemaining;
};
