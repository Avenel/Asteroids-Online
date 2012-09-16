#include "EntityManager.h"


EntityManager::EntityManager(void) {
	this->clientEntities = new hash_map<int, hash_map<int, list<Entity*>*> *>();
}


EntityManager::~EntityManager(void) {
	delete this->clientEntities;
}

void EntityManager::addEntity(Entity *entity) {
	this->clientEntities->find(entity->getClientId())->second->find(entity->getType())->second->push_back(entity);
}

Entity* EntityManager::getEntity(int id, int clientId, int type) {
	list<Entity*> *clientList = this->clientEntities->find(clientId)->second->find(type)->second;
	for (list<Entity*>::iterator it = clientList->begin(); it != clientList->end(); ++it) {
		if ((*it)->getId() == id) {
			return (*it);
		}
	}
	return 0;
}