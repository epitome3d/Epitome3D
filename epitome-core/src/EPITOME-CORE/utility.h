#pragma once

/* Utility structures */
namespace EPITOME {
	template <typename T>
	struct point
	{
		T x;
		T y;

		point(T x, T y)
		{
			this->x = x;
			this->y = y;
		}
	};

	template <typename T>
	struct size
	{
		T width;
		T height;

		size(T width, T height)
		{
			this->width = width;
			this->height = height;
		}
	};
}