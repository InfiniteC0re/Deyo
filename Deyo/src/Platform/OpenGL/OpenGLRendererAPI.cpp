#include "pch.h"
#include "OpenGLRendererAPI.h"

namespace Deyo
{
	void OpenGLRendererAPI::Init()
	{
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA );

		glEnable( GL_DEPTH_TEST );
		glEnable( GL_LINE_SMOOTH );
	}

	void OpenGLRendererAPI::SetClearColor( const glm::vec4& color )
	{
		glClearColor( color.r, color.g, color.b, color.a );
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

	void OpenGLRendererAPI::DrawArrays( const Ref<VertexArray>& vertexArray, uint32_t count )
	{
		vertexArray->Bind();
		glDrawArrays( GL_TRIANGLES, 0, count );
	}

	void OpenGLRendererAPI::DrawIndexed( const Ref<VertexArray>& vertexArray, uint32_t indexCount )
	{
		vertexArray->Bind();
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements( GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr );
	}

	void OpenGLRendererAPI::SetViewport( uint32_t x, uint32_t y, uint32_t width, uint32_t height )
	{
		glViewport( x, y, width, height );
	}
}