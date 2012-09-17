#pragma once

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
private:
	UnitType type;
};

