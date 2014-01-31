#include "math3d.h"

namespace D3DLIB {

	float Abs(float value)
	{
		if (value < 0) { return -value; }
		return value;
	}

}