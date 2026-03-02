#pragma once
#include "RHI/RHIDevice.h"
#include "SDL3CommandList.h"

class SDL3Device : public RHIDevice
{
public:
	~SDL3Device();

	bool Initialize(const WindowHandle& windowHandle, uint32_t width, uint32_t height) override;

	void BeginFrame() override { /* SDL_GPU는 Command 시작 시 알아서 처리 */ }
	void EndFrame() override;
	void SubmitCommandList(RHICommandList* cmd) override;
	void Present() override { /* Submit 단계에서 이미 화면에 그려짐 */ }

	RHICommandList* GetCommandList() override { return (RHICommandList*)&m_commandList; }

private:
	SDL_GPUDevice* m_gpuDevice = nullptr;
	SDL_Window* m_window = nullptr;
	SDL3CommandList m_commandList;
};