#pragma once

#include "..\Entity\Entity.h"
#include <list>
#include <map>

class EntityManager
{
public:
	EntityManager(void);
	~EntityManager(void);

	void addEntity(Entity *newEntity);
	Entity* getEntity(int id, int clientId, int type);
	map<int, map<int, Entity*>*>* getClientEntities(int clientId);
	list<Entity*> getAlleEntities();
	void deleteEntity(Entity *entity);

private:
	/** Es gibt 3 Hashmaps:	1) Geordnet nach ClientIds
							2) Geordnet nach Types
							3) Geordnet nach Entities
	*/
			//clientid     type		entities      
	std::map<int, std::map<int, std::map<int, Entity*>*> *> *clientEntities;

	// Flache Hierarchie um schnell alle Entities durchgehen zu können
	list<Entity*> *entitiesFlat;
};

