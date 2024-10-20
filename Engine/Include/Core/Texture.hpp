#pragma once

#include <Util/Common.hpp>

namespace blox
{
	class Texture
	{
	private:
		uint id;
		int width;
		int height;

	public:
		Texture();

		void Bind();
		int GetWidth();
		int GetHeight();

		static void LoadFromFile(Texture* texture, std::string path);
	};
}