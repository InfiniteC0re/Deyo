#pragma once
#include "Deyo/Renderer/VertexArray.h"
#include "Deyo/Renderer/RendererAPI.h"

#include <glm/glm.hpp>

namespace Deyo
{
	class RenderCommand
	{
	public:
		static void Clear()
		{
			s_RendererAPI->Clear();
		}

		static void SetViewport( uint32_t x, uint32_t y, uint32_t width, uint32_t height )
		{
			s_RendererAPI->SetViewport( x, y, width, height );
		}

		static void SetClearColor( const glm::vec4& color )
		{
			s_RendererAPI->SetClearColor( color );
		}

		static void DrawArrays( const Ref<VertexArray>& vertexArray, uint32_t count )
		{
			s_RendererAPI->DrawArrays( vertexArray, count );
		}

		static void DrawIndexed( const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0 )
		{
			s_RendererAPI->DrawIndexed( vertexArray, indexCount );
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}