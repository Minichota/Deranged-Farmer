#ifndef SIZED_HPP
#define SIZED_HPP

#include "vectors.hpp"

template <class T>
class Sized
{
	public:
	Sized(Vector<T> pos, Vector<T> size)
	{
		this->pos = pos;
		this->size = size;
	};
	Sized<T>(T pos_x, T pos_y, T size_x, T size_y)
	{
		this->pos = Vector<T>(pos_x, pos_y);
		this->size = Vector<T>(size_x, size_y);
	};
	~Sized()
	{
	};

	virtual Vector<T>& get_pos()
	{
		return this->pos;
	};
	virtual void set_pos(Vector<T> pos)
	{
		this->pos = pos;
	};
	virtual void set_pos(T pos_x, T pos_y)
	{
		this->pos = Vector<T>(pos_x, pos_y);
	};

	virtual Vector<T>& get_size()
	{
		return this->size;
	};
	virtual void set_size(Vector<T> size)
	{
		this->size = size;
	};
	virtual void set_size(T size_x, T size_y)
	{
		this->size = Vector<T>(size_x, size_y);
	};

	protected:
	Vector<T> pos;
	Vector<T> size;
};
#endif
