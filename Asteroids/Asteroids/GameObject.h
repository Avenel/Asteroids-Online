#pragma once

#include <SFML/Network.hpp>
#include <iostream>

using namespace sf;
using namespace std;

/**
	Ein "GameObject" dient als Grundlage aller Objekte die im Spiel vorkommen werden
**/

class GameObject
{
public:
	GameObject(void);
	GameObject(int id, int type);
	~GameObject(void);

	virtual void refresh(Packet packet);
	
	void setId(int id);
	int getId();

	int getClientId();

	int getType();
	void setType(int type);

	Packet getPacket(int clientId);

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

