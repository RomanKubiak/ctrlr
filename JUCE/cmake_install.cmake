# Install script for directory: /vm/devel/ctrlr/JUCE

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-6.0.7" TYPE FILE FILES
    "/vm/devel/ctrlr/JUCE/JUCEConfigVersion.cmake"
    "/vm/devel/ctrlr/JUCE/JUCEConfig.cmake"
    "/vm/devel/ctrlr/JUCE/extras/Build/CMake/JUCEHelperTargets.cmake"
    "/vm/devel/ctrlr/JUCE/extras/Build/CMake/JUCECheckAtomic.cmake"
    "/vm/devel/ctrlr/JUCE/extras/Build/CMake/JUCEUtils.cmake"
    "/vm/devel/ctrlr/JUCE/extras/Build/CMake/LaunchScreen.storyboard"
    "/vm/devel/ctrlr/JUCE/extras/Build/CMake/PIPAudioProcessor.cpp.in"
    "/vm/devel/ctrlr/JUCE/extras/Build/CMake/PIPComponent.cpp.in"
    "/vm/devel/ctrlr/JUCE/extras/Build/CMake/PIPConsole.cpp.in"
    "/vm/devel/ctrlr/JUCE/extras/Build/CMake/RecentFilesMenuTemplate.nib"
    "/vm/devel/ctrlr/JUCE/extras/Build/CMake/UnityPluginGUIScript.cs.in"
    "/vm/devel/ctrlr/JUCE/extras/Build/CMake/copyDir.cmake"
    "/vm/devel/ctrlr/JUCE/extras/Build/CMake/juce_runtime_arch_detection.cpp"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/vm/devel/ctrlr/JUCE/modules/cmake_install.cmake")
  include("/vm/devel/ctrlr/JUCE/extras/Build/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/vm/devel/ctrlr/JUCE/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
