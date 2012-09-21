#pragma once
#include "View.h"

class BulletView : public View
{
public:
	BulletView(float radius = 1.0f);
	~BulletView(void);

	void draw(sf::RenderWindow *target, sf::RenderStates &states);
	void setPosition(float x, float y);
	void setRotation(float degree);

private:
	float radius;
	sf::CircleShape* bulletPolygon;

	void createBulletPolygon();
};

