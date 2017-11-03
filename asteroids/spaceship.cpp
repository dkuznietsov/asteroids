#include "spaceship.h"
#include "Shoot.h"
#include "Game.h"
#include <vector>

extern std::vector<Shoot> shots;
void spaceship::shoot()
{
	
	fpoint front_pt{ pos.x() + 10 * std::cos(mov->get_angle()), pos.y() + 10 * std::sin(mov->get_angle()) };
	Shoot sh{ front_pt, mov->get_angle() };

	shots.push_back(sh);

	Game::Instance().get_objects_list().push_back(dynamic_cast<game_object_interface*>(&shots.back()));

	//getchar();

}

void spaceship::handle(SDL_Event *)
{
	auto state = SDL_GetKeyboardState(NULL);
	float shift_vel = 0.0f;
	float shift_angle = 0.0f;

	if (state[SDL_SCANCODE_UP]) {
		shift_vel += 3;
	}
	if (state[SDL_SCANCODE_DOWN]) {
		shift_vel -= 3;

	}
	if (state[SDL_SCANCODE_LEFT]) {
		shift_angle -= 0.1f;
	}
	if (state[SDL_SCANCODE_RIGHT]) {
		shift_angle += 0.1f;
	}

	if (state[SDL_SCANCODE_SPACE]) {
		shoot();
	}

	mov->add(shift_vel, shift_angle);
	rot_shift += shift_angle;

}