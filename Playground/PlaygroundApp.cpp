#include <Deyo.h>

class PlaygroundApp : public Deyo::Application
{
public:
	PlaygroundApp()
	{
		DEYO_INFO("Welcome to the test application");
	}
};

Deyo::Application* Deyo::CreateApplication()
{
	return new PlaygroundApp();
}