# Automatically generated makefile, created by the Projucer
# Don't edit this file! Your changes will be overwritten when you re-save the Projucer project!

# build with "V=1" for verbose builds
ifeq ($(V), 1)
V_AT =
else
V_AT = @
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef STRIP
  STRIP=strip
endif

ifndef AR
  AR=ar
endif

ifndef CONFIG
  CONFIG=Debug
endif

JUCE_ARCH_LABEL := $(shell uname -m)

ifeq ($(CONFIG),Debug)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Debug
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := 
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DDEBUG=1" "-D_DEBUG=1" "-DJUCE_USE_CUSTOM_PLUGIN_STANDALONE_APP=1" "-DJUCER_LINUX_MAKE_6D53C8B4=1" "-DJUCE_APP_VERSION=5.5" "-DJUCE_APP_VERSION_HEX=0x50500" $(shell pkg-config --cflags alsa freetype2 libcurl luabind lua52 x11 zlib) -pthread -I../../JUCE/modules/juce_audio_processors/format_types/VST3_SDK -I../../Source/Misc/vst2sdk -I../../JuceLibraryCode -I../../JUCE/modules -I../../Source -I../../Source/Misc/misc -I../../Source/Misc/include -Idnl../../Source/Misc/lua/include -Idnl../../Source/Misc/luabind -Idnl../../Source/Misc/libusb/include -Idnl../../Source/Misc/boost -I../../Source/MIDI -I../../Source/Core -I../../Source/Native -I../../Source/Plugin -I../../Source/UIComponents -I../../Source/Lua $(CPPFLAGS)

  JUCE_CPPFLAGS_VST :=  "-DJucePlugin_Build_VST=1" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_RTAS=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0"
  JUCE_CFLAGS_VST := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST := -shared -Wl,--no-undefined
  JUCE_TARGET_VST := Ctrlr-Debug.so
  JUCE_VSTDESTDIR := $(HOME)/.vst
  JUCE_COPYCMD_VST := $(JUCE_OUTDIR)/Ctrlr-Debug.so $(JUCE_VSTDESTDIR)

  JUCE_CPPFLAGS_VST3 :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=1" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_RTAS=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0"
  JUCE_CFLAGS_VST3 := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST3 := -shared -Wl,--no-undefined
  JUCE_VST3DIR := Ctrlr-Debug.vst3
  VST3_PLATFORM_ARCH := $(shell $(CXX) make_helpers/arch_detection.cpp 2>&1 | tr '\n' ' ' | sed "s/.*JUCE_ARCH \([a-zA-Z0-9_-]*\).*/\1/")
  JUCE_VST3SUBDIR := Contents/$(VST3_PLATFORM_ARCH)-linux
  JUCE_TARGET_VST3 := $(JUCE_VST3DIR)/$(JUCE_VST3SUBDIR)/Ctrlr-Debug.so
  JUCE_VST3DESTDIR := $(HOME)/.vst3
  JUCE_COPYCMD_VST3 := $(JUCE_OUTDIR)/$(JUCE_VST3DIR) $(JUCE_VST3DESTDIR)

  JUCE_CPPFLAGS_STANDALONE_PLUGIN :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_RTAS=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=1" "-DJucePlugin_Build_Unity=0"
  JUCE_TARGET_STANDALONE_PLUGIN := Ctrlr-Debug

  JUCE_CPPFLAGS_SHARED_CODE :=  "-DJucePlugin_Build_VST=1" "-DJucePlugin_Build_VST3=1" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_RTAS=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=1" "-DJucePlugin_Build_Unity=0" "-DJUCE_SHARED_CODE=1"
  JUCE_TARGET_SHARED_CODE := Ctrlr-Debug.a

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -g -ggdb -O0 -Wall -Wextra -Wstrict-aliasing -Wuninitialized -Wunused-parameter -Wsign-compare -Woverloaded-virtual -Wreorder -Wsign-conversion -Wunreachable-code -Wzero-as-null-pointer-constant -Wcast-align -Wno-implicit-fallthrough -Wno-maybe-uninitialized -Wno-missing-field-initializers -Wno-ignored-qualifiers -Wswitch-enum -Wredundant-decls -w $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=gnu++14 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) $(shell pkg-config --libs alsa freetype2 libcurl luabind lua52 x11 zlib) -fvisibility=hidden -lrt -ldl -lpthread -l:libbfd.a -liberty $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

ifeq ($(CONFIG),Release)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Release
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := 
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DNDEBUG=1" "-DJUCE_USE_CUSTOM_PLUGIN_STANDALONE_APP=1" "-DJUCER_LINUX_MAKE_6D53C8B4=1" "-DJUCE_APP_VERSION=5.5" "-DJUCE_APP_VERSION_HEX=0x50500" $(shell pkg-config --cflags alsa freetype2 libcurl luabind lua52 x11 zlib) -pthread -I../../JUCE/modules/juce_audio_processors/format_types/VST3_SDK -I../../Source/Misc/vst2sdk -I../../JuceLibraryCode -I../../JUCE/modules -I../../Source -I../../Source/Misc -I../../Source/Misc/include -Idnl../../Source/Misc/lua/include -Idnl../../Source/Misc/luabind -Idnl../../Source/Misc/libusb/include -Idnl../../Source/Misc/boost -I../../Source/MIDI -I../../Source/Core -I../../Source/Native -I../../Source/Plugin -I../../Source/UIComponents -I../../Source/Lua $(CPPFLAGS)

  JUCE_CPPFLAGS_VST :=  "-DJucePlugin_Build_VST=1" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_RTAS=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0"
  JUCE_CFLAGS_VST := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST := -shared -Wl,--no-undefined
  JUCE_TARGET_VST := Ctrlr.so
  JUCE_VSTDESTDIR := $(HOME)/.vst
  JUCE_COPYCMD_VST := $(JUCE_OUTDIR)/Ctrlr.so $(JUCE_VSTDESTDIR)

  JUCE_CPPFLAGS_VST3 :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=1" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_RTAS=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0"
  JUCE_CFLAGS_VST3 := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST3 := -shared -Wl,--no-undefined
  JUCE_VST3DIR := Ctrlr.vst3
  VST3_PLATFORM_ARCH := $(shell $(CXX) make_helpers/arch_detection.cpp 2>&1 | tr '\n' ' ' | sed "s/.*JUCE_ARCH \([a-zA-Z0-9_-]*\).*/\1/")
  JUCE_VST3SUBDIR := Contents/$(VST3_PLATFORM_ARCH)-linux
  JUCE_TARGET_VST3 := $(JUCE_VST3DIR)/$(JUCE_VST3SUBDIR)/Ctrlr.so
  JUCE_VST3DESTDIR := $(HOME)/.vst3
  JUCE_COPYCMD_VST3 := $(JUCE_OUTDIR)/$(JUCE_VST3DIR) $(JUCE_VST3DESTDIR)

  JUCE_CPPFLAGS_STANDALONE_PLUGIN :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=0" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_RTAS=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=1" "-DJucePlugin_Build_Unity=0"
  JUCE_TARGET_STANDALONE_PLUGIN := Ctrlr

  JUCE_CPPFLAGS_SHARED_CODE :=  "-DJucePlugin_Build_VST=1" "-DJucePlugin_Build_VST3=1" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_RTAS=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=1" "-DJucePlugin_Build_Unity=0" "-DJUCE_SHARED_CODE=1"
  JUCE_TARGET_SHARED_CODE := Ctrlr.a

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -O3 -flto -w $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=gnu++14 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) $(shell pkg-config --libs alsa freetype2 libcurl luabind lua52 x11 zlib) -fvisibility=hidden -flto -lrt -ldl -lpthread -l:libbfd.a -liberty $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

OBJECTS_ALL := \

OBJECTS_VST := \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_VST2_dd551e08.o \

OBJECTS_VST3 := \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_VST3_dd633589.o \

OBJECTS_STANDALONE_PLUGIN := \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_Standalone_1a871192.o \

OBJECTS_SHARED_CODE := \
  $(JUCE_OBJDIR)/keys_7e3b415d.o \
  $(JUCE_OBJDIR)/libr-bfd_95e2a509.o \
  $(JUCE_OBJDIR)/libr_651d24f6.o \
  $(JUCE_OBJDIR)/CtrlrManager_f2f12d08.o \
  $(JUCE_OBJDIR)/CtrlrManagerInstance_44eac03d.o \
  $(JUCE_OBJDIR)/CtrlrManagerVst_cf4a0139.o \
  $(JUCE_OBJDIR)/CtrlrModulator_3ba73888.o \
  $(JUCE_OBJDIR)/CtrlrModulatorProcessor_9c865db4.o \
  $(JUCE_OBJDIR)/CtrlrEvaluationScopes_91b73ea1.o \
  $(JUCE_OBJDIR)/CtrlrPanel_4772c8e8.o \
  $(JUCE_OBJDIR)/CtrlrPanelFileOperations_9097aa50.o \
  $(JUCE_OBJDIR)/CtrlrPanelMIDIInputThread_f05ccf35.o \
  $(JUCE_OBJDIR)/CtrlrPanelMIDISnapshot_ac52ded.o \
  $(JUCE_OBJDIR)/CtrlrPanelProcessor_90473954.o \
  $(JUCE_OBJDIR)/CtrlrPanelResource_c8914716.o \
  $(JUCE_OBJDIR)/CtrlrPanelResourceManager_ded72841.o \
  $(JUCE_OBJDIR)/CtrlrPanelSchemeMigration_35bff32b.o \
  $(JUCE_OBJDIR)/CtrlrPanelUndoManager_544c802b.o \
  $(JUCE_OBJDIR)/CtrlrStandaloneApplication_2835f456.o \
  $(JUCE_OBJDIR)/CtrlrStandaloneWindow_42dbf3b4.o \
  $(JUCE_OBJDIR)/CtrlrFontManager_edb07ae8.o \
  $(JUCE_OBJDIR)/CtrlrIDManager_40d647fc.o \
  $(JUCE_OBJDIR)/CtrlrLog_cd89ebce.o \
  $(JUCE_OBJDIR)/CtrlrProperties_eb107cf3.o \
  $(JUCE_OBJDIR)/CtrlrSysexProcessor_bc5102f2.o \
  $(JUCE_OBJDIR)/CtrlrSysexProcessorOwned_1864a89d.o \
  $(JUCE_OBJDIR)/CtrlrSysexToken_f2c07259.o \
  $(JUCE_OBJDIR)/CtrlrUtilities_e2afb8d4.o \
  $(JUCE_OBJDIR)/CtrlrUtilitiesGUI_cf4b83d1.o \
  $(JUCE_OBJDIR)/stdafx_a1c77ec1.o \
  $(JUCE_OBJDIR)/stdafx_luabind_6366fab7.o \
  $(JUCE_OBJDIR)/CtrlrLuaBigInteger_5ff71375.o \
  $(JUCE_OBJDIR)/CtrlrLuaComponentAnimator_bfec1d7.o \
  $(JUCE_OBJDIR)/CtrlrLuaFile_1a330f53.o \
  $(JUCE_OBJDIR)/CtrlrLuaMemoryBlock_85081d5f.o \
  $(JUCE_OBJDIR)/CtrlrLuaRectangle_baaae0c2.o \
  $(JUCE_OBJDIR)/LAudio_273674e0.o \
  $(JUCE_OBJDIR)/LComponents_6368b696.o \
  $(JUCE_OBJDIR)/LCore_60dceadf.o \
  $(JUCE_OBJDIR)/LGraphics_349e924b.o \
  $(JUCE_OBJDIR)/LJuce_5bd1d72d.o \
  $(JUCE_OBJDIR)/LMemory_dc39a081.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethod_23ff560f.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodManager_c621ff28.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodManagerCalls_d460a557.o \
  $(JUCE_OBJDIR)/CtrlrLuaAudioConverter_d897847b.o \
  $(JUCE_OBJDIR)/CtrlrLuaDebugger_36763bb2.o \
  $(JUCE_OBJDIR)/CtrlrLuaManager_89c5eb06.o \
  $(JUCE_OBJDIR)/CtrlrLuaObject_85f4d2d0.o \
  $(JUCE_OBJDIR)/CtrlrLuaObjectWrapper_dab692d.o \
  $(JUCE_OBJDIR)/CtrlrLuaPanelCanvasLayer_a584fbc6.o \
  $(JUCE_OBJDIR)/CtrlrLuaUtils_3835430a.o \
  $(JUCE_OBJDIR)/CtrlrMIDIDevice_275facd9.o \
  $(JUCE_OBJDIR)/CtrlrMIDIDeviceManager_d382511e.o \
  $(JUCE_OBJDIR)/CtrlrMIDIFilter_9c3df8fb.o \
  $(JUCE_OBJDIR)/CtrlrMidiInputComparator_b50d6fc7.o \
  $(JUCE_OBJDIR)/CtrlrMidiInputComparatorMulti_a3cb717c.o \
  $(JUCE_OBJDIR)/CtrlrMidiInputComparatorSingle_c444d6af.o \
  $(JUCE_OBJDIR)/CtrlrMidiMessage_f1795a0e.o \
  $(JUCE_OBJDIR)/CtrlrMidiMessageEx_a0d44f21.o \
  $(JUCE_OBJDIR)/CtrlrOwnedMidiMessage_b2a92f23.o \
  $(JUCE_OBJDIR)/CtrlrLinux_981545c6.o \
  $(JUCE_OBJDIR)/CtrlrMac_67f057e1.o \
  $(JUCE_OBJDIR)/CtrlrNative_a50436cf.o \
  $(JUCE_OBJDIR)/CtrlrWindows_8f7a495.o \
  $(JUCE_OBJDIR)/CtrlrProcessor_a9d8df48.o \
  $(JUCE_OBJDIR)/CtrlrProcessorEditorForLive_da85400a.o \
  $(JUCE_OBJDIR)/CtrlrDocumentPanel_a034ed7c.o \
  $(JUCE_OBJDIR)/CtrlrEditor_794f45c4.o \
  $(JUCE_OBJDIR)/CtrlrEditorApplicationCommands_a8897f1e.o \
  $(JUCE_OBJDIR)/CtrlrEditorApplicationCommandsHandlers_9fe09027.o \
  $(JUCE_OBJDIR)/CtrlrEditorApplicationCommandsMenus_98f1ccc0.o \
  $(JUCE_OBJDIR)/CtrlrSettings_18014fa.o \
  $(JUCE_OBJDIR)/CtrlrButton_4f3b25fd.o \
  $(JUCE_OBJDIR)/CtrlrCustomButtonInternal_1d79572b.o \
  $(JUCE_OBJDIR)/CtrlrHyperlink_769f0345.o \
  $(JUCE_OBJDIR)/CtrlrImageButton_2e69b94c.o \
  $(JUCE_OBJDIR)/CtrlrToggleButton_d75ffbf1.o \
  $(JUCE_OBJDIR)/CtrlrGroup_20cf8805.o \
  $(JUCE_OBJDIR)/CtrlrTabsComponent_73b077a5.o \
  $(JUCE_OBJDIR)/CtrlrImage_24ad6b56.o \
  $(JUCE_OBJDIR)/CtrlrLabel_34cbcc6f.o \
  $(JUCE_OBJDIR)/CtrlrLCDLabel_ad580dd6.o \
  $(JUCE_OBJDIR)/CtrlrFixedImageSlider_275f8744.o \
  $(JUCE_OBJDIR)/CtrlrFixedSlider_82d122c3.o \
  $(JUCE_OBJDIR)/CtrlrImageSlider_4e5cefea.o \
  $(JUCE_OBJDIR)/CtrlrSlider_b3526a5d.o \
  $(JUCE_OBJDIR)/CtrlrSliderInternal_c4abb6ba.o \
  $(JUCE_OBJDIR)/CtrlrFileListBox_a780e671.o \
  $(JUCE_OBJDIR)/CtrlrListBox_5b68770d.o \
  $(JUCE_OBJDIR)/CtrlrMidiKeyboard_66fc6d32.o \
  $(JUCE_OBJDIR)/CtrlrProgressBar_be7eb366.o \
  $(JUCE_OBJDIR)/CtrlrWaveform_80c97e47.o \
  $(JUCE_OBJDIR)/CtrlrXYModulator_401428ce.o \
  $(JUCE_OBJDIR)/CtrlrXYSurface_ed8dc70c.o \
  $(JUCE_OBJDIR)/CtrlrArrow_f7d8e9a4.o \
  $(JUCE_OBJDIR)/CtrlrCombo_d9a943ff.o \
  $(JUCE_OBJDIR)/CtrlrComponent_565a21ee.o \
  $(JUCE_OBJDIR)/CtrlrComponentLuaRegistration_c369de8d.o \
  $(JUCE_OBJDIR)/CtrlrComponentTypeManager_eb8d7f4f.o \
  $(JUCE_OBJDIR)/CtrlrCustomComponent_8d0e28fd.o \
  $(JUCE_OBJDIR)/CtrlrFilmStripPainter_44309df0.o \
  $(JUCE_OBJDIR)/CtrlrLuaCodeTokeniser_f07b7773.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodCodeEditor_2dacc3f5.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodCodeEditorSettings_3cdccab8.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerControls_6e517932.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerInfo_e4ac56aa.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerPrompt_18948aa0.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerStackTrace_5f5a64d9.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerVars_901d2128.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodEditArea_91f2aef2.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodEditor_22103128.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodEditorConsole_27c91699.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodEditorTabs_38c06846.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodFind_27828f4.o \
  $(JUCE_OBJDIR)/CtrlrMethodEditorTabCloseButton_77eee52b.o \
  $(JUCE_OBJDIR)/CtrlrLuaConsole_ed40c4ae.o \
  $(JUCE_OBJDIR)/CtrlrMIDIBuffer_96c85485.o \
  $(JUCE_OBJDIR)/CtrlrMIDICalculator_478db247.o \
  $(JUCE_OBJDIR)/CtrlrMIDIMon_9099a031.o \
  $(JUCE_OBJDIR)/CtrlrMIDISettingsDevices_266f355f.o \
  $(JUCE_OBJDIR)/CtrlrMIDISettingsDialog_46327210.o \
  $(JUCE_OBJDIR)/CtrlrMIDISettingsRouting_44fccc8.o \
  $(JUCE_OBJDIR)/CtrlrPanelCanvas_6acd392b.o \
  $(JUCE_OBJDIR)/CtrlrPanelCanvasHandlers_af43ed34.o \
  $(JUCE_OBJDIR)/CtrlrPanelCanvasLayer_3ae11ab0.o \
  $(JUCE_OBJDIR)/CtrlrPanelCanvasLayers_24f6490d.o \
  $(JUCE_OBJDIR)/CtrlrPanelComponentProperties_a6700c67.o \
  $(JUCE_OBJDIR)/CtrlrPanelEditor_b6d0d2c0.o \
  $(JUCE_OBJDIR)/CtrlrPanelFindProperty_6784c901.o \
  $(JUCE_OBJDIR)/CtrlrPanelLayerList_8154b2e6.o \
  $(JUCE_OBJDIR)/CtrlrPanelLayerListItem_f5855019.o \
  $(JUCE_OBJDIR)/CtrlrPanelModulatorList_dbb12084.o \
  $(JUCE_OBJDIR)/CtrlrPanelModulatorListTree_d70579c2.o \
  $(JUCE_OBJDIR)/CtrlrPanelProperties_a872c86.o \
  $(JUCE_OBJDIR)/CtrlrPanelResourceEditor_5b3b6e.o \
  $(JUCE_OBJDIR)/CtrlrPanelUtilities_c2ab4ae1.o \
  $(JUCE_OBJDIR)/CtrlrPanelViewport_dadb95f9.o \
  $(JUCE_OBJDIR)/CtrlrViewport_fa4a1ea1.o \
  $(JUCE_OBJDIR)/CtrlrPropertyComponent_8edd6f2a.o \
  $(JUCE_OBJDIR)/CtrlrChildWindow_4cf4d23d.o \
  $(JUCE_OBJDIR)/CtrlrChildWindowContainer_4534500e.o \
  $(JUCE_OBJDIR)/CtrlrChildWindowContent_3235f206.o \
  $(JUCE_OBJDIR)/CtrlrDialogWindow_cdbe7431.o \
  $(JUCE_OBJDIR)/CtrlrManagerWindowManager_d5d813c9.o \
  $(JUCE_OBJDIR)/CtrlrPanelWindowManager_d36a6b52.o \
  $(JUCE_OBJDIR)/CtrlrAbout_dbdebdec.o \
  $(JUCE_OBJDIR)/CtrlrComponentSelection_86f225a.o \
  $(JUCE_OBJDIR)/CtrlrLogViewer_9aac1755.o \
  $(JUCE_OBJDIR)/CtrlrTextEditor_e95be6c5.o \
  $(JUCE_OBJDIR)/CtrlrValueMap_3b250f6.o \
  $(JUCE_OBJDIR)/CtrlrValueTreeEditor_fdda055b.o \
  $(JUCE_OBJDIR)/BinaryData_ce4232d4.o \
  $(JUCE_OBJDIR)/include_juce_audio_basics_8a4e984a.o \
  $(JUCE_OBJDIR)/include_juce_audio_devices_63111d02.o \
  $(JUCE_OBJDIR)/include_juce_audio_formats_15f82001.o \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_utils_e32edaee.o \
  $(JUCE_OBJDIR)/include_juce_audio_processors_10c03666.o \
  $(JUCE_OBJDIR)/include_juce_audio_utils_9f9fb2d6.o \
  $(JUCE_OBJDIR)/include_juce_core_f26d17db.o \
  $(JUCE_OBJDIR)/include_juce_data_structures_7471b1e3.o \
  $(JUCE_OBJDIR)/include_juce_events_fd7d695.o \
  $(JUCE_OBJDIR)/include_juce_graphics_f817e147.o \
  $(JUCE_OBJDIR)/include_juce_gui_basics_e3f79785.o \
  $(JUCE_OBJDIR)/include_juce_gui_extra_6dee1c1a.o \

.PHONY: clean all strip VST VST3 Standalone

all : VST VST3 Standalone

VST : $(JUCE_OUTDIR)/$(JUCE_TARGET_VST)
VST3 : $(JUCE_OUTDIR)/$(JUCE_TARGET_VST3)
Standalone : $(JUCE_OUTDIR)/$(JUCE_TARGET_STANDALONE_PLUGIN)


$(JUCE_OUTDIR)/$(JUCE_TARGET_VST) : $(OBJECTS_VST) $(RESOURCES) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE)
	@command -v pkg-config >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@pkg-config --print-errors alsa freetype2 libcurl luabind lua52 x11 zlib
	@echo Linking "Ctrlr - VST"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/$(JUCE_TARGET_VST) $(OBJECTS_VST) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_LDFLAGS) $(JUCE_LDFLAGS_VST) $(RESOURCES) $(TARGET_ARCH)
	-$(V_AT)mkdir -p $(JUCE_VSTDESTDIR)
	-$(V_AT)cp -R $(JUCE_COPYCMD_VST)

$(JUCE_OUTDIR)/$(JUCE_TARGET_VST3) : $(OBJECTS_VST3) $(RESOURCES) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE)
	@command -v pkg-config >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@pkg-config --print-errors alsa freetype2 libcurl luabind lua52 x11 zlib
	@echo Linking "Ctrlr - VST3"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)/$(JUCE_VST3DIR)/$(JUCE_VST3SUBDIR)
	$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/$(JUCE_TARGET_VST3) $(OBJECTS_VST3) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_LDFLAGS) $(JUCE_LDFLAGS_VST3) $(RESOURCES) $(TARGET_ARCH)
	-$(V_AT)mkdir -p $(JUCE_VST3DESTDIR)
	-$(V_AT)cp -R $(JUCE_COPYCMD_VST3)

$(JUCE_OUTDIR)/$(JUCE_TARGET_STANDALONE_PLUGIN) : $(OBJECTS_STANDALONE_PLUGIN) $(RESOURCES) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE)
	@command -v pkg-config >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@pkg-config --print-errors alsa freetype2 libcurl luabind lua52 x11 zlib
	@echo Linking "Ctrlr - Standalone Plugin"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/$(JUCE_TARGET_STANDALONE_PLUGIN) $(OBJECTS_STANDALONE_PLUGIN) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_LDFLAGS) $(JUCE_LDFLAGS_STANDALONE_PLUGIN) $(RESOURCES) $(TARGET_ARCH)

$(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) : $(OBJECTS_SHARED_CODE) $(RESOURCES)
	@command -v pkg-config >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@pkg-config --print-errors alsa freetype2 libcurl luabind lua52 x11 zlib
	@echo Linking "Ctrlr - Shared Code"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(AR) -rcs $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(OBJECTS_SHARED_CODE)

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_VST2_dd551e08.o: ../../JuceLibraryCode/include_juce_audio_plugin_client_VST2.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_plugin_client_VST2.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_VST) $(JUCE_CFLAGS_VST) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_VST3_dd633589.o: ../../JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_plugin_client_VST3.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_VST3) $(JUCE_CFLAGS_VST3) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_Standalone_1a871192.o: ../../JuceLibraryCode/include_juce_audio_plugin_client_Standalone.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_plugin_client_Standalone.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_STANDALONE_PLUGIN) $(JUCE_CFLAGS_STANDALONE_PLUGIN) -o "$@" -c "$<"

$(JUCE_OBJDIR)/keys_7e3b415d.o: ../../Source/Misc/misc/keys.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling keys.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/libr-bfd_95e2a509.o: ../../Source/Misc/misc/libr-bfd.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling libr-bfd.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/libr_651d24f6.o: ../../Source/Misc/misc/libr.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling libr.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrManager_f2f12d08.o: ../../Source/Core/CtrlrManager/CtrlrManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrManagerInstance_44eac03d.o: ../../Source/Core/CtrlrManager/CtrlrManagerInstance.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrManagerInstance.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrManagerVst_cf4a0139.o: ../../Source/Core/CtrlrManager/CtrlrManagerVst.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrManagerVst.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrModulator_3ba73888.o: ../../Source/Core/CtrlrModulator/CtrlrModulator.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrModulator.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrModulatorProcessor_9c865db4.o: ../../Source/Core/CtrlrModulator/CtrlrModulatorProcessor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrModulatorProcessor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrEvaluationScopes_91b73ea1.o: ../../Source/Core/CtrlrPanel/CtrlrEvaluationScopes.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrEvaluationScopes.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanel_4772c8e8.o: ../../Source/Core/CtrlrPanel/CtrlrPanel.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelFileOperations_9097aa50.o: ../../Source/Core/CtrlrPanel/CtrlrPanelFileOperations.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelFileOperations.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelMIDIInputThread_f05ccf35.o: ../../Source/Core/CtrlrPanel/CtrlrPanelMIDIInputThread.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelMIDIInputThread.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelMIDISnapshot_ac52ded.o: ../../Source/Core/CtrlrPanel/CtrlrPanelMIDISnapshot.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelMIDISnapshot.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelProcessor_90473954.o: ../../Source/Core/CtrlrPanel/CtrlrPanelProcessor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelProcessor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelResource_c8914716.o: ../../Source/Core/CtrlrPanel/CtrlrPanelResource.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelResource.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelResourceManager_ded72841.o: ../../Source/Core/CtrlrPanel/CtrlrPanelResourceManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelResourceManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelSchemeMigration_35bff32b.o: ../../Source/Core/CtrlrPanel/CtrlrPanelSchemeMigration.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelSchemeMigration.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelUndoManager_544c802b.o: ../../Source/Core/CtrlrPanel/CtrlrPanelUndoManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelUndoManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrStandaloneApplication_2835f456.o: ../../Source/Core/StandaloneWrapper/CtrlrStandaloneApplication.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrStandaloneApplication.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrStandaloneWindow_42dbf3b4.o: ../../Source/Core/StandaloneWrapper/CtrlrStandaloneWindow.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrStandaloneWindow.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrFontManager_edb07ae8.o: ../../Source/Core/CtrlrFontManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrFontManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrIDManager_40d647fc.o: ../../Source/Core/CtrlrIDManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrIDManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLog_cd89ebce.o: ../../Source/Core/CtrlrLog.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLog.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrProperties_eb107cf3.o: ../../Source/Core/CtrlrProperties.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrProperties.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrSysexProcessor_bc5102f2.o: ../../Source/Core/CtrlrSysexProcessor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrSysexProcessor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrSysexProcessorOwned_1864a89d.o: ../../Source/Core/CtrlrSysexProcessorOwned.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrSysexProcessorOwned.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrSysexToken_f2c07259.o: ../../Source/Core/CtrlrSysexToken.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrSysexToken.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrUtilities_e2afb8d4.o: ../../Source/Core/CtrlrUtilities.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrUtilities.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrUtilitiesGUI_cf4b83d1.o: ../../Source/Core/CtrlrUtilitiesGUI.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrUtilitiesGUI.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/stdafx_a1c77ec1.o: ../../Source/Core/stdafx.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling stdafx.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/stdafx_luabind_6366fab7.o: ../../Source/Core/stdafx_luabind.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling stdafx_luabind.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaBigInteger_5ff71375.o: ../../Source/Lua/Deprecated/CtrlrLuaBigInteger.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaBigInteger.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaComponentAnimator_bfec1d7.o: ../../Source/Lua/Deprecated/CtrlrLuaComponentAnimator.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaComponentAnimator.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaFile_1a330f53.o: ../../Source/Lua/Deprecated/CtrlrLuaFile.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaFile.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMemoryBlock_85081d5f.o: ../../Source/Lua/Deprecated/CtrlrLuaMemoryBlock.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMemoryBlock.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaRectangle_baaae0c2.o: ../../Source/Lua/Deprecated/CtrlrLuaRectangle.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaRectangle.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LAudio_273674e0.o: ../../Source/Lua/JuceClasses/LAudio.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LAudio.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LComponents_6368b696.o: ../../Source/Lua/JuceClasses/LComponents.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LComponents.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LCore_60dceadf.o: ../../Source/Lua/JuceClasses/LCore.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LCore.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LGraphics_349e924b.o: ../../Source/Lua/JuceClasses/LGraphics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LGraphics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LJuce_5bd1d72d.o: ../../Source/Lua/JuceClasses/LJuce.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LJuce.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LMemory_dc39a081.o: ../../Source/Lua/JuceClasses/LMemory.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LMemory.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethod_23ff560f.o: ../../Source/Lua/Methods/CtrlrLuaMethod.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethod.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodManager_c621ff28.o: ../../Source/Lua/Methods/CtrlrLuaMethodManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodManagerCalls_d460a557.o: ../../Source/Lua/Methods/CtrlrLuaMethodManagerCalls.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodManagerCalls.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaAudioConverter_d897847b.o: ../../Source/Lua/CtrlrLuaAudioConverter.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaAudioConverter.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaDebugger_36763bb2.o: ../../Source/Lua/CtrlrLuaDebugger.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaDebugger.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaManager_89c5eb06.o: ../../Source/Lua/CtrlrLuaManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaObject_85f4d2d0.o: ../../Source/Lua/CtrlrLuaObject.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaObject.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaObjectWrapper_dab692d.o: ../../Source/Lua/CtrlrLuaObjectWrapper.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaObjectWrapper.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaPanelCanvasLayer_a584fbc6.o: ../../Source/Lua/CtrlrLuaPanelCanvasLayer.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaPanelCanvasLayer.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaUtils_3835430a.o: ../../Source/Lua/CtrlrLuaUtils.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaUtils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDIDevice_275facd9.o: ../../Source/MIDI/CtrlrMIDIDevice.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDIDevice.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDIDeviceManager_d382511e.o: ../../Source/MIDI/CtrlrMIDIDeviceManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDIDeviceManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDIFilter_9c3df8fb.o: ../../Source/MIDI/CtrlrMIDIFilter.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDIFilter.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMidiInputComparator_b50d6fc7.o: ../../Source/MIDI/CtrlrMidiInputComparator.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMidiInputComparator.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMidiInputComparatorMulti_a3cb717c.o: ../../Source/MIDI/CtrlrMidiInputComparatorMulti.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMidiInputComparatorMulti.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMidiInputComparatorSingle_c444d6af.o: ../../Source/MIDI/CtrlrMidiInputComparatorSingle.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMidiInputComparatorSingle.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMidiMessage_f1795a0e.o: ../../Source/MIDI/CtrlrMidiMessage.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMidiMessage.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMidiMessageEx_a0d44f21.o: ../../Source/MIDI/CtrlrMidiMessageEx.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMidiMessageEx.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrOwnedMidiMessage_b2a92f23.o: ../../Source/MIDI/CtrlrOwnedMidiMessage.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrOwnedMidiMessage.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLinux_981545c6.o: ../../Source/Native/CtrlrLinux.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLinux.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMac_67f057e1.o: ../../Source/Native/CtrlrMac.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMac.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrNative_a50436cf.o: ../../Source/Native/CtrlrNative.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrNative.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrWindows_8f7a495.o: ../../Source/Native/CtrlrWindows.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrWindows.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrProcessor_a9d8df48.o: ../../Source/Plugin/CtrlrProcessor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrProcessor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrProcessorEditorForLive_da85400a.o: ../../Source/Plugin/CtrlrProcessorEditorForLive.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrProcessorEditorForLive.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrDocumentPanel_a034ed7c.o: ../../Source/UIComponents/CtrlrApplicationWindow/CtrlrDocumentPanel.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrDocumentPanel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrEditor_794f45c4.o: ../../Source/UIComponents/CtrlrApplicationWindow/CtrlrEditor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrEditor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrEditorApplicationCommands_a8897f1e.o: ../../Source/UIComponents/CtrlrApplicationWindow/CtrlrEditorApplicationCommands.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrEditorApplicationCommands.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrEditorApplicationCommandsHandlers_9fe09027.o: ../../Source/UIComponents/CtrlrApplicationWindow/CtrlrEditorApplicationCommandsHandlers.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrEditorApplicationCommandsHandlers.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrEditorApplicationCommandsMenus_98f1ccc0.o: ../../Source/UIComponents/CtrlrApplicationWindow/CtrlrEditorApplicationCommandsMenus.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrEditorApplicationCommandsMenus.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrSettings_18014fa.o: ../../Source/UIComponents/CtrlrApplicationWindow/CtrlrSettings.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrSettings.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrButton_4f3b25fd.o: ../../Source/UIComponents/CtrlrComponents/Buttons/CtrlrButton.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrButton.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrCustomButtonInternal_1d79572b.o: ../../Source/UIComponents/CtrlrComponents/Buttons/CtrlrCustomButtonInternal.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrCustomButtonInternal.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrHyperlink_769f0345.o: ../../Source/UIComponents/CtrlrComponents/Buttons/CtrlrHyperlink.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrHyperlink.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrImageButton_2e69b94c.o: ../../Source/UIComponents/CtrlrComponents/Buttons/CtrlrImageButton.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrImageButton.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrToggleButton_d75ffbf1.o: ../../Source/UIComponents/CtrlrComponents/Buttons/CtrlrToggleButton.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrToggleButton.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrGroup_20cf8805.o: ../../Source/UIComponents/CtrlrComponents/Groups/CtrlrGroup.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrGroup.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrTabsComponent_73b077a5.o: ../../Source/UIComponents/CtrlrComponents/Groups/CtrlrTabsComponent.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrTabsComponent.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrImage_24ad6b56.o: ../../Source/UIComponents/CtrlrComponents/Labels/CtrlrImage.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrImage.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLabel_34cbcc6f.o: ../../Source/UIComponents/CtrlrComponents/Labels/CtrlrLabel.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLabel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLCDLabel_ad580dd6.o: ../../Source/UIComponents/CtrlrComponents/Labels/CtrlrLCDLabel.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLCDLabel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrFixedImageSlider_275f8744.o: ../../Source/UIComponents/CtrlrComponents/Sliders/CtrlrFixedImageSlider.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrFixedImageSlider.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrFixedSlider_82d122c3.o: ../../Source/UIComponents/CtrlrComponents/Sliders/CtrlrFixedSlider.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrFixedSlider.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrImageSlider_4e5cefea.o: ../../Source/UIComponents/CtrlrComponents/Sliders/CtrlrImageSlider.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrImageSlider.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrSlider_b3526a5d.o: ../../Source/UIComponents/CtrlrComponents/Sliders/CtrlrSlider.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrSlider.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrSliderInternal_c4abb6ba.o: ../../Source/UIComponents/CtrlrComponents/Sliders/CtrlrSliderInternal.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrSliderInternal.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrFileListBox_a780e671.o: ../../Source/UIComponents/CtrlrComponents/Specials/CtrlrFileListBox.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrFileListBox.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrListBox_5b68770d.o: ../../Source/UIComponents/CtrlrComponents/Specials/CtrlrListBox.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrListBox.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMidiKeyboard_66fc6d32.o: ../../Source/UIComponents/CtrlrComponents/Specials/CtrlrMidiKeyboard.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMidiKeyboard.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrProgressBar_be7eb366.o: ../../Source/UIComponents/CtrlrComponents/Specials/CtrlrProgressBar.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrProgressBar.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrWaveform_80c97e47.o: ../../Source/UIComponents/CtrlrComponents/Specials/CtrlrWaveform.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrWaveform.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrXYModulator_401428ce.o: ../../Source/UIComponents/CtrlrComponents/Specials/CtrlrXYModulator.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrXYModulator.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrXYSurface_ed8dc70c.o: ../../Source/UIComponents/CtrlrComponents/Specials/CtrlrXYSurface.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrXYSurface.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrArrow_f7d8e9a4.o: ../../Source/UIComponents/CtrlrComponents/Statics/CtrlrArrow.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrArrow.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrCombo_d9a943ff.o: ../../Source/UIComponents/CtrlrComponents/CtrlrCombo.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrCombo.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrComponent_565a21ee.o: ../../Source/UIComponents/CtrlrComponents/CtrlrComponent.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrComponent.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrComponentLuaRegistration_c369de8d.o: ../../Source/UIComponents/CtrlrComponents/CtrlrComponentLuaRegistration.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrComponentLuaRegistration.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrComponentTypeManager_eb8d7f4f.o: ../../Source/UIComponents/CtrlrComponents/CtrlrComponentTypeManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrComponentTypeManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrCustomComponent_8d0e28fd.o: ../../Source/UIComponents/CtrlrComponents/CtrlrCustomComponent.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrCustomComponent.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrFilmStripPainter_44309df0.o: ../../Source/UIComponents/CtrlrComponents/CtrlrFilmStripPainter.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrFilmStripPainter.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaCodeTokeniser_f07b7773.o: ../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaCodeTokeniser.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaCodeTokeniser.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodCodeEditor_2dacc3f5.o: ../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodCodeEditor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodCodeEditor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodCodeEditorSettings_3cdccab8.o: ../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodCodeEditorSettings.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodCodeEditorSettings.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerControls_6e517932.o: ../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerControls.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodDebuggerControls.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerInfo_e4ac56aa.o: ../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerInfo.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodDebuggerInfo.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerPrompt_18948aa0.o: ../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerPrompt.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodDebuggerPrompt.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerStackTrace_5f5a64d9.o: ../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerStackTrace.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodDebuggerStackTrace.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerVars_901d2128.o: ../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerVars.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodDebuggerVars.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodEditArea_91f2aef2.o: ../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditArea.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodEditArea.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodEditor_22103128.o: ../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodEditor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodEditorConsole_27c91699.o: ../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditorConsole.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodEditorConsole.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodEditorTabs_38c06846.o: ../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditorTabs.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodEditorTabs.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodFind_27828f4.o: ../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodFind.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodFind.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMethodEditorTabCloseButton_77eee52b.o: ../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrMethodEditorTabCloseButton.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMethodEditorTabCloseButton.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaConsole_ed40c4ae.o: ../../Source/UIComponents/CtrlrLua/CtrlrLuaConsole.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaConsole.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDIBuffer_96c85485.o: ../../Source/UIComponents/CtrlrMIDI/CtrlrMIDIBuffer.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDIBuffer.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDICalculator_478db247.o: ../../Source/UIComponents/CtrlrMIDI/CtrlrMIDICalculator.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDICalculator.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDIMon_9099a031.o: ../../Source/UIComponents/CtrlrMIDI/CtrlrMIDIMon.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDIMon.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDISettingsDevices_266f355f.o: ../../Source/UIComponents/CtrlrMIDI/CtrlrMIDISettingsDevices.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDISettingsDevices.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDISettingsDialog_46327210.o: ../../Source/UIComponents/CtrlrMIDI/CtrlrMIDISettingsDialog.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDISettingsDialog.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDISettingsRouting_44fccc8.o: ../../Source/UIComponents/CtrlrMIDI/CtrlrMIDISettingsRouting.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDISettingsRouting.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelCanvas_6acd392b.o: ../../Source/UIComponents/CtrlrPanel/CtrlrPanelCanvas.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelCanvas.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelCanvasHandlers_af43ed34.o: ../../Source/UIComponents/CtrlrPanel/CtrlrPanelCanvasHandlers.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelCanvasHandlers.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelCanvasLayer_3ae11ab0.o: ../../Source/UIComponents/CtrlrPanel/CtrlrPanelCanvasLayer.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelCanvasLayer.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelCanvasLayers_24f6490d.o: ../../Source/UIComponents/CtrlrPanel/CtrlrPanelCanvasLayers.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelCanvasLayers.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelComponentProperties_a6700c67.o: ../../Source/UIComponents/CtrlrPanel/CtrlrPanelComponentProperties.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelComponentProperties.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelEditor_b6d0d2c0.o: ../../Source/UIComponents/CtrlrPanel/CtrlrPanelEditor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelEditor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelFindProperty_6784c901.o: ../../Source/UIComponents/CtrlrPanel/CtrlrPanelFindProperty.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelFindProperty.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelLayerList_8154b2e6.o: ../../Source/UIComponents/CtrlrPanel/CtrlrPanelLayerList.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelLayerList.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelLayerListItem_f5855019.o: ../../Source/UIComponents/CtrlrPanel/CtrlrPanelLayerListItem.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelLayerListItem.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelModulatorList_dbb12084.o: ../../Source/UIComponents/CtrlrPanel/CtrlrPanelModulatorList.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelModulatorList.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelModulatorListTree_d70579c2.o: ../../Source/UIComponents/CtrlrPanel/CtrlrPanelModulatorListTree.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelModulatorListTree.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelProperties_a872c86.o: ../../Source/UIComponents/CtrlrPanel/CtrlrPanelProperties.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelProperties.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelResourceEditor_5b3b6e.o: ../../Source/UIComponents/CtrlrPanel/CtrlrPanelResourceEditor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelResourceEditor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelUtilities_c2ab4ae1.o: ../../Source/UIComponents/CtrlrPanel/CtrlrPanelUtilities.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelUtilities.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelViewport_dadb95f9.o: ../../Source/UIComponents/CtrlrPanel/CtrlrPanelViewport.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelViewport.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrViewport_fa4a1ea1.o: ../../Source/UIComponents/CtrlrPanel/CtrlrViewport.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrViewport.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPropertyComponent_8edd6f2a.o: ../../Source/UIComponents/CtrlrPropertyEditors/CtrlrPropertyComponent.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPropertyComponent.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrChildWindow_4cf4d23d.o: ../../Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindow.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrChildWindow.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrChildWindowContainer_4534500e.o: ../../Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindowContainer.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrChildWindowContainer.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrChildWindowContent_3235f206.o: ../../Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindowContent.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrChildWindowContent.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrDialogWindow_cdbe7431.o: ../../Source/UIComponents/CtrlrWindowManagers/CtrlrDialogWindow.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrDialogWindow.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrManagerWindowManager_d5d813c9.o: ../../Source/UIComponents/CtrlrWindowManagers/CtrlrManagerWindowManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrManagerWindowManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelWindowManager_d36a6b52.o: ../../Source/UIComponents/CtrlrWindowManagers/CtrlrPanelWindowManager.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelWindowManager.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrAbout_dbdebdec.o: ../../Source/UIComponents/CtrlrAbout.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrAbout.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrComponentSelection_86f225a.o: ../../Source/UIComponents/CtrlrComponentSelection.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrComponentSelection.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLogViewer_9aac1755.o: ../../Source/UIComponents/CtrlrLogViewer.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLogViewer.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrTextEditor_e95be6c5.o: ../../Source/UIComponents/CtrlrTextEditor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrTextEditor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrValueMap_3b250f6.o: ../../Source/UIComponents/CtrlrValueMap.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrValueMap.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrValueTreeEditor_fdda055b.o: ../../Source/UIComponents/CtrlrValueTreeEditor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrValueTreeEditor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling BinaryData.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_basics_8a4e984a.o: ../../JuceLibraryCode/include_juce_audio_basics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_devices_63111d02.o: ../../JuceLibraryCode/include_juce_audio_devices.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_devices.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_formats_15f82001.o: ../../JuceLibraryCode/include_juce_audio_formats.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_formats.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_utils_e32edaee.o: ../../JuceLibraryCode/include_juce_audio_plugin_client_utils.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_plugin_client_utils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_processors_10c03666.o: ../../JuceLibraryCode/include_juce_audio_processors.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_processors.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_utils_9f9fb2d6.o: ../../JuceLibraryCode/include_juce_audio_utils.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_utils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_core_f26d17db.o: ../../JuceLibraryCode/include_juce_core.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_core.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_data_structures_7471b1e3.o: ../../JuceLibraryCode/include_juce_data_structures.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_data_structures.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_events_fd7d695.o: ../../JuceLibraryCode/include_juce_events.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_events.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_graphics_f817e147.o: ../../JuceLibraryCode/include_juce_graphics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_graphics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_gui_basics_e3f79785.o: ../../JuceLibraryCode/include_juce_gui_basics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_gui_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_gui_extra_6dee1c1a.o: ../../JuceLibraryCode/include_juce_gui_extra.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_gui_extra.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

clean:
	@echo Cleaning Ctrlr
	$(V_AT)$(CLEANCMD)

strip:
	@echo Stripping Ctrlr
	-$(V_AT)$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(TARGET)

-include $(OBJECTS_VST:%.o=%.d)
-include $(OBJECTS_VST3:%.o=%.d)
-include $(OBJECTS_STANDALONE_PLUGIN:%.o=%.d)
-include $(OBJECTS_SHARED_CODE:%.o=%.d)
