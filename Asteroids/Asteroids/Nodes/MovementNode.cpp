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
	return (entity->hasComponent(Unit::MOTION) && entity->hasComponent(Unit::POSITION));
}

void MovementNode::addEntity() {
	this->motion = (Motion*)this->entity->getComponent(Unit::MOTION);
	this->position = (Position*)this->entity->getComponent(Unit::POSITION);
}

Position* MovementNode::getPosition() {
	return this->position;
}

Motion* MovementNode::getMotion() {
	return this->motion;
}
