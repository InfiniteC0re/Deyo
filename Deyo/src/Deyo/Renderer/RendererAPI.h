#pragma once
#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Deyo
{
	class RendererAPI
	{
	public:
		enum class API { None, OpenGL };

		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawArrays(const Ref<VertexArray>& vertexArray, uint32_t count) = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) = 0;
		
		inline static API GetAPI() { return s_API; }
		static Scope<RendererAPI> Create();

	private:
		static API s_API;
	};
}