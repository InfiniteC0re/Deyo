#pragma once
#include <cstdint>

namespace Deyo
{
	using Key = uint16_t;

	enum : Key
	{
		DEYO_KEY_SPACE              = 32,
		DEYO_KEY_APOSTROPHE         = 39,  /* ' */
		DEYO_KEY_COMMA              = 44,  /* , */
		DEYO_KEY_MINUS              = 45,  /* - */
		DEYO_KEY_PERIOD             = 46,  /* . */
		DEYO_KEY_SLASH              = 47,  /* / */
		DEYO_KEY_0                  = 48,
		DEYO_KEY_1                  = 49,
		DEYO_KEY_2                  = 50,
		DEYO_KEY_3                  = 51,
		DEYO_KEY_4                  = 52,
		DEYO_KEY_5                  = 53,
		DEYO_KEY_6                  = 54,
		DEYO_KEY_7                  = 55,
		DEYO_KEY_8                  = 56,
		DEYO_KEY_9                  = 57,
		DEYO_KEY_SEMICOLON          = 59,  /* ; */
		DEYO_KEY_EQUAL              = 61,  /* = */
		DEYO_KEY_A                  = 65,
		DEYO_KEY_B                  = 66,
		DEYO_KEY_C                  = 67,
		DEYO_KEY_D                  = 68,
		DEYO_KEY_E                  = 69,
		DEYO_KEY_F                  = 70,
		DEYO_KEY_G                  = 71,
		DEYO_KEY_H                  = 72,
		DEYO_KEY_I                  = 73,
		DEYO_KEY_J                  = 74,
		DEYO_KEY_K                  = 75,
		DEYO_KEY_L                  = 76,
		DEYO_KEY_M                  = 77,
		DEYO_KEY_N                  = 78,
		DEYO_KEY_O                  = 79,
		DEYO_KEY_P                  = 80,
		DEYO_KEY_Q                  = 81,
		DEYO_KEY_R                  = 82,
		DEYO_KEY_S                  = 83,
		DEYO_KEY_T                  = 84,
		DEYO_KEY_U                  = 85,
		DEYO_KEY_V                  = 86,
		DEYO_KEY_W                  = 87,
		DEYO_KEY_X                  = 88,
		DEYO_KEY_Y                  = 89,
		DEYO_KEY_Z                  = 90,
		DEYO_KEY_LEFT_BRACKET       = 91,  /* [ */
		DEYO_KEY_BACKSLASH          = 92,  /* \ */
		DEYO_KEY_RIGHT_BRACKET      = 93,  /* ] */
		DEYO_KEY_GRAVE_ACCENT       = 96,  /* ` */
		DEYO_KEY_WORLD_1            = 161, /* non-US #1 */
		DEYO_KEY_WORLD_2            = 162, /* non-US #2 */

		/* Function keys */
		DEYO_KEY_ESCAPE             = 256,
		DEYO_KEY_ENTER              = 257,
		DEYO_KEY_TAB                = 258,
		DEYO_KEY_BACKSPACE          = 259,
		DEYO_KEY_INSERT             = 260,
		DEYO_KEY_DELETE             = 261,
		DEYO_KEY_RIGHT              = 262,
		DEYO_KEY_LEFT               = 263,
		DEYO_KEY_DOWN               = 264,
		DEYO_KEY_UP                 = 265,
		DEYO_KEY_PAGE_UP            = 266,
		DEYO_KEY_PAGE_DOWN          = 267,
		DEYO_KEY_HOME               = 268,
		DEYO_KEY_END                = 269,
		DEYO_KEY_CAPS_LOCK          = 280,
		DEYO_KEY_SCROLL_LOCK        = 281,
		DEYO_KEY_NUM_LOCK           = 282,
		DEYO_KEY_PRINT_SCREEN       = 283,
		DEYO_KEY_PAUSE              = 284,
		DEYO_KEY_F1                 = 290,
		DEYO_KEY_F2                 = 291,
		DEYO_KEY_F3                 = 292,
		DEYO_KEY_F4                 = 293,
		DEYO_KEY_F5                 = 294,
		DEYO_KEY_F6                 = 295,
		DEYO_KEY_F7                 = 296,
		DEYO_KEY_F8                 = 297,
		DEYO_KEY_F9                 = 298,
		DEYO_KEY_F10                = 299,
		DEYO_KEY_F11                = 300,
		DEYO_KEY_F12                = 301,
		DEYO_KEY_F13                = 302,
		DEYO_KEY_F14                = 303,
		DEYO_KEY_F15                = 304,
		DEYO_KEY_F16                = 305,
		DEYO_KEY_F17                = 306,
		DEYO_KEY_F18                = 307,
		DEYO_KEY_F19                = 308,
		DEYO_KEY_F20                = 309,
		DEYO_KEY_F21                = 310,
		DEYO_KEY_F22                = 311,
		DEYO_KEY_F23                = 312,
		DEYO_KEY_F24                = 313,
		DEYO_KEY_F25                = 314,
		DEYO_KEY_KP_0               = 320,
		DEYO_KEY_KP_1               = 321,
		DEYO_KEY_KP_2               = 322,
		DEYO_KEY_KP_3               = 323,
		DEYO_KEY_KP_4               = 324,
		DEYO_KEY_KP_5               = 325,
		DEYO_KEY_KP_6               = 326,
		DEYO_KEY_KP_7               = 327,
		DEYO_KEY_KP_8               = 328,
		DEYO_KEY_KP_9               = 329,
		DEYO_KEY_KP_DECIMAL         = 330,
		DEYO_KEY_KP_DIVIDE          = 331,
		DEYO_KEY_KP_MULTIPLY        = 332,
		DEYO_KEY_KP_SUBTRACT        = 333,
		DEYO_KEY_KP_ADD             = 334,
		DEYO_KEY_KP_ENTER           = 335,
		DEYO_KEY_KP_EQUAL           = 336,
		DEYO_KEY_LEFT_SHIFT         = 340,
		DEYO_KEY_LEFT_CONTROL       = 341,
		DEYO_KEY_LEFT_ALT           = 342,
		DEYO_KEY_LEFT_SUPER         = 343,
		DEYO_KEY_RIGHT_SHIFT        = 344,
		DEYO_KEY_RIGHT_CONTROL      = 345,
		DEYO_KEY_RIGHT_ALT          = 346,
		DEYO_KEY_RIGHT_SUPER        = 347,
		DEYO_KEY_MENU               = 348,
	};
}