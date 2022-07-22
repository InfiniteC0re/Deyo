#pragma once

// For client use only

#ifndef DEYO_CLIENT
	#error "Include <Deyo/Deyo.h> instead please"
#endif

extern Deyo::Application* Deyo::CreateApplication();

#ifdef DEYO_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
	// initialize log system
	Deyo::Log::Init();

	DEYO_CORE_INFO("Initialized log system");
	DEYO_CORE_INFO("Welcome to the Deyo Engine");

	// create the application
	Deyo::Application* app = Deyo::CreateApplication();

	// run it
	app->Run();

	// delete it since we're exiting
	delete app;

	return 0;
}

#endif