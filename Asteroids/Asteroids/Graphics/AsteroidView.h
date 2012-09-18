#pragma once
#include "View.h"

class AsteroidView : public View
{
public:
	AsteroidView(void);
	~AsteroidView(void);

	void draw(sf::RenderWindow *target, sf::RenderStates &states);
	void setPosition(float x, float y);
	void setRotation(float degree);

private:
};
