#pragma once
#include <Deyo/Core/Core.h>
#include <Deyo/Renderer/VertexArray.h>

namespace Deyo
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() override;
		void Unbind() override;

		void AddVertexBuffer( const Ref<VertexBuffer>& vertexBuffer ) override;
		void SetIndexBuffer( const Ref<IndexBuffer>& indexBuffer ) override;

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override;
		const Ref<IndexBuffer>& GetIndexBuffer() const override;

	private:
		Ref<IndexBuffer> m_IndexBuffer;
		std::vector<Ref<VertexBuffer>> m_Buffers;
		GLuint m_BufferSlotIndex = 0;
		GLuint m_Id;
	};
}