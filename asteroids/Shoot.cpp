#include "Shoot.h"

const fshape pts{ { { 0.f, -1.f },{ 10.f, -1.f },{ 10.f, 1.f },{ 0.f, -1.f },{ 0.f, -1.f } },
{ { 0.f, -1.f },{ 10.f, -1.f },{ 10.f, 1.f },{ 0.f, -1.f },{ 0.f, -1.f } } };

const short shoot_lifespan = 20;

const float max_shoot_vel = 20.f;

Shoot::Shoot(fpoint & pt, float angle):
	game_object{ pts, fpoint{ 0.f, 0.f }, new constant_move{max_shoot_vel, angle, max_shoot_vel}, 0.f, angle }, lifespan{shoot_lifespan}
{
	fshape temp;

	namespace t = g::strategy::transform;
	t::translate_transformer<float, 2, 2> mov(pt.x(), pt.y());
	g::transform(shp, temp, mov);
	shp = temp;

	g::strategy::centroid::bashein_detmer<fpoint>strat;
	g::centroid<fshape, fpoint, g::strategy::centroid::bashein_detmer<fpoint>>(shp, pos, strat);

}

void Shoot::update(){
	lifespan--;
	if (lifespan == 0) {
		dead = true;
		return;
	}
	this->game_object::update();
}

Shoot::~Shoot()
{
}
