#include "Window.h"
#include <SDL3/SDL.h>

bool Window::Initialize(const char* title, uint32_t width, uint32_t height, uint32_t flags)
{
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

#if defined(ENABLE_VULKAN)
	flags |= SDL_WINDOW_VULKAN;
#endif

	m_window = SDL_CreateWindow(title, width, height, flags);
	if (!m_window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		SDL_Quit();
		return false;
	}
	
	return true;
}

void Window::Release()
{
	if (m_window)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}
	SDL_Quit();
}

bool Window::PollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT: return true;
		case SDL_EVENT_WINDOW_CLOSE_REQUESTED: return true;
		case SDL_EVENT_KEY_DOWN:
			if (event.key.key == SDLK_ESCAPE) return true;
		break;
		case SDL_EVENT_KEY_UP:
			break;
		}
	}
	return false;
}