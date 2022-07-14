#pragma once

// this entrypoint is to be used by apps, not by the engine

#if defined(DEYO_PLATFORM_WINDOWS)

extern Deyo::Application* Deyo::GetApplication();

int main(int argc, char** argv)
{
	// get the application
	Deyo::Application* app = Deyo::GetApplication();

	// run it
	app->Run();

	// delete it since we're exiting
	delete app;

	return 0;
}

#endif