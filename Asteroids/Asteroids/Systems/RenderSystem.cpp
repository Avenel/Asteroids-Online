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
	if(this->familyManager != 0) {
		delete this->familyManager;
	}
}

void RenderSystem::update() {
	list<Node*>* renderNodes;
	renderNodes = familyManager->getMemberOfFamilies(FamilyManager::Family::RENDER_SYSTEM);
}
