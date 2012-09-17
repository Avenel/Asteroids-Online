#include "RenderNode.h"

RenderNode::RenderNode(Entity* entity)
{
	//::Node(entity);
	list<Unit*>* units;
	units = entity->getAllUnits();
	for (list<Unit*>::iterator it = units->begin(); it != units->end(); ++it) {
		switch((*it)->getType()) {
		case Unit::DISPLAY: 
			this->display = (Display*)(*it);
			break;
		case Unit::POSITION:
			this->position = (Position*)(*it);
			break;
		default:
			break;
		}
	}
}


RenderNode::~RenderNode(void)
{
	delete this->display;
	delete this->position;
}
