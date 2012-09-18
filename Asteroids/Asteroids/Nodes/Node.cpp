#include "Node.h"

Node::Node(){
}

Node::Node(Entity* entity)
{
}


Node::~Node(void)
{
}

int Node::getEntityId() {
	return this->entity->getId();
}

int Node::getEntityClientId() {
	return this->entity->getClientId();
}

bool Node::isEntityMember(Entity* entity) {
	return false;
}

void Node::addEntity() {
}
