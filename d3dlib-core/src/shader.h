#ifndef D3DLIB_SHADER
#define D3DLIB_SHADER

//includes
#pragma warning (disable:4005)
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
#include <vector>
using namespace std;

#include "bitmap.h"
#include "globals.h"

namespace D3DLIB
{
	struct Buffer
	{

	};

	class BufferDirectory
	{
	public:
		BufferDirectory();

		void Add(ID3D11Buffer** buffer);
		void Add(ID3D11Buffer** bufferlist[], int count);
		void Shutdown();

	private:
		std::vector<ID3D11Buffer**> buffers;
	};

	class Shader
	{
	protected:
		virtual bool Initialize(ID3D11Device*, HWND) = 0;
		void GetQuaternion(D3DXQUATERNION &quad, float rotX, float rotY, float rotZ, Orientation orient);
		void ThrowBlobError(ID3D10Blob*, HWND, WCHAR*);

		struct MatrixBufferType : Buffer
		{
			D3DXMATRIX world;
			D3DXMATRIX view;
			D3DXMATRIX projection;
		};

		BufferDirectory bd = BufferDirectory();

	public:
		Shader();
		Shader(const Shader&);
		~Shader();
		
		virtual bool Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
			D3DXMATRIX projectionMatrix, Transform transform, Orientation orient) = 0;
		virtual Shader* Clone() = 0;
	};

}

#endif