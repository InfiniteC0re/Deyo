#pragma once
#include <Deyo/Renderer/RendererAPI.h>

namespace Deyo
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		OpenGLRendererAPI() = default;

		void Init() override;
		void Clear() override;
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void SetClearColor(const glm::vec4& color) override;

		void DrawArrays(const Ref<VertexArray>& vertexArray, uint32_t count) override;
		void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
	};
}