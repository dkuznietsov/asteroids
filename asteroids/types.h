#pragma once
#include <boost\geometry\geometries\point_xy.hpp> 
#include <boost\geometry\geometries\polygon.hpp> 
#include <boost\math\constants\constants.hpp>

namespace g = boost::geometry;


typedef g::model::d2::point_xy<float> fpoint;
typedef g::model::polygon<fpoint> fshape;

const float pi = boost::math::constants::pi<float>();
