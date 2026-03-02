#pragma once
#include "RHI/RHIDevice.h"

struct SDL_Window;

class Window
{
public:
	bool Initialize(const char* title, uint32_t width, uint32_t height, uint32_t flags);
	void Release();

	bool PollEvents();

	WindowHandle GetHandle() { return { m_window }; }

private:
	SDL_Window* m_window;
};