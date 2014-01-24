#ifndef D3DLIB_MATH_3D
#define D3DLIB_MATH_3D

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

namespace D3DLIB
{
	namespace Math
	{
		void DrawCircle();
	}
}

#endif