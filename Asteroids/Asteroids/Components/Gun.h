#pragma once
#include "Unit.h"

class Gun : public Unit
{
public:
	Gun(void);
	~Gun(void);

	void addDataToPacket(sf::Packet* packet);
	void refresh(sf::Packet *packet);

	void setBulletRange(float bulletRange);
	float getBulletRange();

	void setBulletSpeed(float bulletSpeed);
	float getBulletSpeed();

private:
	float bulletRange;
	float bulletSpeed;
};

