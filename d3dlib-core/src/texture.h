#ifndef D3DLIB_TEXTURE
#define D3DLIB_TEXTURE

#pragma warning (disable:4005)
#include <D3D11.h>
#include <D3DX11tex.h>

namespace D3DLIB
{
	class Texture
	{
	public:
		Texture();
		Texture(ID3D11Device*, WCHAR*);
		Texture(const Texture&);
		~Texture();

		bool Initialize(ID3D11Device*, WCHAR*);
		void Shutdown();
		ID3D11ShaderResourceView* GetTexture();
	private:
		ID3D11ShaderResourceView* m_texture;
	};
}

#endif