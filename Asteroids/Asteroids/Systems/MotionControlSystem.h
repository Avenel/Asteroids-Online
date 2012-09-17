#pragma once
#include <iostream>
#include <SFML\Window\Keyboard.hpp>
#include "SystemCore.h"

using namespace std;

class MotionControlSystem : public SystemCore
{
public:
	MotionControlSystem(void);
	~MotionControlSystem(void);
	void update();
};
