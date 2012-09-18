#pragma once
#include "View.h"
#include <SFML\Graphics\ConvexShape.hpp>

class StarshipView : public View
{
public:
	StarshipView(void);
	~StarshipView(void);

	void draw(sf::RenderWindow *target, sf::RenderStates &states);
	void setPosition(float x, float y);
	void setRotation(float degree);

private:	
	static float const size; 

	sf::ConvexShape *shipPolygon;
};

