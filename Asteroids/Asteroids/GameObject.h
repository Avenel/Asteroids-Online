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
	GameObject(int id);
	~GameObject(void);

	void refresh(Packet packet);

	int getId();
	Packet getPacket();


	// Temp!
	int getX();
	int getY();
	void setId(int id);
	void setX(int x);
	void setY(int y);

protected:
	int id;

	// Temp!
	int x;
	int y;
};

