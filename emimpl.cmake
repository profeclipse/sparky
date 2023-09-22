set(warnings
	-Wall
	-Wextra
	-Wno-unused-parameter
	-Wno-deprecated-declarations
	-Wno-unused-but-set-variable
	-Wno-deprecated-non-prototype
	-Wno-implicit-function-declaration
	-Wno-misleading-indentation
	-Wno-switch
	-Wno-sign-compare
	-Wno-unused-variable
	-Wno-unused-const-variable
	-Wno-format
	-Wno-unused-private-field
	-Wno-logical-op-parentheses
	-Wno-logical-not-parentheses
	-Wno-unused-value
	-Wno-deprecated-copy-with-user-provided-copy
	-Wno-unused-function
	-Wno-bitwise-op-parentheses
	-Wno-missing-field-initializers
	-Wno-missing-braces
	-Wno-char-subscripts
	-Wno-null-pointer-subtraction
	-Wno-incompatible-pointer-types-discards-qualifiers
)

add_compile_options(
	${warnings}
)

add_link_options(
	--preload-file ${PROJECT_SOURCE_DIR}/sparky-demo/src/res@res
	-sUSE_GLFW=3
	-sMAX_WEBGL_VERSION=2
	-sFULL_ES3=1
	-sASSERTIONS=1
	-sWASM=1
	-sASYNCIFY
)
set(CMAKE_EXECUTABLE_SUFFIX ".html")

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
set(freetype-gl_BUILD_DEMOS OFF)
set(freetype-gl_BUILD_APIDOC OFF)
set(freetype-gl_BUILD_TESTS OFF)
set(freetype-gl_BUILD_MAKEFONT OFF)
set(freetype-gl_WITH_GLEW OFF)
include_directories(
	${glad_BINARY_DIR}/include
)
set(FREETYPE_LIBRARY ${freetype_BINARY_DIR}/freetype.bc)
set(FREETYPE_INCLUDE_DIRS ${freetype_SOURCE_DIR}/include)
FetchContent_MakeAvailable(freetype-gl)
else()
add_subdirectory(dependencies)
endif()
