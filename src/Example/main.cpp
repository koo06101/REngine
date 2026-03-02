#include "Core/Window.h"
#include "RHI/RHI.h"
#include <SDL3/SDL.h>
#include <string.h>

int main()
{
	char title[256] = {};
#if defined(ENABLE_D3D12)
	strncpy_s(title, "D3D12 Renderer", sizeof(title));
#elif defined(ENABLE_VULKAN)
	strncpy_s(title, "Vulkan Renderer", sizeof(title));
#elif defined(ENABLE_SDL3)
	strncpy_s(title, "SDL3 Renderer", sizeof(title));
#endif
	
	Window window;
	if(!window.Initialize(title, 800, 600, SDL_WINDOW_RESIZABLE)) return -1;

	RHIDevice* device = CreateRHIDevice();
	device->Initialize(window.GetHandle(), 800, 600);
	
	bool quit = false;
	while (!quit)
	{
		quit = window.PollEvents();

		device->BeginFrame();
		
		RHICommandList* cmd = device->GetCommandList();
		cmd->Begin();
		cmd->ClearScreen(0.4f, 0.7f, 1.0f, 1.0f);
		// Render
		cmd->End();

		device->SubmitCommandList(cmd);
		
		device->Present(); // to swapchain

		device->EndFrame();
	}
	delete device;
	
	window.Release();
	return 0;
}