#include "pch.h"
#include "Buffer.h"
#include "Renderer.h"

#include <Platform/OpenGL/OpenGLBuffer.h>

namespace Deyo
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			if (size > 0) { return CreateRef<OpenGLVertexBuffer>(size); }
			else { return CreateRef<OpenGLVertexBuffer>(); }
			break;
		default:
			DEYO_ASSERT(false, "Unsupported Renderer API");
			return nullptr;
		}
	}

	Deyo::Ref<Deyo::IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(indices, size);
			break;
		default:
			DEYO_ASSERT(false, "Unsupported Renderer API");
			return nullptr;
		}
	}

}