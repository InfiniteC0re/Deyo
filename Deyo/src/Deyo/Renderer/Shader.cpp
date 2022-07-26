#include "pch.h"
#include "Shader.h"

#include <Deyo/Renderer/Renderer.h>
#include <Platform/OpenGL/OpenGLShader.h>

namespace Deyo
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(filepath);
			break;
		default:
			DEYO_ASSERT(false, "Unsupported Renderer API");
			return nullptr;
		}
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& pixelSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(name, vertexSrc, pixelSrc);
			break;
		default:
			DEYO_ASSERT(false, "Unsupported Renderer API");
			return nullptr;
		}
	}
}