#include "SDL2/SDL.h"

#define FILE_PATH "obama.wav"

struct AudioData
{
	Uint8* pos;
	Uint32 length;
};

void MyAudioCallback(void* userdata, Uint8* stream, int streamLength)
{
	AudioData* audio = (AudioData*)userdata;

	if(audio->length == 0)
	{
		return;
	}

	Uint32 length = (Uint32)streamLength;
	length = (length > audio->length ? audio->length : length);

	SDL_memcpy(stream, audio->pos, length);

	audio->pos += length;
	audio->length -= length;
}

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_AUDIO);

	SDL_AudioSpec wavSpec;
	Uint8* wavStart;
	Uint32 wavLength;

	if(SDL_LoadWAV(FILE_PATH, &wavSpec, &wavStart, &wavLength) == NULL)
	{
		// TODO: Proper error handling
        printf("Error: could not be loaded as an audio file");
		return 1;
	}

	AudioData audio;
	audio.pos = wavStart;
	audio.length = wavLength;

	wavSpec.callback = MyAudioCallback;
	wavSpec.userdata = &audio;

	SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL,
			SDL_AUDIO_ALLOW_ANY_CHANGE);
	if(device == 0)
	{
		
		printf("Error: ", SDL_GetError(), "\n");
		return 1;
	}

	SDL_PauseAudioDevice(device, 0);

	while(audio.length > 0)
	{
		SDL_Delay(100);
	}

	SDL_CloseAudioDevice(device);
	SDL_FreeWAV(wavStart);
	SDL_Quit();
	return 0;
}