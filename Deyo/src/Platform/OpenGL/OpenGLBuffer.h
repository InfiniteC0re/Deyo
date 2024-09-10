#pragma once
#include <Deyo/Renderer/Buffer.h>

namespace Deyo
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer();
		OpenGLVertexBuffer( uint32_t size );
		OpenGLVertexBuffer( const void* data, uint32_t size );
		~OpenGLVertexBuffer();

		virtual void SetData( const void* data, uint32_t size ) override;
		virtual void SetData( const void* data, uint32_t offset, uint32_t size ) override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override;
		virtual void SetLayout( const BufferLayout& layout ) override;

	private:
		BufferLayout m_Layout;
		GLuint m_Id;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer( uint32_t* indices, uint32_t count );
		~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override;

	private:
		GLuint m_Id;
		uint32_t m_Count;
	};
}