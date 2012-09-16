#pragma once
#include "gameobject.h"
#include "Starship.h"

class Player : public GameObject
{
public:
	Player(void);
	~Player(void);
	void setStarship();
	Starship* getStarship();
private:
	Starship* starship;
};

