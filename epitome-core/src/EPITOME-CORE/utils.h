#pragma once

#include <functional>

/* Utility structures */
namespace EPITOME {
	/*
	* Applies to classes that can be disposed once
	*/
	class Disposable
	{
	public:
		virtual void dispose() = 0;
	};
	
	/*
	* Applies to classes that store data on disk and can be loaded and unloaded to/from memory as well as disposed.
	*/
	class Bin : public Disposable
	{
	public:
		virtual void load() = 0;
		virtual void unload() = 0;
		virtual bool isLoaded() = 0;
	};

	template <typename T>
	struct Point
	{
		T x;
		T y;

		Point()
		{
			this->x = 0;
			this->y = 0;
		}
		Point(T x, T y)
		{
			this->x = x;
			this->y = y;
		}
		Point(const Point &other)
		{
			this->x = other.x;
			this->y = other.y;
		}
	};

	template <typename T>
	struct Size
	{
		T width;
		T height;

		Size()
		{
			this->width = 0;
			this->height = 0;
		}
		Size(T width, T height)
		{
			this->width = width;
			this->height = height;
		}
		Size(const Size &other)
		{
			this->width = other.width;
			this->height = other.height;
		}
	};
}