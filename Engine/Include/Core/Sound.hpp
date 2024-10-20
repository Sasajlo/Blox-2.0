#pragma once

#include <Util/Common.hpp>
#include <irrklang/irrKlang.h>

namespace blox
{
	class Sound
	{
	private:
		static irrklang::ISoundEngine* soundEngine;
		std::string path;
		float volume;

	public:
		Sound();
		Sound(std::string path);
		
		void Play();
		void SetVolume(float volume);

		static void Load(Sound* sound, std::string path);
		static void Destroy();
	};
}