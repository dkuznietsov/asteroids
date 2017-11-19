#pragma once
#include "game_object.h"
class shot :
	public game_object
{
	short lifespan = 60;
public:
	using game_object::game_object;
	void update() override;
	~shot();
};

