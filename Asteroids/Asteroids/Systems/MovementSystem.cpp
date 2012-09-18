#include "MovementSystem.h"


MovementSystem::MovementSystem(void)
{
}

MovementSystem::MovementSystem(FamilyManager* familyManager)
{
	this->familyManager = familyManager;
}

MovementSystem::~MovementSystem(void)
{
}

void MovementSystem::update() {
	list<Node*>* movementNodes;
	movementNodes = familyManager->getMemberOfFamilies(FamilyManager::Family::MOVEMENT_SYSTEM);

	Position* position;
	Motion* motion;

	for (list<Node*>::iterator it = movementNodes->begin(); it != movementNodes->end(); ++it) {
		position = ((MovementNode*)(*it))->getPosition();
		motion = ((MovementNode*)(*it))->getMotion();

		position->setX(position->getX() + (position->getX() * motion->getSpeedX()));
		position->setY(position->getY() + (position->getY() * motion->getSpeedY()));
	}

}
