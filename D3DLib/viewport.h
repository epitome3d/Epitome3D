#ifndef D3DLIB_VIEWPORT
#define D3DLIB_VIEWPORT

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
#include <vector>
#include <algorithm>
using namespace std;

namespace D3DLIB
{
	class Viewport
	{
	public:
		Viewport();
		Viewport(ID3D11DeviceContext* deviceContext, D3D11_VIEWPORT default_port);
		
		void SetViewport(ID3D11DeviceContext* deviceContext,
			float width, float height, float mindepth,
			float maxdepth, float topleftX, float topleftY);
		void SetViewport(ID3D11DeviceContext* deviceContext,
			D3D11_VIEWPORT viewport);
		void RenderViewport(ID3D11DeviceContext* deviceContext);

		D3D11_VIEWPORT GetViewport();
		
	private:
		D3D11_VIEWPORT active;

	};
}

#endif