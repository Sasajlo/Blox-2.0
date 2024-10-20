#pragma once

#include <GLFW/glfw3.h>

namespace blox
{
    enum class Key {
        // Unknown key
        UNKNOWN = GLFW_KEY_UNKNOWN,

        // Alphabet keys
        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E = GLFW_KEY_E,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        Q = GLFW_KEY_Q,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        V = GLFW_KEY_V,
        W = GLFW_KEY_W,
        X = GLFW_KEY_X,
        Y = GLFW_KEY_Y,
        Z = GLFW_KEY_Z,

        // Number keys (Top row)
        NUMBER_0 = GLFW_KEY_0,
        NUMBER_1 = GLFW_KEY_1,
        NUMBER_2 = GLFW_KEY_2,
        NUMBER_3 = GLFW_KEY_3,
        NUMBER_4 = GLFW_KEY_4,
        NUMBER_5 = GLFW_KEY_5,
        NUMBER_6 = GLFW_KEY_6,
        NUMBER_7 = GLFW_KEY_7,
        NUMBER_8 = GLFW_KEY_8,
        NUMBER_9 = GLFW_KEY_9,

        // Function keys
        F1 = GLFW_KEY_F1,
        F2 = GLFW_KEY_F2,
        F3 = GLFW_KEY_F3,
        F4 = GLFW_KEY_F4,
        F5 = GLFW_KEY_F5,
        F6 = GLFW_KEY_F6,
        F7 = GLFW_KEY_F7,
        F8 = GLFW_KEY_F8,
        F9 = GLFW_KEY_F9,
        F10 = GLFW_KEY_F10,
        F11 = GLFW_KEY_F11,
        F12 = GLFW_KEY_F12,

        // Control keys
        ESCAPE = GLFW_KEY_ESCAPE,
        TAB = GLFW_KEY_TAB,
        CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
        LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
        LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
        LEFT_ALT = GLFW_KEY_LEFT_ALT,
        SPACE = GLFW_KEY_SPACE,
        RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
        RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
        RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
        ENTER = GLFW_KEY_ENTER,
        BACKSPACE = GLFW_KEY_BACKSPACE,

        // Arrow keys
        ARROW_LEFT = GLFW_KEY_LEFT,
        ARROW_RIGHT = GLFW_KEY_RIGHT,
        ARROW_UP = GLFW_KEY_UP,
        ARROW_DOWN = GLFW_KEY_DOWN,

        // Navigation keys
        INSERT = GLFW_KEY_INSERT,
        DELETE = GLFW_KEY_DELETE,
        HOME = GLFW_KEY_HOME,
        END = GLFW_KEY_END,
        PAGE_UP = GLFW_KEY_PAGE_UP,
        PAGE_DOWN = GLFW_KEY_PAGE_DOWN,

        // Modifier keys
        LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
        RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
        MENU = GLFW_KEY_MENU,

        // Punctuation and symbols
        SEMICOLON = GLFW_KEY_SEMICOLON,         // ;
        EQUAL = GLFW_KEY_EQUAL,                 // =
        COMMA = GLFW_KEY_COMMA,                 // ,
        MINUS = GLFW_KEY_MINUS,                 // -
        PERIOD = GLFW_KEY_PERIOD,               // .
        SLASH = GLFW_KEY_SLASH,                 // /
        BACKQUOTE = GLFW_KEY_GRAVE_ACCENT,      // `
        LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,   // [
        BACKSLASH = GLFW_KEY_BACKSLASH,         /* \ */
        RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET, // ]
        APOSTROPHE = GLFW_KEY_APOSTROPHE,       // '

        // Numpad keys
        NUMPAD_0 = GLFW_KEY_KP_0,
        NUMPAD_1 = GLFW_KEY_KP_1,
        NUMPAD_2 = GLFW_KEY_KP_2,
        NUMPAD_3 = GLFW_KEY_KP_3,
        NUMPAD_4 = GLFW_KEY_KP_4,
        NUMPAD_5 = GLFW_KEY_KP_5,
        NUMPAD_6 = GLFW_KEY_KP_6,
        NUMPAD_7 = GLFW_KEY_KP_7,
        NUMPAD_8 = GLFW_KEY_KP_8,
        NUMPAD_9 = GLFW_KEY_KP_9,
        NUMPAD_DECIMAL = GLFW_KEY_KP_DECIMAL,
        NUMPAD_DIVIDE = GLFW_KEY_KP_DIVIDE,
        NUMPAD_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
        NUMPAD_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
        NUMPAD_ADD = GLFW_KEY_KP_ADD,
        NUMPAD_ENTER = GLFW_KEY_KP_ENTER,
        NUMPAD_EQUAL = GLFW_KEY_KP_EQUAL,

        // Lock keys
        NUM_LOCK = GLFW_KEY_NUM_LOCK,
        SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,

        // Additional keys
        PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
        PAUSE = GLFW_KEY_PAUSE,
        APPLICATION = GLFW_KEY_MENU, // Context menu key

        LAST = GLFW_KEY_LAST // Last key index
    };


	class Input
	{
    private:
        static Input input;

        bool keys[(int)Key::LAST] = {};
        bool previousKeys[(int)Key::LAST] = {};

        Input();

	public:
        static void Update(GLFWwindow* window);
		static bool KeyPressed(Key key);
		static bool IsKeyReleased(Key key);
		static bool KeyHeld(Key key);
	};
}