cmake_minimum_required(VERSION 2.8.0)

project(Ctrlr)

include_directories(
	Boost/
	Source/Core
	Source/Lua
	Source/Misc
	Source/MIDI
	Source/UIComponents
	Source/Misc/include
	Source/Misc/luabind
	Source/Misc/lua/include
	Source/Misc/liblo/include
	Source/Misc/libusb/include)

file(GLOB_RECURSE SOURCES "Source/*.cpp")

add_executable(Ctrlr WIN32 ${SOURCES})
