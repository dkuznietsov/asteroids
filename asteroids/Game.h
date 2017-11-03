#pragma once
#include "SDL.h"
#include <list>
#include <vector>
#include <iostream>
#include "game_obj_interface.h"


class Game
{
public:
	Game(Game&) = delete;
	Game& operator=(Game&) = delete;

	static const Game& Instance();

	SDL_Window* GetWindow() const;
	SDL_Renderer* GetRenderer() const;
	std::list<game_object_interface*> &get_objects_list() const {return objects; }

private:
	//methods
	Game();
	~Game();
	//properties
	SDL_Window * win;
	SDL_Renderer * render;
	std::list<game_object_interface*> &objects;
};

