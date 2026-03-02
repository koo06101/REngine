#pragma once
#include "RHI/RHIDevice.h"

struct VKInstance;
struct VKSurfaceKHR;

class VulkanDevice : public RHIDevice
{
public:
	~VulkanDevice();

	bool Initialize(const WindowHandle& windowHandle, uint32_t width, uint32_t height) override;

	void BeginFrame() override;
	void EndFrame() override;

	void SubmitCommandList(RHICommandList* cmd) override;
	void Present() override;

	RHICommandList* GetCommandList() override { return nullptr; }

private:
	VkInstance m_instance = nullptr;
	VkSurfaceKHR m_surface = 0;
};