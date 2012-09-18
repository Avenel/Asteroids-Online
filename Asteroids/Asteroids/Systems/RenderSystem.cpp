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
}

void RenderSystem::update() {
	list<Node*>* renderNodes;
	renderNodes = familyManager->getMemberOfFamilies(FamilyManager::Family::RENDER_SYSTEM);

	Position *position;
	Display *display;

	for (list<Node*>::iterator it = renderNodes->begin(); it != renderNodes->end(); ++it) {
		position = ((RenderNode*)(*it))->getPosition();
		display = ((RenderNode*)(*it))->getDisplay();
		display->setPosition(position->getX(), position->getY());
		display->draw(this->window, sf::RenderStates());
	}

}
