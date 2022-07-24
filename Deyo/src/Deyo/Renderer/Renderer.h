#pragma once
#include "RendererAPI.h"

namespace Deyo
{
	class Renderer
	{
	public:
		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}