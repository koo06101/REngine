#include "VulkanDevice.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

VulkanDevice::~VulkanDevice()
{
	if (m_surface) SDL_Vulkan_DestroySurface(m_instance, m_surface, NULL);
}

bool VulkanDevice::Initialize(const WindowHandle& windowHandle, uint32_t width, uint32_t height)
{
	SDL_Window* window = static_cast<SDL_Window*>(windowHandle.windowPointer);

	// 1. Vulkan instance creation

	if (!SDL_Vulkan_CreateSurface(window, m_instance, NULL, &m_surface))
	{
		return false;
	}

	return true;
}

void VulkanDevice::BeginFrame()
{
}

void VulkanDevice::EndFrame()
{
}

void VulkanDevice::SubmitCommandList(RHICommandList* cmd)
{
}

void VulkanDevice::Present()
{
}