#ifndef D3DLIB_FRUSTUM
#define D3DLIB_FRUSTUM

#pragma warning (disable:4005)
#include <D3DX10math.h>

namespace D3DLIB
{
	class Frustum
	{
	public:
		Frustum();
		Frustum(const Frustum&);
		~Frustum();

		void ConstructFrustum(float screenDepth,
			D3DXMATRIX projectionMatrix, D3DXMATRIX viewMatrix);
		bool CheckPoint(float x, float y, float z);
		bool CheckCube(float xCenter, float yCenter, float zCenter, float radius);
		bool CheckSphere(float xCenter, float yCenter, float zCenter, float radius);
		bool CheckRectangle(float xCenter, float yCenter, float zCenter,
			float xSize, float ySize, float zSize);

	private:
		D3DXPLANE m_planes[6];
	};
}

#endif