#pragma once

#ifdef DEYO_ENGINE
	#error "This header should only be included by clients"
#else
	#define DEYO_CLIENT
#endif

#include <Deyo/Core/Application.h>
#include <Deyo/Core/Layer.h>
#include <Deyo/Core/Log.h>
#include <Deyo/ImGui/ImGuiLayer.h>

// Entrypoint
#include <Deyo/Core/Entrypoint.h>
