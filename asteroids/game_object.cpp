#include "game_object.h"



void game_object::draw()
{
	std::vector<SDL_Point>to_draw;

	std::transform(shp.outer().begin(), shp.outer().end(), std::back_inserter(to_draw),
		[](fpoint pt) {return SDL_Point{ (int)std::round(pt.x()), (int)std::round(pt.y()) }; });

	SDL_SetRenderDrawColor(Game::Instance().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderDrawLines(Game::Instance().GetRenderer(), to_draw.data(), to_draw.size());
}

void game_object::update(){
	using namespace std;
	fshape temp{shp};
	auto prev_pos = pos;
	this->mov->move(pos, shp);

	
	// Create the matrix_trasformer for a simple rotation matrix


	namespace t = g::strategy::transform;
	t::translate_transformer<float, 2, 2> mov_origin(-prev_pos.x(), -prev_pos.y());
	t::rotate_transformer<boost::geometry::radian, float, 2, 2> rot(rot_shift);
	t::translate_transformer<float, 2, 2> mov_back(pos.x(), pos.y());
	//combine
	//auto update_matrix = mov_origin.matrix() - rot.matrix();
	//t::matrix_transformer<float, 2, 2> update (update_matrix);
	//g::transform(shp, temp, update);
	g::transform(temp, shp, mov_origin);
	g::transform(shp, temp, rot);
	g::transform(temp, shp, mov_back);
	//shp = temp;

	rot_shift = 0;


}

game_object::game_object(fshape shp, fpoint pt , constant_move* mov, float rangle, float shift):
	shp{ shp }, pos{ pt }, mov{mov}, rot_angle{ rangle }, rot_shift{ shift }, dead{false}
{
}

game_object::~game_object()
{
	delete mov;
}
