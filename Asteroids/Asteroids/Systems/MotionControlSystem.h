#pragma once
#include <iostream>
#include <SFML\Window\Keyboard.hpp>

using namespace std;

class MotionControlSystem
{
public:
	MotionControlSystem(void);
	~MotionControlSystem(void);
	void update();
};
