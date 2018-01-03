#pragma once
#include <cstdint>
#include "Vec.h"
namespace TD
{
	class Matrix 
	{
	public:
		Matrix();
		
		Matrix transpose() const;


		const double_t*	operator()(uint8_t i) const;
		const double_t&	operator()(uint8_t i, uint8_t j) const;
		double_t*		operator()(uint8_t i);
		double_t&		operator()(uint8_t i, uint8_t j);


		double_t m[4][4];

		static const Matrix identityMatrix;
	};

	Matrix operator*(const Matrix & left, const Matrix& right);
	Vec3Wd operator*(const Vec3Wd & left, const Matrix & right);
	std::ostream& operator<<(std::ostream& os, const Matrix & m);

} // namespace TD