cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(Ctrlr)

message("PROJECT_TARGET: ${PROJECT_TARGET}")
message("TARGET_SOURCES: ${TARGET_SOURCES}")
message("TARGET_COMPILE_DEFINITIONS: ${TARGET_COMPILE_OPTIONS}")
message("TARGET_LIBRARIES: ${TARGET_LIBRARIES}")
message("TARGET_LINKER_FLAGS: ${TARGET_LINKER_FLAGS}")

add_executable(${PROJECT_NAME} "")

# If build type not passed assume it is Debug
if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
    message(STATUS "CMAKE_BUILD_TYPE not set, assuming debug build...")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Build type: Debug")
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DDEBUG)
    #target_compile_options(${PROJECT_NAME} PUBLIC -O3)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Build type: Release")
    target_compile_options(${PROJECT_NAME} PUBLIC -O0)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    message(STATUS "Build type: RelWithDebInfo")
    target_compile_options(${PROJECT_NAME} PUBLIC -O0)
    target_compile_options(${PROJECT_NAME} PUBLIC -g3)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DDEBUG)
endif ()

set(PROJECT_LIB_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/" CACHE STRING "Output path for static libraries")
message("Setting PROJECT_LIB_DIRECTORY to ${PROJECT_LIB_DIRECTORY}")
target_link_directories(${PROJECT_NAME} PUBLIC ${PROJECT_LIB_DIRECTORY})

target_compile_definitions(${PROJECT_NAME} PUBLIC ${PROJECT_CONFIG_DEFINITIONS})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${TARGET_COMPILE_DEFINITIONS})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${PROJECT_TARGET})

target_compile_options(${PROJECT_NAME} PUBLIC ${TARGET_COMPILE_OPTIONS})
target_compile_options(${PROJECT_NAME} PUBLIC $<$<COMPILE_LANGUAGE:C>:-std=c++17>)


target_compile_features(${PROJECT_NAME} PUBLIC
        ${TARGET_COMPILE_FEATURES})


# Warnings related flags
target_compile_options(${PROJECT_NAME} PUBLIC -Wall)
target_compile_options(${PROJECT_NAME} PUBLIC $<$<COMPILE_LANGUAGE:C>:-Wno-discarded-qualifiers>)

target_sources(${CMAKE_PROJECT_NAME} PUBLIC ${TARGET_SOURCES})
target_sources(${CMAKE_PROJECT_NAME}
        PRIVATE
        Source/Core/StandaloneWrapper/CtrlrStandaloneApplication.cpp      
        PUBLIC
        Source/Core/StandaloneWrapper/CtrlrStandaloneWindow.h
        )

message("${PROJECT_NAME}: add_subdirectory Source/Core")
add_subdirectory(Source/Core)

message("${PROJECT_NAME}: add_subdirectory Source/Lua")
add_subdirectory(Source/Lua)

message("${PROJECT_NAME}: add_subdirectory Source/Misc")
add_subdirectory(Source/Misc)

message("${PROJECT_NAME}: add_subdirectory Source/UIComponents")
add_subdirectory(Source/UIComponents)

message("${PROJECT_NAME}: add_subdirectory Source/Native")
add_subdirectory(Source/Native)

message("${PROJECT_NAME}: add_subdirectory Source/Plugin")
add_subdirectory(Source/Plugin)

message("${PROJECT_NAME}: add_subdirectory Source/MIDI")
add_subdirectory(Source/MIDI)

target_link_libraries(${PROJECT_NAME} ${TARGET_LIBRARIES})
target_link_options(${PROJECT_NAME} PUBLIC ${TARGET_LINK_OPTIONS})
