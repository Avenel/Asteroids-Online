#include "EntityManager.h"


EntityManager::EntityManager(void) {
	this->clientEntities = new std::map<int, std::map<int, std::map<int, Entity*>*> *>();
	this->entitiesFlat = new list<Entity*>();
}


EntityManager::~EntityManager(void) {
	delete this->clientEntities;
	delete this->entitiesFlat;
}

void EntityManager::addEntity(Entity *entity) {

	std::cout << "Added Entity: " << entity->getId() << ", " << entity->getClientId() << ", " << entity->getType() << endl;

	if ((*this->clientEntities)[entity->getClientId()] == 0 ) (*this->clientEntities)[entity->getClientId()] =  new std::map<int, std::map<int, Entity*>*>();
	if ((*(*this->clientEntities)[entity->getClientId()])[entity->getType()] == 0 ) (*(*this->clientEntities)[entity->getClientId()])[entity->getType()] =  new std::map<int, Entity*>();	
	(*(*(*this->clientEntities)[entity->getClientId()])[entity->getType()])[entity->getId()] = entity;

	std::cout << "Added Entity to list: " << entity->getId() << ", " << entity->getClientId() << ", " << entity->getType() << endl;
	this->entitiesFlat->push_back(entity);
}

Entity* EntityManager::getEntity(int id, int clientId, int type) {
	if ((*this->clientEntities)[clientId] == 0) return 0;
	if ((*(*this->clientEntities)[clientId])[type] == 0) return 0;

	return (*(*(*this->clientEntities)[clientId])[type])[id];
}

map<int, map<int, Entity*>*>* EntityManager::getClientEntities(int clientId) {
	return (*this->clientEntities)[clientId];
}

void EntityManager::deleteEntity(Entity *entity) {
	(*(*(*this->clientEntities)[entity->getClientId()])[entity->getType()]).erase(entity->getId());

	// Leider noch etwas "teuer" ...
	int findId = entity->getId();
	for (list<Entity*>::iterator it = this->entitiesFlat->begin(); it != this->entitiesFlat->end(); ++it) {
		if ((*it)->getId() == findId) {
			this->entitiesFlat->erase(it);
		}
	}
}

list<Entity*>* EntityManager::getAllEntitiesFlat() {
	return this->entitiesFlat;
}

std::map<int, std::map<int, std::map<int, Entity*>*> *>* EntityManager::getAllEntitiesMap() {
	return this->clientEntities;
}