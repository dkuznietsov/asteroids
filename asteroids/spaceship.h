#pragma once
#include "game_object.h"
class spaceship :
	public game_object
{
	void shoot();
public:
	using game_object::game_object;
	void handle(SDL_Event*);
};

