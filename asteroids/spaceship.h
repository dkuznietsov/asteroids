#pragma once
#include "Game.h"
#include "game_object.h"
#include <list>
#include "shot.h"

class spaceship :
	public game_object
{
	std::list<shot> shots{};
public:
	using game_object::game_object;

	void handle();
	void shoot();

	~spaceship();
};

