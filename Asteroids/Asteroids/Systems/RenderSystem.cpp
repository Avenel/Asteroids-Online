#include "RenderSystem.h"

RenderSystem::RenderSystem()
{
	this->familyManager = 0;
}

RenderSystem::RenderSystem(FamilyManager* familyManager, sf::RenderWindow *window) {
	this->familyManager = familyManager;
	this->window = window;
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

	for (list<Node*>::iterator it = renderNodes->begin(); it != renderNodes->end(); ++it) {
	}

}
