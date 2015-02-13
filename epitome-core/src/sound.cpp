#include "sound.h"

namespace EPITOME
{

	Sound::Sound()
	{
		m_DirectSound = 0;
		m_primaryBuffer = 0;
	}

	Sound::Sound(const Sound& other)
	{
	}

	Sound::~Sound()
	{
	}

	//Release of buffers is required prior to calling this
	void Sound::Shutdown()
	{
		//shutdown the DSound API
		ShutdownDirectSound();

		return;
	}

	void Sound::ShutdownDirectSound()
	{
		// Release the primary sound buffer pointer.
		if(m_primaryBuffer)
		{
			m_primaryBuffer->Release();
			m_primaryBuffer = 0;
		}
 
		// Release the direct sound interface pointer.
		if(m_DirectSound)
		{
			m_DirectSound->Release();
			m_DirectSound = 0;
		}
 
		return;
	}

	void Sound::ShutdownBuffer(IDirectSoundBuffer8** buffer)
	{
		// Release the secondary sound buffer.
		if(*buffer)
		{
			(*buffer)->Release();
			*buffer = 0;
		}

		return;
	}

	bool Sound::SetVolume(IDirectSoundBuffer8* buffer, int DSBVOLUME)
	{
		HRESULT result;
		result = buffer->SetVolume(DSBVOLUME);
		if (FAILED(result)) { return false; }
		return true;
	}

	bool Sound::SetPan(IDirectSoundBuffer8* buffer, long DSBPAN)
	{
		HRESULT result;
		result = buffer->SetPan(DSBPAN);
		if (FAILED(result)) { return false; }
		return true;
	}

	bool Sound::GetCurrentPosition(IDirectSoundBuffer8* buffer, LPDWORD playPos, LPDWORD writePos)
	{
		HRESULT result;
		LPDWORD curPlay, curWrite;
		curPlay = curWrite = 0;
		result = buffer->GetCurrentPosition(curPlay, curWrite);
		playPos = curPlay;
		writePos = curWrite;
		if (FAILED(result)) { return false; }
		return true;
	}

	bool Sound::SetCurrentPosition(IDirectSoundBuffer8* buffer, DWORD position)
	{
		HRESULT result;
		result = buffer->SetCurrentPosition(position);
		if (FAILED(result)) { return false; }
		return true;
	}

	bool Sound::Play(IDirectSoundBuffer8* buffer, bool loop)
	{
		HRESULT result;
		
		/*//set the position at the beginning of the sound buffer
		result = buffer->SetCurrentPosition(position);
		if (FAILED(result)) { return false; }*/

		//play the contents of the secondary sound buffer
		DWORD flags = 0;
		if (loop)
		{
			flags = DSCBSTART_LOOPING;
		}
		result = buffer->Play(0, 0, flags);
		if (FAILED(result)) { return false; }

		return true;
	}

	bool Sound::Pause(IDirectSoundBuffer8* buffer)
	{
		HRESULT result;
		result = buffer->Stop();
		if (FAILED(result)) 
		{
			return false; 
		}
		return true;
	}

	bool Sound::Stop(IDirectSoundBuffer8* buffer)
	{
		HRESULT result;
		result = buffer->Stop();
		if (FAILED(result)) 
		{
			return false; 
		}
		result = buffer->SetCurrentPosition(0);
		if (FAILED(result)) 
		{
			return false; 
		}
		return true;
	}

}