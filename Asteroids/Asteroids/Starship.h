#pragma once
#include "gameobject.h"
#include <SFML/Graphics/ConvexShape.hpp>

class Starship : public GameObject, public sf::ConvexShape
{
public:
	Starship(sf::Color color);
	~Starship(void);
private:

};

