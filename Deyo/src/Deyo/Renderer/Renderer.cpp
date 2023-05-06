#include "pch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace Deyo
{
	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray)
	{
		RenderCommand::DrawIndexed(vertexArray);
	}
}