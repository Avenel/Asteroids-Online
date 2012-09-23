#pragma once
#include <SFML/Network.hpp>

class Unit
{
public:
	Unit(void);
	~Unit(void);

	enum UnitType {
		ASTEROID,
		BULLET,
		DISPLAY,
		GAMEMAP,
		GUN,
		GUNCONTROL,
		GAMESYSTEM,
		ITEM,
		MOTION,
		MOTIONCONTROL,
		POSITION,
		STARSHIP
	};
	void setType(UnitType type);
	UnitType getType();

	virtual void addDataToPacket(sf::Packet* packet);
	virtual void refresh(sf::Packet *packet);

protected:
	UnitType type;
};

