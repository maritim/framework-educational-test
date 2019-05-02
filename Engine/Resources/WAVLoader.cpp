#include "WAVLoader.h"

#include <SDL/SDL_audio.h>

#include "Audio/AudioClip.h"

#include "Core/Console/Console.h"

Object* WAVLoader::Load(const std::string& filename)
{
	AudioClip* audioClip = new AudioClip ();

	SDL_AudioSpec spec;
	unsigned int size;
	unsigned char* buffer;

	if (SDL_LoadWAV (filename.c_str (), &spec, &buffer, &size) == nullptr) {
		Console::LogError ("Unable to load \"" + filename + "\"!");
		exit (0);
	}

	audioClip->SetName (filename);
	audioClip->SetData (buffer, size, spec.freq);

	return audioClip;
}