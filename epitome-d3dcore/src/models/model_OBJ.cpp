#include "model_OBJ.h"

namespace EPITOME
{
	Model_OBJ::Model_OBJ() : Model()
	{
		
	}

	bool Model_OBJ::LoadModel(char* filename)
	{
		return LoadDataStructures(filename);
	}

	bool Model_OBJ::LoadDataStructures(char* filename)
	{
		ifstream fin;
		char input, input2;
		vector<FaceType>* m_faces = new vector<FaceType>();
		vector<D3DXVECTOR3>* vertices = new vector<D3DXVECTOR3>();
		vector<D3DXVECTOR2>* uvs = new vector<D3DXVECTOR2>();
		vector<D3DXVECTOR3>* normals = new vector<D3DXVECTOR3>();

		m_model = new vector<VertexType>();
		m_indices = new vector<unsigned int>();

		m_vertexCount = 0;
		m_indexCount = 0;
		m_normalCount = 0;
		m_UVCount = 0;
		int m_faceCount = 0;

		// Open the file.
		fin.open(filename);

		// Check if it was successful in opening the file.
		if (fin.fail() == true)
		{
			return false;
		}

		// Read in the vertices, texture coordinates, and normals into the data structures.
		// Important: Also convert to left hand coordinate system since Maya uses right hand coordinate system.
		fin.get(input);
		while (!fin.eof() && !fin.fail())
		{
			if (input == 'v')
			{
				fin.get(input);

				// Read in the vertices.
				if (input == ' ')
				{
					D3DXVECTOR3 vertex = D3DXVECTOR3();
					fin >> vertex.x >> vertex.y >> vertex.z;
					vertex.z = vertex.z * -1.0f; // Convert to left hand
					vertices->push_back(vertex);
					m_vertexCount++;
				}

				// Read in the texture uv coordinates.
				if (input == 't')
				{
					D3DXVECTOR2 vertex = D3DXVECTOR2();
					fin >> vertex.x >> vertex.y;
					vertex.y = 1.0f - vertex.y; //Convert to left hand
					uvs->push_back(vertex);
					m_UVCount++;
				}

				// Read in the normals.
				if (input == 'n')
				{
					D3DXVECTOR3 vertex = D3DXVECTOR3();
					fin >> vertex.x >> vertex.y >> vertex.z;
					vertex.z = vertex.z * -1.0f; // Convert to left hand
					normals->push_back(vertex);
					m_normalCount++;
				}
			}

			// Read in the faces.
			if (input == 'f')
			{
				fin.get(input);
				if (input == ' ')
				{
					FaceType face = FaceType();
					// Read the face data in backwards to convert it to a left hand system from right hand system.
					fin >> face.vIndex3 >> input2 >> face.tIndex3 >> input2 >> face.nIndex3
						>> face.vIndex2 >> input2 >> face.tIndex2 >> input2 >> face.nIndex2
						>> face.vIndex1 >> input2 >> face.tIndex1 >> input2 >> face.nIndex1;

					m_faces->push_back(face);
					m_faceCount++;
					m_indexCount = m_indexCount + 3;
				}
			}

			// Read in the remainder of the line.
			while ((input != '\n') && (!fin.eof()))
			{
				fin.get(input);
			}

			// Start reading the beginning of the next line.
			fin.get(input);
		}

		// Close the file.
		fin.close();

		int vIndex, tIndex, nIndex;
		m_vertexCount = 0;

		// Now loop through all the faces and output the three vertices for each face.
		for (int i = 0; i < m_faceCount; i++)
		{
			VertexType v1 = VertexType();
			VertexType v2 = VertexType();
			VertexType v3 = VertexType();

			vIndex = m_faces->at(i).vIndex1 - 1;
			tIndex = m_faces->at(i).tIndex1 - 1;
			nIndex = m_faces->at(i).nIndex1 - 1;

			v1.pos = vertices->at(vIndex);
			v1.uv = uvs->at(tIndex);
			v1.norm = normals->at(nIndex);

			vIndex = m_faces->at(i).vIndex2 - 1;
			tIndex = m_faces->at(i).tIndex2 - 1;
			nIndex = m_faces->at(i).nIndex2 - 1;

			v2.pos = vertices->at(vIndex);
			v2.uv = uvs->at(tIndex);
			v2.norm = normals->at(nIndex);

			vIndex = m_faces->at(i).vIndex3 - 1;
			tIndex = m_faces->at(i).tIndex3 - 1;
			nIndex = m_faces->at(i).nIndex3 - 1;

			v3.pos = vertices->at(vIndex);
			v3.uv = uvs->at(tIndex);
			v3.norm = normals->at(nIndex);

			m_model->push_back(v1);
			m_model->push_back(v2);
			m_model->push_back(v3);
			m_indices->push_back((unsigned int)(i * 3));
			m_indices->push_back((unsigned int)((i * 3) + 1));
			m_indices->push_back((unsigned int)((i * 3) + 2));
			m_vertexCount += 3;
		}

		return true;
	}

}