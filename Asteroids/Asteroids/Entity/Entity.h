#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include "..\Components\Unit.h"
#include <list>

using namespace std;




/**
	Ein "Entity" dient als Grundlage aller Objekte die im Spiel vorkommen werden
**/

class Entity
{
public:

	Entity(void);
	Entity(int id);
	~Entity(void);

	virtual void refresh(sf::Packet packet);
	
	void setId(int id);
	int getId();

	int getClientId();
	void setClientId(int clientId);

	sf::Packet getPacket(int clientId);

	void addUnit(Unit *unit);
	void deleteUnit(Unit *unit);
	list<Unit*>* getAllUnits();

protected:
	int id;
	int clientId;

private:
	list<Unit*> *units;
};

