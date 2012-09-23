#pragma once
#include "Unit.h"
#include "../Graphics/View.h"

class Display : public Unit
{
public:
	Display(void);
	~Display(void);
	void setDisplayObject(View* view);
	View* getDisplayObject();

	void addDataToPacket(sf::Packet* packet);
	void refresh(sf::Packet *packet);
	
	void draw(sf::RenderWindow *target, sf::RenderStates &states);
	void setPosition(float x, float y);
	void setRotation(float degree);

private:
	View* displayObject;
};
