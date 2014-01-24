#ifndef D3DLIB_BITMAP
#define D3DLIB_BITMAP

//includes
#pragma warning (disable:4005)
#include <D3D11.h>
#include <D3DX10math.h>

//my class includes
#include "texture.h"

namespace D3DLIB
{

	class Bitmap
	{
	private:
		struct VertexType
		{
			D3DXVECTOR3 position;
			D3DXVECTOR2 texture;
		};

	public:
		Bitmap();
		Bitmap(const Bitmap&);
		~Bitmap();

		bool Initialize(ID3D11Device*, int screenWidth, int screenHeight);
		void Shutdown();
		bool Render(ID3D11DeviceContext* deviceContext, int positionX, int positionY
			, int bitmapWidth, int bitmapHeight, float depth);

		int GetIndexCount();
		int GetBitmapWidth();
		int GetBitmapHeight();

	private:
		bool InitializeBuffers(ID3D11Device*);
		void ShutdownBuffers();
		bool UpdateBuffers(ID3D11DeviceContext*, int, int, int, int, float depth);
		void RenderBuffers(ID3D11DeviceContext*);

		ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
		int m_vertexCount, m_indexCount;

		int m_screenWidth, m_screenHeight;
		int m_bitmapWidth, m_bitmapHeight;
		int m_previousPosX, m_previousPosY;
	};

}

#endif