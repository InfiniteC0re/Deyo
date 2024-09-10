#include "pch.h"
#include "OpenGLBuffer.h"

namespace Deyo
{
	/////////////////////////////////////////////////
	// OpenGLVertexBuffer
	/////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer()
	{
		glGenBuffers( 1, &m_Id );
		glBindBuffer( GL_ARRAY_BUFFER, m_Id );
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer( uint32_t size )
	{
		glGenBuffers( 1, &m_Id );
		glBindBuffer( GL_ARRAY_BUFFER, m_Id );
		glBufferData( GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW );
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer( const void* data, uint32_t size )
	{
		glGenBuffers( 1, &m_Id );
		glBindBuffer( GL_ARRAY_BUFFER, m_Id );
		glBufferData( GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW );
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers( 1, &m_Id );
	}

	void OpenGLVertexBuffer::SetData( const void* data, uint32_t offset, uint32_t size )
	{
		glBindBuffer( GL_ARRAY_BUFFER, m_Id );
		glBufferSubData( GL_ARRAY_BUFFER, offset, size, data );
	}

	void OpenGLVertexBuffer::SetData( const void* data, uint32_t size )
	{
		glBindBuffer( GL_ARRAY_BUFFER, m_Id );
		glBufferData( GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW );
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer( GL_ARRAY_BUFFER, m_Id );
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
	}

	const Deyo::BufferLayout& OpenGLVertexBuffer::GetLayout() const
	{
		return m_Layout;
	}

	void OpenGLVertexBuffer::SetLayout( const BufferLayout& layout )
	{
		m_Layout = layout;
	}

	/////////////////////////////////////////////////
	// OpenGLIndexBuffer
	/////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer( uint32_t* indices, uint32_t count )
	{
		glGenBuffers( 1, &m_Id );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_Id );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( uint32_t ) * count, indices, GL_STATIC_DRAW );
		m_Count = count;
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers( 1, &m_Id );
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_Id );
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	}

	uint32_t OpenGLIndexBuffer::GetCount() const
	{
		return m_Count;
	}
}