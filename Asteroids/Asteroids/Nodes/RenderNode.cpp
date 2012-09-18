#include "RenderNode.h"

RenderNode::RenderNode()
{
}

RenderNode::RenderNode(Entity* entity)
{
	this->Node::Node(entity);
	this->addEntity();
}


RenderNode::~RenderNode(void)
{
}

bool RenderNode::isEntityMember(Entity* entity) {
	return (entity->hasComponent(Unit::DISPLAY) && entity->hasComponent(Unit::POSITION));
}

void RenderNode::addEntity() {
	this->display = (Display*)this->entity->getComponent(Unit::DISPLAY);
	this->position = (Position*)this->entity->getComponent(Unit::POSITION);
}