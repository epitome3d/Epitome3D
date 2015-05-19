#include "camera.h"

namespace EPITOME
{

	Camera::Camera()
	{
		m_positionX = 0;
		m_positionY = 0;
		m_positionZ = 0;
		m_rotationX = 0;
		m_rotationY = 0;
		m_rotationZ = 0;
	}

	Camera::Camera(const Camera& other)
	{
	}

	Camera::~Camera()
	{
		//TODO this
	}

	void Camera::SetPosition(float x, float y, float z)
	{
		m_positionX = x;
		m_positionY = y;
		m_positionZ = z;
		return;
	}

	void Camera::SetRotation(float x, float y, float z)
	{
		m_rotationX = x;
		m_rotationY = y;
		m_rotationZ = z;
		return;
	}

	D3DXVECTOR3 Camera::GetPosition()
	{
		return D3DXVECTOR3(m_positionX, m_positionY, m_positionZ);
	}

	D3DXVECTOR3 Camera::GetRotation()
	{
		return D3DXVECTOR3(m_rotationX, m_rotationY, m_rotationZ);
	}

	void Camera::Render()
	{
		D3DXVECTOR3 up, position, lookAt;
		float yaw, pitch, roll;
		D3DXMATRIX rotationMatrix;

		//setup the vector that points upwards
		up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//setup where the camera is looking by default
		lookAt = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		//setup the position of the camera in the world
		position.x = m_positionX;
		position.y = m_positionY;
		position.z = m_positionZ;

		//set the yaw (y), pitch (x), and roll (z) rotations in radians
		pitch = m_rotationX * 0.0174532925f;
		yaw = m_rotationY * 0.0174532925f;
		roll = m_rotationZ * 0.0174532925f;

		//create the rotation matrix from the yaw, pitch, and roll
		D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

		//transform the rotated camera position to the location of the viewer
		D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
		D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

		//translate the rotated camera position to the location of the viewer
		lookAt = position + lookAt;

		//finally create the view matrix from the three updated vectors
		D3DXMatrixLookAtLH(&m_viewMatrix, &position, &lookAt, &up);

		return;
	}

	void Camera::GetViewMatrix(D3DXMATRIX& viewMatrix)
	{
		viewMatrix = m_viewMatrix;
		return;
	}

}