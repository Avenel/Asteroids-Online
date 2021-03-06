#pragma once
#include "Unit.h"

class Position : public Unit
{
public:
	Position(float x, float y, int rotation=0);
	~Position(void);
	void setX(float x);
	void setY(float y);
	float getX();
	float getY();

	void addDataToPacket(sf::Packet* packet);
	void refresh(sf::Packet *packet);

	void rotateLeft(float speed);
	void rotateRight(float speed);
	int getRotation();

private:
	float x;
	float y;
	int rotation;
};

