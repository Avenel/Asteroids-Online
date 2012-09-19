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

		

		position->setX(newX);
		position->setY(newY);
	}

}
