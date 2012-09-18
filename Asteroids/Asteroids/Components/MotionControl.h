#pragma once
#include "Unit.h"

class MotionControl : public Unit
{
public:
	MotionControl(void);
	~MotionControl(void);

	sf::Packet getPacket();
	void refresh(sf::Packet packet);
private:
	int left;
	int right;
	int accelerate;
	int accelerationRate;
	int	rotationRate;
};

