#pragma once
#include "..\Entity\Entity.h"
#include "Starship.h"

class Player : public Entity
{
public:
	Player(void);
	~Player(void);
	void setStarship();
	Starship* getStarship();

	sf::Packet getPacket();
	void refresh(sf::Packet packet);
private:
	Starship* starship;
};

