#pragma once
#include <Deyo/Window.h>

class WinWindow : public Deyo::IWindow
{
public:
	using WindowSettings = Deyo::WindowFactory::WindowSettings;

	WinWindow(const Deyo::WindowFactory::WindowSettings& settings);

	virtual void OnUpdate() override;

	virtual uint16_t GetWidth() const override;

	virtual uint16_t GetHeight() const override;

	virtual const std::string& GetTitle() const override;

	virtual void* GetNativeWindow() const override;

	virtual void SetEventCallback(const EventCb& callback) override;

	virtual bool IsVSync() const override;

	virtual void SetVSync(bool state) override;

private:
	struct WindowData : public WindowSettings
	{
		EventCb EventCallback;
	};

private:
	WindowData m_Data;
};

