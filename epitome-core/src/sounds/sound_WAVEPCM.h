#ifndef EPITOME_SOUND_WAVEPCM
#define EPITOME_SOUND_WAVEPCM

#include "../sound.h"

namespace EPITOME
{
	class Sound_WAVEPCM : public Sound
	{
	public:
		Sound_WAVEPCM();
		Sound_WAVEPCM(const Sound_WAVEPCM&);
		~Sound_WAVEPCM();

		bool Initialize(HWND);
		bool LoadFile(IDirectSoundBuffer8**, char*);

	private:
		bool InitializeDirectSound(HWND);

		struct WaveHeaderType
		{
			char chunkId[4];
			unsigned long chunkSize;
			char format[4];
			char subChunkId[4];
			unsigned long subChunkSize;
			unsigned short audioFormat;
			unsigned short numChannels;
			unsigned long sampleRate;
			unsigned long bytesPerSecond;
			unsigned short blockAlign;
			unsigned short bitsPerSample;
			char dataChunkId[4];
			unsigned long dataSize;
		};

	};
}

#endif