#pragma once

#include <functional>

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

	/*
	* Applies to classes that are part of the Epitome3D pipeline and require and Update() method on every event loop
    */
	__interface Updateable
	{
	public:
		virtual void Update() = 0;
	};

	/*
	* Applies to classes that can be disposed once
	*/
	__interface Disposable
	{
	public:
		virtual void Dispose() = 0;
	};
	
	/*
	* Applies to classes that store data on disk and can be loaded and unloaded to/from memory.
	*/
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