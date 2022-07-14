#pragma once

// this entrypoint is meant to be used by apps, not by the engine

#if defined(DEYO_PLATFORM_WINDOWS)

extern Deyo::Application* Deyo::CreateApplication();

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