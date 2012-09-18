#pragma once

#include "Node.h"
#include "../Components/Display.h"
#include "../Components/Position.h"

class RenderNode : public Node
{
public:
	RenderNode();
	RenderNode(Entity* entity);
	~RenderNode(void);
	static bool isEntityMember(Entity* entity);
	void addEntity();

	Position* getPosition();
	Display* getDisplay();

private:
	Position* position;
	Display* display;
};
