#include "Game.h"
#include <exception>
#include <stdexcept>


Game::Game():
	objects{ *new std::list<game_object_interface*>()} {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		throw std::runtime_error(SDL_GetError());
	}

	auto wind = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 640, 0);
	if (wind == NULL) {
		throw std::runtime_error(SDL_GetError());
	}
	this->win = wind;
	auto renderer = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	
	if (renderer == NULL) {
		throw std::runtime_error(SDL_GetError());
	}
	this->render = renderer;


}

Game const & Game::Instance()
{
	try {
		static Game instance;
		return instance;
	}
	catch (std::runtime_error) {
		throw;
	}

}

SDL_Window * Game::GetWindow() const
{
	return this->win;
}

SDL_Renderer * Game::GetRenderer() const
{
	return this->render;
}

Game::~Game()
{
	if(this->render != NULL){
		SDL_DestroyRenderer(this->render);
	}
	if(this->win != NULL){
		SDL_DestroyWindow(this->win);
	}
	delete &objects;
	
}
