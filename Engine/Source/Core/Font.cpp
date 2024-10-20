#include <Core/Font.hpp>

using namespace blox;

Font::Font()
{
    this->height = 0;
}

Font::Font(std::string path, int fontSize) : Font()
{
    Load(this, path, fontSize);
}

Character Font::GetCharacter(uchar c)
{
    return this->characters[c];
}

float Font::GetHeight()
{
    return this->height;
}

void Font::Load(Font* font, std::string path, int fontSize)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        throw std::runtime_error("[Error] Failed to load FreeType Library");
    }

    FT_Face face;
    if (FT_New_Face(ft, path.c_str(), 0, &face))
    {
        FT_Done_FreeType(ft);
        throw std::runtime_error("[Error] Failed to load font");
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Only 1 byte for color

    float maxAscent = 0.0f;
    float maxDescent = 0.0f;

    for (uchar c = 0; c < 128; c++)
    {
        // Load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            FT_Done_Face(face);
            FT_Done_FreeType(ft);
            throw std::runtime_error("[Error] Failed to load character: " + c);
        }

        // Generate texture
        uint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };

        font->characters.insert(std::pair<char, Character>(c, character));

        // Calculate height
        float ascent = character.bearing.y;
        float descent = character.size.y - ascent;

        if (ascent > maxAscent)
            maxAscent = ascent;

        if (descent > maxDescent)
            maxDescent = descent;
    }

    font->height = maxDescent + maxAscent;

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}
