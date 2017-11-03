
//Using SDL and standard IO

#include "SDL.h"
#include "spaceship.h"
#include "Shoot.h"
#include "Game.h"
#include <stdio.h>
#include <stdexcept>
#include <iostream>
#include "types.h"
#include <vector>

std::vector<Shoot> shots{};

void loop() {
	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		auto objects = Game::Instance().get_objects_list();
		//std::cout << objects.size() << std::endl;
		dynamic_cast<spaceship*>(objects.front())->handle(&e);
		SDL_SetRenderDrawColor(Game::Instance().GetRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(Game::Instance().GetRenderer());
		for (auto i = objects.begin(); i != objects.end();) {
			auto object = *i;
			if (object->if_dead() == true) {
				i = objects.erase(i);
				continue;
			}
			object->update();
			object->draw();

			i++;

		}
		SDL_Delay(17);
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

	fshape pts{ { { 310.f, 310.f },{330.f, 310.f }, {330.f, 330.f}, {310.f, 330.f}, {310.f, 310.f } },
		{ { 310.f, 310.f },{ 330.f, 310.f },{ 330.f, 330.f },{ 310.f, 330.f },{ 310.f, 310.f } } };
	
	auto *acc = new accelerated_move{ 0.0f, 5.0f, -0.1f, -pi / 2 };
	spaceship spc{ pts, pos, dynamic_cast<constant_move*>(acc), 0.f, 0.0f };
	Game::Instance().get_objects_list().push_back(dynamic_cast<game_object_interface*>(&spc));
	loop();

	return 0;

}

