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
			return (size > 0) ? CreateRef<OpenGLVertexBuffer>(size) : CreateRef<OpenGLVertexBuffer>();
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