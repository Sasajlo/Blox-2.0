#include <Core/Text.hpp>

using namespace blox;

Text::Text(std::string text, Font font)
{
    this->text = text;
    this->font = font;

	this->position.x = 0.0f;
	this->position.y = 0.0f;
	this->position.z = 0.0f;

    this->size.width = 0;
    this->size.height = font.GetHeight();

    this->anchor.x = 0.5f;
    this->anchor.y = 0.5f;

	Shader::Load(&shader, "Engine/Shader/Text.vert", "Engine/Shader/Text.frag");

	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

    UpdateWidth();
}

void Text::UpdateWidth()
{
    this->size.width = 0;

    // Iterate through all characters
    for (const char& c : this->text)
    {
        Character ch = this->font.GetCharacter(c);
        this->size.width += ch.advance >> 6;
    }
}

void Text::SetPosition(Vec2i position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}

void Text::SetText(std::string text)
{
    this->text = text;
    UpdateWidth();
}

void Text::SetAnchor(Vec2 anchor)
{
    this->anchor.x = Math::Min(Math::Max(anchor.x, 0.0f), 1.0f);
    this->anchor.y = Math::Min(Math::Max(anchor.y, 0.0f), 1.0f);
}

Size Text::GetSize()
{
    return this->size;
}

void Text::Render()
{
	this->shader.Use();

	this->shader.SetVector3("textColor", { 1.0f, 1.0f, 1.0f });

    // Set projection matrix
    glm::mat4 projection = Math::OrthographicProjection(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
    this->shader.SetUniformMat4("projection", projection);

    const float scale = 1.0f;
    float x = this->position.x;
    float y = this->position.y;

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->vao);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = this->text.begin(); c != this->text.end(); c++)
    {
        Character ch = this->font.GetCharacter(*c);

        Vec2 offset = {
            anchor.x * size.width,
            anchor.y * size.height
        };

        float xpos = x + ch.bearing.x * scale - offset.x;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale - offset.y;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

        // Update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureID);

        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
