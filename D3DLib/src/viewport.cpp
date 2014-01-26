#include "viewport.h"

namespace D3DLIB
{

	Viewport::Viewport()
	{
		active = D3D11_VIEWPORT();		
	}

	Viewport::Viewport(ID3D11DeviceContext* deviceContext, D3D11_VIEWPORT default_port)
	{
		active = D3D11_VIEWPORT();
		SetViewport(deviceContext, default_port);
	}

	void Viewport::SetViewport(ID3D11DeviceContext* deviceContext, 
		float width, float height, float mindepth,
		float maxdepth, float topleftX, float topleftY)
	{
		D3D11_VIEWPORT viewport = D3D11_VIEWPORT();
		viewport.Width = width;
		viewport.Height = height;
		viewport.MinDepth = mindepth;
		viewport.MaxDepth = maxdepth;
		viewport.TopLeftX = topleftX;
		viewport.TopLeftY = topleftY;

		active = viewport;
	}

	void Viewport::SetViewport(ID3D11DeviceContext* deviceContext,
			D3D11_VIEWPORT viewport)
	{		
		active = viewport;
	}

	void Viewport::RenderViewport(ID3D11DeviceContext* deviceContext)
	{
		deviceContext->RSSetViewports(1, &active);
	}

	D3D11_VIEWPORT Viewport::GetViewport()
	{
		return active;
	}
}