#pragma once
#define _USE_MATH_DEFINES
#include "Unit.h"
#include <cmath>

class Motion : public Unit
{
public:
	Motion(void);
	~Motion(void);

	sf::Packet getPacket();
	void refresh(sf::Packet packet);

	void increaseSpeed(int rotation, int accelerationRate);

	float getSpeedX();
	float getSpeedY();

private:
	float speedX;
	float speedY;
	float damping;
};

