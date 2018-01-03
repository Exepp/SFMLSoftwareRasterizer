//namespace TD	// delete
//{
	template<class T>
	inline AABB2<T>::AABB2(T left, T right, T top, T bottom)
	{
		this->left = left;
		this->right = right;
		this->top = top;
		this->bottom = bottom;
	}

	template<class T>
	inline bool AABB2<T>::contains(const Vec2<T>& point) const
	{
		return (point.x >= left && point.x <= right) && (point.y <= top  && point.y >= bottom);
	}

	template<class T>
	inline void AABB2<T>::setBounds(const Vec2<T>& v0, const Vec2<T>& v1, const Vec2<T>& v2)
	{
		top = fmin(fmin(v0.y, v1.y), v2.y);
		bottom = fmax(fmax(v0.y, v1.y), v2.y);
		left = fmin(fmin(v0.x, v1.x), v2.x);
		right = fmax(fmax(v0.x, v1.x), v2.x);
	}
	template<class T>
	inline void TD::AABB2<T>::clampBounds(T topB, T bottomB, T leftB, T rightB)
	{
		top = fmax(top, topB);
		bottom = fmin(bottom, bottomB);
		left = fmax(left, leftB);
		right = fmin(right, rightB);
	}
//}				// delete
