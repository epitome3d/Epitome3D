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
	class D3DDesc
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

			int operator== (const Rasterizer &other) const;
		};
	};

	///<summary>Default D3D settings applied to all models.</summary>
	struct D3DDEFAULTS
	{
	public:
		///<summary>Set the D3D settings to defaults.  (Y-positive, Left-handed, UV TopLeft, Radians)</summary>
		D3DDEFAULTS();
		///<summary>Set the D3D settings.</summary>
		///<param name='world'>Default world orientation.  All models automatically conform to this.</param>
		///<param name='rot'>Default rotation type.  Used when no specification is present. (Default=Rad)</param>
		D3DDEFAULTS(Orientation world, RotMode rot);

		Orientation world; //default world orientation, all models automatically conform to this
		RotMode rot; //default rotation type, used when no specification present
	};

	//globals
	static D3DDEFAULTS* _defaults = 0;
}