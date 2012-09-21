#include "MotionControlSystem.h"


MotionControlSystem::MotionControlSystem(void)
{
	this->familyManager = 0;
}

MotionControlSystem::MotionControlSystem(FamilyManager* familyManager)
{
	this->familyManager = familyManager;
}


MotionControlSystem::~MotionControlSystem(void)
{
}

void MotionControlSystem::update() {
	/*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
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
	}	*/

	list<Node*>* motionControlNodes;
	motionControlNodes = familyManager->getMemberOfFamilies(FamilyManager::Family::MOTION_CONTROL_SYSTEM);

	Position* position;
	Motion* motion;
	MotionControl* motionControl;
	float angle;
	float accelerationRate;
	float speedX;
	float speedY;

	for (list<Node*>::iterator it = motionControlNodes->begin(); it != motionControlNodes->end(); ++it) {
		position = ((MotionControlNode*)(*it))->getPosition();
		motion = ((MotionControlNode*)(*it))->getMotion();
		motionControl = ((MotionControlNode*)(*it))->getMotionControl();
		
		if(sf::Keyboard::isKeyPressed(motionControl->getLeft())) {
			//cout << "Links" << endl;
			position->rotateLeft(motionControl->getRotationRate());
		}

		if(sf::Keyboard::isKeyPressed(motionControl->getRight())) {
			//cout << "Rechts" << endl;
			position->rotateRight(motionControl->getRotationRate());
		}

		if(sf::Keyboard::isKeyPressed(motionControl->getAccelerate())) {
			//cout << "Beschleunigen" << endl;
			angle = position->getRotation() * M_PI / 180.0f;
			accelerationRate = motionControl->getAccelerationRate();
			speedX = cosf(angle) * accelerationRate;
			speedY = sinf(angle) * accelerationRate;

			motion->increaseSpeed(speedX, speedY);
		}

	}
}
