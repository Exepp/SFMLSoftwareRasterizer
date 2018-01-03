#pragma once
#include "Vec.h"

namespace TD
{
	template <class T>
	struct AABB2
	{
	public:
		AABB2() {};
		AABB2(T left, T right, T top, T bottom);

		bool contains(const Vec2<T> & point) const;
		void setBounds(const Vec2<T> & v0, const Vec2<T> & v1, const Vec2<T> & v2);
		void clampBounds(T topB, T bottomB, T leftB, T rightB);
		
		T top;
		T bottom;
		T left;
		T right;
	};

	typedef AABB2<double_t> AABB2d;
	typedef AABB2<uint32_t> AABB2u;
	typedef AABB2<int32_t> AABB2i;

#include "AABB2.inl"

} // namespace TD

