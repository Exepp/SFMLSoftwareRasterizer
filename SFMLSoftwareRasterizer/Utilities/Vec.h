#pragma once
#include <iostream>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <iomanip>

namespace TD
{


	template<class T>
	struct Vec2
	{
		template <typename U>
		explicit Vec2(const Vec2<U> & vec);
		Vec2(T x, T y);
		Vec2();

		T			length() const;
		Vec2<T>		normalized() const;
		Vec2<T>&	normalize();

		T x;
		T y;

		static const Vec2<T> zeroVector;
		static const Vec2<T> oneVector;
	};

	template<class T>
	const Vec2<T> Vec2<T>::zeroVector = Vec2<T>(0, 0);
	template<class T>
	const Vec2<T> Vec2<T>::oneVector = Vec2<T>(1, 1);

	template<class T>
	struct Vec3
	{		
		template <typename U>
		explicit Vec3(const Vec3<U> & vec);
		Vec3(T x, T y, T z);
		Vec3();

		T			length() const;
		T			dotProduct(const Vec3<T> & vec) const;
		Vec3<T>		crossProduct(const Vec3<T> & vec) const;
		Vec3<T>		normalized() const;
		Vec3<T>&	normalize();

		T x;
		T y;
		T z;

		static const Vec3<T> zeroVector;
		static const Vec3<T> oneVector;
	};

	template<class T>
	const Vec3<T> Vec3<T>::zeroVector = Vec3<T>(0,0,0);
	template<class T>
	const Vec3<T> Vec3<T>::oneVector = Vec3<T>(1,1,1);


	template<class T>
	struct Vec3W : public Vec3<T>
	{
		template <typename U>
		explicit Vec3W(const Vec3W<U> & vec);
		 Vec3W(const Vec3<T> & vec);
		 Vec3W(T x, T y, T z, T w = 1);
		explicit Vec3W();

		Vec3W<T>&	normalizeW();

		T w;
	};

	typedef Vec2<int32_t>	Vec2i;
	typedef Vec2<uint32_t>	Vec2u;
	typedef Vec2<double_t>	Vec2d;

	typedef Vec3<int32_t>	Vec3i;
	typedef Vec3<uint32_t>	Vec3u;
	typedef Vec3<double_t>	Vec3d;
	typedef Vec3<uint8_t>	RGB;

	typedef Vec3W<int32_t>	Vec3Wi;
	typedef Vec3W<uint32_t>	Vec3Wu;
	typedef Vec3W<double_t>	Vec3Wd;

#include "Vec.inl"		// operators, definitions

}	// namespace TD