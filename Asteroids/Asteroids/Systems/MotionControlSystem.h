#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <SFML\Window\Keyboard.hpp>
#include "SystemCore.h"
#include "FamilyManager.h"

using namespace std;

class MotionControlSystem : public SystemCore
{
public:
	MotionControlSystem(void);
	MotionControlSystem(FamilyManager* familyManager);
	~MotionControlSystem(void);
	void update();

private:
	FamilyManager* familyManager;
};
