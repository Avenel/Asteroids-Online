#pragma once
#include "Unit.h"

class Position : public Unit
{
public:
	Position(float x, float y);
	~Position(void);
	void setX(float x);
	void setY(float y);
	float getX();
	float getY();

	sf::Packet* getPacket(int clientId, int id);
	void refresh(sf::Packet packet);

	void rotateLeft();
	void rotateRight();
	int getRotation();

private:
	float x;
	float y;
	int rotation;
};

