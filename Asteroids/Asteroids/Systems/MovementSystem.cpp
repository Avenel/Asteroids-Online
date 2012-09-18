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

		position->setX((float)position->getX() + (float)motion->getSpeedX());
		position->setY((float)position->getY() + (float)motion->getSpeedY());
	}

}
