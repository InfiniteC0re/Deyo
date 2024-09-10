#pragma once
#include "Shader.h"
#include "VertexArray.h"

#include "Deyo/Math/TransformObject.h"

namespace Deyo
{
	class Mesh
	{
	public:
		Mesh()
		{
			SetVertexArray( VertexArray::Create() );
			SetShader( nullptr );
		}

		Mesh( const Ref<Shader>& shader )
		{
			SetVertexArray( VertexArray::Create() );
			SetShader( shader );
		}

		void SetVertexArray( const Ref<VertexArray>& vertexArray )
		{
			m_VertexArray = vertexArray;
		}

		void SetShader( const Ref<Shader>& shader )
		{
			m_Shader = shader;
		}

		TransformObject& GetTransformObject()
		{
			return m_Transform;
		}

		Ref<VertexArray>& GetVertexArray()
		{
			return m_VertexArray;
		}

		Ref<Shader>& GetShader()
		{
			return m_Shader;
		}

		const TransformObject& GetTransformObject() const
		{
			return m_Transform;
		}

		const Ref<VertexArray>& GetVertexArray() const
		{
			return m_VertexArray;
		}

		const Ref<Shader>& GetShader() const
		{
			return m_Shader;
		}

		const Matrix4& GetModelMatrix() const
		{
			return m_Transform.GetModelMatrix();
		}

	private:
		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_Shader;
		TransformObject m_Transform;
	};
}