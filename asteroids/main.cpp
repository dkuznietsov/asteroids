
//Using SDL and standard IO

#include "SDL.h"
#include "Game.h"
#include <stdio.h>
#include <stdexcept>
#include <iostream>
#include "types.h"
#include <vector>
#include "game_object.h"
#include "game_obj_inetrfaces.h"
#include "spaceship.h"
#include "asteroid.h"


//std::vector<Shoot> shots{};

void loop() {
	bool quit = false;
	
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		auto begin_time = SDL_GetTicks();
		//auto objects = Game::Instance().get_objects_list();
		//std::cout << objects.size() << std::endl;
		auto temp = dynamic_cast<spaceship*>(Game::Instance().get_objects_list().front().get());
		//std::list<int> objects{};
		temp->handle();

		SDL_SetRenderDrawColor(Game::Instance().GetRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(Game::Instance().GetRenderer());

		for (auto i = Game::Instance().get_objects_list().begin(); i != Game::Instance().get_objects_list().end();) {
			//auto object = *i;
			if ((*i)->if_dead() == true) {
				Game::Instance().get_objects_list().erase(i++);
				continue;
			}
			(*i)->update();
			(*i)->draw();
			i++;

		}
		auto end_time = SDL_GetTicks();
		auto frame_time = end_time - begin_time;
		if (frame_time <= 17) {
			SDL_Delay(17 - frame_time);
		}
		else
		{

			SDL_Delay(17);
		}
		
		SDL_RenderPresent(Game::Instance().GetRenderer());
	}
}


int main(int argc, char* args[])
{
	try {
		Game::Instance();
	}
	catch (std::runtime_error &err) {
		std::cout << err.what() << std::endl;
		return 0;

	}
	fpoint pos(320.0f, 320.0f);

	fshape pts{ { { 310.f, 310.f },{330.f, 310.f }, {330.f, 330.f}, {310.f, 330.f}, {310.f, 310.f } }};
	
	constant_move* mov = new spaceship_move(0.0f, 5.0f, -0.1f, -pi / 2);
	auto ptr = std::make_unique<spaceship>( pts, pos, mov, 0.f, 0.0f );

	Game::Instance().get_objects_list().push_back(std::move(ptr));
	

	auto ast_mov = new constant_move(5.f, pi / 5, 20.f);
	auto ast_ptr = std::make_unique<asteroid>(50.f, pos, ast_mov, 0.f, 0.2f);
	Game::Instance().get_objects_list().push_back(std::move(ast_ptr));
	loop();

	return 0;

}

