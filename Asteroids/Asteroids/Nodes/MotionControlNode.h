#pragma once
#include "Node.h"
#include "../Components/Motion.h"
#include "../Components/MotionControl.h"
#include "../Components/Position.h"

class MotionControlNode : public Node
{
public:
	MotionControlNode(void);
	MotionControlNode(Entity* entity);
	~MotionControlNode(void);

	Position* getPosition();
	Motion* getMotion();
	MotionControl* getMotionControl();

	static bool isEntityMember(Entity* entity);
	void addEntity();

private:
	Motion* motion;
	MotionControl* motionControl;
	Position* position;
};
