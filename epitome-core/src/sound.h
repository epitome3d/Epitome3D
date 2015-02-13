#ifndef EPITOME_SOUND
#define EPITOME_SOUND

//linking
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

//includes
#include <Windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>

//codec includes
//#include "sound_WAVEPCM.h"

namespace EPITOME
{
	class Sound
	{
	public:
		Sound();
		Sound(const Sound&);
		~Sound();

		void Shutdown();

		void ShutdownBuffer(IDirectSoundBuffer8**);
		bool Play(IDirectSoundBuffer8* buffer, bool loop);
		bool Pause(IDirectSoundBuffer8* buffer);
		bool Stop(IDirectSoundBuffer8* buffer);
		bool SetVolume(IDirectSoundBuffer8* buffer, int DSBVOLUME);
		bool SetPan(IDirectSoundBuffer8* buffer, long DSBPAN);
		bool GetCurrentPosition(IDirectSoundBuffer8* buffer, LPDWORD playPos, LPDWORD writePos);
		bool SetCurrentPosition(IDirectSoundBuffer8* buffer, DWORD position);

	protected:
		void ShutdownDirectSound();	
		IDirectSound8* m_DirectSound;
		IDirectSoundBuffer* m_primaryBuffer;
	};

}

#endif