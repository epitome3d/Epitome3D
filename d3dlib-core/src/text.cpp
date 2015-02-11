#include "text.h"

namespace D3DLIB
{

	Text::Text()
	{
		m_viewport = &D3D11_VIEWPORT();
		m_fontwrapper = 0;
	}

	Text::Text(const Text& other)
	{

	}

	Text::~Text()
	{

	}

	bool Text::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
	{
		HRESULT result;
	
		D3D11_VIEWPORT vp = {0};
		UINT i = 1;
		deviceContext->RSGetViewports(&i, &vp);
		m_viewport = &D3D11_VIEWPORT(vp);

		//create the font wrapper
		IFW1Factory *pFW1Factory;
		result = FW1CreateFactory(FW1_VERSION, &pFW1Factory);
		if (FAILED(result)) { return false; }

		result = pFW1Factory->CreateFontWrapper(device, L"Arial", &m_fontwrapper);
		if (FAILED(result)) { return false; }

		pFW1Factory->Release();

		return true;
	}

	void Text::Render(ID3D11DeviceContext* deviceContext, const WCHAR* string, const WCHAR* fontfamily, float positionX, float positionY, float fontsize,
						   UINT32 colorABGR, UINT FW1_TEXT_FLAGs)
	{
		float left = positionX;
		float top = positionY;

		// Draw some strings
		m_fontwrapper->DrawString(
		deviceContext,
		string,	// String
		fontfamily, //Font Family
		fontsize,// Font size
		left,// X offset
		top,// Y offset
		colorABGR,// Text color, 0xAaBbGgRr
		FW1_TEXT_FLAGs// Flags
		);
	
		return;
	}

	void Text::Shutdown()
	{
		if (m_fontwrapper)
		{
			m_fontwrapper->Release();
			//delete m_fontwrapper;
			m_fontwrapper = 0;
		}	
		return;
	}

}