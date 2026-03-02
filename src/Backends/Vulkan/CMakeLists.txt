add_library(Backend_Vulkan STATIC
	VulkanDevice.cpp
)

find_package(Vulkan REQUIRED)

target_link_libraries(Backend_Vulkan PRIVATE
	SDL3::SDL3
	Vulkan::Vulkan
)

target_include_directories(Backend_Vulkan PRIVATE
	${CMAKE_SOURCE_DIR}/src
)