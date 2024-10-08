#pragma once
#include "VertexArray.h"

#include <glm/glm.hpp>

namespace Deyo
{
	class RendererAPI
	{
	public:
		enum class API { None, OpenGL };

		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetClearColor( const glm::vec4& color ) = 0;
		virtual void SetViewport( uint32_t x, uint32_t y, uint32_t width, uint32_t height ) = 0;
		virtual void Clear() = 0;

		virtual void DrawArrays( const Ref<VertexArray>& vertexArray, uint32_t count ) = 0;
		virtual void DrawIndexed( const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0 ) = 0;

		inline static API GetAPI() { return s_API; }
		static RendererAPI* Create();

	private:
		static API s_API;
	};
}