#pragma once

#include <SFML/Graphics.hpp>

class View
{
public:
	View(void);
	~View(void);

	virtual void draw(sf::RenderWindow *target, sf::RenderStates &states);
	virtual void setPosition(float x, float y);
	virtual void setRotation(float degree);
};
