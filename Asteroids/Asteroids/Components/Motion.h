#pragma once
#include "Unit.h"

class Motion : public Unit
{
public:
	Motion(void);
	~Motion(void);

	sf::Packet* getPacket(int clientId, int id);
	void refresh(sf::Packet packet);
private:
	float speedX;
	float speedY;
	float damping;
};

