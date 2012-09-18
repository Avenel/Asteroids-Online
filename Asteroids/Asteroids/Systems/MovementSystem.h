#pragma once
#include "SystemCore.h"
#include "FamilyManager.h"

class MovementSystem : public SystemCore
{
public:
	MovementSystem(void);
	MovementSystem(FamilyManager* familyManager);
	~MovementSystem(void);
	void update();

	private:
	FamilyManager* familyManager;
};
