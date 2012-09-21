#pragma once
#include "Unit.h"

class Motion : public Unit
{
public:
	Motion(void);
	~Motion(void);

	sf::Packet getPacket(int clientId, int id);
	void refresh(sf::Packet packet);

	void increaseSpeed(float speedX, float speedY);

	float getSpeedX();
	float getSpeedY();
	void setSpeedX(float dx);
	float getDamping();
	void setSpeedY(float dy);
	void setDamping(float damping);

private:
	float speedX;
	float speedY;
	float damping;
};

