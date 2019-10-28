cmake_minimum_required (VERSION 3.10)
include (PrecompiledHeader.cmake)
project (Ctrlr)
set (Ctrlr_VERSION_MAJOR 6)
set (Ctrlr_VERSION_MINOR 0)

find_package(PkgConfig REQUIRED)
pkg_check_modules (OSLIBS alsa x11 xinerama xext freetype2 webkit2gtk-4.0 gtk+-x11-3.0 libcurl REQUIRED)

add_definitions(-DJUCE_USE_CUSTOM_PLUGIN_STANDALONE_APP=1
		-DJUCE_APP_VERSION=6.0.0
		-DJUCE_APP_VERSION_HEX=0x60000
		-DJucePlugin_Build_VST=1
		-DJucePlugin_Build_VST3=0
		-DJucePlugin_Build_AU=0
		-DJucePlugin_Build_AUv3=0
		-DJucePlugin_Build_RTAS=0
		-DJucePlugin_Build_AAX=0
		-DJucePlugin_Build_Standalone=1
		-DJucePlugin_Build_Unity=0)

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

file(GLOB_RECURSE Core Source/Core/*.cpp)
file(GLOB_RECURSE MIDI Source/MIDI/*.cpp)
file(GLOB_RECURSE UIComponents Source/UIComponents/*.cpp)
file(GLOB_RECURSE Lua Source/Lua/*.cpp)
file(GLOB_RECURSE Plugin Source/Plugin/*.cpp)
file(GLOB_RECURSE Luabind Source/Misc/luabind/*.cpp)
file(GLOB_RECURSE Libusb Source/Misc/libusb/*.c)
list(REMOVE_ITEM Plugin "Source/Core/StandaloneWrapper/CtrlrStandaloneApplication.cpp")
list(REMOVE_ITEM Core Source/Core/stdafx_luabind.cpp)
file(GLOB_RECURSE Lua5.2 Source/Misc/lua/*.c)

add_subdirectory(JuceLibraryCode)

add_executable(Ctrlr 
		${Core}
		${MIDI}
		${UIComponents}
		${Lua}
		${Luabind}
		${Lua5.2}
)

target_link_libraries(Ctrlr JUCE ${OSLIBS_LIBRARIES})
target_compile_options(Ctrlr PRIVATE -w -pthread)
add_precompiled_header(Ctrlr Source/Core/stdafx_luabind.h SOURCE_CXX Source/Core/stadfx_luabind.cpp FORCEINCLUDE)