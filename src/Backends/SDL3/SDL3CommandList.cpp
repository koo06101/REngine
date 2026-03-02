#include "SDL3CommandList.h"
#include <SDL3/SDL.h>

void SDL3CommandList::Begin()
{
	m_cmdBuffer = SDL_AcquireGPUCommandBuffer(m_device);
}

void SDL3CommandList::ClearScreen(float r, float g, float b, float a)
{
	if (!m_cmdBuffer) return;

	// Load Swapchain Texture
	SDL_GPUTexture* swapchainTexture;
	if (!SDL_WaitAndAcquireGPUSwapchainTexture(m_cmdBuffer, m_window, &swapchainTexture, nullptr, nullptr))
		return; // Minimum Window or unable

	// Set Render Target(Color Target) and Clear Color
	SDL_GPUColorTargetInfo colorTarget = {};
	colorTarget.texture = swapchainTexture;
	colorTarget.clear_color = { r, g, b, a };
	colorTarget.load_op = SDL_GPU_LOADOP_CLEAR; // overwrite
	colorTarget.store_op = SDL_GPU_STOREOP_STORE;

	// Start Render Pass
	m_renderPass = SDL_BeginGPURenderPass(m_cmdBuffer, &colorTarget, 1, nullptr);
}

void SDL3CommandList::End()
{
	if (m_renderPass)
	{
		SDL_EndGPURenderPass(m_renderPass);
		m_renderPass = nullptr;
	}
}