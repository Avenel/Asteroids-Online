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

void MovementSystem::update() {
	list<Node*>* movementNodes;
	movementNodes = familyManager->getMemberOfFamilies(FamilyManager::Family::MOVEMENT_SYSTEM);

	Position* position;
	Motion* motion;
	float damping;
	float rotation;
	float dampingX;
	float dampingY;
	float speedX;
	float speedY;

	for (list<Node*>::iterator it = movementNodes->begin(); it != movementNodes->end(); ++it) {
		position = ((MovementNode*)(*it))->getPosition();
		motion = ((MovementNode*)(*it))->getMotion();
		damping = motion->getDamping();

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

		
		rotation = motion->getSpeedRotation();
		dampingX = (float)(cos(rotation * M_PI / 180)) * damping;
		dampingY = (float)(sin(rotation * M_PI / 180)) * damping;
		speedX = motion->getSpeedX();
		speedY = motion->getSpeedY();
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


		//motion->setSpeedX(motion->getSpeedX()*0.90f);
		//motion->setSpeedY(motion->getSpeedY()*0.90f);

		position->setX(newX);
		position->setY(newY);
	}

}
