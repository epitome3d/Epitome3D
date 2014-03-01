#pragma once

//libraries
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
#include "globals.h"

namespace D3DLIB
{
	class Descriptions
	{
	public:
		struct Rasterizer
		{
		public:
			Rasterizer();
			Rasterizer(bool alphablend, D3D11_CULL_MODE cull, D3D11_FILL_MODE fill);

			bool alphablend; //alpha blending enabled
			D3D11_CULL_MODE cull; //backface culling
			D3D11_FILL_MODE fill; //fill mode
		};
	};

	struct D3DDEFAULTS
	{
	public:
		D3DDEFAULTS();
		D3DDEFAULTS(Orientation world, RotMode rot, Descriptions::Rasterizer rasterizer);

		Orientation world; //default world orientation, all models automatically conform to this
		RotMode rot; //default rotation type, used when no specification present
	};

	struct D3DDESC
	{
	public:
		D3DDESC();
		D3DDESC(D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection,
			D3DXMATRIX ortho, D3D11_VIEWPORT viewport, Descriptions::Rasterizer rasterizer);

		D3DXMATRIX* world; //world matrix
		D3DXMATRIX* view; //view matrix
		D3DXMATRIX* projection; //projection matrix
		D3DXMATRIX* ortho; //ortho matrix
		D3D11_VIEWPORT* viewport; //viewport

		Descriptions::Rasterizer* rasterizer; //rasterizer state
	};
}