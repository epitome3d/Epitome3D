#ifndef EPITOME_CAMERA
#define EPITOME_CAMERA

#pragma warning (disable:4005)
#include <D3DX10math.h>

namespace EPITOME
{
	class Camera
	{
	public:
		Camera();
		Camera(const Camera&);
		~Camera();

		void SetPosition(float, float, float);
		void SetRotation(float, float, float);

		D3DXVECTOR3 GetPosition();
		D3DXVECTOR3 GetRotation();

		void Render();
		void GetViewMatrix(D3DXMATRIX&);

	private:
		float m_positionX, m_positionY, m_positionZ;
		float m_rotationX, m_rotationY, m_rotationZ;
		D3DXMATRIX m_viewMatrix;
	};
}

#endif