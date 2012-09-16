#pragma once
#include "View.h"
#include <SFML\Graphics\ConvexShape.hpp>

class StarshipView : public View, public sf::ConvexShape
{
public:
	StarshipView(void);
	~StarshipView(void);

private:	
	const float size = 15.0; 
};

