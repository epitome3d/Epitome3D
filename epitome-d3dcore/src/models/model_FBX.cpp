#include "model_FBX.h"

namespace EPITOME
{
	Model_FBX::Model_FBX() : Model()
	{
		g_pFbxSdkManager = 0;
	}

	bool Model_FBX::LoadModel(char* filename)
	{
		if (g_pFbxSdkManager == nullptr)
		{
			g_pFbxSdkManager = FbxManager::Create();

			FbxIOSettings* pIOsettings = FbxIOSettings::Create(g_pFbxSdkManager, IOSROOT);
			g_pFbxSdkManager->SetIOSettings(pIOsettings);
		}

		FbxImporter* pImporter = FbxImporter::Create(g_pFbxSdkManager, "");
		FbxScene* pFbxScene = FbxScene::Create(g_pFbxSdkManager, "");

		bool bSuccess = pImporter->Initialize(filename, -1, g_pFbxSdkManager->GetIOSettings());
		if (!bSuccess) return false;

		bSuccess = pImporter->Import(pFbxScene);
		if (!bSuccess) return false;

		pImporter->Destroy();

		FbxNode* pFbxRootNode = pFbxScene->GetRootNode();

		/*** ZERO VARIABLES ***/

		m_model = new vector<VertexType>();
		m_indices = new vector<unsigned int>();

		m_vertexCount = 0;
		m_indexCount = 0;
		m_normalCount = 0;
		m_UVCount = 0;

		if (pFbxRootNode)
		{
			/*** LOAD MESH DATA ***/

			for (int i = 0; i < pFbxRootNode->GetChildCount(); i++)
			{
				FbxNode* pFbxChildNode = pFbxRootNode->GetChild(i);
				if (pFbxChildNode->GetNodeAttribute() == NULL)
					continue;
				FbxNodeAttribute::EType AttributeType = pFbxChildNode->GetNodeAttribute()->GetAttributeType();
				if (AttributeType != FbxNodeAttribute::eMesh)
					continue;
				FbxMesh* pMesh = (FbxMesh*)pFbxChildNode->GetNodeAttribute();


				/*** LOAD POLYGON DATA ***/
				//(not by control points, but by polygon

				LoadPolygonData(pMesh);
			}

		}

		return true;
	}

	bool Model_FBX::LoadPolygonData(FbxMesh* mesh)
	{
		int baseVertex = m_vertexCount;
		int polygonCount = mesh->GetPolygonCount();
		FbxVector4* pVertices = mesh->GetControlPoints(); //get vertices

		//just get polygons, vertices = indices
		//JUST LOOK AT INDICES

		/*** GET LOCATION (from indices) ***/
		int indexCount = mesh->GetPolygonVertexCount();
		int* indices = new int[indexCount];
		indices = mesh->GetPolygonVertices();
		for (int i = 0; i < indexCount; i++)
		{
			VertexType vertex;
			vertex.pos.x = (float)pVertices[indices[i] + baseVertex].mData[0];
			vertex.pos.y = (float)pVertices[indices[i] + baseVertex].mData[1];
			vertex.pos.z = (float)pVertices[indices[i] + baseVertex].mData[2];
			m_indices->push_back((unsigned int)i);
			m_model->push_back(vertex); //??? : would this make this backwards?
			m_vertexCount++;
		}

		m_indexCount = m_vertexCount;

		/*** GET NORMALS ***/
		FbxGeometryElementNormal* normalel = mesh->GetElementNormal();
		if (normalel)
		{
			int vertexCounter = 0;
			for (int i = 0; i < mesh->GetPolygonCount(); i++)
			{
				for (int j = 0; j < 3; j++)
				{
					FbxVector4 normal = normalel->GetDirectArray().GetAt(vertexCounter);
					VertexType vertex = m_model->at(m_normalCount);
					vertex.norm.x = (float)normal[0];
					vertex.norm.y = (float)normal[1];
					vertex.norm.z = (float)normal[2];
					m_model->at(m_normalCount) = vertex;
					m_normalCount++;
					vertexCounter++;
				}
			}
		}

		/*** GET UVs ***/
		int vertexCounter = 0;
		for (int i = 0; i < polygonCount; i++)
		{
			FbxLayerElementArrayTemplate<FbxVector2>* uvArray = 0;
			mesh->GetTextureUV(&uvArray, FbxLayerElement::eTextureDiffuse);

			for (int j = 0; j < mesh->GetPolygonSize(i); j++)
			{
				VertexType vertex = m_model->at(m_UVCount);
				vertex.uv.x = 1 - (float)uvArray->GetAt(mesh->GetTextureUVIndex(i, j)).mData[0];
				vertex.uv.y = 1 - (float)uvArray->GetAt(mesh->GetTextureUVIndex(i, j)).mData[1];
				m_model->at(m_UVCount) = vertex;
				m_UVCount++;
			}
		}

		return true;
	}

}