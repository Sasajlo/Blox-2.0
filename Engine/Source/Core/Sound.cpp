#include <Core/Sound.hpp>"

using namespace blox;

irrklang::ISoundEngine* Sound::soundEngine = irrklang::createIrrKlangDevice();

Sound::Sound()
{
}

Sound::Sound(std::string path)
{
	this->path = path;
	this->volume = 1.0f;
}

void Sound::Play()
{
	Sound::soundEngine->setSoundVolume(this->volume);
	Sound::soundEngine->play2D(this->path.c_str());
}

void Sound::SetVolume(float volume)
{
	this->volume = volume;
}

void Sound::Load(Sound* sound, std::string path)
{
	sound->path = path;
	sound->volume = 1.0f;
}

void Sound::Destroy()
{
	Sound::soundEngine->drop();
}
