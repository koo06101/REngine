add_library(Backend_SDL3 STATIC
	"SDL3Device.cpp"
	"SDL3CommandList.cpp"
)

target_link_libraries(Backend_SDL3 PRIVATE
	SDL3::SDL3
)

target_include_directories(Backend_SDL3 PRIVATE
	${CMAKE_SOURCE_DIR}/src
)