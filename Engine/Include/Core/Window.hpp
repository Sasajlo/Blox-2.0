#pragma once

#include <Util/Common.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Core/Sprite.hpp>

namespace blox
{
	enum WindowStyle
	{
		WINDOWED,
		FULLSCREEN
	};

	class Window
	{
	private:
		static GLFWwindow* window;

		std::string title;
		WindowStyle style;
		Color backgroundColor;

		int framesCount = 0;
		float framesTime = 0.0f;
		int fps = 0;

	public:
		Window(std::string title, int width, int height, WindowStyle style);

		void SetBackgroundColor(Color backgroundColor);
		bool IsOpen();

		void UpdateFPS();
		int GetFPS();

		void Clear();
		void Update();
		void Close();

		static void Destroy();
	};
}