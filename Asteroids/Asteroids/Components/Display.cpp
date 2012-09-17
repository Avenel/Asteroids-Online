#include "Display.h"


Display::Display(void)
{
}


Display::~Display(void)
{
}

void Display::setDisplayObject(View* view) {
	this->displayObject = view;
}

View* Display::getDisplayObject() {
	return this->displayObject;
}
