#pragma once
#include "Vec.h"

namespace TD
{
	enum class Axis : uint8_t { X, Y, Z, W };

	struct Vert
	{
	public:
		Vert() = default;
		Vert(const Vec3Wd & position);
		Vert(const Vec3Wd & position, const RGB & color);
		Vert(const Vec3Wd & position, const RGB & color, const Vec2u & textCoords);

		Vec3Wd position;
		RGB color = RGB(255,255,255);
		Vec2u textCoords;

		double_t& operator[](Axis index);
		const double_t& operator[](Axis index) const;
	};
}
