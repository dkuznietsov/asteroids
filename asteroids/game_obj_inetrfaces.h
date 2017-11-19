#pragma once
#include "types.h"
#include <iostream>
#include <boost\geometry\strategies\transform\matrix_transformers.hpp>
#include <boost\geometry\algorithms\transform.hpp> 


class constant_move{
protected:
	float vel;
	float angle;
	float max_spd;
public:
	constant_move(float velocity, float angle, float max_speed)
		:vel{ velocity }, angle{ angle }, max_spd{max_speed} {};
	virtual void move(fpoint& pt, fshape &shp){
		fshape temp;
		if (vel > max_spd) vel = max_spd;
		if (vel < 0) vel = 0;

		if (angle > 2 * pi) angle -= 2 * pi;
		if (angle < 0) angle += 2 * pi;

		float shift_x = vel * std::cos(angle);
		float shift_y = vel * std::sin(angle);

		//repair
		if (pt.x() > 640.0f) shift_x -= 640.f;
		if (pt.x() < 0.0f) shift_x += 640.f;
		if (pt.y() > 640.0f) shift_y -= 640.f;
		if (pt.y() < 0.0f) shift_y += 640.f;


		pt.x(pt.x() + shift_x);
		pt.y(pt.y() + shift_y);

		namespace t = g::strategy::transform;
		t::translate_transformer<float, 2, 2> mov(shift_x, shift_y);
		g::transform(shp, temp, mov);
		shp = temp;
	}

	float get_angle() { return angle; }
	float get_velocity() { return vel; }
	virtual ~constant_move() {
	}

};

class accelerated_move : public constant_move {
protected:
	float acc;
public:
	accelerated_move(float velocity, float max_speed, float acceleration, float angle)
		:constant_move{ velocity, angle, max_speed }, acc{ acceleration } {};
	virtual void move(fpoint &pt, fshape& shp) override{
		vel += acc;
		constant_move::move(pt, shp);
	}
	virtual ~accelerated_move() {}
};

class spaceship_move : public accelerated_move {
public:
	using accelerated_move::accelerated_move;
	void add(float velocity, float angle) {
		this->angle += angle;
		this->vel += velocity;
	}
	~spaceship_move() {}
};

