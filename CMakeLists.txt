cmake_minimum_required(VERSION 3.20)
project(SuRengine CXX)

set(CMAKE_CXX_STANDARD 20) # Modern C++ standard (C++20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	src/Core/Window.cpp
	src/RHI/RHIFactory.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
	"${CMAKE_SOURCE_DIR}/src"
)

# ===== ===== ===== ===== ===== Compile options ===== ===== ===== ===== =====
if(MSVC)
	# Enable warnings as errors for MSVC
	target_compile_options(${PROJECT_NAME} PRIVATE /W3 /WX)

	target_compile_options(${PROJECT_NAME} PRIVATE /utf-8) # Ensure UTF-8 encoding for source files
else()
	# Enable warnings as errors for other compilers
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
endif()
# ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====

# external dependencies
add_subdirectory(external/SDL)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3)

# Backend options
if(B_D3D12)
	set(ENABLE_D3D12 ON CACHE BOOL "Force ON" FORCE)
	set(ENABLE_VULKAN OFF CACHE BOOL "Force OFF" FORCE) set(ENABLE_SDL3 OFF CACHE BOOL "Force OFF" FORCE)
elseif(B_VULKAN)
	set(ENABLE_VULKAN ON CACHE BOOL "Force ON" FORCE)
	set(ENABLE_D3D12 OFF CACHE BOOL "Force OFF" FORCE) set(ENABLE_SDL3 OFF CACHE BOOL "Force OFF" FORCE)
else()
	set(ENABLE_SDL3 ON CACHE BOOL "Force ON" FORCE)
	set(ENABLE_D3D12 OFF CACHE BOOL "Force OFF" FORCE) set(ENABLE_VULKAN OFF CACHE BOOL "Force OFF" FORCE)
endif()

if(ENABLE_D3D12)
	target_compile_definitions(${PROJECT_NAME} PUBLIC ENABLE_D3D12)
	add_subdirectory(src/Backends/D3D12)
	target_link_libraries(${PROJECT_NAME} PRIVATE Backend_D3D12)
endif()

if(ENABLE_VULKAN)
	target_compile_definitions(${PROJECT_NAME} PUBLIC ENABLE_VULKAN)
	add_subdirectory(src/Backends/Vulkan)
	target_link_libraries(${PROJECT_NAME} PRIVATE Backend_Vulkan)
endif()

if(ENABLE_SDL3)
	target_compile_definitions(${PROJECT_NAME} PUBLIC ENABLE_SDL3)
	add_subdirectory(src/Backends/SDL3)
	target_link_libraries(${PROJECT_NAME} PRIVATE Backend_SDL3)
endif()

# Only add the executable if this is the main project being built (not when included as a subdirectory in another project)
if(CMAKE_PROJECT_NAME  STREQUAL PROJECT_NAME)
	add_executable("${PROJECT_NAME}_Example"
		src/Examples/main.cpp
	)

	target_link_libraries("${PROJECT_NAME}_Example" PRIVATE ${PROJECT_NAME})

	set_property(TARGET "${PROJECT_NAME}_Example" PROPERTY FOLDER "${PROJECT_NAME}_Example")
endif()

# ===== Configuration Messages =====
if(WIN32)
    message(STATUS "Windows 환경 감지됨!")
elseif(APPLE)
    message(STATUS "macOS 환경 감지됨!")
elseif(ANDROID)
    message(STATUS "Android 모바일 빌드 감지됨!")
elseif(UNIX AND NOT APPLE)
    message(STATUS "Linux 환경 감지됨!")
endif()

if(ENABLE_D3D12)
	message(STATUS "D3D12를 준비합니다")
endif()
if(ENABLE_VULKAN)
	message(STATUS "Vulkan을 준비합니다")
endif()
if(ENABLE_SDL3)
	message(STATUS "SDL3를 준비합니다")
endif()