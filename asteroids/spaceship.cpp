#include "spaceship.h"
#include <boost\geometry\strategies\transform\matrix_transformers.hpp>
#include <boost\geometry\algorithms\transform.hpp> 

void spaceship::handle()
{
	auto state = SDL_GetKeyboardState(NULL);


	float change_vel = 0.f;
	float change_angle = 0.f;
	auto spc_mov = dynamic_cast<spaceship_move*>(mov);

	if (spc_mov == nullptr) {
		std::cout << "error" <<std::endl;
	}

	if (state[SDL_SCANCODE_UP]) {
		change_vel += 10.f;
	}
	if (state[SDL_SCANCODE_DOWN]) {
		change_vel -= 10.f;
	}
	if (state[SDL_SCANCODE_LEFT]) {
		change_angle -= 0.1f;
	}
	if (state[SDL_SCANCODE_RIGHT]) {
		change_angle += 0.1f;
	}
	if (state[SDL_SCANCODE_SPACE]) {
		shoot();
	}
	spc_mov->add(change_vel, change_angle);

	//Look into rotate func
	this->rot_shift -= change_angle;

}

void spaceship::shoot()
{
	
	fshape shot_shp{ { { 0.f, 0.f },{ 10.f, 0.f },{ 10.f, 3.f },{ 0.f, 3.f },{ 0.f, 0.f } }};
	fshape temp;

	namespace t = g::strategy::transform;
	//rotate
	t::rotate_transformer<boost::geometry::radian, float, 2, 2> rot(-mov->get_angle());
	//center polygon around its pos
	t::translate_transformer<float, 2, 2> move(pos.x(), pos.y());
	//combine
	g::transform(shot_shp, temp, rot);
	g::transform(temp, shot_shp, move);

	auto ptr = std::make_unique<shot>(shot_shp, pos, new constant_move(20.f, mov->get_angle(), 20.f), rot_angle, rot_shift);
	Game::Instance().get_objects_list().push_back(std::move(ptr));

}

spaceship::~spaceship()
{
	//delete mov;
}
