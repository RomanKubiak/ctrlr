# Automatically generated makefile, created by the Projucer
# Don't edit this file! Your changes will be overwritten when you re-save the Projucer project!

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

ifeq ($(CONFIG),Debug)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Debug
  JUCE_OUTDIR := ../../../../Bin

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DDEBUG=1 -D_DEBUG=1 -DCTRLR_NIGHTLY=1 -DJucePlugin_Build_Standalone -DUSE_ANSI_C=1 -DJUCER_LINUX_MAKE_CC96CACF=1 -DJUCE_APP_VERSION=5.4.0 -DJUCE_APP_VERSION_HEX=0x50400 -pthread -I../../../Standalone/JuceLibraryCode -I../../../../Juce/modules -I../../../../Boost -I../../../../Source/Lua -I../../../../Source/Lua/luabind -I../../../../Source/Lua/luabind/luabind -I../../../../Source/Lua/LuaSocket/include -I../../../../Source/Misc -I../../../../Source/Misc/include -I../../../../Source/MIDI -I../../../../Source -I../../../../Source/UIComponents -I../../../../Source/Core -I../../../../Source/Plugin -I../../../../Source/Application -I../../../../Source/Misc/libusb -I../../../../Source/Misc/include/lo -I/usr/include/freetype2
  JUCE_CFLAGS += $(CFLAGS) $(JUCE_CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0 -fpermissive -std=c++0x -Wno-ignored-qualifiers -Wno-unused-variable -Wno-unused-parameter -Wno-reorder -Wno-empty-body -w -fexceptions -fPIC -fexpensive-optimizations
  JUCE_CXXFLAGS += $(CXXFLAGS) $(JUCE_CFLAGS) -std=c++11
  JUCE_LDFLAGS += $(LDFLAGS) $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt libbfd-$(ARCH).a libiberty-$(ARCH).a -lz -lGL -ludev

  TARGET := Ctrlr-Debug
  BLDCMD = $(CXX) -o $(JUCE_OUTDIR)/$(TARGET) $(OBJECTS) $(JUCE_LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

ifeq ($(CONFIG),Release)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Release
  JUCE_OUTDIR := ../../../../Bin

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DNDEBUG=1 -DJUCE_FORCE_DEBUG=0 -DCTRLR_NIGHTLY=0 -DJucePlugin_Build_Standalone -DUSE_ANSI_C=1 -DJUCER_LINUX_MAKE_CC96CACF=1 -DJUCE_APP_VERSION=5.4.0 -DJUCE_APP_VERSION_HEX=0x50400 -pthread -I../../../Standalone/JuceLibraryCode -I../../../../Juce/modules -I../../../../Boost -I../../../../Source/Lua -I../../../../Source/Lua/luabind -I../../../../Source/Lua/luabind/luabind -I../../../../Source/Misc -I../../../../Source/Misc/include -I../../../../Source/MIDI -I../../../../Source -I../../../../Source/UIComponents -I../../../../Source/Core -I../../../../Source/Plugin -I../../../../Source/Application -I../../../../Source/Misc/libusb
  JUCE_CFLAGS += $(CFLAGS) $(JUCE_CPPFLAGS) $(TARGET_ARCH) -Os -fpermissive -std=c++0x -Wno-ignored-qualifiers -Wno-unused-variable -Wno-unused-parameter -Wno-reorder -Wno-empty-body -w -fexceptions -fPIC -fexpensive-optimizations
  JUCE_CXXFLAGS += $(CXXFLAGS) $(JUCE_CFLAGS) -std=c++11
  JUCE_LDFLAGS += $(LDFLAGS) $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt libbfd-$(ARCH).a libiberty-$(ARCH).a -lz -lGL -ludev

  TARGET := Ctrlr
  BLDCMD = $(CXX) -o $(JUCE_OUTDIR)/$(TARGET) $(OBJECTS) $(JUCE_LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

ifeq ($(CONFIG),Release_Nightly)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Release_Nightly
  JUCE_OUTDIR := ../../../../Bin

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := 
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DNDEBUG=1 -DJUCE_FORCE_DEBUG=0 -DCTRLR_NIGHTLY=1 -DJucePlugin_Build_Standalone -DUSE_ANSI_C=1 -DJUCER_LINUX_MAKE_CC96CACF=1 -DJUCE_APP_VERSION=5.4.0 -DJUCE_APP_VERSION_HEX=0x50400 -pthread -I../../../Standalone/JuceLibraryCode -I../../../../Juce/modules -I../../../../Boost -I../../../../Source/Lua -I../../../../Source/Lua/luabind -I../../../../Source/Lua/luabind/luabind -I../../../../Source/Lua/LuaSocket/include -I../../../../Source/Misc -I../../../../Source/Misc/include -I../../../../Source/MIDI -I../../../../Source -I../../../../Source/UIComponents -I../../../../Source/Core -I../../../../Source/Plugin -I../../../../Source/Application -I../../../../Source/Misc/libusb -I../../../../Source/Misc/include/lo -I/usr/include/freetype2
  JUCE_CFLAGS += $(CFLAGS) $(JUCE_CPPFLAGS) $(TARGET_ARCH) -Ofast -fpermissive -std=c++0x -Wno-ignored-qualifiers -Wno-unused-variable -Wno-unused-parameter -Wno-reorder -Wno-empty-body -w -fexceptions -fPIC -fexpensive-optimizations
  JUCE_CXXFLAGS += $(CXXFLAGS) $(JUCE_CFLAGS) -std=c++11
  JUCE_LDFLAGS += $(LDFLAGS) $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt libbfd-$(ARCH).a libiberty-$(ARCH).a -lz -lGL -ludev

  TARGET := Ctrlr-$(ARCH)
  BLDCMD = $(CXX) -o $(JUCE_OUTDIR)/$(TARGET) $(OBJECTS) $(JUCE_LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

OBJECTS := \
  $(JUCE_OBJDIR)/CtrlrOSC_bdc93ba9.o \
  $(JUCE_OBJDIR)/CtrlrUtilitiesGUI_4d233a31.o \
  $(JUCE_OBJDIR)/CtrlrSysexProcessorOwned_b505063d.o \
  $(JUCE_OBJDIR)/CtrlrFontManager_54d87888.o \
  $(JUCE_OBJDIR)/CtrlrIDManager_f212d9c.o \
  $(JUCE_OBJDIR)/CtrlrLog_50d9896e.o \
  $(JUCE_OBJDIR)/CtrlrManager_ea5c8368.o \
  $(JUCE_OBJDIR)/CtrlrManagerInstance_3849b69d.o \
  $(JUCE_OBJDIR)/CtrlrManagerVst_43428ed9.o \
  $(JUCE_OBJDIR)/CtrlrModulator_46c05ee8.o \
  $(JUCE_OBJDIR)/CtrlrModulatorProcessor_7fe26354.o \
  $(JUCE_OBJDIR)/CtrlrPanelOSC_d70b84a1.o \
  $(JUCE_OBJDIR)/CtrlrPanelUndoManager_d8053dcb.o \
  $(JUCE_OBJDIR)/CtrlrEvaluationScopes_156ffc41.o \
  $(JUCE_OBJDIR)/CtrlrPanel_bc84f48.o \
  $(JUCE_OBJDIR)/CtrlrPanelFileOperations_281288b0.o \
  $(JUCE_OBJDIR)/CtrlrPanelMIDIInputThread_483dbcd5.o \
  $(JUCE_OBJDIR)/CtrlrPanelMIDISnapshot_fe24244d.o \
  $(JUCE_OBJDIR)/CtrlrPanelProcessor_e852def4.o \
  $(JUCE_OBJDIR)/CtrlrPanelResource_d3aa6d76.o \
  $(JUCE_OBJDIR)/CtrlrPanelResourceManager_36b815e1.o \
  $(JUCE_OBJDIR)/CtrlrProperties_e6224b53.o \
  $(JUCE_OBJDIR)/CtrlrSysexProcessor_2314a152.o \
  $(JUCE_OBJDIR)/CtrlrSysexToken_edd240b9.o \
  $(JUCE_OBJDIR)/CtrlrUpdateManager_a061528e.o \
  $(JUCE_OBJDIR)/CtrlrUtilities_b0fa9e74.o \
  $(JUCE_OBJDIR)/CtrlrStandaloneApplication_a59f41f6.o \
  $(JUCE_OBJDIR)/CtrlrStandaloneWindow_cb00a214.o \
  $(JUCE_OBJDIR)/stdafx_b1a20461.o \
  $(JUCE_OBJDIR)/LAudio_a50e2b40.o \
  $(JUCE_OBJDIR)/LComponents_29c3fc36.o \
  $(JUCE_OBJDIR)/LCore_c804e87f.o \
  $(JUCE_OBJDIR)/LGraphics_a64ebfeb.o \
  $(JUCE_OBJDIR)/LJuce_c2f9d4cd.o \
  $(JUCE_OBJDIR)/LMemory_1958b621.o \
  $(JUCE_OBJDIR)/CtrlrLuaDebugger_31880a12.o \
  $(JUCE_OBJDIR)/CtrlrLuaAudioConverter_9ced0adb.o \
  $(JUCE_OBJDIR)/CtrlrLuaCustomComponent_32c93605.o \
  $(JUCE_OBJDIR)/CtrlrLuaManager_5810d0a6.o \
  $(JUCE_OBJDIR)/CtrlrLuaModulator_66e250e8.o \
  $(JUCE_OBJDIR)/CtrlrLuaMultiTimer_5dca06fd.o \
  $(JUCE_OBJDIR)/CtrlrLuaObject_b5e6b930.o \
  $(JUCE_OBJDIR)/CtrlrLuaObjectWrapper_7f5b96cd.o \
  $(JUCE_OBJDIR)/CtrlrLuaPanel_8a5b287d.o \
  $(JUCE_OBJDIR)/CtrlrLuaPanelCanvas_e2d997f5.o \
  $(JUCE_OBJDIR)/CtrlrLuaPanelCanvasLayer_aa926a26.o \
  $(JUCE_OBJDIR)/CtrlrLuaPanelEditor_2edd318a.o \
  $(JUCE_OBJDIR)/CtrlrLuaUtils_293d10aa.o \
  $(JUCE_OBJDIR)/CtrlrLuaBigInteger_d3efa115.o \
  $(JUCE_OBJDIR)/CtrlrLuaComponentAnimator_a379a037.o \
  $(JUCE_OBJDIR)/CtrlrLuaFile_e08e54f3.o \
  $(JUCE_OBJDIR)/CtrlrLuaMemoryBlock_902143bf.o \
  $(JUCE_OBJDIR)/CtrlrLuaRectangle_849a1f22.o \
  $(JUCE_OBJDIR)/luabind_8688111a.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethod_e854dc6f.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodManager_3a1a8cc8.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodManagerCalls_c7bf9bb7.o \
  $(JUCE_OBJDIR)/CtrlrMIDIDevice_22717b39.o \
  $(JUCE_OBJDIR)/CtrlrMIDIDeviceManager_99dd96be.o \
  $(JUCE_OBJDIR)/CtrlrMidiMessageEx_ddf364c1.o \
  $(JUCE_OBJDIR)/CtrlrMidiInputComparator_51adcd67.o \
  $(JUCE_OBJDIR)/CtrlrMidiInputComparatorMulti_aee497dc.o \
  $(JUCE_OBJDIR)/CtrlrMidiInputComparatorSingle_1c507c4f.o \
  $(JUCE_OBJDIR)/CtrlrMIDILibrary_c0bb646a.o \
  $(JUCE_OBJDIR)/CtrlrMidiMessage_58a157ae.o \
  $(JUCE_OBJDIR)/CtrlrOwnedMidiMessage_76feb583.o \
  $(JUCE_OBJDIR)/address_7a9598ba.o \
  $(JUCE_OBJDIR)/blob_6e9d9821.o \
  $(JUCE_OBJDIR)/bundle_1833bc06.o \
  $(JUCE_OBJDIR)/compat_419eff06.o \
  $(JUCE_OBJDIR)/core_707e1fa3.o \
  $(JUCE_OBJDIR)/darwin_usb_594f06f0.o \
  $(JUCE_OBJDIR)/descriptor_c730b833.o \
  $(JUCE_OBJDIR)/enums_78c5918.o \
  $(JUCE_OBJDIR)/hotplug_4a7ef261.o \
  $(JUCE_OBJDIR)/io_5af75f2a.o \
  $(JUCE_OBJDIR)/keys_84371cb8.o \
  $(JUCE_OBJDIR)/lapi_7f139a72.o \
  $(JUCE_OBJDIR)/lauxlib_2fc7b333.o \
  $(JUCE_OBJDIR)/lbaselib_2b98be6c.o \
  $(JUCE_OBJDIR)/lbitlib_160ab68a.o \
  $(JUCE_OBJDIR)/lcode_66b9d01f.o \
  $(JUCE_OBJDIR)/lcorolib_4a57dc94.o \
  $(JUCE_OBJDIR)/lctype_7a3624f5.o \
  $(JUCE_OBJDIR)/ldblib_8faab99f.o \
  $(JUCE_OBJDIR)/ldebug_9441dfab.o \
  $(JUCE_OBJDIR)/ldo_41aba7d.o \
  $(JUCE_OBJDIR)/ldump_68c77666.o \
  $(JUCE_OBJDIR)/lfunc_6c316b36.o \
  $(JUCE_OBJDIR)/lgc_41bea8e.o \
  $(JUCE_OBJDIR)/libr-bfd_c5515a4.o \
  $(JUCE_OBJDIR)/libr_7f7e1b11.o \
  $(JUCE_OBJDIR)/linit_70eb4a82.o \
  $(JUCE_OBJDIR)/linux_udev_659c49af.o \
  $(JUCE_OBJDIR)/linux_usbfs_67550e0c.o \
  $(JUCE_OBJDIR)/liolib_ae58e1f7.o \
  $(JUCE_OBJDIR)/llex_7fa9d537.o \
  $(JUCE_OBJDIR)/lmathlib_c48e4895.o \
  $(JUCE_OBJDIR)/lmem_7fb7c36d.o \
  $(JUCE_OBJDIR)/loadlib_99fa99e5.o \
  $(JUCE_OBJDIR)/lobject_d8b8cdb1.o \
  $(JUCE_OBJDIR)/lopcodes_8b7e76fd.o \
  $(JUCE_OBJDIR)/loslib_f291a7f9.o \
  $(JUCE_OBJDIR)/lparser_1a20ae91.o \
  $(JUCE_OBJDIR)/lstate_c7497669.o \
  $(JUCE_OBJDIR)/lstring_3e519e03.o \
  $(JUCE_OBJDIR)/lstrlib_3e798be6.o \
  $(JUCE_OBJDIR)/ltable_dbce1266.o \
  $(JUCE_OBJDIR)/ltablib_9df6c902.o \
  $(JUCE_OBJDIR)/ltm_421f8eb.o \
  $(JUCE_OBJDIR)/lundump_b97382ff.o \
  $(JUCE_OBJDIR)/lutf8lib_e5e839cc.o \
  $(JUCE_OBJDIR)/lvm_422e1a9.o \
  $(JUCE_OBJDIR)/lzio_8070cdf8.o \
  $(JUCE_OBJDIR)/message_f0a0440d.o \
  $(JUCE_OBJDIR)/method_4af3c0a5.o \
  $(JUCE_OBJDIR)/pattern_match_f4afc7dc.o \
  $(JUCE_OBJDIR)/poll_posix_37a8f9c7.o \
  $(JUCE_OBJDIR)/poll_windows_7e84da07.o \
  $(JUCE_OBJDIR)/send_8b3ce94c.o \
  $(JUCE_OBJDIR)/server_b7920e87.o \
  $(JUCE_OBJDIR)/strerror_5e4de4fb.o \
  $(JUCE_OBJDIR)/structs_4f124184.o \
  $(JUCE_OBJDIR)/sync_8c56bb9f.o \
  $(JUCE_OBJDIR)/threads_posix_2509d033.o \
  $(JUCE_OBJDIR)/threads_windows_9709c573.o \
  $(JUCE_OBJDIR)/timetag_49c3d033.o \
  $(JUCE_OBJDIR)/usb_4a02eca.o \
  $(JUCE_OBJDIR)/version_f296709e.o \
  $(JUCE_OBJDIR)/windows_usb_69ee250e.o \
  $(JUCE_OBJDIR)/CtrlrLinux_891d1366.o \
  $(JUCE_OBJDIR)/CtrlrMac_55cf0d81.o \
  $(JUCE_OBJDIR)/CtrlrNative_d4f61d2f.o \
  $(JUCE_OBJDIR)/CtrlrWindows_d7428a35.o \
  $(JUCE_OBJDIR)/CtrlrProcessor_1100dce8.o \
  $(JUCE_OBJDIR)/CtrlrProcessorEditorForLive_e59e666a.o \
  $(JUCE_OBJDIR)/CtrlrAbout_18fdd38c.o \
  $(JUCE_OBJDIR)/CtrlrDocumentPanel_929b23dc.o \
  $(JUCE_OBJDIR)/CtrlrEditor_9def7b64.o \
  $(JUCE_OBJDIR)/CtrlrEditorApplicationCommands_4671257e.o \
  $(JUCE_OBJDIR)/CtrlrEditorApplicationCommandsHandlers_606bd687.o \
  $(JUCE_OBJDIR)/CtrlrEditorApplicationCommandsMenus_7bb32260.o \
  $(JUCE_OBJDIR)/CtrlrLookAndFeel_6692d7b1.o \
  $(JUCE_OBJDIR)/CtrlrSettings_7ee9629a.o \
  $(JUCE_OBJDIR)/CtrlrButton_bea1a45d.o \
  $(JUCE_OBJDIR)/CtrlrCustomButtonInternal_52f32d8b.o \
  $(JUCE_OBJDIR)/CtrlrHyperlink_3eeb68e5.o \
  $(JUCE_OBJDIR)/CtrlrImageButton_153336ec.o \
  $(JUCE_OBJDIR)/CtrlrToggleButton_c9c63251.o \
  $(JUCE_OBJDIR)/CtrlrCombo_5229199f.o \
  $(JUCE_OBJDIR)/CtrlrComponent_39b6278e.o \
  $(JUCE_OBJDIR)/CtrlrComponentTypeManager_ddf3b5af.o \
  $(JUCE_OBJDIR)/CtrlrCustomComponent_a77769d.o \
  $(JUCE_OBJDIR)/CtrlrFilmStripPainter_73f10450.o \
  $(JUCE_OBJDIR)/CtrlrGroup_32821e65.o \
  $(JUCE_OBJDIR)/CtrlrTabsComponent_6616ae05.o \
  $(JUCE_OBJDIR)/CtrlrImage_366001b6.o \
  $(JUCE_OBJDIR)/CtrlrLabel_467e62cf.o \
  $(JUCE_OBJDIR)/CtrlrLCDLabel_2ac15b76.o \
  $(JUCE_OBJDIR)/CtrlrFixedImageSlider_75038da4.o \
  $(JUCE_OBJDIR)/CtrlrFixedSlider_699aa063.o \
  $(JUCE_OBJDIR)/CtrlrImageSlider_35266d8a.o \
  $(JUCE_OBJDIR)/CtrlrSlider_22b8e8bd.o \
  $(JUCE_OBJDIR)/CtrlrSliderInternal_b65dd51a.o \
  $(JUCE_OBJDIR)/CtrlrProgressBar_b0e4e9c6.o \
  $(JUCE_OBJDIR)/CtrlrFileListBox_99e71cd1.o \
  $(JUCE_OBJDIR)/CtrlrListBox_8b28dd6d.o \
  $(JUCE_OBJDIR)/CtrlrMidiKeyboard_c15d02d2.o \
  $(JUCE_OBJDIR)/CtrlrWaveform_4915e3e7.o \
  $(JUCE_OBJDIR)/CtrlrXYModulator_327a5f2e.o \
  $(JUCE_OBJDIR)/CtrlrXYSurface_2ece156c.o \
  $(JUCE_OBJDIR)/CtrlrArrow_1c791f44.o \
  $(JUCE_OBJDIR)/CtrlrComponentSelection_b1d830ba.o \
  $(JUCE_OBJDIR)/CtrlrLogViewer_61075cf5.o \
  $(JUCE_OBJDIR)/CtrlrLuaConsole_70f9824e.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerVars_b2defec8.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerInfo_76e344a.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodEditorConsole_5d42ecf9.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerStackTrace_7e678a79.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerPrompt_92558040.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerControls_7bab86d2.o \
  $(JUCE_OBJDIR)/CtrlrLuaCodeTokeniser_e22d95d3.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodCodeEditor_94898995.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodCodeEditorSettings_5be9f058.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodEditArea_d6845c92.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodEditor_7c70c6c8.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodEditorTabs_9f9d2de6.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodFind_e941a694.o \
  $(JUCE_OBJDIR)/CtrlrMethodEditorTabCloseButton_15d68b8b.o \
  $(JUCE_OBJDIR)/CtrlrMIDISettingsRouting_28f00268.o \
  $(JUCE_OBJDIR)/CtrlrMIDISettingsDevices_4b0f6aff.o \
  $(JUCE_OBJDIR)/CtrlrMIDISettingsDialog_57e50870.o \
  $(JUCE_OBJDIR)/CtrlrMIDIBuffer_8a274ae5.o \
  $(JUCE_OBJDIR)/CtrlrMIDIBufferEditor_370fe5f2.o \
  $(JUCE_OBJDIR)/CtrlrMIDILibraryEditor_837e6cd.o \
  $(JUCE_OBJDIR)/CtrlrMIDICalculator_ebca78a7.o \
  $(JUCE_OBJDIR)/CtrlrMIDIMon_e8a545d1.o \
  $(JUCE_OBJDIR)/CtrlrViewport_7e02dc41.o \
  $(JUCE_OBJDIR)/CtrlrPanelCanvas_248178b.o \
  $(JUCE_OBJDIR)/CtrlrPanelCanvasHandlers_1eaa6b94.o \
  $(JUCE_OBJDIR)/CtrlrPanelCanvasLayer_b7523850.o \
  $(JUCE_OBJDIR)/CtrlrPanelCanvasLayers_36a8df6d.o \
  $(JUCE_OBJDIR)/CtrlrPanelComponentProperties_8d398a07.o \
  $(JUCE_OBJDIR)/CtrlrPanelEditor_4e4bb120.o \
  $(JUCE_OBJDIR)/CtrlrPanelLayerList_64b0b886.o \
  $(JUCE_OBJDIR)/CtrlrPanelLayerListItem_1a2585b9.o \
  $(JUCE_OBJDIR)/CtrlrPanelModulatorList_515624.o \
  $(JUCE_OBJDIR)/CtrlrPanelModulatorListTree_9f51df62.o \
  $(JUCE_OBJDIR)/CtrlrPanelProperties_92abdae6.o \
  $(JUCE_OBJDIR)/CtrlrPanelResourceEditor_6fc1b9ce.o \
  $(JUCE_OBJDIR)/CtrlrPanelUtilities_a6075081.o \
  $(JUCE_OBJDIR)/CtrlrPanelViewport_7f185c59.o \
  $(JUCE_OBJDIR)/CtrlrModulatorListProperty_417f3f84.o \
  $(JUCE_OBJDIR)/CtrlrTimestampProperty_5aa7a6d.o \
  $(JUCE_OBJDIR)/CtrlrBooleanPropertyComponent_696ccd48.o \
  $(JUCE_OBJDIR)/CtrlrButtonPropertyComponent_b941f3b8.o \
  $(JUCE_OBJDIR)/CtrlrChoicePropertyComponent_3c8068a9.o \
  $(JUCE_OBJDIR)/CtrlrColourPropertyComponent_b131615e.o \
  $(JUCE_OBJDIR)/CtrlrExpressionProperty_98008635.o \
  $(JUCE_OBJDIR)/CtrlrFilePropertyComponent_9cf08eee.o \
  $(JUCE_OBJDIR)/CtrlrFontPropertyComponent_fb3309fb.o \
  $(JUCE_OBJDIR)/CtrlrLuaMethodProperty_c1c1bd0.o \
  $(JUCE_OBJDIR)/CtrlrMultiMidiPropertyComponent_2f5c07f6.o \
  $(JUCE_OBJDIR)/CtrlrPropertyComponent_808f8d8a.o \
  $(JUCE_OBJDIR)/CtrlrSliderPropertyComponent_3cfad569.o \
  $(JUCE_OBJDIR)/CtrlrSysExEditor_8120b80f.o \
  $(JUCE_OBJDIR)/CtrlrSysExFormulaEditor_4a7f649b.o \
  $(JUCE_OBJDIR)/CtrlrSysExPropertyComponent_54ec74d0.o \
  $(JUCE_OBJDIR)/CtrlrTextPropertyComponent_43b7a7dd.o \
  $(JUCE_OBJDIR)/CtrlrUnknownPropertyComponent_48ed5666.o \
  $(JUCE_OBJDIR)/CtrlrTextEditor_ee695525.o \
  $(JUCE_OBJDIR)/CtrlrValueMap_c807d756.o \
  $(JUCE_OBJDIR)/CtrlrValueTreeEditor_71d292fb.o \
  $(JUCE_OBJDIR)/CtrlrChildWindow_ca5e1fdd.o \
  $(JUCE_OBJDIR)/CtrlrChildWindowContainer_92d8566e.o \
  $(JUCE_OBJDIR)/CtrlrChildWindowContent_23e81066.o \
  $(JUCE_OBJDIR)/CtrlrDialogWindow_fd7eda91.o \
  $(JUCE_OBJDIR)/CtrlrManagerWindowManager_237c1a29.o \
  $(JUCE_OBJDIR)/CtrlrPanelWindowManager_c51c89b2.o \
  $(JUCE_OBJDIR)/BinaryData_f3ae2c2f.o \
  $(JUCE_OBJDIR)/juce_audio_basics_595e56e6.o \
  $(JUCE_OBJDIR)/juce_audio_devices_75f931e6.o \
  $(JUCE_OBJDIR)/juce_audio_formats_28e034e5.o \
  $(JUCE_OBJDIR)/juce_audio_processors_3e574702.o \
  $(JUCE_OBJDIR)/juce_audio_utils_ae8fb0ba.o \
  $(JUCE_OBJDIR)/juce_core_ea833277.o \
  $(JUCE_OBJDIR)/juce_cryptography_5bc7c644.o \
  $(JUCE_OBJDIR)/juce_data_structures_6da81dc7.o \
  $(JUCE_OBJDIR)/juce_events_5ad1ba31.o \
  $(JUCE_OBJDIR)/juce_graphics_6c274de3.o \
  $(JUCE_OBJDIR)/juce_gui_basics_91de4d21.o \
  $(JUCE_OBJDIR)/juce_gui_extra_7bcc42fe.o \
  $(JUCE_OBJDIR)/juce_opengl_5583e6c7.o \

.PHONY: clean

$(JUCE_OUTDIR)/$(TARGET): $(OBJECTS) $(RESOURCES)
	@echo Linking Ctrlr_Standalone
	-@mkdir -p $(JUCE_BINDIR)
	-@mkdir -p $(JUCE_LIBDIR)
	-@mkdir -p $(JUCE_OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning Ctrlr_Standalone
	@$(CLEANCMD)

strip:
	@echo Stripping Ctrlr_Standalone
	-@$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(TARGET)

$(JUCE_OBJDIR)/CtrlrOSC_bdc93ba9.o: ../../../../Source/Core/CtrlrOSC.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrOSC.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrUtilitiesGUI_4d233a31.o: ../../../../Source/Core/CtrlrUtilitiesGUI.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrUtilitiesGUI.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrSysexProcessorOwned_b505063d.o: ../../../../Source/Core/CtrlrSysexProcessorOwned.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrSysexProcessorOwned.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrFontManager_54d87888.o: ../../../../Source/Core/CtrlrFontManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrFontManager.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrIDManager_f212d9c.o: ../../../../Source/Core/CtrlrIDManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrIDManager.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLog_50d9896e.o: ../../../../Source/Core/CtrlrLog.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLog.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrManager_ea5c8368.o: ../../../../Source/Core/CtrlrManager/CtrlrManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrManager.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrManagerInstance_3849b69d.o: ../../../../Source/Core/CtrlrManager/CtrlrManagerInstance.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrManagerInstance.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrManagerVst_43428ed9.o: ../../../../Source/Core/CtrlrManager/CtrlrManagerVst.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrManagerVst.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrModulator_46c05ee8.o: ../../../../Source/Core/CtrlrModulator/CtrlrModulator.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrModulator.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrModulatorProcessor_7fe26354.o: ../../../../Source/Core/CtrlrModulator/CtrlrModulatorProcessor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrModulatorProcessor.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelOSC_d70b84a1.o: ../../../../Source/Core/CtrlrPanel/CtrlrPanelOSC.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelOSC.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelUndoManager_d8053dcb.o: ../../../../Source/Core/CtrlrPanel/CtrlrPanelUndoManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelUndoManager.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrEvaluationScopes_156ffc41.o: ../../../../Source/Core/CtrlrPanel/CtrlrEvaluationScopes.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrEvaluationScopes.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanel_bc84f48.o: ../../../../Source/Core/CtrlrPanel/CtrlrPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanel.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelFileOperations_281288b0.o: ../../../../Source/Core/CtrlrPanel/CtrlrPanelFileOperations.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelFileOperations.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelMIDIInputThread_483dbcd5.o: ../../../../Source/Core/CtrlrPanel/CtrlrPanelMIDIInputThread.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelMIDIInputThread.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelMIDISnapshot_fe24244d.o: ../../../../Source/Core/CtrlrPanel/CtrlrPanelMIDISnapshot.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelMIDISnapshot.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelProcessor_e852def4.o: ../../../../Source/Core/CtrlrPanel/CtrlrPanelProcessor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelProcessor.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelResource_d3aa6d76.o: ../../../../Source/Core/CtrlrPanel/CtrlrPanelResource.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelResource.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelResourceManager_36b815e1.o: ../../../../Source/Core/CtrlrPanel/CtrlrPanelResourceManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelResourceManager.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrProperties_e6224b53.o: ../../../../Source/Core/CtrlrProperties.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrProperties.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrSysexProcessor_2314a152.o: ../../../../Source/Core/CtrlrSysexProcessor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrSysexProcessor.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrSysexToken_edd240b9.o: ../../../../Source/Core/CtrlrSysexToken.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrSysexToken.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrUpdateManager_a061528e.o: ../../../../Source/Core/CtrlrUpdateManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrUpdateManager.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrUtilities_b0fa9e74.o: ../../../../Source/Core/CtrlrUtilities.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrUtilities.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrStandaloneApplication_a59f41f6.o: ../../../../Source/Core/StandaloneWrapper/CtrlrStandaloneApplication.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrStandaloneApplication.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrStandaloneWindow_cb00a214.o: ../../../../Source/Core/StandaloneWrapper/CtrlrStandaloneWindow.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrStandaloneWindow.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/stdafx_b1a20461.o: ../../../../Source/Core/stdafx.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling stdafx.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LAudio_a50e2b40.o: ../../../../Source/Lua/JuceClasses/LAudio.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LAudio.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LComponents_29c3fc36.o: ../../../../Source/Lua/JuceClasses/LComponents.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LComponents.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LCore_c804e87f.o: ../../../../Source/Lua/JuceClasses/LCore.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LCore.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LGraphics_a64ebfeb.o: ../../../../Source/Lua/JuceClasses/LGraphics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LGraphics.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LJuce_c2f9d4cd.o: ../../../../Source/Lua/JuceClasses/LJuce.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LJuce.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LMemory_1958b621.o: ../../../../Source/Lua/JuceClasses/LMemory.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LMemory.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaDebugger_31880a12.o: ../../../../Source/Lua/CtrlrLuaDebugger.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaDebugger.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaAudioConverter_9ced0adb.o: ../../../../Source/Lua/CtrlrLuaAudioConverter.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaAudioConverter.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaCustomComponent_32c93605.o: ../../../../Source/Lua/CtrlrLuaCustomComponent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaCustomComponent.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaManager_5810d0a6.o: ../../../../Source/Lua/CtrlrLuaManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaManager.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaModulator_66e250e8.o: ../../../../Source/Lua/CtrlrLuaModulator.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaModulator.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMultiTimer_5dca06fd.o: ../../../../Source/Lua/CtrlrLuaMultiTimer.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMultiTimer.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaObject_b5e6b930.o: ../../../../Source/Lua/CtrlrLuaObject.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaObject.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaObjectWrapper_7f5b96cd.o: ../../../../Source/Lua/CtrlrLuaObjectWrapper.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaObjectWrapper.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaPanel_8a5b287d.o: ../../../../Source/Lua/CtrlrLuaPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaPanel.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaPanelCanvas_e2d997f5.o: ../../../../Source/Lua/CtrlrLuaPanelCanvas.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaPanelCanvas.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaPanelCanvasLayer_aa926a26.o: ../../../../Source/Lua/CtrlrLuaPanelCanvasLayer.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaPanelCanvasLayer.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaPanelEditor_2edd318a.o: ../../../../Source/Lua/CtrlrLuaPanelEditor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaPanelEditor.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaUtils_293d10aa.o: ../../../../Source/Lua/CtrlrLuaUtils.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaUtils.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaBigInteger_d3efa115.o: ../../../../Source/Lua/Deprecated/CtrlrLuaBigInteger.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaBigInteger.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaComponentAnimator_a379a037.o: ../../../../Source/Lua/Deprecated/CtrlrLuaComponentAnimator.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaComponentAnimator.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaFile_e08e54f3.o: ../../../../Source/Lua/Deprecated/CtrlrLuaFile.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaFile.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMemoryBlock_902143bf.o: ../../../../Source/Lua/Deprecated/CtrlrLuaMemoryBlock.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMemoryBlock.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaRectangle_849a1f22.o: ../../../../Source/Lua/Deprecated/CtrlrLuaRectangle.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaRectangle.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/luabind_8688111a.o: ../../../../Source/Lua/luabind/src/luabind.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling luabind.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethod_e854dc6f.o: ../../../../Source/Lua/Methods/CtrlrLuaMethod.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethod.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodManager_3a1a8cc8.o: ../../../../Source/Lua/Methods/CtrlrLuaMethodManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodManager.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodManagerCalls_c7bf9bb7.o: ../../../../Source/Lua/Methods/CtrlrLuaMethodManagerCalls.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodManagerCalls.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDIDevice_22717b39.o: ../../../../Source/MIDI/CtrlrMIDIDevice.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDIDevice.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDIDeviceManager_99dd96be.o: ../../../../Source/MIDI/CtrlrMIDIDeviceManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDIDeviceManager.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMidiMessageEx_ddf364c1.o: ../../../../Source/MIDI/CtrlrMidiMessageEx.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMidiMessageEx.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMidiInputComparator_51adcd67.o: ../../../../Source/MIDI/CtrlrMidiInputComparator.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMidiInputComparator.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMidiInputComparatorMulti_aee497dc.o: ../../../../Source/MIDI/CtrlrMidiInputComparatorMulti.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMidiInputComparatorMulti.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMidiInputComparatorSingle_1c507c4f.o: ../../../../Source/MIDI/CtrlrMidiInputComparatorSingle.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMidiInputComparatorSingle.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDILibrary_c0bb646a.o: ../../../../Source/MIDI/CtrlrMIDILibrary/CtrlrMIDILibrary.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDILibrary.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMidiMessage_58a157ae.o: ../../../../Source/MIDI/CtrlrMidiMessage.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMidiMessage.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrOwnedMidiMessage_76feb583.o: ../../../../Source/MIDI/CtrlrOwnedMidiMessage.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrOwnedMidiMessage.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/address_7a9598ba.o: ../../../../Source/Misc/address.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling address.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/blob_6e9d9821.o: ../../../../Source/Misc/blob.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling blob.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/bundle_1833bc06.o: ../../../../Source/Misc/bundle.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling bundle.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/compat_419eff06.o: ../../../../Source/Misc/compat.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling compat.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/core_707e1fa3.o: ../../../../Source/Misc/core.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling core.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/darwin_usb_594f06f0.o: ../../../../Source/Misc/darwin_usb.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling darwin_usb.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/descriptor_c730b833.o: ../../../../Source/Misc/descriptor.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling descriptor.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/enums_78c5918.o: ../../../../Source/Misc/enums.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling enums.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/hotplug_4a7ef261.o: ../../../../Source/Misc/hotplug.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling hotplug.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/io_5af75f2a.o: ../../../../Source/Misc/io.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling io.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/keys_84371cb8.o: ../../../../Source/Misc/keys.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling keys.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lapi_7f139a72.o: ../../../../Source/Misc/lapi.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lapi.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lauxlib_2fc7b333.o: ../../../../Source/Misc/lauxlib.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lauxlib.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lbaselib_2b98be6c.o: ../../../../Source/Misc/lbaselib.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lbaselib.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lbitlib_160ab68a.o: ../../../../Source/Misc/lbitlib.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lbitlib.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lcode_66b9d01f.o: ../../../../Source/Misc/lcode.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lcode.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lcorolib_4a57dc94.o: ../../../../Source/Misc/lcorolib.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lcorolib.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lctype_7a3624f5.o: ../../../../Source/Misc/lctype.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lctype.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ldblib_8faab99f.o: ../../../../Source/Misc/ldblib.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ldblib.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ldebug_9441dfab.o: ../../../../Source/Misc/ldebug.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ldebug.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ldo_41aba7d.o: ../../../../Source/Misc/ldo.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ldo.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ldump_68c77666.o: ../../../../Source/Misc/ldump.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ldump.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lfunc_6c316b36.o: ../../../../Source/Misc/lfunc.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lfunc.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lgc_41bea8e.o: ../../../../Source/Misc/lgc.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lgc.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/libr-bfd_c5515a4.o: ../../../../Source/Misc/libr-bfd.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling libr-bfd.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/libr_7f7e1b11.o: ../../../../Source/Misc/libr.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling libr.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/linit_70eb4a82.o: ../../../../Source/Misc/linit.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling linit.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/linux_udev_659c49af.o: ../../../../Source/Misc/linux_udev.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling linux_udev.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/linux_usbfs_67550e0c.o: ../../../../Source/Misc/linux_usbfs.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling linux_usbfs.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/liolib_ae58e1f7.o: ../../../../Source/Misc/liolib.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling liolib.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/llex_7fa9d537.o: ../../../../Source/Misc/llex.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling llex.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lmathlib_c48e4895.o: ../../../../Source/Misc/lmathlib.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lmathlib.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lmem_7fb7c36d.o: ../../../../Source/Misc/lmem.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lmem.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/loadlib_99fa99e5.o: ../../../../Source/Misc/loadlib.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling loadlib.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lobject_d8b8cdb1.o: ../../../../Source/Misc/lobject.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lobject.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lopcodes_8b7e76fd.o: ../../../../Source/Misc/lopcodes.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lopcodes.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/loslib_f291a7f9.o: ../../../../Source/Misc/loslib.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling loslib.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lparser_1a20ae91.o: ../../../../Source/Misc/lparser.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lparser.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lstate_c7497669.o: ../../../../Source/Misc/lstate.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lstate.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lstring_3e519e03.o: ../../../../Source/Misc/lstring.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lstring.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lstrlib_3e798be6.o: ../../../../Source/Misc/lstrlib.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lstrlib.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ltable_dbce1266.o: ../../../../Source/Misc/ltable.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ltable.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ltablib_9df6c902.o: ../../../../Source/Misc/ltablib.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ltablib.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ltm_421f8eb.o: ../../../../Source/Misc/ltm.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ltm.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lundump_b97382ff.o: ../../../../Source/Misc/lundump.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lundump.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lutf8lib_e5e839cc.o: ../../../../Source/Misc/lutf8lib.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lutf8lib.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lvm_422e1a9.o: ../../../../Source/Misc/lvm.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lvm.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lzio_8070cdf8.o: ../../../../Source/Misc/lzio.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lzio.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/message_f0a0440d.o: ../../../../Source/Misc/message.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling message.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/method_4af3c0a5.o: ../../../../Source/Misc/method.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling method.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pattern_match_f4afc7dc.o: ../../../../Source/Misc/pattern_match.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pattern_match.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/poll_posix_37a8f9c7.o: ../../../../Source/Misc/poll_posix.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling poll_posix.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/poll_windows_7e84da07.o: ../../../../Source/Misc/poll_windows.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling poll_windows.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/send_8b3ce94c.o: ../../../../Source/Misc/send.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling send.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/server_b7920e87.o: ../../../../Source/Misc/server.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling server.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/strerror_5e4de4fb.o: ../../../../Source/Misc/strerror.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling strerror.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/structs_4f124184.o: ../../../../Source/Misc/structs.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling structs.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sync_8c56bb9f.o: ../../../../Source/Misc/sync.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling sync.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/threads_posix_2509d033.o: ../../../../Source/Misc/threads_posix.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling threads_posix.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/threads_windows_9709c573.o: ../../../../Source/Misc/threads_windows.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling threads_windows.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/timetag_49c3d033.o: ../../../../Source/Misc/timetag.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling timetag.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/usb_4a02eca.o: ../../../../Source/Misc/usb.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling usb.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/version_f296709e.o: ../../../../Source/Misc/version.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling version.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/windows_usb_69ee250e.o: ../../../../Source/Misc/windows_usb.c
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling windows_usb.c"
	@$(CC) $(JUCE_CFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLinux_891d1366.o: ../../../../Source/Native/CtrlrLinux.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLinux.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMac_55cf0d81.o: ../../../../Source/Native/CtrlrMac.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMac.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrNative_d4f61d2f.o: ../../../../Source/Native/CtrlrNative.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrNative.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrWindows_d7428a35.o: ../../../../Source/Native/CtrlrWindows.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrWindows.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrProcessor_1100dce8.o: ../../../../Source/Plugin/CtrlrProcessor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrProcessor.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrProcessorEditorForLive_e59e666a.o: ../../../../Source/Plugin/CtrlrProcessorEditorForLive.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrProcessorEditorForLive.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrAbout_18fdd38c.o: ../../../../Source/UIComponents/CtrlrAbout.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrAbout.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrDocumentPanel_929b23dc.o: ../../../../Source/UIComponents/CtrlrApplicationWindow/CtrlrDocumentPanel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrDocumentPanel.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrEditor_9def7b64.o: ../../../../Source/UIComponents/CtrlrApplicationWindow/CtrlrEditor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrEditor.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrEditorApplicationCommands_4671257e.o: ../../../../Source/UIComponents/CtrlrApplicationWindow/CtrlrEditorApplicationCommands.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrEditorApplicationCommands.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrEditorApplicationCommandsHandlers_606bd687.o: ../../../../Source/UIComponents/CtrlrApplicationWindow/CtrlrEditorApplicationCommandsHandlers.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrEditorApplicationCommandsHandlers.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrEditorApplicationCommandsMenus_7bb32260.o: ../../../../Source/UIComponents/CtrlrApplicationWindow/CtrlrEditorApplicationCommandsMenus.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrEditorApplicationCommandsMenus.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLookAndFeel_6692d7b1.o: ../../../../Source/UIComponents/CtrlrApplicationWindow/CtrlrLookAndFeel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLookAndFeel.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrSettings_7ee9629a.o: ../../../../Source/UIComponents/CtrlrApplicationWindow/CtrlrSettings.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrSettings.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrButton_bea1a45d.o: ../../../../Source/UIComponents/CtrlrComponents/Buttons/CtrlrButton.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrButton.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrCustomButtonInternal_52f32d8b.o: ../../../../Source/UIComponents/CtrlrComponents/Buttons/CtrlrCustomButtonInternal.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrCustomButtonInternal.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrHyperlink_3eeb68e5.o: ../../../../Source/UIComponents/CtrlrComponents/Buttons/CtrlrHyperlink.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrHyperlink.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrImageButton_153336ec.o: ../../../../Source/UIComponents/CtrlrComponents/Buttons/CtrlrImageButton.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrImageButton.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrToggleButton_c9c63251.o: ../../../../Source/UIComponents/CtrlrComponents/Buttons/CtrlrToggleButton.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrToggleButton.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrCombo_5229199f.o: ../../../../Source/UIComponents/CtrlrComponents/CtrlrCombo.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrCombo.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrComponent_39b6278e.o: ../../../../Source/UIComponents/CtrlrComponents/CtrlrComponent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrComponent.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrComponentTypeManager_ddf3b5af.o: ../../../../Source/UIComponents/CtrlrComponents/CtrlrComponentTypeManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrComponentTypeManager.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrCustomComponent_a77769d.o: ../../../../Source/UIComponents/CtrlrComponents/CtrlrCustomComponent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrCustomComponent.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrFilmStripPainter_73f10450.o: ../../../../Source/UIComponents/CtrlrComponents/CtrlrFilmStripPainter.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrFilmStripPainter.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrGroup_32821e65.o: ../../../../Source/UIComponents/CtrlrComponents/Groups/CtrlrGroup.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrGroup.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrTabsComponent_6616ae05.o: ../../../../Source/UIComponents/CtrlrComponents/Groups/CtrlrTabsComponent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrTabsComponent.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrImage_366001b6.o: ../../../../Source/UIComponents/CtrlrComponents/Labels/CtrlrImage.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrImage.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLabel_467e62cf.o: ../../../../Source/UIComponents/CtrlrComponents/Labels/CtrlrLabel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLabel.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLCDLabel_2ac15b76.o: ../../../../Source/UIComponents/CtrlrComponents/Labels/CtrlrLCDLabel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLCDLabel.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrFixedImageSlider_75038da4.o: ../../../../Source/UIComponents/CtrlrComponents/Sliders/CtrlrFixedImageSlider.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrFixedImageSlider.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrFixedSlider_699aa063.o: ../../../../Source/UIComponents/CtrlrComponents/Sliders/CtrlrFixedSlider.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrFixedSlider.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrImageSlider_35266d8a.o: ../../../../Source/UIComponents/CtrlrComponents/Sliders/CtrlrImageSlider.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrImageSlider.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrSlider_22b8e8bd.o: ../../../../Source/UIComponents/CtrlrComponents/Sliders/CtrlrSlider.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrSlider.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrSliderInternal_b65dd51a.o: ../../../../Source/UIComponents/CtrlrComponents/Sliders/CtrlrSliderInternal.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrSliderInternal.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrProgressBar_b0e4e9c6.o: ../../../../Source/UIComponents/CtrlrComponents/Specials/CtrlrProgressBar.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrProgressBar.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrFileListBox_99e71cd1.o: ../../../../Source/UIComponents/CtrlrComponents/Specials/CtrlrFileListBox.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrFileListBox.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrListBox_8b28dd6d.o: ../../../../Source/UIComponents/CtrlrComponents/Specials/CtrlrListBox.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrListBox.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMidiKeyboard_c15d02d2.o: ../../../../Source/UIComponents/CtrlrComponents/Specials/CtrlrMidiKeyboard.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMidiKeyboard.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrWaveform_4915e3e7.o: ../../../../Source/UIComponents/CtrlrComponents/Specials/CtrlrWaveform.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrWaveform.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrXYModulator_327a5f2e.o: ../../../../Source/UIComponents/CtrlrComponents/Specials/CtrlrXYModulator.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrXYModulator.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrXYSurface_2ece156c.o: ../../../../Source/UIComponents/CtrlrComponents/Specials/CtrlrXYSurface.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrXYSurface.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrArrow_1c791f44.o: ../../../../Source/UIComponents/CtrlrComponents/Statics/CtrlrArrow.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrArrow.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrComponentSelection_b1d830ba.o: ../../../../Source/UIComponents/CtrlrComponentSelection.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrComponentSelection.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLogViewer_61075cf5.o: ../../../../Source/UIComponents/CtrlrLogViewer.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLogViewer.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaConsole_70f9824e.o: ../../../../Source/UIComponents/CtrlrLua/CtrlrLuaConsole.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaConsole.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerVars_b2defec8.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerVars.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodDebuggerVars.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerInfo_76e344a.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerInfo.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodDebuggerInfo.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodEditorConsole_5d42ecf9.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditorConsole.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodEditorConsole.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerStackTrace_7e678a79.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerStackTrace.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodDebuggerStackTrace.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerPrompt_92558040.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerPrompt.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodDebuggerPrompt.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodDebuggerControls_7bab86d2.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodDebuggerControls.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodDebuggerControls.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaCodeTokeniser_e22d95d3.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaCodeTokeniser.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaCodeTokeniser.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodCodeEditor_94898995.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodCodeEditor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodCodeEditor.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodCodeEditorSettings_5be9f058.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodCodeEditorSettings.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodCodeEditorSettings.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodEditArea_d6845c92.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditArea.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodEditArea.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodEditor_7c70c6c8.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodEditor.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodEditorTabs_9f9d2de6.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditorTabs.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodEditorTabs.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodFind_e941a694.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodFind.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodFind.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMethodEditorTabCloseButton_15d68b8b.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrMethodEditorTabCloseButton.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMethodEditorTabCloseButton.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDISettingsRouting_28f00268.o: ../../../../Source/UIComponents/CtrlrMIDI/CtrlrMIDISettingsRouting.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDISettingsRouting.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDISettingsDevices_4b0f6aff.o: ../../../../Source/UIComponents/CtrlrMIDI/CtrlrMIDISettingsDevices.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDISettingsDevices.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDISettingsDialog_57e50870.o: ../../../../Source/UIComponents/CtrlrMIDI/CtrlrMIDISettingsDialog.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDISettingsDialog.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDIBuffer_8a274ae5.o: ../../../../Source/UIComponents/CtrlrMIDI/CtrlrMIDIBuffer.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDIBuffer.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDIBufferEditor_370fe5f2.o: ../../../../Source/UIComponents/CtrlrMIDI/CtrlrMIDIBufferEditor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDIBufferEditor.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDILibraryEditor_837e6cd.o: ../../../../Source/UIComponents/CtrlrMIDI/CtrlrMIDILibraryEditor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDILibraryEditor.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDICalculator_ebca78a7.o: ../../../../Source/UIComponents/CtrlrMIDI/CtrlrMIDICalculator.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDICalculator.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMIDIMon_e8a545d1.o: ../../../../Source/UIComponents/CtrlrMIDI/CtrlrMIDIMon.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMIDIMon.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrViewport_7e02dc41.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrViewport.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrViewport.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelCanvas_248178b.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelCanvas.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelCanvas.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelCanvasHandlers_1eaa6b94.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelCanvasHandlers.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelCanvasHandlers.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelCanvasLayer_b7523850.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelCanvasLayer.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelCanvasLayer.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelCanvasLayers_36a8df6d.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelCanvasLayers.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelCanvasLayers.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelComponentProperties_8d398a07.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelComponentProperties.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelComponentProperties.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelEditor_4e4bb120.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelEditor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelEditor.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelLayerList_64b0b886.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelLayerList.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelLayerList.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelLayerListItem_1a2585b9.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelLayerListItem.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelLayerListItem.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelModulatorList_515624.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelModulatorList.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelModulatorList.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelModulatorListTree_9f51df62.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelModulatorListTree.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelModulatorListTree.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelProperties_92abdae6.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelProperties.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelProperties.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelResourceEditor_6fc1b9ce.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelResourceEditor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelResourceEditor.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelUtilities_a6075081.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelUtilities.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelUtilities.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelViewport_7f185c59.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelViewport.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelViewport.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrModulatorListProperty_417f3f84.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrModulatorListProperty.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrModulatorListProperty.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrTimestampProperty_5aa7a6d.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrTimestampProperty.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrTimestampProperty.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrBooleanPropertyComponent_696ccd48.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrBooleanPropertyComponent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrBooleanPropertyComponent.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrButtonPropertyComponent_b941f3b8.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrButtonPropertyComponent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrButtonPropertyComponent.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrChoicePropertyComponent_3c8068a9.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrChoicePropertyComponent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrChoicePropertyComponent.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrColourPropertyComponent_b131615e.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrColourPropertyComponent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrColourPropertyComponent.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrExpressionProperty_98008635.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrExpressionProperty.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrExpressionProperty.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrFilePropertyComponent_9cf08eee.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrFilePropertyComponent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrFilePropertyComponent.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrFontPropertyComponent_fb3309fb.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrFontPropertyComponent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrFontPropertyComponent.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrLuaMethodProperty_c1c1bd0.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrLuaMethodProperty.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrLuaMethodProperty.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrMultiMidiPropertyComponent_2f5c07f6.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrMultiMidiPropertyComponent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrMultiMidiPropertyComponent.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPropertyComponent_808f8d8a.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrPropertyComponent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPropertyComponent.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrSliderPropertyComponent_3cfad569.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrSliderPropertyComponent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrSliderPropertyComponent.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrSysExEditor_8120b80f.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrSysExEditor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrSysExEditor.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrSysExFormulaEditor_4a7f649b.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrSysExFormulaEditor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrSysExFormulaEditor.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrSysExPropertyComponent_54ec74d0.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrSysExPropertyComponent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrSysExPropertyComponent.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrTextPropertyComponent_43b7a7dd.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrTextPropertyComponent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrTextPropertyComponent.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrUnknownPropertyComponent_48ed5666.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrUnknownPropertyComponent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrUnknownPropertyComponent.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrTextEditor_ee695525.o: ../../../../Source/UIComponents/CtrlrTextEditor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrTextEditor.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrValueMap_c807d756.o: ../../../../Source/UIComponents/CtrlrValueMap.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrValueMap.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrValueTreeEditor_71d292fb.o: ../../../../Source/UIComponents/CtrlrValueTreeEditor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrValueTreeEditor.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrChildWindow_ca5e1fdd.o: ../../../../Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindow.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrChildWindow.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrChildWindowContainer_92d8566e.o: ../../../../Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindowContainer.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrChildWindowContainer.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrChildWindowContent_23e81066.o: ../../../../Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindowContent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrChildWindowContent.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrDialogWindow_fd7eda91.o: ../../../../Source/UIComponents/CtrlrWindowManagers/CtrlrDialogWindow.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrDialogWindow.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrManagerWindowManager_237c1a29.o: ../../../../Source/UIComponents/CtrlrWindowManagers/CtrlrManagerWindowManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrManagerWindowManager.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CtrlrPanelWindowManager_c51c89b2.o: ../../../../Source/UIComponents/CtrlrWindowManagers/CtrlrPanelWindowManager.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CtrlrPanelWindowManager.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/BinaryData_f3ae2c2f.o: ../../../Standalone/JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_basics_595e56e6.o: ../../../Standalone/JuceLibraryCode/juce_audio_basics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_devices_75f931e6.o: ../../../Standalone/JuceLibraryCode/juce_audio_devices.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_formats_28e034e5.o: ../../../Standalone/JuceLibraryCode/juce_audio_formats.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_processors_3e574702.o: ../../../Standalone/JuceLibraryCode/juce_audio_processors.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_utils_ae8fb0ba.o: ../../../Standalone/JuceLibraryCode/juce_audio_utils.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_utils.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_core_ea833277.o: ../../../Standalone/JuceLibraryCode/juce_core.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_cryptography_5bc7c644.o: ../../../Standalone/JuceLibraryCode/juce_cryptography.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_cryptography.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_data_structures_6da81dc7.o: ../../../Standalone/JuceLibraryCode/juce_data_structures.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_events_5ad1ba31.o: ../../../Standalone/JuceLibraryCode/juce_events.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_graphics_6c274de3.o: ../../../Standalone/JuceLibraryCode/juce_graphics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_gui_basics_91de4d21.o: ../../../Standalone/JuceLibraryCode/juce_gui_basics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_gui_extra_7bcc42fe.o: ../../../Standalone/JuceLibraryCode/juce_gui_extra.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_opengl_5583e6c7.o: ../../../Standalone/JuceLibraryCode/juce_opengl.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_opengl.cpp"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
