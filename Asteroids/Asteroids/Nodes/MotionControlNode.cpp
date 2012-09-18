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
	return false;
}

void MotionControlNode::addEntity() {
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
