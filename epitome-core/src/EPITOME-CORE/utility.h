#pragma once

/* Utility structures */
namespace EPITOME {
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