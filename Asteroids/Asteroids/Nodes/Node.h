#pragma once
#include "../Entity/Entity.h"

class Node
{
public:
	Node();
	Node(Entity* entity);
	~Node(void);

	int getEntityId();
	int getEntityClientId();

	static bool isEntityMember(Entity* entity);
	virtual void addEntity();

protected:
	Entity* entity;
};
