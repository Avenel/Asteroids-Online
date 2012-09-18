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

	sf::Packet getPacket();
	void refresh(sf::Packet packet);
	void draw(sf::RenderWindow *target, sf::RenderStates &states);
private:
	View* displayObject;
};
