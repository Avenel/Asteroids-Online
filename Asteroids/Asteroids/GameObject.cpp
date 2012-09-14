#include "GameObject.h"


GameObject::GameObject(void)
{
}

GameObject::GameObject(int id)
{
	this->id = id;
}

GameObject::~GameObject(void)
{
}

void GameObject::refresh(Packet packet)
{
	packet >> this->id >> this->x >> this->y;
}

int GameObject::getId() 
{ 
	return this->id;
}

int GameObject::getX()
{
	return this->x;
}

int GameObject::getY()
{
	return this->y;
}

void GameObject::setId(int id)
{
	this->id = id;
}
void GameObject::setX(int x)
{
	this->x = x;
}

void GameObject::setY(int y)
{
	this->y = y;
}