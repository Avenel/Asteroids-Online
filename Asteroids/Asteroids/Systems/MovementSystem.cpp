#include "MovementSystem.h"


MovementSystem::MovementSystem(void)
{
}

MovementSystem::MovementSystem(FamilyManager* familyManager, sf::Vector2u windowSize)
{
	this->familyManager = familyManager;
	this->windowSize = windowSize;
}

MovementSystem::~MovementSystem(void)
{
}

void MovementSystem::damping(Motion* motion) {
	float damping = motion->getDamping();
	//Damping anwenden?
	if(damping > 0.0f) {
		float speedX = motion->getSpeedX();
		float speedY = motion->getSpeedY();
		float speedAtan;
		float dampingX;
		float dampingY;

		if(speedX != 0.0f) {
			speedAtan = atanf(speedY/speedX);
		}
		else if (speedY >= 0.0f) {
			//PI/2
			speedAtan = (float)M_PI_2;
		}
		else {
			//3/2 PI
			speedAtan = (float)(M_PI + M_PI_2);
		}

		if(speedX >= 0.0f && speedY < 0.0f) {
			//2 PI
			speedAtan += (float)(2 * M_PI);
		}
		else if(speedX < 0.0f) {
			//PI
			speedAtan += (float)M_PI;	
		}

		dampingX = cos(speedAtan) * damping;
		dampingY = sin(speedAtan) * damping;
		dampingX *= sqrt(pow(speedX,2) + pow(speedY,2));
		dampingY *= sqrt(pow(speedX,2) + pow(speedY,2));

		if((abs(speedX) - dampingX) < 0) {
			motion->setSpeedX(0);
		}
		else {
			motion->setSpeedX(speedX - dampingX);
		}

		if((abs(speedY) - dampingY) < 0) {
			motion->setSpeedY(0);
		}
		else {
			motion->setSpeedY(speedY - dampingY);
		}
	}
}

void MovementSystem::update() {
	list<Node*>* movementNodes;
	movementNodes = familyManager->getMemberOfFamilies(FamilyManager::Family::MOVEMENT_SYSTEM);

	Position* position;
	Motion* motion;

	for (list<Node*>::iterator it = movementNodes->begin(); it != movementNodes->end(); ++it) {
		position = ((MovementNode*)(*it))->getPosition();
		motion = ((MovementNode*)(*it))->getMotion();
		
		float newX = (float)position->getX() + (float)motion->getSpeedX();
		if(newX > this->windowSize.x) {
			newX -= this->windowSize.x;
		}
		else if( newX < 0.0 ) {
			newX += this->windowSize.x;
		}
		
		float newY = (float)position->getY() + (float)motion->getSpeedY();
		if(newY > this->windowSize.y) {
			newY -= this->windowSize.y;
		}
		else if( newY < 0.0 ) {
			newY += this->windowSize.y;
		}

		//Geschwindigkeit daempfen
		this->damping(motion);

		position->setX(newX);
		position->setY(newY);
	}

}