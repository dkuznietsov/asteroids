#include "shot.h"


void shot::update()
{
	if (lifespan == 0) {
		dead = true;
		return;
	}
	lifespan--;
	this->game_object::update();
}


shot::~shot()
{
}
