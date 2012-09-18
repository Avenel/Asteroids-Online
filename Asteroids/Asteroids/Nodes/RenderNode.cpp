#include "RenderNode.h"

RenderNode::RenderNode(Entity* entity)
{
	this->Node::Node(entity);
	//list<Unit*>* units;
	//units = entity->getAllUnits();
	//for (list<Unit*>::iterator it = units->begin(); it != units->end(); ++it) {
	//	switch((*it)->getType()) {
	//	case Unit::DISPLAY: 
	//		this->display = (Display*)(*it);
	//		break;
	//	case Unit::POSITION:
	//		this->position = (Position*)(*it);
	//		break;
	//	default:
	//		break;
	//	}
	//}
}


RenderNode::~RenderNode(void)
{
	delete this->display;
	delete this->position;
}

bool RenderNode::isEntityMember() {
	if(this->entity->hasComponent(Unit::DISPLAY) && this->entity->hasComponent(Unit::POSITION)) {
		this->addEntity();
		return true;
	}
	return false;
}

void RenderNode::addEntity() {
	this->display = (Display*)this->entity->getComponent(Unit::DISPLAY);
	this->position = (Position*)this->entity->getComponent(Unit::POSITION);
}