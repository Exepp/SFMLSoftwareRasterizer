
template<class T>
template<class U>
inline Vec2<T>::Vec2(const Vec2<U>& vec) : x(T(vec.x)), y(T(vec.y))
{
}

template<class T>
inline Vec2<T>::Vec2(T x, T y) : x(x), y(y)
{
}

template<class T>
inline Vec2<T>::Vec2() : x(0), y(0)
{
}

template<class T>
inline T Vec2<T>::length() const
{
	return sqrt(x * x + y * y);
}

template<class T>
inline Vec2<T> Vec2<T>::normalized() const
{
	return Vec2<T>(*this).normalize();
}

template<class T>
inline Vec2<T>& Vec2<T>::normalize()
{
	T leng = length();
	if (leng)
	{
		x /= leng;
		y /= leng;
	}

	return *this;
}


////////////////////////////////////////////////////////// Vec3 //////////////////////////////////////////////////////////

template<class T>
template<typename U>
inline Vec3<T>::Vec3(const Vec3<U>& vec) : x(T(vec.x)), y(T(vec.y)), z(T(vec.z))
{
}

template<class T>
inline Vec3<T>::Vec3(T x, T y, T z) : x(x), y(y), z(z){}

template<class T>
inline Vec3<T>::Vec3() : x(0), y(0), z(0){}

template<class T>
inline T Vec3<T>::length() const
{
	return sqrt(x * x + y * y + z * z);
}

template<class T>
inline T Vec3<T>::dotProduct(const Vec3<T>& vec) const
{
	return  x * vec.x + y * vec.y + z * vec.z;;
}

template<class T>
inline Vec3<T> Vec3<T>::crossProduct(const Vec3<T>& vec) const
{
	Vec3<T> perp;

	perp.x = y * vec.z - z * vec.y;
	perp.y = z * vec.x - x * vec.z;
	perp.z = x * vec.y - y * vec.z;

	return perp;
}

template<class T>
inline Vec3<T> Vec3<T>::normalized() const
{
	return Vec3<T>(*this).normalize();
}

template<class T>
inline Vec3<T>& Vec3<T>::normalize()
{
	T leng = length();
	if (leng)
	{
		x /= leng;
		y /= leng;
		z /= leng;
	}
	return *this;
}


////////////////////////////////////////////////////////// Vec3W //////////////////////////////////////////////////////////


template<class T>
template<typename U>
inline Vec3W<T>::Vec3W(const Vec3W<U>& vec) : Vec3(vec)
{
	w = vec.w;
}

template<class T>
inline TD::Vec3W<T>::Vec3W(const Vec3<T>& vec) : Vec3(vec)
{
}

template<class T>
inline TD::Vec3W<T>::Vec3W(T x, T y, T z, T w) : Vec3(x, y, z)
{
	this->w = w;
}

template<class T>
inline TD::Vec3W<T>::Vec3W() : Vec3() 
{
	w = 1;
}

template<class T>
inline Vec3W<T>& Vec3W<T>::normalizeW()
{
	if (w != 1)
	{
		x /= w;
		y /= w;
		z /= w;
		w = 1;
	}
	return *this;
}

////////////////////////////////////////////////////////// operators //////////////////////////////////////////////////////////


template<class T>
inline Vec2<T> operator+(const Vec2<T> & left, const Vec2<T> & right)
{
	return Vec2<T>(left.x + right.x, left.y + right.y);
}

template<class T>
inline Vec2<T> operator-(const Vec2<T> & left, const Vec2<T> & right)
{
	return Vec2<T>(left.x - right.x, left.y - right.y);
}

template<class T>
inline Vec2<T> operator-(const Vec2<T> & right)
{
	return Vec2<T>(-right.x, -right.y);
}

template<class T, class U>
inline Vec2<T> operator*(const Vec2<T> & left, U right)
{
	return Vec2<T>(left.x * right, left.y * right);
}

template<class T, class U>
inline Vec2<T> operator*(U left, const Vec2<T> & right)
{
	return Vec2<T>(left * right.x, left * right.y);
}

// if right == 0, returns zero vector
template<class T>
inline Vec2<T> operator/(const Vec2<T> & left, T right)
{
	if (right)
		return Vec2<T>(left.x / right, left.y / right);
	else
		return Vec2<T>();
}

template<class T>
inline Vec2<T> operator/(T left, const Vec2<T> & right)
{
	return Vec2<T>(right.x != 0 ? left / right.x : 0, right.y != 0 ? left / right.y : 0);
}

template<class T>
inline Vec2<T>& operator+=(Vec2<T> & left, const Vec2<T> & right)
{
	left.x += right.x;
	left.y += right.y;
	return left;
}

template<class T>
inline Vec2<T>& operator-=(Vec2<T> & left, const Vec2<T> & right)
{
	left.x -= right.x;
	left.y -= right.y;
	return left;
}

template<class T>
inline Vec2<T>& operator*=(Vec2<T> & left, T right)
{
	left.x *= right.x;
	left.y *= right.y;
	return left;
}

// if right == 0, returns zero vector
template<class T>
inline Vec2<T>& operator/=(Vec2<T> & left, T right)
{
	if (right)
	{
		left.x /= right;
		left.y /= right;
	}
	else
		left = Vec2<T>();
	return left;
}

template<class T>
inline bool operator==(const Vec2<T> & left, const Vec2<T> & right)
{
	return left.x == right.x && left.y == right.y;
}

template<class T>
inline bool operator!=(const Vec2<T> & left, const Vec2<T> & right)
{
	return !(left == right);
}


template<class T>
std::ostream& operator<<(std::ostream& os, const Vec2<T>& v)
{
	os.precision(3);
	os.setf(std::ios::fixed);
	os << "x: " << std::setprecision(3) << std::setw(10) << v.x << "   ";
	os << "y: " << std::setprecision(3) << std::setw(10) << v.y << "   ";
	os << std::endl;
	return os;
}


////////////////////////////////////////////////////////// Vec3 //////////////////////////////////////////////////////////


template<class T>
inline Vec3<T> operator+(const Vec3<T> & left, const Vec3<T> & right)
{
	return Vec3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}

template<class T>
inline Vec3<T> operator-(const Vec3<T> & left, const Vec3<T> & right)
{
	return Vec3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}

template<class T>
inline Vec3<T> operator-(const Vec3<T> & right)
{
	return Vec3<T>(-right.x, -right.y, -right.z);
}

template<class T>
inline Vec3<T> operator*(const Vec3<T> & left, double_t right)
{
	return Vec3<T>(left.x * right, left.y * right, left.z * right);
}

template<class T>
inline Vec3<T> operator*(double_t left, const Vec3<T> & right)
{
	return Vec3<T>(left * right.x, left * right.y, left * right.z);
}

// if right == 0, returns zero vector
template<class T>
inline Vec3<T> operator/(const Vec3<T> & left, double_t right)
{
	if (right)
		return Vec3<T>(left.x / right, left.y / right, left.z / right);
	else
		return Vec3<T>();
}

template<class T>
inline Vec3<T> operator/(double_t left, const Vec3<T> & right)
{
	return Vec3<T>(right.x != 0 ? left / right.x : 0, right.y != 0 ? left / right.y : 0, right.z != 0 ? left / right.z : 0);
}

template<class T>
inline Vec3<T>& operator+=(Vec3<T> & left, const Vec3<T> & right)
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;
	return left;
}

template<class T>
inline Vec3<T>& operator-=(Vec3<T> & left, const Vec3<T> & right)
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;
	return left;
}

template<class T>
inline Vec3<T>& operator*=(Vec3<T> & left, T right)
{
	left.x *= right;
	left.y *= right;
	left.z *= right;
	return left;
}

// if right == 0, returns zero vector
template<class T>
inline Vec3<T>& operator/=(Vec3<T> & left, T right)
{
	if (right)
	{
		left.x /= right;
		left.y /= right;
		left.z /= right;
	}
	else
		left = Vec3<T>();
	return left;
}

template<class T>
inline bool operator==(const Vec3<T> & left, const Vec3<T> & right)
{
	return left.x == right.x && left.y == right.y && left.z == right.z;
}

template<class T>
inline bool operator!=(const Vec3<T> & left, const Vec3<T> & right)
{
	return !(left == right);
}


template<class T>
std::ostream& operator<<(std::ostream& os, const Vec3<T>& v)
{
	os.precision(3);
	os.setf(std::ios::fixed);
	os << "x: " << std::setprecision(3) << std::setw(10) << v.x << "   ";
	os << "y: " << std::setprecision(3) << std::setw(10) << v.y << "   ";
	os << "z: " << std::setprecision(3) << std::setw(10) << v.z << "   ";
	os << std::endl;
	return os;
}


////////////////////////////////////////////////////////// Vec3W //////////////////////////////////////////////////////////


template<class T>
inline Vec3W<T> operator+(const Vec3W<T> & left, const Vec3W<T> & right)
{
	return Vec3W<T>(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
}

template<class T>
inline Vec3W<T> operator-(const Vec3W<T> & left, const Vec3W<T> & right)
{
	return Vec3W<T>(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
}

template<class T>
inline Vec3W<T> operator-(const Vec3W<T> & right)
{
	return Vec3W<T>(-right.x, -right.y, -right.z, -right.w);
}

template<class T>
inline Vec3W<T> operator*(const Vec3W<T> & left, double_t right)
{
	return Vec3W<T>(left.x * right, left.y * right, left.z * right, left.w * right);
}

template<class T>
inline Vec3W<T> operator*(double_t left, const Vec3W<T> & right)
{
	return Vec3W<T>(left * right.x, left * right.y, left * right.z, left * right.w);
}

// if right == 0, returns zero vector
template<class T>
inline Vec3W<T> operator/(const Vec3W<T> & left, double_t right)
{
	if (right)
		return Vec3W<T>(left.x / right, left.y / right, left.z / right, left.w / right);
	else
		return Vec3W<T>();
}

template<class T>
inline Vec3W<T> operator/(double_t left, const Vec3W<T> & right)
{
	return Vec3W<T>(right.x != 0 ? left / right.x : 0, right.y != 0 ? left / right.y : 0, right.z != 0 ? left / right.z : 0, right.w != 0 ? left / right.w : 0);
}

template<class T>
inline Vec3W<T>& operator+=(Vec3W<T> & left, const Vec3W<T> & right)
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;
	left.w += right.w;
	return left;
}

template<class T>
inline Vec3W<T>& operator-=(Vec3W<T> & left, const Vec3W<T> & right)
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;
	left.w -= right.w;
	return left;
}

template<class T>
inline Vec3W<T>& operator*=(Vec3W<T> & left, T right)
{
	left.x *= right;
	left.y *= right;
	left.z *= right;
	left.w *= right;
	return left;
}

// if right == 0, returns zero vector
template<class T>
inline Vec3W<T>& operator/=(Vec3W<T> & left, T right)
{
	if (right)
	{
		left.x /= right;
		left.y /= right;
		left.z /= right;
		left.w /= right;
	}
	else
		left = Vec3W<T>();
	return left;
}

template<class T>
inline bool operator==(const Vec3W<T> & left, const Vec3W<T> & right)
{
	return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
}

template<class T>
inline bool operator!=(const Vec3W<T> & left, const Vec3W<T> & right)
{
	return !(left == right);
}


template<class T>
std::ostream& operator<<(std::ostream& os, const Vec3W<T>& v)
{
	os.precision(3);
	os.setf(std::ios::fixed);
	os << "x: " << std::setprecision(3) << std::setw(10) << v.x << "   ";
	os << "y: " << std::setprecision(3) << std::setw(10) << v.y << "   ";
	os << "z: " << std::setprecision(3) << std::setw(10) << v.z << "   ";
	os << "w: " << std::setprecision(3) << std::setw(10) << v.w << "   ";
	os << std::endl;
	return os;
}