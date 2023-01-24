cmake_minimum_required(VERSION 3.23)

if(APPLE)
	set(CMAKE_OSX_DEPLOYMENT_TARGET 10.15 CACHE STRING "")
	set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "Build architectures for Mac OS X" FORCE)
endif(APPLE)

SET(CMAKE_C_LINK_EXECUTABLE ${CMAKE_CXX_LINK_EXECUTABLE})

project(ctrlr VERSION 5.7.1)
set(CTRLR_LUA_VERSION "5.1")

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH
	${CMAKE_SOURCE_DIR}/cmake
	${CMAKE_SOURCE_DIR}/config
	${CMAKE_SOURCE_DIR}/config/platform
)


find_package(PkgConfig REQUIRED)
include(ExternalProject)
include(CheckCXXSourceCompiles)

#find_package(lua5.1 REQUIRED)
pkg_check_modules(LUA REQUIRED IMPORTED_TARGET lua${CTRLR_LUA_VERSION})
if (LUA_FOUND)
else(LUA_FOUND)
	ExternalProject_Add(lua
		URL https://www.lua.org/ftp/lua-5.1.5.tar.gz
		CONFIGURE_COMMAND ""
		BUILD_COMMAND make generic
		BUILD_ALWAYS true
		BUILD_IN_SOURCE true
		INSTALL_COMMAND ""
	)
	add_library(liblua STATIC IMPORTED)
	add_library(PkgConfig::LUA ALIAS lua)
	ExternalProject_Get_property(lua SOURCE_DIR)
	message("liblua will be found at \'${SOURCE_DIR}/src\'")
endif(LUA_FOUND)

#find_package(lua5.1-bitop REQUIRED)
pkg_check_modules(LUABITOP
		 REQUIRED
		 IMPORTED_TARGET lua${CTRLR_LUA_VERSION}-bitop
)
message("searching for luabind in  \'${CMAKE_MODULE_PATH}/src\'")

find_package(Luabind REQUIRED)
list(APPEND CMAKE_REQUIRED_INCLUDES
	    ${LUA_INCLUDE_DIRS}
	     ${LUABIND_INCLUDE_DIRS}
)
list(APPEND CMAKE_REQUIRED_LIBRARIES ${LUABIND_LIBRARIES} PkgConfig::LUA)

check_cxx_source_compiles("extern \"C\"
{
    #include \"lua.h\"
    #include \"lualib.h\"
    #include \"lauxlib.h\"
}

#include <iostream>
#include <luabind/luabind.hpp>

void greet()
{
    std::cout << \"hello world!\" << std::endl;
}

class cl {
public:
      void memberGreet() {
          std::cout << \"hello member!\" << std::endl;
      }
      static void staticGreet() {
          std::cout << \"hello static!\" << std::endl;
      }
};

int init(lua_State* L)
{
    using namespace luabind;

    open(L);

    module(L)
    [
        def(\"greet\", &greet),
	class_<cl>(\"cl\")
	.def(\"memberGreet\",&cl::memberGreet)
	.scope[
		def(\"staticGreet\",&cl::staticGreet)
	]
    ];

    return 0;
}
int main() {
    lua_State* L = luaL_newstate();
#if LUA_VERSION_NUM >= 501
    luaL_openlibs(L);
#else
    lua_baselibopen(L);
#endif

    using namespace luabind;

    open(L);
    init(L);
    luabind::call_function<void>(L, \"greet\");
    lua_close(L);
}"
luabindlink)
unset(CMAKE_REQUIRED_INCLUDES)
unset(CMAKE_REQUIRED_LIBRARIES)

if (luabindlink)
   add_library(Ctrlr::luabind ALIAS luabind)
else (luabindlink)
   message("Configuring included luabind library")
   set(LUABIND_USE_CXX11 ON)
   add_subdirectory(libs/luabind EXCLUDE_FROM_ALL)
   add_library(Ctrlr::luabind ALIAS luabind)
endif(luabindlink)


add_subdirectory(JUCE EXCLUDE_FROM_ALL)

if (APPLE)
	juce_set_vst2_sdk_path(/Users/atom/devel/vst2sdk)
elseif(UNIX)
	juce_set_vst2_sdk_path(Source/Misc/vst2sdk)
elseif(WIN32)
	juce_set_vst2_sdk_path(c:/Users/atom/devel/vst2sdk)
endif(APPLE)

set(CMAKE_DEBUG_TARGET_PROPERTIES COMPILE_DEFINITIONS)

juce_add_plugin(ctrlr
	COMPANY_NAME "Instigator"
	PLUGIN_MANUFACTURER_CODE inSt
	PLUGIN_CODE cTrl
	PLUGIN_NAME Ctrlr
	FORMATS VST3 VST AU Standalone
	PRODUCT_NAME "ctrlr"
	ICON_BIG "Source/Resources/Icons/ctrlr_logo.svg"
	ICON_SMALL "Source/Resources/Icons/ctrlr_logo.svg"
	BUNDLE_ID "com.instigator.Ctrlr"
	COMPANY_WEBSITE https://github.com/RomanKubiak/ctrlr
	DOCUMENT_EXTENSIONS panel
	DESCRIPTION "Control any MIDI enabled hardware: synthesizers,\
 drum machines, samplers, effects. Create custom User\
 interfaces. Host them as VST or AU plugins in your favorite DAWs."
	NEEDS_MIDI_INPUT true
	NEEDS_MIDI_OUTPUT true
	VST_NUM_MIDI_INS 2
	VST_NUM_MIDI_OUTS 2
	VST2_CATEGORY kPlugCategUnknown
	VST3_CATEGORIES NoOfflineProcess Tools
	AU_MAIN_TYPE kAudioUnitType_MIDIProcessor
)

target_precompile_headers(ctrlr
	PUBLIC
	Source/Core/stdafx.h
	Source/Core/stdafx_luabind.h
)



target_sources(ctrlr
        PRIVATE
	Source/Core/CtrlrFontManager.cpp
	Source/Core/CtrlrIDManager.cpp
	Source/Core/CtrlrLog.cpp
	Source/Core/CtrlrProperties.cpp
	Source/Core/CtrlrSysexProcessor.cpp
	Source/Core/CtrlrSysexProcessorOwned.cpp
	Source/Core/CtrlrSysexToken.cpp
	Source/Core/CtrlrUtilities.cpp
	Source/Core/CtrlrUtilitiesGUI.cpp
	Source/Core/StandaloneWrapper/CtrlrStandaloneWindow.cpp
	Source/Core/StandaloneWrapper/CtrlrStandaloneApplication.cpp
	Source/Plugin/CtrlrProcessor.cpp
	Source/Plugin/CtrlrProcessorEditorForLive.cpp
	Source/Lua/CtrlrLuaAudioConverter.cpp
	Source/Lua/CtrlrLuaDebugger.cpp
	Source/Lua/CtrlrLuaManager.cpp
	Source/Lua/CtrlrLuaObject.cpp
	Source/Lua/CtrlrLuaObjectWrapper.cpp
	Source/Lua/CtrlrLuaPanelCanvasLayer.cpp
	Source/Lua/CtrlrLuaUtils.cpp
	Source/MIDI/CtrlrMIDIDevice.cpp
	Source/MIDI/CtrlrMIDIDeviceManager.cpp
	Source/MIDI/CtrlrMIDIFilter.cpp
	Source/MIDI/CtrlrMidiInputComparator.cpp
	Source/MIDI/CtrlrMidiInputComparatorMulti.cpp
	Source/MIDI/CtrlrMidiInputComparatorSingle.cpp
	Source/MIDI/CtrlrMidiMessage.cpp
	Source/MIDI/CtrlrMidiMessageEx.cpp
	Source/MIDI/CtrlrOwnedMidiMessage.cpp
	Source/UIComponents/CtrlrAbout.cpp
	Source/UIComponents/CtrlrComponentSelection.cpp
	Source/UIComponents/CtrlrLogViewer.cpp
	Source/UIComponents/CtrlrTextEditor.cpp
	Source/UIComponents/CtrlrValueMap.cpp
	Source/UIComponents/CtrlrValueTreeEditor.cpp
#	Source/Misc/lua/src/lua.c
# 	Source/Misc/luabind/src/class.cpp
# 	Source/Misc/luabind/src/class_info.cpp
# 	Source/Misc/luabind/src/class_registry.cpp
# 	Source/Misc/luabind/src/class_rep.cpp
# 	Source/Misc/luabind/src/create_class.cpp
# 	Source/Misc/luabind/src/error.cpp
# 	Source/Misc/luabind/src/exception_handler.cpp
# 	Source/Misc/luabind/src/function.cpp
# 	Source/Misc/luabind/src/function_introspection.cpp
# 	Source/Misc/luabind/src/inheritance.cpp
# 	Source/Misc/luabind/src/link_compatibility.cpp
# 	Source/Misc/luabind/src/lua51compat.cpp
# 	Source/Misc/luabind/src/object_rep.cpp
# 	Source/Misc/luabind/src/open.cpp
# 	Source/Misc/luabind/src/operator.cpp
# 	Source/Misc/luabind/src/pcall.cpp
# 	Source/Misc/luabind/src/scope.cpp
# 	Source/Misc/luabind/src/set_package_preload.cpp
# 	Source/Misc/luabind/src/shared_ptr_converter.cpp
# 	Source/Misc/luabind/src/stack_content_by_name.cpp
# 	Source/Misc/luabind/src/weak_ref.cpp
# 	Source/Misc/luabind/src/wrapper_base.cpp
	Source/Core/CtrlrModulator/CtrlrModulator.cpp
	Source/Core/CtrlrModulator/CtrlrModulatorProcessor.cpp
	Source/Lua/Methods/CtrlrLuaMethod.cpp
	Source/Lua/Methods/CtrlrLuaMethodManagerCalls.cpp
	Source/Lua/Methods/CtrlrLuaMethodManager.cpp
	Source/Lua/JuceClasses/LAudio.cpp
	Source/Lua/JuceClasses/LComponents.cpp
	Source/Lua/JuceClasses/LCore.cpp
	Source/Lua/JuceClasses/LGraphics.cpp
	Source/Lua/JuceClasses/LJuce.cpp
	Source/Lua/JuceClasses/LMemory.cpp
	Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindowContainer.cpp
	Source/UIComponents/CtrlrApplicationWindow/CtrlrDocumentPanel.cpp
	Source/UIComponents/CtrlrApplicationWindow/CtrlrEditorApplicationCommands.cpp
	Source/UIComponents/CtrlrApplicationWindow/CtrlrEditorApplicationCommandsHandlers.cpp
	Source/UIComponents/CtrlrApplicationWindow/CtrlrEditorApplicationCommandsMenus.cpp
	Source/UIComponents/CtrlrApplicationWindow/CtrlrEditor.cpp
	Source/UIComponents/CtrlrApplicationWindow/CtrlrSettings.cpp
	Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindowContent.cpp
	Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindow.cpp
	Source/UIComponents/CtrlrWindowManagers/CtrlrDialogWindow.cpp
	Source/UIComponents/CtrlrWindowManagers/CtrlrManagerWindowManager.cpp
	Source/UIComponents/CtrlrWindowManagers/CtrlrPanelWindowManager.cpp
	Source/UIComponents/CtrlrPropertyEditors/CtrlrPropertyComponent.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelCanvas.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelCanvasHandlers.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelCanvasLayer.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelCanvasLayers.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelComponentProperties.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelEditor.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelFindProperty.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelLayerList.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelLayerListItem.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelModulatorList.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelModulatorListTree.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelProperties.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelResourceEditor.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelUtilities.cpp
	Source/UIComponents/CtrlrPanel/CtrlrPanelViewport.cpp
	Source/UIComponents/CtrlrPanel/CtrlrViewport.cpp
	Source/UIComponents/CtrlrMIDI/CtrlrMIDIBuffer.cpp
	Source/UIComponents/CtrlrMIDI/CtrlrMIDICalculator.cpp
	Source/UIComponents/CtrlrMIDI/CtrlrMIDIMon.cpp
	Source/UIComponents/CtrlrMIDI/CtrlrMIDISettingsDevices.cpp
	Source/UIComponents/CtrlrMIDI/CtrlrMIDISettingsDialog.cpp
	Source/UIComponents/CtrlrMIDI/CtrlrMIDISettingsRouting.cpp
	Source/UIComponents/CtrlrLua/CtrlrLuaConsole.cpp
	Source/UIComponents/CtrlrComponents/CtrlrCombo.cpp
	Source/UIComponents/CtrlrComponents/CtrlrComponent.cpp
	Source/UIComponents/CtrlrComponents/CtrlrComponentLuaRegistration.cpp
	Source/UIComponents/CtrlrComponents/CtrlrComponentTypeManager.cpp
	Source/UIComponents/CtrlrComponents/CtrlrCustomComponent.cpp
	Source/UIComponents/CtrlrComponents/CtrlrFilmStripPainter.cpp
	JuceLibraryCode/BinaryData.cpp
	Source/Core/CtrlrManager/CtrlrManager.cpp
	Source/Core/CtrlrManager/CtrlrManagerInstance.cpp
	Source/Core/CtrlrManager/CtrlrManagerVst.cpp
	Source/Core/CtrlrModulator/CtrlrModulator.cpp
	Source/Core/CtrlrModulator/CtrlrModulatorProcessor.cpp
	Source/Core/CtrlrPanel/CtrlrEvaluationScopes.cpp
	Source/Core/CtrlrPanel/CtrlrPanel.cpp
	Source/Core/CtrlrPanel/CtrlrPanelFileOperations.cpp
	Source/Core/CtrlrPanel/CtrlrPanelMIDIInputThread.cpp
	Source/Core/CtrlrPanel/CtrlrPanelMIDISnapshot.cpp
	Source/Core/CtrlrPanel/CtrlrPanelProcessor.cpp
	Source/Core/CtrlrPanel/CtrlrPanelResource.cpp
	Source/Core/CtrlrPanel/CtrlrPanelResourceManager.cpp
	Source/Core/CtrlrPanel/CtrlrPanelSchemeMigration.cpp
	Source/Core/CtrlrPanel/CtrlrPanelUndoManager.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaCodeTokeniser.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodCodeEditor.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodCodeEditorSettings.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerControls.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerInfo.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerPrompt.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerStackTrace.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerVars.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditArea.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditorConsole.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditor.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditorTabs.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodFind.cpp
	Source/UIComponents/CtrlrLua/MethodEditor/CtrlrMethodEditorTabCloseButton.cpp
	Source/UIComponents/CtrlrComponents/Statics/CtrlrArrow.cpp
	Source/UIComponents/CtrlrComponents/Specials/CtrlrFileListBox.cpp
	Source/UIComponents/CtrlrComponents/Specials/CtrlrListBox.cpp
	Source/UIComponents/CtrlrComponents/Specials/CtrlrMidiKeyboard.cpp
	Source/UIComponents/CtrlrComponents/Specials/CtrlrProgressBar.cpp
	Source/UIComponents/CtrlrComponents/Specials/CtrlrWaveform.cpp
	Source/UIComponents/CtrlrComponents/Specials/CtrlrXYModulator.cpp
	Source/UIComponents/CtrlrComponents/Specials/CtrlrXYSurface.cpp
	Source/UIComponents/CtrlrComponents/Sliders/CtrlrFixedImageSlider.cpp
	Source/UIComponents/CtrlrComponents/Sliders/CtrlrFixedSlider.cpp
	Source/UIComponents/CtrlrComponents/Sliders/CtrlrImageSlider.cpp
	Source/UIComponents/CtrlrComponents/Sliders/CtrlrSlider.cpp
	Source/UIComponents/CtrlrComponents/Sliders/CtrlrSliderInternal.cpp
	Source/UIComponents/CtrlrComponents/Labels/CtrlrImage.cpp
	Source/UIComponents/CtrlrComponents/Labels/CtrlrLabel.cpp
	Source/UIComponents/CtrlrComponents/Labels/CtrlrLCDLabel.cpp
	Source/UIComponents/CtrlrComponents/Groups/CtrlrGroup.cpp
	Source/UIComponents/CtrlrComponents/Groups/CtrlrTabsComponent.cpp
	Source/UIComponents/CtrlrComponents/Buttons/CtrlrButton.cpp
	Source/UIComponents/CtrlrComponents/Buttons/CtrlrCustomButtonInternal.cpp
	Source/UIComponents/CtrlrComponents/Buttons/CtrlrHyperlink.cpp
	Source/UIComponents/CtrlrComponents/Buttons/CtrlrImageButton.cpp
	Source/UIComponents/CtrlrComponents/Buttons/CtrlrToggleButton.cpp
	Source/Lua/Deprecated/CtrlrLuaBigInteger.cpp
	Source/Lua/Deprecated/CtrlrLuaComponentAnimator.cpp
	Source/Lua/Deprecated/CtrlrLuaFile.cpp
	Source/Lua/Deprecated/CtrlrLuaMemoryBlock.cpp
	Source/Lua/Deprecated/CtrlrLuaRectangle.cpp
	Source/Native/CtrlrLinux.cpp
	Source/Native/CtrlrMac.cpp
	Source/Native/CtrlrWindows.cpp
	Source/Native/CtrlrNative.cpp
	Source/Misc/libusb/src/compat.c
	Source/Misc/libusb/src/core.c
	Source/Misc/libusb/src/darwin_usb.c
	Source/Misc/libusb/src/descriptor.c
	Source/Misc/libusb/src/enums.c
	Source/Misc/libusb/src/hotplug.c
	Source/Misc/libusb/src/io.c
	Source/Misc/libusb/src/linux_udev.c
	Source/Misc/libusb/src/linux_usbfs.c
	Source/Misc/libusb/src/poll_posix.c
	Source/Misc/libusb/src/poll_windows.c
	Source/Misc/libusb/src/strerror.c
	Source/Misc/libusb/src/structs.c
	Source/Misc/libusb/src/sync.c
	Source/Misc/libusb/src/threads_posix.c
	Source/Misc/libusb/src/threads_windows.c
	Source/Misc/libusb/src/usb.c
	Source/Misc/libusb/src/windows_usb.c
)
#add_library(ctrlr-misc OBJECT
#)
add_library(ctrlr-misc STATIC
	Source/Misc/misc/libr-bfd.c
	Source/Misc/misc/libr.c
)
set_property(TARGET ctrlr-misc PROPERTY POSITION_INDEPENDENT_CODE ON)



target_compile_options(ctrlr PUBLIC "-w")
target_compile_options(ctrlr-misc PUBLIC "-w")

target_compile_definitions(ctrlr
	PRIVATE
	# JUCE_WEB_BROWSER and JUCE_USE_CURL should be handled automatically
	JUCE_WEB_BROWSER=0
	JUCE_USE_CURL=0
#	JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:ctrlr,JUCE_PRODUCT_NAME>"
#	JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:ctrlr,JUCE_VERSION>"
#	JUCE_VST3_CAN_REPLACE_VST2=0
#	JUCE_DEBUG=1
	JUCE_USE_CUSTOM_PLUGIN_STANDALONE_APP=1
)



string(TIMESTAMP BUILD_TIME)
configure_file(	"Source/Core/CtrlrRevision.template" 
  "CtrlrRevision.h")
include_directories(${CMAKE_CURRENT_BINARY_DIR}
	      )

target_include_directories(ctrlr
  PUBLIC
#	Source/Misc/lua/include
#	Source/Misc/luabind
#	Source/Misc/boost
	Source/Misc
	Source/Misc/include
	Source/Misc/libusb/include
	Source/Core
	Source/MIDI
	Source/Lua
	Source/UIComponents
	Source/Plugin
	Source/
	include
	JuceLibraryCode
	${CMAKE_CURRENT_BINARY_DIR}
        ${LUABITOP_INCLUDE_DIRS}
)
target_include_directories(ctrlr-misc
  PUBLIC
	Source/Misc/include
	include
	JuceLibraryCode
	JUCE/modules
	${CMAKE_CURRENT_BINARY_DIR}
        ${LUABITOP_INCLUDE_DIRS}
	
)

target_link_libraries(ctrlr
		PRIVATE
			juce::juce_gui_extra
			juce::juce_audio_basics
			juce::juce_audio_devices
			juce::juce_audio_formats
			juce::juce_audio_processors
			juce::juce_audio_utils
			PkgConfig::LUABITOP
			Ctrlr::luabind
			luausb
		PUBLIC
			juce::juce_recommended_config_flags
			juce::juce_recommended_lto_flags
			juce::juce_recommended_warning_flags
	)
if(UNIX AND NOT APPLE)
	target_sources(ctrlr-misc
		PRIVATE
		Source/Misc/misc/keys.cpp
	)


	find_package(X11 REQUIRED)
	find_package(ZLIB REQUIRED)
	find_library(LIB_UDEV udev REQUIRED)
	find_library(LIB_BFD libbfd.a REQUIRED)
	find_library(LIB_SFRAME sframe REQUIRED)
	find_library(LIB_IBERTY iberty REQUIRED)

	target_link_libraries(ctrlr
		PRIVATE
		ctrlr-misc
		X11::X11
		ZLIB::ZLIB
		${LIB_UDEV}
		${LIB_BFD}
		${LIB_SFRAME}
		${LIB_IBERTY}
	)
endif()

set_source_files_properties(
	JUCE/modules/juce_gui_extra/juce_gui_extra.cpp
	JUCE/modules/juce_gui_extra/juce_gui_extra.mm
	JUCE/modules/juce_gui_basics/juce_gui_basics.cpp
	JUCE/modules/juce_gui_basics/juce_gui_basics.mm
	JUCE/modules/juce_graphics/juce_graphics.cpp
	JUCE/modules/juce_graphics/juce_graphics.mm
	JUCE/modules/juce_events/juce_events.cpp
	JUCE/modules/juce_events/juce_events.mm
	JUCE/modules/juce_core/juce_core.cpp
	JUCE/modules/juce_core/juce_core.mm
	JUCE/modules/juce_data_structures/juce_data_structures.cpp
	JUCE/modules/juce_data_structures/juce_data_structures.mm
	JUCE/modules/juce_audio_basics/juce_audio_basics.cpp
	JUCE/modules/juce_audio_basics/juce_audio_basics.mm
	JUCE/modules/juce_audio_devices/juce_audio_devices.cpp
	JUCE/modules/juce_audio_devices/juce_audio_devices.mm
	JUCE/modules/juce_audio_formats/juce_audio_formats.cpp
	JUCE/modules/juce_audio_formats/juce_audio_formats.mm
	JUCE/modules/juce_audio_processors/juce_audio_processors.cpp
	JUCE/modules/juce_audio_processors/juce_audio_processors.mm
	JUCE/modules/juce_audio_utils/juce_audio_utils.cpp
	JUCE/modules/juce_audio_utils/juce_audio_utils.mm
	JUCE/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp
	JUCE/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.mm
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_VST2.cpp
	JUCE/modules/juce_audio_plugin_client/VST3/juce_VST3_Wrapper.cpp
	JUCE/modules/juce_audio_plugin_client/VST3/juce_VST3_Wrapper.mm
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_AAX.mm
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_RTAS_3.cpp
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_VST3.cpp
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_Unity.cpp
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_Standalone.cpp
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_RTAS_4.cpp
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_RTAS_2.cpp
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_RTAS_1.cpp
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_VST2.cpp
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_RTAS_utils.mm
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_VST_utils.mm
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_AUv3.mm
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_AU_2.mm
	JUCE/modules/juce_audio_plugin_client/juce_audio_plugin_client_AU_1.mm
	Source/Misc/lua/src/lua.c
	Source/Misc/luabind/src/class.cpp
	Source/Misc/luabind/src/class_info.cpp
	Source/Misc/luabind/src/class_registry.cpp
	Source/Misc/luabind/src/class_rep.cpp
	Source/Misc/luabind/src/create_class.cpp
	Source/Misc/luabind/src/error.cpp
	Source/Misc/luabind/src/exception_handler.cpp
	Source/Misc/luabind/src/function.cpp
	Source/Misc/luabind/src/function_introspection.cpp
	Source/Misc/luabind/src/inheritance.cpp
	Source/Misc/luabind/src/link_compatibility.cpp
	Source/Misc/luabind/src/lua51compat.cpp
	Source/Misc/luabind/src/object_rep.cpp
	Source/Misc/luabind/src/open.cpp
	Source/Misc/luabind/src/operator.cpp
	Source/Misc/luabind/src/pcall.cpp
	Source/Misc/luabind/src/scope.cpp
	Source/Misc/luabind/src/set_package_preload.cpp
	Source/Misc/luabind/src/shared_ptr_converter.cpp
	Source/Misc/luabind/src/stack_content_by_name.cpp
	Source/Misc/luabind/src/weak_ref.cpp
	Source/Misc/luabind/src/wrapper_base.cpp
	Source/Misc/libusb/src/compat.c
	Source/Misc/libusb/src/core.c
	Source/Misc/libusb/src/darwin_usb.c
	Source/Misc/libusb/src/descriptor.c
	Source/Misc/libusb/src/enums.c
	Source/Misc/libusb/src/hotplug.c
	Source/Misc/libusb/src/io.c
	Source/Misc/libusb/src/linux_udev.c
	Source/Misc/libusb/src/linux_usbfs.c
	Source/Misc/libusb/src/poll_posix.c
	Source/Misc/libusb/src/poll_windows.c
	Source/Misc/libusb/src/strerror.c
	Source/Misc/libusb/src/structs.c
	Source/Misc/libusb/src/sync.c
	Source/Misc/libusb/src/threads_posix.c
	Source/Misc/libusb/src/threads_windows.c
	Source/Misc/libusb/src/usb.c
	Source/Misc/libusb/src/windows_usb.c
	Source/Misc/keys.cpp
	JuceLibraryCode/BinaryData.cpp
	PROPERTIES SKIP_PRECOMPILE_HEADERS ON
)

# Copy properties from ctrlr to ctrlr-misc
get_target_property(MAIN_COMPILE_DEFINITIONS ctrlr COMPILE_DEFINITIONS)
target_compile_definitions(ctrlr-misc
	PRIVATE
	${MAIN_COMPILE_DEFINITIONS}
)
get_target_property(MAIN_COMPILE_OPTIONS ctrlr COMPILE_OPTIONS)
target_compile_options(ctrlr-misc
	PRIVATE
	${MAIN_COMPILE_OPTIONS}
)
#get_target_property(MAIN_COMPILE_FLAGS ctrlr COMPILE_FLAGS)
##get_target_property(MAIN_STATIC_LIBRARY_FLAGS ctrlr STATIC_LIBRLRY_FLAGS)
target_compile_options(ctrlr-misc
	PRIVATE
#	${MAIN_COMPILE_FLAGS}
#	${MAIN_STATIC_LIBRARY_FLAGS}
)
# get_target_property(MAIN_COMPILE_FEATURES ctrlr COMPILE_FEATURES)
# target_compile_features(ctrlr-misc
# 	PRIVATE
# 	${MAIN_COMPILE_FEATURES}
# )
#

#set_target_properties(ctrlr_VST
#	PROPERTIES
#         LIBRARY_OUTPUT_DIRECTORY ${PROJECT_LIBRARY_DIR}/vst)
#set_target_properties(ctrlr_VST3
#	PROPERTIES
#         LIBRARY_OUTPUT_DIRECTORY ${PROJECT_LIBRARY_DIR}/vst3)
	 
if (APPLE)
   set(CTRLR_INSTALL_EXTRA_OPTIONS MACOSX_BUNDLE)
else(APPLE)
   set(CTRLR_INSTALL_EXTRA_OPTIONS )
endif(APPLE)

install(TARGETS ctrlr_Standalone
	RUNTIME
	${CTRLR_INSTALL_EXTRA_OPTIONS}
	DESTINATION bin)
install(TARGETS ctrlr_VST
	${CTRLR_INSTALL_EXTRA_OPTIONS}
	DESTINATION lib/vst)
install(TARGETS ctrlr_VST3
	${CTRLR_INSTALL_EXTRA_OPTIONS}
	DESTINATION lib/vst3)
