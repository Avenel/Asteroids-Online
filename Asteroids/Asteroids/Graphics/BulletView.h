#pragma once
#include "View.h"

class BulletView : public View
{
public:
	BulletView(void);
	~BulletView(void);

	void draw(sf::RenderWindow *target, sf::RenderStates &states);
	void setPosition(float x, float y);
	void setRotation(float degree);
};

