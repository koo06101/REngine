#pragma once
#include "RHI/RHICommandList.h"

struct SDL_Window;
struct SDL_GPUDevice;
struct SDL_GPUCommandBuffer;
struct SDL_GPURenderPass;

class SDL3CommandList : public RHICommandList
{
public:
	void SetDevice(SDL_GPUDevice* device, SDL_Window* window)
	{
		m_device = device;
		m_window = window;
	}
	
	void Begin() override;
	void ClearScreen(float r, float g, float b, float a) override;
	void End() override;

	SDL_GPUCommandBuffer* GetNativeCmd() { return m_cmdBuffer; }
	
private:
	SDL_GPUDevice* m_device = nullptr;
	SDL_Window* m_window = nullptr;
	SDL_GPUCommandBuffer* m_cmdBuffer = nullptr;
	SDL_GPURenderPass* m_renderPass = nullptr;
};