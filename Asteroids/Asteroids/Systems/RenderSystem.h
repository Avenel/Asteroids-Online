#pragma once

#include "SystemCore.h"

class RenderSystem : public SystemCore
{
public:
	RenderSystem(FamiliyManager* familyManager);
	~RenderSystem(void);
private:
	FamilyManager* familyManager;
};
