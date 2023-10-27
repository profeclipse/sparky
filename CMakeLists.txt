cmake_minimum_required(VERSION 3.27.6)

project(sparky
	VERSION 1.0.0
	LANGUAGES CXX C
	)

# Set a default build type if none was specified
set(default_build_type "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_CXX_STANDARD 17)

option(BUILD_DEMO "Build demo application" ON)

message("Sparky Version: ${sparky_VERSION}")

if(DEFINED EMSCRIPTEN)
	set(pkgname "emsparky")
else()
	set(pkgname "sparky")
endif()

message("Package Name: ${pkgname}")

include(GNUInstallDirs)

add_subdirectory(dependencies)
add_subdirectory(sparky)

if(BUILD_DEMO)
	add_subdirectory(sparky-demo)
endif()

include(CMakePackageConfigHelpers)

configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/emconfig.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/${pkgname}-config.cmake"
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${pkgname}
	)

set(version 1.0.0)
set_property(TARGET sparky PROPERTY VERSION ${version})
set_property(TARGET sparky PROPERTY SOVERSION 1)
set_property(TARGET sparky PROPERTY
  INTERFACE_sparky_MAJOR_VERSION 1)
set_property(TARGET sparky APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING sparky_MAJOR_VERSION
)

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${pkgname}-config-version.cmake"
  VERSION "${version}"
  COMPATIBILITY AnyNewerVersion
)

install(TARGETS sparky
	EXPORT ${pkgname}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${pkgname}
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${pkgname}
	FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${pkgname}
	)

install(EXPORT ${pkgname}
	NAMESPACE sparky::
	DESTINATION lib/cmake/${pkgname}
	)

install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/${pkgname}-config.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/${pkgname}-config-version.cmake"
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${pkgname}
	)
