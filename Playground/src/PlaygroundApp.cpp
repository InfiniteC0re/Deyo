#include <Deyo.h>

class TestLayer : public Deyo::Layer
{
public:
	TestLayer() : Layer("TestLayer") {};

	void OnEvent(Deyo::Event& e) override
	{
		DEYO_INFO("FirstLayer: {0}", e.ToString());
		e.SetHandled(true);
	}
};

class PlaygroundApp : public Deyo::Application
{
public:
	PlaygroundApp()
	{
		PushLayer(new TestLayer());
	}
};

Deyo::Application* Deyo::CreateApplication()
{
	return new PlaygroundApp();
}