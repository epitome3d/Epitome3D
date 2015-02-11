#include "model.h"

namespace D3DLIB
{

	Model::Model()
	{
		m_vertexBuffer = 0;
		m_indexBuffer = 0;
		m_model = 0;
		m_indices = 0;
		m_data = 0;
	}

	bool Model::Initialize(ID3D11Device* device, char* modelFilename, bool getdata)
	{
		bool result;

		m_data = new ModelData();
		m_data->Reset();

		//Load in the model
		result = LoadModel(modelFilename);
		if(!result)
		{
			return false;
		}

		//Initialize the vertex and index buffers.
		result = InitializeBuffers(device, getdata);
		if(!result)
		{
			return false;
		}

		return true;
	}

	void Model::Shutdown()
	{
		//shutdown the vertex and index buffers
		ShutdownBuffers();

		//release the model
		ReleaseModel();

		return;
	}

	void Model::Render(ID3D11DeviceContext* deviceContext)
	{
		//put the vertex and index buffers on the graphics pipeline to prepare them for drawing
		RenderBuffers(deviceContext);

		return;
	}

	int Model::GetIndexCount()
	{
		return m_indexCount;
	}

	bool Model::InitializeBuffers(ID3D11Device* device, bool getdata)
	{
		VertexType* vertices;
		unsigned int* indices;
		D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
		D3D11_SUBRESOURCE_DATA vertexData, indexData;
		HRESULT result;

		// Create the vertex array.
		vertices = new VertexType[m_vertexCount];
		if(!vertices) {	return false; }
		//vertices = m_vertices;

		// Create the index array.
		indices = new unsigned int[m_indexCount];
		if(!indices) { return false; }

		//indices = m_indices;

		if (getdata)
		{
			// Load the vertex array with data and get the size
			float xL = FLT_MAX, yL = FLT_MAX, zL = FLT_MAX;
			float xR = FLT_MIN, yR = FLT_MIN, zR = FLT_MIN;
			float radius = 0;

			int loc = 0;
			for(vector<VertexType>::iterator i=m_model->begin(); i!=m_model->end(); ++i)
			{
				vertices[loc].pos = D3DXVECTOR3(i->pos.x, i->pos.y, i->pos.z);
				vertices[loc].uv = D3DXVECTOR2(i->uv.x, i->uv.y);
				vertices[loc].norm = D3DXVECTOR3(i->norm.x, i->norm.y, i->norm.z);

				if (i->pos.x > xR) { xR = i->pos.x; }
				if (i->pos.x < xL) { xL = i->pos.x; }
				if (i->pos.y > yR) { yR = i->pos.y; }
				if (i->pos.y < yL) { yL = i->pos.y; }
				if (i->pos.z > zR) { zR = i->pos.z; }
				if (i->pos.z < zL) { zL = i->pos.z; }

				loc++;
			}

			m_data->xSize = Abs(xR - xL);
			m_data->ySize = Abs(yR - yL);
			m_data->zSize = Abs(zR - zL);

			m_data->xCenter = (xL + xR) / 2;
			m_data->yCenter = (yL + yR) / 2;
			m_data->zCenter = (zL + zR) / 2;

			radius = m_data->xSize;
			if (m_data->ySize > radius) { radius = m_data->ySize; }
			if (m_data->zSize > radius) { radius = m_data->zSize; }

			m_data->radius = radius;
		}
		else 
		{ 
			int loc = 0;
			for(vector<VertexType>::iterator i=m_model->begin(); i!=m_model->end(); ++i)
			{
				vertices[loc].pos = D3DXVECTOR3(i->pos.x, i->pos.y, i->pos.z);
				vertices[loc].uv = D3DXVECTOR2(i->uv.x, i->uv.y);
				vertices[loc].norm = D3DXVECTOR3(i->norm.x, i->norm.y, i->norm.z);

				loc++;
			}

			m_data->data = false;
		}

		int loc = 0;
		for (vector<unsigned int>::iterator i=m_indices->begin(); i!=m_indices->end(); ++i)
		{
			indices[loc] = *i;
			loc++;
		}

		// Set up the description of the static vertex buffer.
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the vertex data.
		vertexData.pSysMem = vertices;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		// Now create the vertex buffer.
		result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
		if(FAILED(result))
		{
			return false;
		}

		// Set up the description of the static index buffer.
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(unsigned int) * m_indexCount;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the index data.
		indexData.pSysMem = indices;
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		// Create the index buffer.
		result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
		if(FAILED(result))
		{
			return false;
		}

		return true;
	}

	void Model::ReleaseModel()
	{
		if(m_model)
		{
			m_model->clear();
			m_model = 0;
		}

		m_vertexCount = 0;
		m_indexCount = 0;
		m_normalCount = 0;
		m_UVCount = 0;

		return;
	}

	void Model::ShutdownBuffers()
	{
		// Release the index buffer.
		if(m_indexBuffer)
		{
			m_indexBuffer->Release();
			m_indexBuffer = 0;
		}

		// Release the vertex buffer.
		if(m_vertexBuffer)
		{
			m_vertexBuffer->Release();
			m_vertexBuffer = 0;
		}

		return;
	}

	void Model::RenderBuffers(ID3D11DeviceContext* deviceContext)
	{
		unsigned int stride;
		unsigned int offset;
		
		// Set vertex buffer stride and offset.
		stride = sizeof(VertexType); 
		offset = 0;

		// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// Set the vertex buffer to active in the input assembler so it can be rendered.
		deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

		// Set the index buffer to active in the input assembler so it can be rendered.
		deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);		

		return;
	}

	ModelData* Model::GetData()
	{
		return m_data;
	}

}