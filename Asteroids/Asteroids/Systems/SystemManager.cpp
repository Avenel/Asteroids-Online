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
