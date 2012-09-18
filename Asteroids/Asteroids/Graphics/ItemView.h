#pragma once
#include "View.h"

class ItemView : public View
{
public:
	ItemView(void);
	~ItemView(void);

	void draw(sf::RenderWindow *target, sf::RenderStates &states);
	void setPosition(float x, float y);
	void setRotation(float degree);
};

