#pragma once

#include <list>
#include "SystemCore.h"

using namespace std;

class SystemManager
{
public:
	SystemManager(void);
	~SystemManager(void);

	void addSystem(SystemCore *system);

	void updateSystems();

private:
	list<SystemCore*> *systems;
};

