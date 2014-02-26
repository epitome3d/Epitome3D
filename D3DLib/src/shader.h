#ifndef D3DLIB_SHADER
#define D3DLIB_SHADER

//includes
#pragma warning (disable:4005)
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;

#include "bitmap.h"
#include "globals.h"

namespace D3DLIB
{
	class Shader
	{
	protected:
		virtual bool Initialize(ID3D11Device*, HWND) = 0;
		void GetQuaternion(D3DXQUATERNION &quad, float rotX, float rotY, float rotZ, Orientation orient);
		void ThrowBlobError(ID3D10Blob*, HWND, WCHAR*);

	public:
		Shader();
		Shader(const Shader&);
		~Shader();

		virtual bool Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
			D3DXMATRIX projectionMatrix, Transform transform, Orientation orient) = 0;
		virtual Shader* Clone() = 0;
	};
}

#endif