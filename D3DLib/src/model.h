#ifndef D3DLIB_MODEL
#define D3DLIB_MODEL

//includes
#pragma warning (disable:4005)
#include <D3D11.h>
#include <D3DX10math.h>
#include <fstream>
#include <d3dx9.h>
#pragma warning (disable:4996)
using namespace std;

//my class includes
#include "texture.h"
#include "globals.h"


namespace D3DLIB
{	
	#define Float_MAX         3.402823466e+38F 
	#define Float_MIN         1.175494351e-38F

	class Model
	{
	private:
		struct VertexType
		{
			D3DXVECTOR3 position;
			D3DXVECTOR2 texture;
			D3DXVECTOR3 normal;
		};
		struct ModelType
		{
			float x, y, z;
			float tu, tv;
			float nx, ny, nz;
		};

	public:
		Model();
		Model(const Model&);
		~Model();

		bool Initialize(ID3D11Device*, char*, bool getdata);
		void Shutdown();
		void Render(ID3D11DeviceContext*);
		int GetIndexCount();
		ModelData* GetData();

	private:
		bool InitializeBuffers(ID3D11Device*, bool);
		void ShutdownBuffers();
		void RenderBuffers(ID3D11DeviceContext*);
		bool LoadModel(char*);
		void ReleaseModel();
				
		float Abs(float value)
		{
			if (value < 0) { return -value; }
			return value;
		}

		ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
		int m_vertexCount, m_indexCount;
		ModelType* m_model;		
		ModelData* m_data;
	};

}
#endif