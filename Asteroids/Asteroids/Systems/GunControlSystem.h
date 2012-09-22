#pragma once
#include "SystemCore.h"
#include "FamilyManager.h"
#include "EntityManager.h"

class GunControlSystem : public SystemCore
{
public:
	GunControlSystem(FamilyManager* familyManager, EntityManager* entityManager);
	~GunControlSystem(void);

	void update();

private:
	FamilyManager* familyManager;
	EntityManager* entityManager;
};
