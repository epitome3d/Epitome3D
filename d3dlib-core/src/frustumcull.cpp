#include "frustumcull.h"

namespace D3DLIB
{
	CullType::CullType() {}
	bool CullType::IsInside(Frustum* frustum, ModelData* data) { return false; }

	CullNone::CullNone() {}
	bool CullNone::IsInside(Frustum* frustum, ModelData* data) 
	{ 
		return true;
	}
	
	CullBox::CullBox(float xCenter, float yCenter, float zCenter,
			float xSize, float ySize, float zSize)
	{
		this->xCenter = xCenter;
		this->yCenter = yCenter;
		this->zCenter = zCenter;
		this->xSize = xSize;
		this->ySize = ySize;
		this->zSize = zSize;
	}
	CullBox::CullBox(float xCenter, float yCenter, float zCenter,
			float size)
	{
		this->xCenter = xCenter;
		this->yCenter = yCenter;
		this->zCenter = zCenter;
		this->xSize = size;
		this->ySize = size;
		this->zSize = size;
	}
	bool CullBox::IsInside(Frustum* frustum, ModelData* data) 
	{ 
		return frustum->CheckRectangle(xCenter, yCenter, zCenter, xSize, ySize, zSize);
	}

	CullSphere::CullSphere(float xCenter, float yCenter, float zCenter, float radius)
	{
		this->xCenter = xCenter;
		this->yCenter = yCenter;
		this->zCenter = zCenter;
		this->radius = radius;
	}
	bool CullSphere::IsInside(Frustum* frustum, ModelData* data)
	{
		return frustum->CheckSphere(xCenter, yCenter, zCenter, radius);
	}

	CullAuto::CullAuto() {}
	bool CullAuto::IsInside(Frustum* frustum, ModelData* data)
	{
		return frustum->CheckRectangle(data->xCenter, data->yCenter, data->zCenter,
			data->xSize, data->ySize, data->zSize);
	}
}