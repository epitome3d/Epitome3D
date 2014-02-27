#include "model_OBJ.h"

namespace D3DLIB
{
	Model_OBJ::Model_OBJ() : Model()
	{
		
	}

	bool Model_OBJ::LoadModel(char* filename)
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
		while (input != ':')
		{
			fin.get(input);
		}

		//read in the vertex count
		fin >> m_vertexCount;

		//set the number of vertices to be the same as the vertex count
		m_indexCount = m_vertexCount;

		//create the model using the vertex count
		m_model = new vector<VertexType>();

		//read upto the beginning of the data
		fin.get(input);
		while (input != ':')
		{
			fin.get(input);
		}

		//read in the vertex data
		for (i = 0; i < m_vertexCount; i++)
		{
			VertexType vertex = VertexType();
			fin >> vertex.pos.x >> vertex.pos.y >> vertex.pos.z;
			fin >> vertex.uv.x >> vertex.uv.y;
			fin >> vertex.norm.x >> vertex.norm.y >> vertex.norm.z;
			m_model->push_back(vertex);
		}

		//close the model file
		fin.close();
		return true;
	}

}