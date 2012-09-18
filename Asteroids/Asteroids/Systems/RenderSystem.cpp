#include "RenderSystem.h"

RenderSystem::RenderSystem()
{
	this->familyManager = 0;
}

RenderSystem::RenderSystem(FamilyManager* familyManager)
{
	this->familyManager = familyManager;
}


RenderSystem::~RenderSystem(void)
{
}
