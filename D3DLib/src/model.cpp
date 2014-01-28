#include "model.h"

namespace D3DLIB
{

	Model::Model()
	{
		m_vertexBuffer = 0;
		m_indexBuffer = 0;
		m_model = 0;
		m_data = 0;
	}

	Model::Model(const Model& other)
	{
	}

	Model::~Model()
	{
	}

	bool Model::Initialize(ID3D11Device* device, char* modelFilename, bool getdata)
	{
		bool result;
		
		m_data = new ModelData();

		m_data->Reset();
		m_data->data = true;

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
		unsigned long* indices;
		D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
		D3D11_SUBRESOURCE_DATA vertexData, indexData;
		HRESULT result;

		// Create the vertex array.
		vertices = new VertexType[m_vertexCount];
		if(!vertices)
		{
			return false;
		}

		// Create the index array.
		indices = new unsigned long[m_indexCount];
		if(!indices)
		{
			return false;
		}

		//Mesh Loading Function!
		//D3DXLoadMeshFromX();

		if (getdata)
		{
			// Load the vertex array with data and get the size

			float xL = FLT_MAX, yL = FLT_MAX, zL = FLT_MAX;
			float xR = FLT_MIN, yR = FLT_MIN, zR = FLT_MIN;
			float radius = 0;

			for(int i=0;i<m_vertexCount;i++)
			{
				vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
				vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
				vertices[i].normal = D3DXVECTOR3(m_model[i].nx, m_model[i].ny, m_model[i].nz);

				if (m_model[i].x > xR) { xR = m_model[i].x; }
				if (m_model[i].x < xL) { xL = m_model[i].x; }
				if (m_model[i].y > yR) { yR = m_model[i].y; }
				if (m_model[i].y < yL) { yL = m_model[i].y; }
				if (m_model[i].z > zR) { zR = m_model[i].z; }
				if (m_model[i].z < zL) { zL = m_model[i].z; }

				indices[i] = i;
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
			// Load the vertex array with data.
			for(int i=0;i<m_vertexCount;i++)
			{
				vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
				vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
				vertices[i].normal = D3DXVECTOR3(m_model[i].nx, m_model[i].ny, m_model[i].nz);

				indices[i] = i;
			}
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
		indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
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

		// Release the arrays now that the vertex and index buffers have been created and loaded.
		delete [] vertices;
		vertices = 0;

		delete [] indices;
		indices = 0;

		return true;
	}

	//THIS FUNCTION PARSES THE VERTICES IN THE ARRAY
	bool Model::LoadModel(char* filename)
	{
		ifstream fin;
		char input;
		int i;

		//open the model file
		fin.open(filename);

		//if it could not open the file, then exit
		if (fin.fail())
		{
			return false;
		}

		//read up to the value of vertex count
		fin.get(input);
		while(input !=':')
		{
			fin.get(input);
		}

		//read in the vertex count
		fin >> m_vertexCount;

		//set the number of vertices to be the same as the vertex count
		m_indexCount = m_vertexCount;

		//create the model using the vertex count
		m_model = new ModelType[m_vertexCount];
		if (!m_model)
		{
			return false;
		}

		//read upto the beginning of the data
		fin.get(input);
		while(input != ':')
		{
			fin.get(input);
		}

		//read in the vertex data
		for (i=0; i<m_vertexCount;i++)
		{
			fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
			fin >> m_model[i].tu >> m_model[i].tv;
			fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
		}

		//close the model file
		fin.close();

		return true;
	}

	void Model::ReleaseModel()
	{
		if(m_model)
		{
			delete [] m_model;
			m_model = 0;
		}

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
    
		// Set the vertex buffer to active in the input assembler so it can be rendered.
		deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

		// Set the index buffer to active in the input assembler so it can be rendered.
		deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		return;
	}

	ModelData* Model::GetData()
	{
		return m_data;
	}

}