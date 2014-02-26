#include "math3d.h"

namespace D3DLIB {

	float Abs(float value)
	{
		if (value < 0) { return -value; }
		return value;
	}
	float xrad(float value)
	{
		return value * PI / 180.0f;
	}
	D3DXVECTOR3 xrad(D3DXVECTOR3 in)
	{
		return D3DXVECTOR3(xrad(in.x), xrad(in.y), xrad(in.z));
	}
	Transform xrad(Transform in)
	{
		Transform out = Transform(Rad);
		out.rotation = xrad(in.rotation);
		out.scale = in.scale;
		out.translation = in.translation;
		return out;
	}
	float xdeg(float value)
	{
		return value / PI * 180.0f;
	}
	D3DXVECTOR3 xdeg(D3DXVECTOR3 in)
	{
		return D3DXVECTOR3(xdeg(in.x), xdeg(in.y), xdeg(in.z));
	}
	Transform xdeg(Transform in)
	{
		Transform out = Transform(Rad);
		out.rotation = xdeg(in.rotation);
		out.scale = in.scale;
		out.translation = in.translation;
		return out;
	}
	Transform xforce(Transform transform, Mode mode)
	{
		if (mode == transform.mode) { return transform; }
		if (mode == Rad) { return xrad(transform); }
		if (mode == Deg) { return xdeg(transform); }
		return transform;
	}
}