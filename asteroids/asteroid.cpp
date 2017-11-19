#include "asteroid.h"




asteroid::asteroid(float rad, fpoint pos , constant_move * mov, float rot_angle, float rot_shift)
	:rad{ rad }, game_object{ fshape{}, pos, mov, rot_angle, rot_shift }
{
	ast_shape();
}

void asteroid::update()
{
	//TODO:FIX:\
		//make new ierarrchy or whatever to exclude saved

	auto saved = rot_shift;
	game_object::update();
	rot_shift = saved;
}

void asteroid::ast_shape()
{
	std::random_device r{};
	std::default_random_engine rand{r()};
	std::uniform_int_distribution<unsigned short> num_gen(5, 12);
	int num_of_pts = num_gen(rand);
	std::uniform_int_distribution<unsigned short> angle_gen(0, 100);
	std::vector<float> r_indexes(num_of_pts);
	std::vector<fpoint> pts(num_of_pts);
	std::generate(r_indexes.begin(), r_indexes.end(), [&rand, &angle_gen]() {return (float)angle_gen(rand); });
	float sum = std::accumulate(r_indexes.begin(), r_indexes.end(), 0.f);
	for (float& a : r_indexes) {
		a /= sum / 2 / pi;
	}

	float acumulate_angle = 0.f;
	float const_rad_part = rad / 4.f;
	float rand_rad_part = rad - const_rad_part;
	std::uniform_int_distribution<int> rad_gen{ 0, 30 };

	for(auto i = 0; i < num_of_pts; i++) {
		float temp_rad = (float)rand_rad_part*rad_gen(rand)/rad_gen.max() + const_rad_part;
		acumulate_angle += r_indexes[i];
		pts[i] = {std::cos(acumulate_angle)*temp_rad,
				  std::sin(acumulate_angle)*temp_rad };
	}
	pts.push_back(pts.front());
	g::assign_points(shp, pts);

	auto temp = shp;
	g::strategy::transform::translate_transformer<float, 2, 2> adjust_to_center(pos.x(), pos.y());
	g::transform(temp, shp, adjust_to_center);
}

asteroid::~asteroid()
{
}
