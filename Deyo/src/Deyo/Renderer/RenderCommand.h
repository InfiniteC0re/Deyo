#pragma once
#include <glm/glm.hpp>

#include <Deyo/Core/Core.h>
#include <Deyo/Renderer/VertexArray.h>
#include <Deyo/Renderer/RendererAPI.h>

namespace Deyo
{
	class RenderCommand
	{
	public:
		static inline void Clear() { s_RendererAPI->Clear(); }
		static inline void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_RendererAPI->SetViewport(x, y, width, height); }
		static inline void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }

		static inline void DrawArrays(const Ref<VertexArray>& vertexArray, uint32_t count) { s_RendererAPI->DrawArrays(vertexArray, count); }
		static inline void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) { s_RendererAPI->DrawIndexed(vertexArray, count); }
	
	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}