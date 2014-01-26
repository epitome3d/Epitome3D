#ifndef D3DLIB_SHADER_TEXTURE
#define D3DLIB_SHADER_TEXTURE

//includes
#include "shader.h"

namespace D3DLIB
{
	class Shader_TEXTURE : public Shader
	{
	private:
		struct MatrixBufferType
		{
			D3DXMATRIX world;
			D3DXMATRIX view;
			D3DXMATRIX projection;
		};

	public:
		Shader_TEXTURE();
		Shader_TEXTURE(const Shader_TEXTURE&);
		~Shader_TEXTURE();

		bool Initialize(ID3D11Device*, HWND) override;
		void Shutdown();

		bool Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
									D3DXMATRIX projectionMatrix, Transform transform) override;
		void SetParameters(ID3D11ShaderResourceView* texture);

		Shader* Clone();
	private:
		bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
		void ShutdownShader();
		bool PrepareShader(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, Transform transform);
		void RenderShader(ID3D11DeviceContext*, int);

	private:
		ID3D11ShaderResourceView* r_texture;

		ID3D11VertexShader* m_vertexShader;
		ID3D11PixelShader* m_pixelShader;
		ID3D11InputLayout* m_layout;
		ID3D11Buffer* m_matrixBuffer;
		ID3D11SamplerState* m_sampleState;
	};

}

#endif