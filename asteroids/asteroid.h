#pragma once
#include "game_object.h"
#include <random>
#include <array>
#include <numeric>
class asteroid :
	public game_object
{
public:
	using game_object::game_object;
	asteroid(float, fpoint, constant_move*, float, float);
	void update() override;
	void ast_shape();
	~asteroid();
private:
	float rad;
};

