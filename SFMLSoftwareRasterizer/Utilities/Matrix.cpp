#include "Matrix.h"
#include <stdexcept>
#include <string>
#include <iomanip>

using namespace TD;

const Matrix Matrix::identityMatrix;

Matrix::Matrix()
{
	for (uint8_t i = 0; i < 4; i++)
		for (uint8_t j = 0; j < 4; j++)
			m[i][j] = uint8_t(i == j);
}

Matrix Matrix::transpose() const
{
	Matrix transpM;

	for (uint8_t i = 0; i < 4; i++)
		for (uint8_t j = 0; j < 4; j++)
			transpM(i, j) = m[j][i];

	return transpM;
}

// operators:


const double_t * Matrix::operator()(uint8_t i) const
{
	if (i < 4)
		return m[i];
	else throw std::out_of_range(std::string("Index out of array's range: ") + std::to_string(i));
}


const double_t& Matrix::operator()(uint8_t i, uint8_t j) const
{
	if (i < 4 && j < 4)
		return m[i][j];
	else throw std::out_of_range(std::string("Index out of array's range: ") + std::to_string(i) + std::to_string(j));
}


double_t * Matrix::operator()(uint8_t i)
{
	if (i < 4)
		return m[i];
	else throw std::out_of_range(std::string("Index out of array's range: ") + std::to_string(i));
}


double_t & Matrix::operator()(uint8_t i, uint8_t j)
{
	if (i < 4 && j < 4)
		return m[i][j];
	else throw std::out_of_range(std::string("Index out of array's range: ") + std::to_string(i) + std::to_string(j));
}


Matrix TD::operator*(const Matrix & left, const Matrix& right)
{
	Matrix product;
	for (uint8_t i = 0; i < 4; i++)
		for (uint8_t j = 0; j < 4; j++)
		{
			product(i, j) = 0;
			for (uint8_t k = 0; k < 4; k++)
				product(i, j) += left(i, k) * right(k, j);
		}
	return product;
}

TD::Vec3Wd TD::operator*(const Vec3Wd & left, const Matrix & right)
{
	return Vec3Wd (	right.m[0][0] * left.x + right.m[1][0] * left.y + right.m[2][0] * left.z + right.m[3][0],
					right.m[0][1] * left.x + right.m[1][1] * left.y + right.m[2][1] * left.z + right.m[3][1],
					right.m[0][2] * left.x + right.m[1][2] * left.y + right.m[2][2] * left.z + right.m[3][2],
					right.m[0][3] * left.x + right.m[1][3] * left.y + right.m[2][3] * left.z + right.m[3][3]);
}

std::ostream & TD::operator<<(std::ostream & os, const Matrix & m)
{
	os.precision(2);
	for (uint8_t i = 0; i < 4; i++)
	{
		os << std::endl;
		for (uint8_t j = 0; j < 4; j++)
			os << std::setw(8) << ((abs(m(i, j)) > 0.0001) ? m(i, j) : 0);
	}
	os << std::endl;
	return os;
}
