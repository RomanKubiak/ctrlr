cmake_minimum_required (VERSION 3.10)
include (PrecompiledHeader.cmake)
project (Ctrlr)
set (Ctrlr_VERSION_MAJOR 6)
set (Ctrlr_VERSION_MINOR 0)

set(default_build_type "Release")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(default_build_type "Debug")
endif()
 
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")	
	add_compile_options(-O0 -ggdb -DDEBUG=1 -D_DEBUG=1 -fPIC -fvisibility=hidden)
else()
	add_compile_options(-Os -march=native)
endif()

if (UNIX)
	find_package(PkgConfig REQUIRED)
	pkg_check_modules (OSLIBS alsa x11 xinerama xext freetype2 webkit2gtk-4.0 gtk+-x11-3.0 libcurl gl REQUIRED)
	add_definitions(-DLINUX)
	add_compile_options(-w)
	set(CMAKE_VERBOSE_MAKEFILE TRUE)
endif(UNIX)

add_definitions(-DJUCE_USE_CUSTOM_PLUGIN_STANDALONE_APP=1
		-DJUCE_APP_VERSION=6.0.0
		-DJUCE_APP_VERSION_HEX=0x60000
		-DJucePlugin_Build_VST=0
		-DJucePlugin_Build_VST3=0
		-DJucePlugin_Build_AU=0
		-DJucePlugin_Build_AUv3=0
		-DJucePlugin_Build_RTAS=0
		-DJucePlugin_Build_AAX=0
		-DJucePlugin_Build_Standalone=1
		-DJucePlugin_Build_Unity=0
		-DJUCE_SHARED_CODE)

#set(CFLAGS_VST, "-fPIC -fvisibility=hidden")
#set(LDFLAGS_VST, "-shared -Wl,--no-undefined")

include_directories(${OSLIBS_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/JUCE/modules)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source/Core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source/Plugin)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source/MIDI)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source/Lua)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source/UIComponents)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source/Misc/boost)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source/Misc/vst2sdk)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source/Misc/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source/Misc/luabind)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source/Misc/lua/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source/Misc/libusb/include)

file(GLOB_RECURSE Core Source/Core/*.cpp)
file(GLOB_RECURSE MIDI Source/MIDI/*.cpp)
file(GLOB_RECURSE UIComponents Source/UIComponents/*.cpp)
file(GLOB_RECURSE Lua Source/Lua/*.cpp)
file(GLOB_RECURSE Plugin Source/Plugin/*.cpp)
file(GLOB_RECURSE Luabind Source/Misc/luabind/*.cpp)
file(GLOB_RECURSE Libusb Source/Misc/libusb/*.c)
list(REMOVE_ITEM Core Source/Core/stdafx_luabind.cpp)
list(REMOVE_ITEM CORE Source/Core/StandaloneWrapper/CtrlrStandaloneApplication.cpp)
file(GLOB_RECURSE Lua5.2 Source/Misc/lua/*.c)
file(GLOB_RECURSE Native Source/Native/*.cpp)
file(GLOB LIBR Source/Misc/*.c)
file(GLOB KEYS Source/Misc/keys.cpp)

add_subdirectory(JuceLibraryCode)

add_library(Ctrlr_min
		${Core}
		${MIDI}
		${UIComponents}
		${Lua}
		${Luabind}
		${Lua5.2}
		${Libusb}
		${Native}
		${Plugin}
		${LIBR}
)

add_library (KEYS_lib ${KEYS})

add_executable (Ctrlr Source/Core/StandaloneWrapper/CtrlrStandaloneApplication.cpp)
target_link_libraries(Ctrlr Ctrlr_min KEYS_lib JUCE ${OSLIBS_LIBRARIES} dl pthread z udev bfd)
add_precompiled_header(Ctrlr_min Source/Core/stdafx_luabind.h SOURCE_CXX Source/Core/stadfx_luabind.cpp FORCEINCLUDE)
