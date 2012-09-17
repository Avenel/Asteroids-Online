#pragma once
#include "Unit.h"

class Motion : public Unit
{
public:
	Motion(void);
	~Motion(void);

private:
	float speedX;
	float speedY;
	float damping;
};

