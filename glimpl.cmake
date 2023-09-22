set(warnings
	-Wall
	-Wextra
	-Wno-unused-parameter
	-Wno-sign-compare
	-Wno-missing-field-initializers
	-Wno-switch
	-Wno-unused-variable
	-Wno-unused-private-field
	-Wno-logical-op-parentheses
	-Wno-logical-not-parentheses
	-Wno-bitwise-op-parentheses
	-Wno-unused-value
	-Wno-null-conversion
	-Wno-unused-function
	-Wno-missing-braces
	-Wno-char-subscripts
	-Wno-format
	-Wno-implicit-function-declaration
	-Wno-incompatible-pointer-types-discards-qualifiers
)

add_compile_options(
	${warnings}
	$<$<CONFIG:RELEASE>:-Ofast>
	$<$<CONFIG:DEBUG>:-g>
)

FetchContent_Declare(
       glfw
       GIT_REPOSITORY https://github.com/glfw/glfw
)
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
   	FetchContent_Populate(glfw)
   	set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
   	set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
   	set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
   	set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
	add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

FetchContent_Declare(
	glad
	GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)
FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
   	FetchContent_Populate(glad)
   	set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
   	set(GLAD_API "gl=,gles=" CACHE STRING
		"API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
   	set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
   	add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
endif()

FetchContent_Declare(
	FreeImage
	GIT_REPOSITORY https://github.com/danoli3/FreeImage.git
)
FetchContent_MakeAvailable(FreeImage)

if(0)
FetchContent_Declare(
	Freetype
	GIT_REPOSITORY https://gitlab.freedesktop.org/freetype/freetype.git
)
FetchContent_MakeAvailable(Freetype)

FetchContent_Declare(
	freetype-gl
	GIT_REPOSITORY https://github.com/rougier/freetype-gl.git
)
set(freetype-gl_WITH_GLAD ON)
set(freetype-gl_BUILD_DEMOS OFF)
set(freetype-gl_BUILD_APIDOC OFF)
set(freetype-gl_BUILD_MAKEFONT OFF)
set(freetype-gl_BUILD_TESTS OFF)
include_directories(
	${glad_BINARY_DIR}/include
)
FetchContent_MakeAvailable(freetype-gl)
else()
add_subdirectory(dependencies)
endif()
