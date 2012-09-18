#include "MotionControlNode.h"


MotionControlNode::MotionControlNode(void)
{
}

MotionControlNode::MotionControlNode(Entity* entity)
{
	this->Node::Node(entity);
	this->addEntity();
}

MotionControlNode::~MotionControlNode(void)
{
}

bool MotionControlNode::isEntityMember(Entity* entity) {
	return (entity->hasComponent(Unit::MOTION) && entity->hasComponent(Unit::POSITION) && entity->hasComponent(Unit::MOTIONCONTROL));
}

void MotionControlNode::addEntity() {
	this->motion = (Motion*)this->entity->getComponent(Unit::MOTION);
	this->motionControl = (MotionControl*)this->entity->getComponent(Unit::MOTIONCONTROL);
	this->position = (Position*)this->entity->getComponent(Unit::POSITION);
}

Position* MotionControlNode::getPosition() {
	return this->position;
}

Motion* MotionControlNode::getMotion() {
	return this->motion;
}

MotionControl* MotionControlNode::getMotionControl() {
	return this->motionControl;
}
