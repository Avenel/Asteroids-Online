#pragma once
#include "Unit.h"
#include <SFML\Window\Keyboard.hpp>

class GunControl : public Unit
{
public:
	GunControl(void);
	~GunControl(void);

	sf::Packet getPacket(int clientId, int id);
	void refresh(sf::Packet packet);

	void setShootKey(sf::Keyboard::Key key);
	sf::Keyboard::Key getShootKey();

private:
	sf::Keyboard::Key shootKey;
};

