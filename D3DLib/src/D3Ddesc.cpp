#include "D3Ddesc.h"

namespace D3DLIB
{
	Descriptions::Rasterizer::Rasterizer()
	{
		alphablend = true;
		cull = D3D11_CULL_NONE;
		fill = D3D11_FILL_SOLID;
	}
	Descriptions::Rasterizer::Rasterizer(bool alphablend, D3D11_CULL_MODE cull, D3D11_FILL_MODE fill)
	{
		this->alphablend = alphablend;
		this->cull = cull;
		this->fill = fill;
	}

	D3DDEFAULTS::D3DDEFAULTS()
	{
		world = Orientation(Ypositive, Left, TopLeft);
		rot = Rad;
	}
	D3DDEFAULTS::D3DDEFAULTS(Orientation world, RotMode rot, Descriptions::Rasterizer rasterizer)
	{
		this->world = world;
		this->rot = rot;
	}

	D3DDESC::D3DDESC()
	{
	}
	D3DDESC::D3DDESC(D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection,
		D3DXMATRIX ortho, D3D11_VIEWPORT viewport, Descriptions::Rasterizer rasterizer)
	{
		this->world = &world;
		this->view = &view;
		this->projection = &projection;
		this->ortho = &ortho;
		this->viewport = &viewport;
		this->rasterizer = &rasterizer;
	}
}