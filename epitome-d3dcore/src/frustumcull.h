#ifndef EPITOME_FRUSTUM_CULL
#define EPITOME_FRUSTUM_CULL

#pragma warning (disable:4005)
#include <D3D10_1.h>
#include "frustum.h"
#include "globals.h"

namespace EPITOME
{
	struct CullType
	{
	public:
		CullType();
		
		virtual bool IsInside(Frustum* frustum, ModelData* data) abstract;
		virtual int GetType() = 0;
	protected:

	};
	struct CullNone : public CullType
	{
	public:
		CullNone();

		int GetType() { return 1; }
		bool IsInside(Frustum* frustum, ModelData* data) override;
	};
	struct CullBox : public CullType
	{
	public:
		CullBox(float xCenter, float yCenter, float zCenter,
			float xSize, float ySize, float zSize);
		CullBox(float xCenter, float yCenter, float zCenter,
			float size);

		bool IsInside(Frustum* frustum, ModelData* data) override;
		int GetType() { return 2; }

		float xCenter, yCenter, zCenter;
		float xSize, ySize, zSize;
	};
	struct CullSphere : public CullType
	{
	public:
		CullSphere(float xCenter, float yCenter, float zCenter,
			float radius);

		int GetType() { return 3; }
		bool IsInside(Frustum* frustum, ModelData* data) override;

		float xCenter, yCenter, zCenter, radius;
	};
	struct CullAuto : public CullType
	{
		CullAuto();

		int GetType() { return 4; }
		bool IsInside(Frustum* frustum, ModelData* data) override;
	};

	//CullNone
	//CullBox
	//CullSphere
	//AutoCull
}
#endif