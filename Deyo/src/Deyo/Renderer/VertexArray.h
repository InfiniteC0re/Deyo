#pragma once
#include <Deyo/Core/Core.h>
#include "Buffer.h"

namespace Deyo
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void AddVertexBuffer( const Ref<VertexBuffer>& vertexBuffer ) = 0;
		virtual void SetIndexBuffer( const Ref<IndexBuffer>& indexBuffer ) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};
}