#pragma once

/* Utility structures */
namespace EPITOME {

	/*
	* Applies to classes that must only initialize once
	*/
	__interface Initializable
	{
	public:
		virtual void Initialize() = 0;
	};

	__interface Disposable
	{
	public:
		virtual void Dispose() = 0;
	};

	__interface Bin : public Disposable
	{
	public:
		virtual void Load() = 0;
		virtual void Unload() = 0;
		virtual void isLoaded() = 0;
	};

	template <typename T>
	struct Point
	{
		T x;
		T y;

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

		Size(T width, T height)
		{
			this->width = width;
			this->height = height;
		}
	};
}