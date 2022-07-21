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
#include <Deyo/Core/Log.h>

#include <Deyo/Events/Event.h>

#include <Deyo/ImGui/ImGuiLayer.h>

// Entry point
#include <Deyo/Core/EntryPoint.h>
