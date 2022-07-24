#include "pch.h"
#include "OpenGLVertexArray.h"

namespace Deyo
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_Id);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_Id);
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_Id);
	}

	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& buffer)
	{
		DEYO_ASSERT(buffer->GetLayout().GetElements().size() > 0, "Vertex buffer doesn't have a layout");
		glBindVertexArray(m_Id);
		buffer->Bind();
		
		auto& layout = buffer->GetLayout();
		auto& elements = layout.GetElements();

		for (auto& element : elements)
		{
			switch (element.GetType())
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
				glEnableVertexAttribArray(m_BufferSlotIndex);
				glVertexAttribPointer(m_BufferSlotIndex++, element.GetComponentCount(), GL_FLOAT, element.GetNormalized(), layout.GetStride(), (void*)element.GetOffset());
				break;
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
				glEnableVertexAttribArray(m_BufferSlotIndex);
				glVertexAttribIPointer(m_BufferSlotIndex++, element.GetComponentCount(), GL_INT, layout.GetStride(), (void*)element.GetOffset());
				break;
			case ShaderDataType::Bool:
				glEnableVertexAttribArray(m_BufferSlotIndex);
				glVertexAttribIPointer(m_BufferSlotIndex++, element.GetComponentCount(), GL_BOOL, layout.GetStride(), (void*)element.GetOffset());
				break;
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(m_BufferSlotIndex);
					glVertexAttribPointer(m_BufferSlotIndex, count, GL_FLOAT, element.GetNormalized(), layout.GetStride(), (void*)(element.GetOffset() + sizeof(float) * count * i));
					glVertexAttribDivisor(m_BufferSlotIndex++, 1);
				}
			}
			}
		}
		
		m_Buffers.push_back(buffer);
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_Id);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

	const std::vector<Deyo::Ref<Deyo::VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
	{
		return m_Buffers;
	}

	const Deyo::Ref<Deyo::IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}

}

