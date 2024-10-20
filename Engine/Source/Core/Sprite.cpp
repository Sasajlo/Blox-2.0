#include <Core/Sprite.hpp>

#include <glad/glad.h>

using namespace blox;

Sprite::Sprite()
{
	this->position = { 0, 0, 0 };
	this->rotation = { 0, 0, 0 };
	this->scale = { 1.0f, 1.0f, 1.0f };

	this->width = 1;
	this->height = 1;

	Shader::Load(&this->shader, "Engine/Shader/Sprite.vert", "Engine/Shader/Sprite.frag");

	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);
	Update();

	this->color = Color::WHITE;
}

void Sprite::SetTexture(Texture* texture)
{
	this->texture = texture;
	SetSize({ texture->GetWidth(), texture->GetHeight() });
}

void Sprite::SetColor(Color color)
{
	this->color = color;

	this->vertices[0 + COLOR_OFFSET] = color.r;
	this->vertices[1 + COLOR_OFFSET] = color.g;
	this->vertices[2 + COLOR_OFFSET] = color.b;

	this->vertices[0 + COLOR_OFFSET + DATA_PER_VERTEX] = color.r;
	this->vertices[1 + COLOR_OFFSET + DATA_PER_VERTEX] = color.g;
	this->vertices[2 + COLOR_OFFSET + DATA_PER_VERTEX] = color.b;

	this->vertices[0 + COLOR_OFFSET + DATA_PER_VERTEX * 2] = color.r;
	this->vertices[1 + COLOR_OFFSET + DATA_PER_VERTEX * 2] = color.g;
	this->vertices[2 + COLOR_OFFSET + DATA_PER_VERTEX * 2] = color.b;

	this->vertices[0 + COLOR_OFFSET + DATA_PER_VERTEX * 3] = color.r;
	this->vertices[1 + COLOR_OFFSET + DATA_PER_VERTEX * 3] = color.g;
	this->vertices[2 + COLOR_OFFSET + DATA_PER_VERTEX * 3] = color.b;

	Update();
}

void Sprite::SetPosition(Vec2 position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}

void Sprite::SetRotation(Vec3 rotation)
{
	this->rotation.x = rotation.x;
	this->rotation.y = rotation.y;
	this->rotation.z = rotation.z;
}

void Sprite::SetScale(Vec2 scale)
{
	this->scale.x = scale.x;
	this->scale.y = scale.y;
}

Vec2 Sprite::GetPosition()
{
	return { this->position.x, this->position.y };
}

Vec2 Sprite::GetScale()
{
	return { this->scale.z, this->scale.y };
}

void Sprite::Move(Vec2 offset)
{
	this->position.x += offset.x;
	this->position.y += offset.y;
}

void Sprite::SetSize(Size size)
{
	this->width = size.width;
	this->height = size.height;
	
	float halfWidth = this->width * 0.5f;
	float halfHeight = this->height * 0.5f;

	this->vertices[0] = -halfWidth;
	this->vertices[1] = -halfHeight;

	this->vertices[0 + DATA_PER_VERTEX] = halfWidth;
	this->vertices[1 + DATA_PER_VERTEX] = -halfHeight;

	this->vertices[0 + DATA_PER_VERTEX * 2] = halfWidth;
	this->vertices[1 + DATA_PER_VERTEX * 2] = halfHeight;

	this->vertices[0 + DATA_PER_VERTEX * 3] = -halfWidth;
	this->vertices[1 + DATA_PER_VERTEX * 3] = halfHeight;

	Update();
}

void Sprite::Render()
{
	// Bind uniforms
	this->shader.Use();

	glm::mat4 model = glm::mat4(1.0f);
	 
	// Translate the model
	model = glm::translate(model, glm::vec3(this->position.x, this->position.y, 0.0f));

	// Rotate the model (around the Z-axis)
	model = glm::rotate(model, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	// Scale the model
	model = glm::scale(model, glm::vec3(this->scale.x, this->scale.y, 1.0));

	this->shader.SetUniformMat4("model", model);

	// Set projection matrix
	glm::mat4 projection = Math::OrthographicProjection(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
	this->shader.SetUniformMat4("projection", projection);
	
	// Set texture
	if (this->texture) 
	{
		this->texture->Bind();
		this->shader.SetInt("useTexture", 1);
	}

	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, INDEX_COUNT, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Sprite::Update()
{
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, VERTEX_COUNT * DATA_PER_VERTEX * sizeof(float), this->vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, DATA_PER_VERTEX * sizeof(float), (void*)(POSITION_OFFSET * sizeof(float)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, DATA_PER_VERTEX * sizeof(float), (void*)(COLOR_OFFSET * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, DATA_PER_VERTEX * sizeof(float), (void*)(TEXTURE_OFFSET * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &this->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDEX_COUNT * sizeof(int), this->indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}
