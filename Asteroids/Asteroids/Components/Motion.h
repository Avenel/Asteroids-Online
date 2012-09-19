#pragma once
#define _USE_MATH_DEFINES
#include "Unit.h"
#include <cmath>
#include <iostream>

class Motion : public Unit
{
public:
	Motion(void);
	~Motion(void);

	sf::Packet* getPacket(int clientId, int id);
	void refresh(sf::Packet packet);

	void increaseSpeed(int rotation, float accelerationRate);

	float getSpeedX();
	float getSpeedY();
	float getDamping();
	void setDamping(float damping);

private:
	float speedX;
	float speedY;
	float damping;
};

