#pragma once

#include "Node.h"
#include "../Components/Display.h"
#include "../Components/Position.h"

class RenderNode : public Node
{
public:
	RenderNode(Entity* entity);
	~RenderNode(void);
	bool isEntityMember();
	void addEntity();


private:
	Position* position;
	Display* display;
};
