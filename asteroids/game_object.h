#pragma once
#include "game_obj_interface.h"
#include "game_obj_inetrfaces.h"
#include "Game.h"
#include "types.h"
#include <iostream>
#include <boost\geometry\strategies\transform\matrix_transformers.hpp>
#include <boost\geometry\algorithms\transform.hpp> 


class game_object :public game_object_interface {
protected:
	fshape shp;
	fpoint pos;

	constant_move* mov;

	float rot_angle;
	float rot_shift;

	bool dead;
public:
	virtual void draw() override;
	virtual void update() override;
	virtual bool if_dead() override { return dead; }
	
	game_object(fshape, fpoint, constant_move*, float, float);
	~game_object();
};

