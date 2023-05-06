#pragma once
#include "RendererAPI.h"

namespace Deyo
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray);

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}