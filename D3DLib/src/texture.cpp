#include "texture.h"


namespace D3DLIB
{

	Texture::Texture()
	{
		m_texture = 0;
	}

	Texture::Texture(const Texture& other)
	{
	}

	Texture::~Texture()
	{
	}

	Texture::Texture(ID3D11Device* device, WCHAR* filename)
	{
		Initialize(device, filename);
	}

	bool Texture::Initialize(ID3D11Device* device, WCHAR* filename)
	{
		HRESULT result;

		//load the texture
		result = D3DX11CreateShaderResourceViewFromFile(device, filename,
			NULL, NULL, &m_texture, NULL);
		if (FAILED(result))
		{
			return false;
		}

		return true;
	}

	void Texture::Shutdown()
	{
		//release the texture resource
		if (m_texture)
		{
			m_texture->Release();
			m_texture = 0;
		}

		return;
	}

	ID3D11ShaderResourceView* Texture::GetTexture()
	{
		return m_texture;
	}

}