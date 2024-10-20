#pragma once

#include <Util/Common.hpp>
#include <Core/Font.hpp>
#include <Core/Shader.hpp>

namespace blox
{
	class Text
	{
	private:
		std::string text;
		Font font;

		uint vao;
		uint vbo;

		Vec3 position;
		Size size;
		Vec2 anchor;

		Shader shader;

	public:
		Text(std::string text, Font font);

	private:
		void UpdateWidth();

	public:
		void SetPosition(Vec2i position);
		void SetText(std::string text);
		void SetAnchor(Vec2 anchor);

		Size GetSize();

		void Render();
	};
}