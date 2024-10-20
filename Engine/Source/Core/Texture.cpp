#include <Core/Texture.hpp>

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace blox;

Texture::Texture()
{
	this->id = -1;
	this->width = 0;
	this->height = 0;
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, this->id);
}

int Texture::GetWidth()
{
	return this->width;
}

int Texture::GetHeight()
{
	return this->height;
}

void Texture::LoadFromFile(Texture* texture, std::string path)
{
	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_2D, texture->id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
	if (!data)
		throw std::runtime_error("[Error] Failed to load texture");

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	texture->width = width;
	texture->height = height;

	stbi_image_free(data);
}
