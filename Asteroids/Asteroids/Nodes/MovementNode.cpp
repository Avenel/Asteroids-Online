#include "MovementNode.h"


MovementNode::MovementNode(void)
{
}

MovementNode::MovementNode(Entity* entity)
{
	this->Node::Node(entity);
	this->addEntity();
}


MovementNode::~MovementNode(void)
{
}

bool MovementNode::isEntityMember(Entity* entity) {
	return false;
}

void MovementNode::addEntity() {
}

Position* MovementNode::getPosition() {
	return this->position;
}

Motion* MovementNode::getMotion() {
	return this->motion;
}
