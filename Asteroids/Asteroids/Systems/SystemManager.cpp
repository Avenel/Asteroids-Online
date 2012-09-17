#include "SystemManager.h"


SystemManager::SystemManager(void) {
	this->systems = new list<SystemCore*>();
}


SystemManager::~SystemManager(void) {
	delete this->systems;
}

void SystemManager::addSystem(SystemCore* system) {
	this->systems->push_back(system);
}

void SystemManager::updateSystems() {
	for (list<SystemCore*>::iterator it = this->systems->begin(); it != this->systems->end(); ++it) {
		(*it)->update();
	}
}
