#include <Core/Input.hpp>

using namespace blox;

Input Input::input = {};

Input::Input()
{
    
}

void Input::Update(GLFWwindow* window)
{
    // Update keyboard
    for (int i = 0; i < (int)Key::LAST; ++i) {
        input.previousKeys[i] = input.keys[i];
        input.keys[i] = glfwGetKey(window, i);
    }
}

bool Input::KeyPressed(Key key)
{
    return input.keys[(int)key] && !input.previousKeys[(int)key];
}

bool Input::IsKeyReleased(Key key)
{
    return !input.keys[(int)key] && input.previousKeys[(int)key];
}

bool Input::KeyHeld(Key key)
{
    return input.keys[(int)key];
}
