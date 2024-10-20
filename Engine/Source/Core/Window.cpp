#include <Core/Window.hpp>
#include <Core/Input.hpp>
#include <Core/Sound.hpp>

using namespace blox;

GLFWwindow* Window::window = nullptr;

void ResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::Window(std::string title, int width, int height, WindowStyle style)
{
	this->title = title;
	this->style = style;

	// Default black background color
	this->backgroundColor.r = Color::BLACK.r;
	this->backgroundColor.g = Color::BLACK.g;
	this->backgroundColor.b = Color::BLACK.b;
	this->backgroundColor.a = Color::BLACK.a;

	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* monitor = nullptr;
	if (style == WindowStyle::FULLSCREEN)
	{
		// Get the primary monitor
		monitor = glfwGetPrimaryMonitor();
		if (!monitor)
			throw std::runtime_error("[Error] Failed to get primary monitor");

		// Get the video mode of the monitor
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		if (!mode)
			throw std::runtime_error("[Error] Failed to get video mode");

		// Set window hints for fullscreen mode
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		// Update width and height to match the monitor's resolution
		width = mode->width;
		height = mode->height;
	}

	// Create window
	Window::window = glfwCreateWindow(width, height, title.c_str(), monitor, NULL);
	if (Window::window == NULL)
		throw std::runtime_error("[Error] Failed to create window");

	glfwMakeContextCurrent(Window::window);

	// Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw std::runtime_error("[Error] Failed to initialize GLAD");
	}

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(Window::window, ResizeCallback);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Disable cursor
	glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::SetBackgroundColor(Color backgroundColor)
{
	this->backgroundColor = backgroundColor;
}

bool Window::IsOpen()
{
	return !glfwWindowShouldClose(this->window);
}

void Window::UpdateFPS()
{
	++this->framesCount;
	this->framesTime += Time::GetDeltaTime();
	if (this->framesTime >= 1.0)
	{
		this->fps = this->framesCount / this->framesTime;
		this->framesCount = 0;
		this->framesTime = 0.0f;
	}
}

int Window::GetFPS()
{
	return this->fps;
}

void Window::Clear()
{
	glClearColor(
		this->backgroundColor.r,
		this->backgroundColor.g,
		this->backgroundColor.b,
		this->backgroundColor.a
	);

	glClear(GL_COLOR_BUFFER_BIT);
}


void Window::Update()
{
	glfwSwapBuffers(this->window);
	glfwPollEvents();
	Input::Update(this->window);
}

void Window::Close()
{
	glfwSetWindowShouldClose(this->window, true);
}

void Window::Destroy()
{
	Sound::Destroy();
	glfwDestroyWindow(Window::window);
	glfwTerminate();
}
