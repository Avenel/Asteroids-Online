#pragma once

#include "Node.h"
#include "../Components/Display.h"
#include "../Components/Position.h"

class RenderNode : public Node
{
public:
	RenderNode(Entity* entity);
	~RenderNode(void);

private:
	Position* position;
	Display* display;
};
