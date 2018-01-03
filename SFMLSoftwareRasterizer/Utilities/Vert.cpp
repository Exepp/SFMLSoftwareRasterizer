#include "Vert.h"

using namespace TD;

TD::Vert::Vert(const Vec3Wd & position) : position(position)
{
}

TD::Vert::Vert(const Vec3Wd & position, const RGB & color) : position(position), color(color)
{
}


TD::Vert::Vert(const Vec3Wd & position, const RGB & color, const Vec2u & textCoords) : position(position), color(color), textCoords(textCoords)
{

}

double_t & TD::Vert::operator[](Axis index)
{
	if (index == Axis::X)
		return position.x;
	if (index == Axis::Y)
		return position.y;
	if (index == Axis::Z)
		return position.z;
	return position.w;
}

const double_t & TD::Vert::operator[](Axis index) const
{
	if (index == Axis::X)
		return position.x;
	if (index == Axis::Y)
		return position.y;
	if (index == Axis::Z)
		return position.z;
	return position.w;
}
