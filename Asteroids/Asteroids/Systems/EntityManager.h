#pragma once

#include "..\Entity\Entity.h"
#include <list>
#include <hash_map>

class EntityManager
{
public:
	EntityManager(void);
	~EntityManager(void);

	void addEntity(Entity *newEntity);
	Entity* getEntity(int id, int clientId, int type);
	hash_map<int, list<Entity*>*>* getClientEntities(int clientId);

private:
	/** Es gibt 2 Hashmaps + 1 Liste:	1) Geordnet nach ClientIds
										2) Geordnet nach Types
										3) enthält Liste der Entities
	*/
			//clientid     type		entities      
	hash_map<int, hash_map<int, list<Entity*>*> *> *clientEntities;
};

