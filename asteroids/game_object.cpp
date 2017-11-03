#include "game_object.h"


SDL_Point fpoint_to_sdl(fpoint pt) {
	return SDL_Point{ (int)std::round(pt.x()), (int)std::round(pt.y()) };
}


void game_object::draw()
{
	std::vector<SDL_Point>to_draw;

	std::transform(shp.outer().begin(), shp.outer().end(), std::back_inserter(to_draw), &fpoint_to_sdl);

	SDL_SetRenderDrawColor(Game::Instance().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderDrawLines(Game::Instance().GetRenderer(), to_draw.data(), to_draw.size());
}

void game_object::update(){
	fshape temp;
	
	mov->move(pos, shp);

	namespace t = g::strategy::transform;
	//move and center polygon around {0, 0} to rotate properly
	t::translate_transformer<float, 2, 2> set(-pos.x(), -pos.y());
	//rotate
	t::rotate_transformer<boost::geometry::radian, float, 2, 2> rot(rot_shift);
	//center polygon around its pos
	t::translate_transformer<float, 2, 2> mov(pos.x(), pos.y());
	//combine
	g::transform(shp, temp, set);
	g::transform(temp, shp, rot);
	g::transform(shp, temp, mov);
	shp = temp;

	rot_shift = 0;


}

game_object::game_object(fshape shp, fpoint pt , constant_move* mov, float rangle, float shift):
	shp{ shp }, pos{ pt }, mov{mov}, rot_angle{ rangle }, rot_shift{ shift }, dead{false}
{
}

game_object::~game_object()
{
//	delete mov;
}
