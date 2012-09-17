#pragma once
#include "Unit.h"

class MotionControl : public Unit
{
public:
	MotionControl(void);
	~MotionControl(void);

	sf::Packet getPacket();
private:
	int left;
	int right;
	int accelerate;
	int accelerationRate;
	int	rotationRate;
};

