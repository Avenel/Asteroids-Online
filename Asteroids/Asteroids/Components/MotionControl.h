#pragma once
#include "Unit.h"
#include <SFML\Window\Keyboard.hpp>

class MotionControl : public Unit
{
public:
	MotionControl();
	~MotionControl(void);

	sf::Packet getPacket();
	void refresh(sf::Packet packet);

	void setLeft(sf::Keyboard::Key key);
	sf::Keyboard::Key getLeft();

	void setRight(sf::Keyboard::Key key);
	sf::Keyboard::Key getRight();

	void setAccelerate(sf::Keyboard::Key key);
	sf::Keyboard::Key getAccelerate();

	void setAccelerationRate(int accelerationRate);
	int getAccelerationRate();

	void setRotationRate(int rotationRate);
	int getRotationRate();

private:
	sf::Keyboard::Key left;
	sf::Keyboard::Key right;
	sf::Keyboard::Key accelerate;
	int accelerationRate;
	int	rotationRate;
};

