#pragma once
#include "Unit.h"
#include "../Graphics/View.h"

class Display : public Unit
{
public:
	Display(void);
	~Display(void);
	void setDisplayObject(View* view);
	View* getDisplayObject();
private:
	View* displayObject;
};