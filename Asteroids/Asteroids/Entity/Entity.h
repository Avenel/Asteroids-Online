#pragma once

#include <SFML/Network.hpp>
#include <iostream>

using namespace std;

/**
	Ein "Entity" dient als Grundlage aller Objekte die im Spiel vorkommen werden
**/

class Entity
{
public:
	Entity(void);
	Entity(int id, int type);
	~Entity(void);

	virtual void refresh(sf::Packet packet);
	
	void setId(int id);
	int getId();

	int getClientId();
	void setClientId(int clientId);

	int getType();
	void setType(int type);

	sf::Packet getPacket(int clientId);

	// Temp!
	void setX(int x);
	int getX();
	
	void setY(int y);
	int getY();

protected:
	int id;
	int clientId;
	int type;

	// Temp!
	int x;
	int y;
};
