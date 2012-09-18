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

	sf::Packet* getPacket(int clientId, int id);
	void refresh(sf::Packet packet);
private:
	Starship* starship;
};

