#include "globals.h"
namespace D3DLIB
{
	Transform::Transform()
	{
		this->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		this->translation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->mode = Rad;
	}

	Transform::Transform(RotMode mode)
	{
		this->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		this->translation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->mode = mode;
	}

	Transform::Transform(D3DXVECTOR3 rotation, D3DXVECTOR3 scale,
		D3DXVECTOR3 translation, RotMode mode)
	{
		this->rotation = rotation;
		this->scale = scale;
		this->translation = translation;
		this->mode = mode;
	}

	Orientation::Orientation()
	{
		this->upaxis = Ypositive;
		this->hand = Left;
	}

	Orientation::Orientation(UpAxis upaxis, Handedness hand, UVOrigin uvorigin)
	{
		this->upaxis = upaxis;
		this->hand = hand;
		this->uvorigin = uvorigin;
	}

}