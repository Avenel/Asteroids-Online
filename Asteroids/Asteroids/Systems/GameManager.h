#pragma once

#include "SystemCore.h"

class GameManager : public SystemCore
{
public:
	GameManager(void);
	~GameManager(void);

	void update();
};

