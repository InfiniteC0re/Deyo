#include <Deyo.h>

class PlaygroundApp : public Deyo::Application
{

};

Deyo::Application* Deyo::GetApplication()
{
	return new PlaygroundApp();
}