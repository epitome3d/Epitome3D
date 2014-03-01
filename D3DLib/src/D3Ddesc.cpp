#include "D3Ddesc.h"

namespace D3DLIB
{
	D3DDesc::Rasterizer::Rasterizer()
	{
		alphablend = true;
		cull = D3D11_CULL_NONE;
		fill = D3D11_FILL_SOLID;
	}
	D3DDesc::Rasterizer::Rasterizer(bool alphablend, D3D11_CULL_MODE cull, D3D11_FILL_MODE fill)
	{
		this->alphablend = alphablend;
		this->cull = cull;
		this->fill = fill;
	}

	int D3DDesc::Rasterizer::operator==(const D3DDesc::Rasterizer &other) const
	{
		if (alphablend != other.alphablend) { return 0; }
		if (cull != other.cull) { return 0; }
		if (fill != other.fill) { return 0; }
		return 1;
	}

	D3DDEFAULTS::D3DDEFAULTS()
	{
		world = Orientation(Ypositive, Left, TopLeft);
		rot = Rad;
	}

	D3DDEFAULTS::D3DDEFAULTS(Orientation world, RotMode rot)
	{
		this->world = world;
		this->rot = rot;
	}

	
}