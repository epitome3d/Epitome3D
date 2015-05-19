#ifndef EPITOME_MODEL
#define EPITOME_MODEL

//includes
#pragma warning (disable:4005)
#include <D3D11.h>
#include <D3DX10math.h>
#include <fstream>
#include <vector>
#include <assert.h>
using namespace std;

//my class includes
#include "texture.h"
#include "globals.h"
#include "math3d.h"
#include "D3Ddesc.h"

namespace EPITOME
{
	class Model abstract
	{
	protected:
		virtual struct VertexType
		{
			D3DXVECTOR3 pos;
			D3DXVECTOR2 uv;
			D3DXVECTOR3 norm;
		};

	public:
		Model();

		bool Initialize(ID3D11Device*, char*, bool getdata);
		void Render(ID3D11DeviceContext*);
		void Shutdown();

		int GetIndexCount();
		ModelData* GetData();
		virtual Orientation GetOrientation() = 0;
	
	protected:
		virtual bool LoadModel(char* filename) = 0;

		void ReleaseModel();
		bool InitializeBuffers(ID3D11Device*, bool);
		void ShutdownBuffers();
		void RenderBuffers(ID3D11DeviceContext*);
		
		vector<VertexType>* m_model; //add vertices to this vector
		vector<unsigned int>* m_indices; //add indices to this vector
		int m_vertexCount, m_indexCount, m_normalCount, m_UVCount;
		
	private:
		ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
		ModelData* m_data;
	};

}
#endif