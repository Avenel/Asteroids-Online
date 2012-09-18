#pragma once

#include "SystemCore.h"
#include "FamilyManager.h"

class RenderSystem : public SystemCore
{
public:
	RenderSystem();
	RenderSystem(FamilyManager* familyManager);
	~RenderSystem(void);
private:
	FamilyManager* familyManager;
};
