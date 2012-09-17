#pragma once
#include "../Entity/Entity.h"

class Node
{
public:
	Node();
	Node(Entity* entity);
	~Node(void);
private:
	Entity* entity;
};
