#include <Deyo.h>

class PlaygroundApp : public Deyo::Application
{
public:
	PlaygroundApp()
	{
		PushOverlay(new Deyo::ImGuiLayer());
	}
};

Deyo::Application* Deyo::CreateApplication()
{
	return new PlaygroundApp();
}