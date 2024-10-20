#pragma once

#include <Util/Common.hpp>

#include <Core/Texture.hpp>
#include <Core/Shader.hpp>

// -----------------------------------------------------------------------
// |     Position     |      Color       | Text Coord |      Normal      |
// -----------------------------------------------------------------------
// | 0.0f, 0.0f, 0.0f | 0.0f, 0.0f, 0.0f | 0.0f, 0.0f | 0.0f, 0.0f, 0.0f |
// -----------------------------------------------------------------------
#define POSITION_OFFSET 0
#define COLOR_OFFSET 3
#define TEXTURE_OFFSET 6
#define NORMAL_OFFSET 8

#define DATA_PER_VERTEX 11 

#define VERTEX_COUNT 4 // Vertex for each corner of rectangle
#define INDEX_COUNT 6  // 2 triangles with 3 vertices

namespace blox
{
	class Sprite
	{
	private:
		float vertices[VERTEX_COUNT * DATA_PER_VERTEX] = {
			// Position           // Color            // Texture Coord    // Normal
			-1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,		  0.0f, 0.0f, -1.0f,  // bottom left
			 1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,		  0.0f, 0.0f, -1.0f,  // bottom right
			 1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,		  0.0f, 0.0f, -1.0f,  // top right
			-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,		  0.0f, 0.0f, -1.0f   // top left
		};

		int indices[INDEX_COUNT] = {
			0, 1, 2,  // First triangle
			0, 2, 3,  // Second triangle
		};

		Vec3 position;
		Vec3 rotation;
		Vec3 scale;

		int width;
		int height;

		Shader shader;

		uint vao;
		uint vbo;
		uint ebo;

		Texture* texture;
		Color color;

	public:
		Sprite();

		void SetTexture(Texture* texture);
		void SetColor(Color color);
		void SetSize(Size size);
		void SetPosition(Vec2 position);
		void SetRotation(Vec3 rotation);
		void SetScale(Vec2 scale);

		Vec2 GetPosition();
		Vec2 GetScale();

		void Move(Vec2 offset);

		void Render();

	private:
		void Update();
	};
}