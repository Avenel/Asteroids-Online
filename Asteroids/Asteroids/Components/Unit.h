#pragma once
#include <SFML/Network.hpp>

class Unit
{
public:
	Unit(void);
	~Unit(void);

	enum UnitType {
		ASTEROID,
		DISPLAY,
		GAMEMAP,
		GUN,
		GUNCONTROL,
		ITEM,
		MOTION,
		MOTIONCONTROL,
		POSITION,
		STARSHIP
	};
	void setType(UnitType type);
	UnitType getType();

	virtual sf::Packet getPacket();
private:
	UnitType type;
};

