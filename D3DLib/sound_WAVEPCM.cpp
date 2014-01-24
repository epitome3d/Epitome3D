#include "sound_WAVEPCM.h"

namespace D3DLIB
{
	Sound_WAVEPCM::Sound_WAVEPCM()
	{
		m_DirectSound = 0;
		m_primaryBuffer = 0;
	}
	Sound_WAVEPCM::Sound_WAVEPCM(const Sound_WAVEPCM& other)
	{
	}
	Sound_WAVEPCM::~Sound_WAVEPCM()
	{
	}

	bool Sound_WAVEPCM::Initialize(HWND hwnd)
	{
		bool result;

		//initialize direct sound and the primary sound buffer
		result = InitializeDirectSound(hwnd);
		if (!result) { return false; }

		return true;
	}
	bool Sound_WAVEPCM::InitializeDirectSound(HWND hwnd)
	{
		HRESULT result;
		DSBUFFERDESC bufferDesc;
		WAVEFORMATEX waveFormat;

		//initialize the DSound interface pointer to the default sound device (player)
		result = DirectSoundCreate8(NULL, &m_DirectSound, NULL);
		if (FAILED(result)) { return false; }

		//set the cooperative level to priority so the format of the primary sound buffer can be modifie
		result = m_DirectSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
		if (FAILED(result)) { return false; }

		//setup the primary buffer description
		bufferDesc.dwSize = sizeof(DSBUFFERDESC);
		bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN; //capabilities and flags
		bufferDesc.dwBufferBytes = 0;
		bufferDesc.dwReserved = 0;
		bufferDesc.lpwfxFormat = NULL;
		bufferDesc.guid3DAlgorithm = GUID_NULL;

		//get controls of the priamry sound buffer on the default sound device
		result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL);
		if (FAILED(result)) { return false; }

		//setup the format of the primary sound buffer
		//in this case it is a WAVE at 44,100 samples/sec
		waveFormat.wFormatTag = WAVE_FORMAT_PCM;
		waveFormat.nSamplesPerSec = 44100;
		waveFormat.wBitsPerSample = 16;
		waveFormat.nChannels = 2;
		waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
		waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
		waveFormat.cbSize = 0;

		//set the primary buffer to be the wave format specified
		result = m_primaryBuffer->SetFormat(&waveFormat);
		if (FAILED(result)) { return false; }

		return true;
	}

	bool Sound_WAVEPCM::LoadFile(IDirectSoundBuffer8** buffer, char* filename)
	{
		int error;
		FILE* filePtr;
		unsigned int count;
		WaveHeaderType waveFileHeader;
		WAVEFORMATEX waveFormat;
		DSBUFFERDESC bufferDesc;
		HRESULT result;
		IDirectSoundBuffer* tempBuffer;
		unsigned char* waveData;
		unsigned char* bufferPtr;
		unsigned long bufferSize;

		//Check for file corruption and correct formatting

		error = fopen_s(&filePtr, filename, "rb");
		if(error != 0)
		{
			return false;
		}
 
		// Read in the wave file header.
		count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
		if(count != 1)
		{
			return false;
		}
 
		// Check that the chunk ID is the RIFF format.
		if((waveFileHeader.chunkId[0] != 'R') || (waveFileHeader.chunkId[1] != 'I') || 
		   (waveFileHeader.chunkId[2] != 'F') || (waveFileHeader.chunkId[3] != 'F'))
		{
			return false;
		}
 
		// Check that the file format is the WAVE format.
		if((waveFileHeader.format[0] != 'W') || (waveFileHeader.format[1] != 'A') ||
		   (waveFileHeader.format[2] != 'V') || (waveFileHeader.format[3] != 'E'))
		{
			return false;
		}
 
		// Check that the sub chunk ID is the fmt format.
		if((waveFileHeader.subChunkId[0] != 'f') || (waveFileHeader.subChunkId[1] != 'm') ||
		   (waveFileHeader.subChunkId[2] != 't') || (waveFileHeader.subChunkId[3] != ' '))
		{
			return false;
		}
 
		// Check that the audio format is WAVE_FORMAT_PCM.
		if(waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
		{
			return false;
		}
 
		// Check that the wave file was recorded in stereo format.
		if(waveFileHeader.numChannels != 2)
		{
			return false;
		}
 
		// Check that the wave file was recorded at a sample rate of 44.1 KHz.
		if(waveFileHeader.sampleRate != 44100)
		{
			return false;
		}
 
		// Ensure that the wave file was recorded in 16 bit format.
		if(waveFileHeader.bitsPerSample != 16)
		{
			return false;
		}
 
		// Check for the data chunk header.
		if((waveFileHeader.dataChunkId[0] != 'd') || (waveFileHeader.dataChunkId[1] != 'a') ||
		   (waveFileHeader.dataChunkId[2] != 't') || (waveFileHeader.dataChunkId[3] != 'a'))
		{
			return false;
		}

		//set the wave format of the secondary buffer
		waveFormat.wFormatTag = WAVE_FORMAT_PCM;
		waveFormat.nSamplesPerSec = 44100;
		waveFormat.wBitsPerSample = 16;
		waveFormat.nChannels = 2;
		waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
		waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
		waveFormat.cbSize = 0;

		//set the buffer description of the secondary buffer
		bufferDesc.dwSize = sizeof(DSBUFFERDESC);
		bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN;
		bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
		bufferDesc.dwReserved = 0;
		bufferDesc.lpwfxFormat = &waveFormat;
		bufferDesc.guid3DAlgorithm = GUID_NULL;

		//create a temporary sound buffer with the specific buffer settings
		result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
		if (FAILED(result)) { return false; }

		//test the buffer format against the DSound8 interface and create the secondary buffer
		result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*buffer);
		if (FAILED(result)) { return false; }

		//release the temporary buffer
		tempBuffer->Release();
		tempBuffer = 0;

		//move to the beginning of the wave data which starts at the end of the chunk header
		fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);

		//create a temporary buffer to hold the wave file data
		waveData = new unsigned char[waveFileHeader.dataSize];
		if(!waveData) { return false; }

		//read in the wave file data into the newly created buffer
		count = fread(waveData, 1, waveFileHeader.dataSize, filePtr);
		if (count != waveFileHeader.dataSize) { return false; }

		//close the file once done reading
		error = fclose(filePtr);
		if (error != 0) { return false; }

		//lock the secondary buffer to write wave data into it
		result = (*buffer)->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
		if (FAILED(result)) { return false; }

		//copy the wave data into the buffer
		memcpy(bufferPtr, waveData, waveFileHeader.dataSize);

		//unlock the secondary buffer after the data has been written to it
		result = (*buffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
		if (FAILED(result)) { return false; }

		//release the wave data since it was copied into the secondary buffer
		delete [] waveData;
		waveData = 0;

		result = SetVolume(*buffer, DSBVOLUME_MAX);
		if (!result)
		{ 
			return false;
		}

		result = (*buffer)->SetCurrentPosition(0);
		if (FAILED(result)) { return false; }

		result = SetPan(*buffer, DSBPAN_CENTER);
		if (FAILED(result)) { return false; }

		return true;
	}
}