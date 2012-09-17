#include "MotionControlSystem.h"


MotionControlSystem::MotionControlSystem(void)
{
}


MotionControlSystem::~MotionControlSystem(void)
{
}

void MotionControlSystem::update() {
	cout << "Taste gedrueckt" << endl;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		cout << "Links" << endl;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		cout << "Rechts" << endl;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		cout << "Oben" << endl;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		cout << "Leertaste" << endl;
	}	
}
