#include "pch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace Deyo
{
	bool Renderer::s_IsInScene = false;
	Matrix4 Renderer::s_ViewProjectionMatrix = Matrix4( 1.0f );
}