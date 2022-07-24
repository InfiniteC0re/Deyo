#include "pch.h"
#include "RenderCommand.h"

namespace Deyo
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}