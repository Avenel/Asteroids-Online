#pragma once
#include "Unit.h"
#include <SFML\Window\Keyboard.hpp>

class MotionControl : public Unit
{
public:
	MotionControl();
	~MotionControl(void);

	void addDataToPacket(sf::Packet* packet);
	void refresh(sf::Packet packet);

	void setLeft(sf::Keyboard::Key key);
	sf::Keyboard::Key getLeft();

	void setRight(sf::Keyboard::Key key);
	sf::Keyboard::Key getRight();

	void setAccelerate(sf::Keyboard::Key key);
	sf::Keyboard::Key getAccelerate();

	void setAccelerationRate(float accelerationRate);
	float getAccelerationRate();

	void setRotationRate(float rotationRate);
	float getRotationRate();

private:
	sf::Keyboard::Key left;
	sf::Keyboard::Key right;
	sf::Keyboard::Key accelerate;
	float accelerationRate;
	float rotationRate;
};

