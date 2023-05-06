#include "pch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Deyo
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	RendererAPI* RendererAPI::Create()
	{
		switch (s_API)
		{
		case API::OpenGL:
			return new OpenGLRendererAPI();
			break;
		default:
			DEYO_ASSERT(false, "Unsupported Renderer API");
			return nullptr;
		}
	}
}