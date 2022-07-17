#include "pch.h"
#include <Platform/Windows/WinWindow.h>

WinWindow::WinWindow(const Deyo::WindowFactory::WindowSettings& settings)
{
	// save settings
	m_Data.Title	 = settings.Title;
	m_Data.Width	 = settings.Width;
	m_Data.Height	 = settings.Height;
	m_Data.VSync	 = settings.VSync;

	// apply settings
	SetVSync(m_Data.VSync);
}

void WinWindow::OnUpdate()
{
	// something useful here
}

uint16_t WinWindow::GetWidth() const
{
	return m_Data.Width;
}

uint16_t WinWindow::GetHeight() const
{
	return m_Data.Height;
}

const std::string& WinWindow::GetTitle() const
{
	return m_Data.Title;
}

void* WinWindow::GetNativeWindow() const
{
	return nullptr;
}

void WinWindow::SetEventCallback(const EventCb& callback)
{
	m_Data.EventCallback = callback;
}

bool WinWindow::IsVSync() const
{
	return m_Data.VSync;
}

void WinWindow::SetVSync(bool state)
{
	// todo: enable/disable vsync
	if (state);
	else;

	m_Data.VSync = state;
}
