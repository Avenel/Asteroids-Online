#pragma once
#include "Unit.h"

class Position : public Unit
{
public:
	Position(int x, int y);
	~Position(void);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();

	sf::Packet* getPacket(int clientId, int id);
	void refresh(sf::Packet packet);

	void rotateLeft();
	void rotateRight();
	int getRotation();

private:
	int x;
	int y;
	int rotation;
};

