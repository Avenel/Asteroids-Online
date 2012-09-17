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
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		cout << "Rechts" << endl;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		cout << "Oben" << endl;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		cout << "Leertaste" << endl;
	}	
}
