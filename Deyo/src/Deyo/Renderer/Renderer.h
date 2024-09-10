#pragma once
#include "RendererAPI.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"

namespace Deyo
{
	class Renderer
	{
	public:
		static void BeginScene( Camera& camera )
		{
			DEYO_ASSERT( !s_IsInScene, "Already in the scene" );
			camera.Update();
			s_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
			s_IsInScene = true;
		}

		static void EndScene()
		{
			DEYO_ASSERT( s_IsInScene, "Not in scene" );
			s_IsInScene = false;
		}

		static void Submit( const Mesh& mesh )
		{
			auto shader = mesh.GetShader();

			shader->Bind();
			shader->SetMat4( "u_ViewProjection", s_ViewProjectionMatrix );
			shader->SetMat4( "u_Transform", mesh.GetModelMatrix() );

			RenderCommand::DrawIndexed( mesh.GetVertexArray() );
		}

		static void Submit( const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const Matrix4& transform )
		{
			shader->Bind();
			shader->SetMat4( "u_ViewProjection", s_ViewProjectionMatrix );
			shader->SetMat4( "u_Transform", transform );

			RenderCommand::DrawIndexed( vertexArray );
		}

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		static bool s_IsInScene;
		static Matrix4 s_ViewProjectionMatrix;
	};
}