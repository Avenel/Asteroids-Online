#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include "..\Components\Unit.h"
#include <map>
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

	std::list<sf::Packet*>* getPackets(int clientId);

	void addUnit(Unit *unit);
	void deleteUnit(Unit *unit);
	std::map<Unit::UnitType, Unit*>* getAllUnits();
	bool hasComponent(Unit::UnitType type);
	Unit* getComponent(Unit::UnitType type);

protected:
	int id;
	int clientId;

	bool synchronized;

private:
	std::map<Unit::UnitType, Unit*> *units;
};

