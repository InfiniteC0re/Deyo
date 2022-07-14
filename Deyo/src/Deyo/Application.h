#pragma once
#include "Core.h"

namespace Deyo
{
	class DEYO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Deyo::Application* CreateApplication();
}

