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
