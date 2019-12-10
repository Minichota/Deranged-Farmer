#ifndef SIZED_HPP
#define SIZED_HPP

#include <SDL2/SDL.h>

#include "vectors.hpp"
#include "error.hpp"

template <class T>
class Sized
{
	public:
	Sized(Vector<T> pos, Vector<T> size, Vector<T> scale, int rotation = 0)
	{
		this->pos = pos;
		this->size = size;
		this->scale = scale;
		Error((int)rotation % 90 != 0, {"Object cannot have rotation that isn't divisible by 90"}, true);
		this->rotation = rotation;
	};
	Sized<T>(T pos_x, T pos_y, T size_x, T size_y, T scale_x, T scale_y, int rotation = 0)
	{
		this->pos = Vector<T>(pos_x, pos_y);
		this->size = Vector<T>(size_x, size_y);
		this->scale = Vector<T>(scale_x, scale_y);
		Error((int)rotation % 90 != 0, {"Object cannot have rotation that isn't divisible by 90"}, true);
		this->rotation = rotation;
	};
	Sized<T>()
	{
		this->pos = Vector<T>(0,0);
		this->size = Vector<T>(0,0);
		this->scale = Vector<T>(0,0);
		this->rotation = 0;
	};
	virtual ~Sized()
	{
	};

	virtual Vector<T>& get_pos()
	{
		return this->pos;
	};
	virtual Vector<T> get_pos_copy()
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
	virtual Vector<T> get_size_copy()
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

	virtual Vector<T>& get_scale()
	{
		return this->scale;
	};
	virtual void set_scale(Vector<T> scale)
	{
		this->scale = scale;
	};
	virtual void set_scale(T scale_x, T scale_y)
	{
		this->size = Vector<T>(scale_x, scale_y);
	};

	virtual float get_rotation()
	{
		return this->rotation;
	};

	inline SDL_Rect get_render_rect()
	{
		return
		{
			(int)std::round(pos.x/scale.x),
			(int)std::round(pos.y/scale.y),
			(int)std::round(size.x),
			(int)std::round(size.y)
		};
	}

	Vector<T> get_collision_pos()
	{
		if(size.x == size.y || (int)rotation % 90 != 0)
		{
			// don't rotate, it's either square or has a dynamic rotation
			return pos;
		}
		float rad_rotation = -(int)rotation % 180 * 3.1415926535f/180.0f;
		float p = pos.x + size.x/2;
		float q = pos.y + size.y/2;
		Fvec pos_prime = Fvec((-size.x/2) * cosf(rad_rotation) + (size.y/2) * sinf(rad_rotation) + p,
							   (size.x/2) * sinf(rad_rotation) + (-size.y/2) * cosf(rad_rotation) + q);
		return pos_prime;
	}
	Vector<T> get_collision_size()
	{
		if(size.x == size.y || (int)rotation % 90 != 0)
		{
			// don't rotate, it's either square or has a dynamic rotation
			return size;
		}
		if((int)rotation % 180 == 0)
		{
			return size;
		}
		if((int)rotation % 90 == 0)
		{
			return Fvec(size.y, size.x);
		}
		return Vector<T>(-1.0f, -1.0f);
	}

	protected:
	Vector<T> pos;
	Vector<T> size;
	Vector<T> scale;
	float rotation;
};
#endif
