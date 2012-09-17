#include "Node.h"

Node::Node(){
}

Node::Node(Entity* entity)
{
	this->entity = entity;
}


Node::~Node(void)
{
	delete this->entity;
}

int Node::getEntityId() {
	return this->entity->getId();
}

int Node::getEntityClientId() {
	return this->entity->getClientId();
}
