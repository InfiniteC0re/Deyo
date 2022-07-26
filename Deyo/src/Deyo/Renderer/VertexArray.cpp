#include "pch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include <Platform/OpenGL/OpenGLVertexArray.h>

namespace Deyo
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexArray>();
			break;
		default:
			DEYO_ASSERT(false, "Unsupported Renderer API");
			return nullptr;
		}
	}
}