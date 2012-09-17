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

private:
	list<SystemCore*> *systems;
};

