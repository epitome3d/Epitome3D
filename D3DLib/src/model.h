#ifndef D3DLIB_MODEL
#define D3DLIB_MODEL

//includes
#pragma warning (disable:4005)
#pragma comment (lib,"libfbxsdk.lib")
#include <D3D11.h>
#include <D3DX10math.h>
#include <fstream>
#include <fbxsdk.h>
#include <vector>
#include <assert.h>
using namespace std;

//my class includes
#include "texture.h"
#include "globals.h"
#include "math3d.h"

namespace D3DLIB
{
	class Model
	{
	private:
		struct VertexType
		{
			D3DXVECTOR3 pos;
			D3DXVECTOR2 uv;
			D3DXVECTOR3 norm;
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
		Orientation GetOrientation() { return m_orient; }

	private:
		bool InitializeBuffers(ID3D11Device*, bool);
		void ShutdownBuffers();
		void RenderBuffers(ID3D11DeviceContext*);

		bool LoadModel(char*);
		void ReleaseModel();

		bool LoadPolygonData(FbxMesh*);

		FbxManager* g_pFbxSdkManager;
		ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;

		int m_vertexCount, m_indexCount, m_normalCount, m_UVCount;
		vector<VertexType>* m_model;

		ModelData* m_data;
		Orientation m_orient;
	};

}
#endif