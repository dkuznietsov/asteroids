#pragma once
#include "game_object.h"
#include <boost/geometry/algorithms/centroid.hpp> 
#include <boost/geometry/strategies/cartesian/centroid_bashein_detmer.hpp> 
#include <boost\geometry\io\dsv\write.hpp>
#include <boost\geometry\strategies\transform\matrix_transformers.hpp>
#include <boost\geometry\algorithms\transform.hpp> 

class Shoot :
	public game_object
{
	short lifespan;
public:
	Shoot(fpoint &pt, float angle);
	virtual void update() override;
	~Shoot();
};

