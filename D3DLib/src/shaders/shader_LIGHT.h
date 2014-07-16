#ifndef D3DLIB_SHADER_LIGHT
#define D3DLIB_SHADER_LIGHT

//includes
#include "../shader.h"

namespace D3DLIB
{
	class Shader_LIGHT : public Shader
	{
	private:
		struct LightBufferType : Buffer
		{
			D3DXVECTOR4 ambientColor;
			D3DXVECTOR4 diffuseColor;
			D3DXVECTOR3 lightDirection;
			float specularPower;
			D3DXVECTOR4 specularColor;
		};
		struct CameraBufferType : Buffer
		{
			D3DXVECTOR3 cameraPosition;
			float padding;
			//padding so structure is a multiple of 16
			//(for some reason required by CreateBuffer...)
		};

	public:
		Shader_LIGHT(WCHAR* VS, WCHAR* PS);
		Shader_LIGHT(const Shader_LIGHT&);
		~Shader_LIGHT();

		bool Initialize(ID3D11Device*, HWND);
		void Shutdown();
		bool Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
			D3DXMATRIX projectionMatrix, Transform transform, Orientation orient);
		void SetParameters(ID3D11ShaderResourceView* texture, D3DXVECTOR3 lightDirection,
			D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor, D3DXVECTOR3 cameraPosition,
			D3DXVECTOR4 specularColor, float specularPower);
		Shader* Clone();

	private:
		bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
		void ShutdownShader();

		bool PrepareShader(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, Transform, Orientation orient);
		void RenderShader(ID3D11DeviceContext*, int);

		ID3D11VertexShader* m_vertexShader;
		ID3D11PixelShader* m_pixelShader;
		ID3D11InputLayout* m_layout;
		ID3D11SamplerState* m_sampleState;

	private:
		ID3D11Buffer* m_matrixBuffer;
		ID3D11Buffer* m_cameraBuffer;
		ID3D11Buffer* m_lightBuffer;
		WCHAR* VS;
		WCHAR* PS;

		ID3D11ShaderResourceView* r_texture;
		D3DXVECTOR3 r_lightDirection, r_cameraPosition;
		D3DXVECTOR4 r_ambientColor, r_diffuseColor, r_specularColor;
		float r_specularPower;
	};

}

#endif