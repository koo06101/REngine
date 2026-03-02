#include "SDL3Device.h"
#include <SDL3/SDL.h>

SDL3Device::~SDL3Device()
{
	if (m_gpuDevice)
	{
		// 창 연결 해제 및 디바이스 파괴
		SDL_ReleaseWindowFromGPUDevice(m_gpuDevice, m_window);
		SDL_DestroyGPUDevice(m_gpuDevice);
	}
}

bool SDL3Device::Initialize(const WindowHandle& windowHandle, uint32_t width, uint32_t height)
{
	m_window = static_cast<SDL_Window*>(windowHandle.windowPointer);

	// auto select backend
	m_gpuDevice = SDL_CreateGPUDevice(
		SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL,
		true,
		nullptr
	);
	if (!m_gpuDevice) return false;

	// connect window to GPU Device (connect Swapchain)
	if (!SDL_ClaimWindowForGPUDevice(m_gpuDevice, m_window)) return false;

	m_commandList.SetDevice(m_gpuDevice, m_window);
	return true;
}

void SDL3Device::SubmitCommandList(RHICommandList* cmd)
{
	SDL3CommandList* sdlCmd = static_cast<SDL3CommandList*>(cmd);

	SDL_SubmitGPUCommandBuffer(sdlCmd->GetNativeCmd());
}

void SDL3Device::EndFrame()
{
	
}