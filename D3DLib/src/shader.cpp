#include "shader.h"

namespace D3DLIB
{
	BufferDirectory::BufferDirectory()
	{
		buffers = std::vector<ID3D11Buffer**>();
	}
	void BufferDirectory::Add(ID3D11Buffer** buffer)
	{
		buffers.push_back(buffer);
	}
	void BufferDirectory::Add(ID3D11Buffer** bufferlist[], int count)
	{
		for (int i = 0; i < count; i++)
		{
			Add(bufferlist[i]);
		}
	}
	void BufferDirectory::Shutdown()
	{
		for (vector<ID3D11Buffer**>::iterator p = buffers.begin(); p != buffers.end(); ++p)
		{
			(*((ID3D11Buffer**)*p))->Release();
			(*((ID3D11Buffer**)*p)) = 0;
		}
	}

	Shader::Shader()
	{

	}
	Shader::Shader(const Shader& other)
	{
	}
	Shader::~Shader()
	{
	}

	bool Shader::Initialize(ID3D11Device* device, HWND hwnd)
	{
		return false;
	}
	bool Shader::Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, 
									D3DXMATRIX projectionMatrix, Transform transform, Orientation orient)
	{
		return false;
	}

	void Shader::GetQuaternion(D3DXQUATERNION &quad, float rotX, float rotY, float rotZ, Orientation orient)
	{
		quad = D3DXQUATERNION();
		if (orient.upaxis == Ypositive)
		{
			D3DXQuaternionRotationYawPitchRoll(&quad, rotX, rotY, rotZ);
		}
		if (orient.upaxis == Zpositive)
		{
			D3DXQuaternionRotationYawPitchRoll(&quad, rotZ, rotY - 90.0f, rotX);
		}
		return;
	}

	void Shader::ThrowBlobError(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
	{
		char* compileErrors;
		unsigned long bufferSize, i;
		ofstream fout;


		// Get a pointer to the error message text buffer.
		compileErrors = (char*)(errorMessage->GetBufferPointer());

		// Get the length of the message.
		bufferSize = errorMessage->GetBufferSize();

		// Open a file to write the error message to.
		fout.open("shader-error.txt");

		// Write out the error message.
		for(i=0; i<bufferSize; i++)
		{
			fout << compileErrors[i];
		}

		// Close the file.
		fout.close();

		// Release the error message.
		errorMessage->Release();
		errorMessage = 0;

		// Pop a message up on the screen to notify the user to check the text file for compile errors.
		DisplayMessage(hwnd, Error, false, false, shaderFilename, L"Shader Compilation Error - Check shader-error.txt");

		return;
	}



}