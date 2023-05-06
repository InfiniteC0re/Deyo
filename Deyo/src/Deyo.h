#pragma once

#ifdef DEYO_ENGINE
	#error "This header should only be included by clients"
#else
	#define DEYO_CLIENT
#endif

#include <Deyo/Core/Application.h>
#include <Deyo/Core/Action.h>
#include <Deyo/Core/Input.h>
#include <Deyo/Core/Layer.h>
#include <Deyo/Core/KeyCodes.h>
#include <Deyo/Core/Log.h>

#include <Deyo/Events/Event.h>

#include <Deyo/Renderer/RenderCommand.h>
#include <Deyo/Renderer/VertexArray.h>
#include <Deyo/Renderer/Shader.h>

#include <Deyo/ImGui/ImGuiLayer.h>

#include <Deyo/FileSystem/FileManager.h>
#include <Deyo/FileSystem/FileSystem.h>

// Entry point
#include <Deyo/Core/EntryPoint.h>
