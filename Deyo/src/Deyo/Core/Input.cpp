#include "pch.h"
#include "Input.h"

namespace Deyo
{
	Input* Input::s_Instance = nullptr;

	void Input::Create()
	{
		DEYO_ASSERT(s_Instance == nullptr, "You're trying to create second instance of Deyo::Input");

		extern Input* CreateInput();
		s_Instance = CreateInput();
	}
}
