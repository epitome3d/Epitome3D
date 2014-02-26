#pragma once

//linking
#pragma warning(disable:4005)
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

//includes
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <math.h>
#include "globals.h"

namespace D3DLIB
{
	#define PI				  (float)D3DX_PI
	#define Float_MAX         3.402823466e+38F 
	#define Float_MIN         1.175494351e-38F

	float Abs(float value);

	float xrad(float value);
	D3DXVECTOR3 xrad(D3DXVECTOR3 in);
	Transform xrad(Transform in);

	///<summary>Convert to degrees.</summary>
	float xdeg(float value);
	D3DXVECTOR3 xdeg(D3DXVECTOR3 in);
	Transform xdeg(Transform in);

	Transform xforce(Transform transform, RotMode mode);
}