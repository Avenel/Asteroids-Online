#pragma once
#include "Node.h"
#include "../Components/Motion.h"
#include "../Components/Position.h"

class MovementNode : public Node
{
public:
	MovementNode(void);
	MovementNode(Entity* entity);
	~MovementNode(void);

	Position* getPosition();
	Motion* getMotion();

	static bool isEntityMember(Entity* entity);
	void addEntity();

private:
	Motion* motion;
	Position* position;
};
