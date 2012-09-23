#pragma once
#include "..\Entity\Entity.h"
#include "Starship.h"

class Player : public Unit
{
public:
	Player(void);
	~Player(void);
	void setStarship();
	Starship* getStarship();

	void addDataToPacket(sf::Packet* packet);
	void refresh(sf::Packet packet);
private:
	Starship* starship;
};

