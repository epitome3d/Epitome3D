#pragma once

namespace EPITOME
{
	/* 
	 * KeyState codes mirrors GLFW macros,
	 * except for NOTPRESSED, which doesn't
	 * exist in GLFW
	 */
	enum KeyState
	{
		KEYS_RELEASED = 0,
		KEYS_PRESSED = 1,
		KEYS_HELD = 2,
		KEYS_NOTPRESSED = 3
	};

	enum Keys
	{
		KEY_UNKNOWN = 0,

		// PRINTABLE KEYS
		KEY_SPACE = 1,
		KEY_APOSTROPHE = 2,
		KEY_COMMA = 3,
		KEY_MINUS = 4,
		KEY_PERIOD = 5,
		KEY_SLASH = 6,
		KEY_0 = 7,
		KEY_1 = 8,
		KEY_2 = 9,
		KEY_3 = 10,
		KEY_4 = 11,
		KEY_5 = 12,
		KEY_6 = 13,
		KEY_7 = 14,
		KEY_8 = 15,
		KEY_9 = 16,
		KEY_SEMICOLON = 17,
		KEY_EQUAL = 18,
		KEY_A = 19,
		KEY_B = 20,
		KEY_C = 21,
		KEY_D = 22,
		KEY_E = 23,
		KEY_F = 24,
		KEY_G = 25,
		KEY_H = 26,
		KEY_I = 27,
		KEY_J = 28,
		KEY_K = 29,
		KEY_L = 30,
		KEY_M = 31,
		KEY_N = 32,
		KEY_O = 33,
		KEY_P = 34,
		KEY_Q = 35,
		KEY_R = 36,
		KEY_S = 37,
		KEY_T = 38,
		KEY_U = 39,
		KEY_V = 40,
		KEY_W = 41,
		KEY_X = 42,
		KEY_Y = 43,
		KEY_Z = 44,
		KEY_LEFT_BRACKET = 45,
		KEY_BACKSLASH = 46,
		KEY_RIGHT_BRACKET = 47,
		KEY_NON_US_1 = 48,
		KEY_NON_US_2 = 49,

		//FUNCTION KEYS
		KEY_ESCAPE = 50,
		KEY_ENTER = 51,
		KEY_TAB = 52,
		KEY_BACKSPACE = 53,
		KEY_INSERT = 54,
		KEY_DELETE = 55,
		KEY_RIGHT = 56,
		KEY_LEFT = 57,
		KEY_DOWN = 58,
		KEY_UP = 59,
		KEY_PAGE_UP = 60,
		KEY_PAGE_DOWN = 61,
		KEY_HOME = 62,
		KEY_END = 63,
		KEY_CAPS_LOCK = 64,
		KEY_SCROLL_LOCK = 65,
		KEY_NUM_LOCK = 66,
		KEY_PRINT_SCREEN = 67,
		KEY_PAUSE = 68,
		KEY_F1 = 69,
		KEY_F2 = 70,
		KEY_F3 = 71,
		KEY_F4 = 72,
		KEY_F5 = 73,
		KEY_F6 = 74,
		KEY_F7 = 75,
		KEY_F8 = 76,
		KEY_F9 = 77,
		KEY_F10 = 78,
		KEY_F11 = 79,
		KEY_F12 = 80,
		KEY_F13 = 81,
		KEY_F14 = 82,
		KEY_F15 = 83,
		KEY_F16 = 84,
		KEY_F17 = 85,
		KEY_F18 = 86,
		KEY_F19 = 87,
		KEY_F20 = 88,
		KEY_F21 = 89,
		KEY_F22 = 90,
		KEY_F23 = 91,
		KEY_F24 = 92,
		KEY_F25 = 93,
		KEY_KEYPAD_0 = 94,
		KEY_KEYPAD_1 = 95,
		KEY_KEYPAD_2 = 96,
		KEY_KEYPAD_3 = 97,
		KEY_KEYPAD_4 = 98,
		KEY_KEYPAD_5 = 99,
		KEY_KEYPAD_6 = 100,
		KEY_KEYPAD_7 = 101,
		KEY_KEYPAD_8 = 102,
		KEY_KEYPAD_9 = 103,
		KEY_KEYPAD_DECIMAL = 104,
		KEY_KEYPAD_DIVIDE = 105,
		KEY_KEYPAD_MULTIPLY = 106,
		KEY_KEYPAD_SUBTRACT = 107,
		KEY_KEYPAD_ADD = 108,
		KEY_KEYPAD_ENTER = 109,
		KEY_KEYPAD_EQUAL = 110,
		KEY_LEFT_SHIFT = 111,
		KEY_LEFT_CONTROL = 112,
		KEY_LEFT_ALT = 113,
		KEY_LEFT_SUPER = 114,
		KEY_RIGHT_SHIFT = 115,
		KEY_RIGHT_CONTROL = 116,
		KEY_RIGHT_ALT = 117,
		KEY_RIGHT_SUPER = 118,
		KEY_MENU = 119,
		KEY_LAST = KEY_MENU
	};

	const short KEYS_COUNT = (short)KEY_LAST + 1;
}