#pragma once

#include <Util/Common.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H  

namespace blox
{
	struct Character {
		uint        textureID;  // ID handle of the glyph texture
		glm::ivec2  size;       // Size of glyph
		glm::ivec2  bearing;    // Offset from baseline to left/top of glyph
		uint        advance;    // Offset to advance to next glyph   
	};

	class Font
	{
	private:
		std::map<char, Character> characters;
		float height;
		
	public:
		Font();
		Font(std::string path, int fontSize);

		Character GetCharacter(uchar c);
		float GetHeight();

		static void Load(Font* font, std::string path, int fontSize);
	};
}