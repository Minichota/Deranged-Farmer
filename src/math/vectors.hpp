#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdlib.h>
#include <ostream>
#include <iostream>

template <class T>
class Vector
{
	public:
	Vector(T x, T y):
	x(x),
	y(y)
	{
	}
	Vector():
	x(0),
	y(0)
	{
	}
	~Vector()
	{
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector& x)
	{
		os << " x: " << x.x << " y: " << x.y << " ";
		return os;
	}

	Vector<T> operator/(const int& other)
	{
		return Vector<T>(this->x / other, this->y / other);
	}

	template <class other_type>
	Vector<T> operator*(const Vector<other_type>& other)
	{
		return Vector<T>(this->x * other.x, this->y * other.y);
	}

	Vector<T> operator*(const double other)
	{
		return Vector<T>(this->x * other, this->y * other);
	}

	template <class other_type>
	Vector<T>& operator+=(const Vector<other_type>& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	template <class other_type>
	Vector<T>& operator-=(const Vector<other_type>& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	template <class other_type>
	Vector<T> operator-(const Vector<other_type>& rhs) const
	{
		Vector<T> ret;
		ret.x = this->x - rhs.x;
		ret.y = this->y - rhs.y;
		return ret;
	}

	T x;
	T y;
};
typedef Vector<float>  Fvec;
typedef Vector<short>  Svec;
typedef Vector<int>    Ivec;
typedef Vector<double> Dvec;
typedef Vector<long>   Lvec;
typedef Vector<size_t> STvec;
typedef Vector<unsigned short> USvec;
#endif
