# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := ../../../../Bin

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "CTRLR_NIGHTLY=1" -D "JucePlugin_Build_Standalone" -D "JUCER_LINUX_MAKE_CC96CACF=1" -D "JUCE_APP_VERSION=5.1.2" -D "JUCE_APP_VERSION_HEX=0x50102" -I /usr/include -I /usr/include/freetype2 -I ../../../Standalone/JuceLibraryCode -I ../../../../Juce/modules -I ../../../../Boost -I ../../../../Source/Lua/luabind -I ../../../../Source/Misc -I ../../../../Source/MIDI -I ../../../../Source -I ../../../../Source/UIComponents -I ../../../../Source/Core -I ../../../../Source/Plugin -I ../../../../Source/Application -I ../../../../Source/Lua -I ../../../../Source/Lua/lua
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0 -fpermissive -w -fPIC
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt -lz -lbfd
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "CTRLR_NIGHTLY=1" -D "JucePlugin_Build_Standalone" -D "JUCER_LINUX_MAKE_CC96CACF=1" -D "JUCE_APP_VERSION=5.1.2" -D "JUCE_APP_VERSION_HEX=0x50102" -I /usr/include -I /usr/include/freetype2 -I ../../../Standalone/JuceLibraryCode -I ../../../../Juce/modules -I ../../../../Boost -I ../../../../Source/Lua/luabind -I ../../../../Source/Misc -I ../../../../Source/MIDI -I ../../../../Source -I ../../../../Source/UIComponents -I ../../../../Source/Core -I ../../../../Source/Plugin -I ../../../../Source/Application -I ../../../../Source/Lua -I ../../../../Source/Lua/lua
  TARGET := Ctrlr-Debug-$(ARCH)
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := ../../../../Bin

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCE_FORCE_DEBUG=0" -D "CTRLR_NIGHTLY=0" -D "JucePlugin_Build_Standalone" -D "JUCER_LINUX_MAKE_CC96CACF=1" -D "JUCE_APP_VERSION=5.1.2" -D "JUCE_APP_VERSION_HEX=0x50102" -I /usr/include -I /usr/include/freetype2 -I ../../../Standalone/JuceLibraryCode -I ../../../../Juce/modules -I ../../../../Boost -I ../../../../Source/Lua/luabind -I ../../../../Source/Misc -I ../../../../Source/MIDI -I ../../../../Source -I ../../../../Source/UIComponents -I ../../../../Source/Core -I ../../../../Source/Plugin -I ../../../../Source/Application -I ../../../../Source/Lua -I ../../../../Source/Lua/lua
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os -fpermissive -w -fPIC
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt -lz -lbfd
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCE_FORCE_DEBUG=0" -D "CTRLR_NIGHTLY=0" -D "JucePlugin_Build_Standalone" -D "JUCER_LINUX_MAKE_CC96CACF=1" -D "JUCE_APP_VERSION=5.1.2" -D "JUCE_APP_VERSION_HEX=0x50102" -I /usr/include -I /usr/include/freetype2 -I ../../../Standalone/JuceLibraryCode -I ../../../../Juce/modules -I ../../../../Boost -I ../../../../Source/Lua/luabind -I ../../../../Source/Misc -I ../../../../Source/MIDI -I ../../../../Source -I ../../../../Source/UIComponents -I ../../../../Source/Core -I ../../../../Source/Plugin -I ../../../../Source/Application -I ../../../../Source/Lua -I ../../../../Source/Lua/lua
  TARGET := Ctrlr
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release_Nightly)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release_Nightly
  OUTDIR := ../../../../Bin

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCE_FORCE_DEBUG=0" -D "CTRLR_NIGHTLY=1" -D "JucePlugin_Build_Standalone" -D "JUCER_LINUX_MAKE_CC96CACF=1" -D "JUCE_APP_VERSION=5.1.2" -D "JUCE_APP_VERSION_HEX=0x50102" -I /usr/include -I /usr/include/freetype2 -I ../../../Standalone/JuceLibraryCode -I ../../../../Juce/modules -I ../../../../Boost -I ../../../../Source/Lua/luabind -I ../../../../Source/Misc -I ../../../../Source/MIDI -I ../../../../Source -I ../../../../Source/UIComponents -I ../../../../Source/Core -I ../../../../Source/Plugin -I ../../../../Source/Application -I ../../../../Source/Lua -I ../../../../Source/Lua/lua
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os -fpermissive -w -fPIC
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt -lz -lbfd
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCE_FORCE_DEBUG=0" -D "CTRLR_NIGHTLY=1" -D "JucePlugin_Build_Standalone" -D "JUCER_LINUX_MAKE_CC96CACF=1" -D "JUCE_APP_VERSION=5.1.2" -D "JUCE_APP_VERSION_HEX=0x50102" -I /usr/include -I /usr/include/freetype2 -I ../../../Standalone/JuceLibraryCode -I ../../../../Juce/modules -I ../../../../Boost -I ../../../../Source/Lua/luabind -I ../../../../Source/Misc -I ../../../../Source/MIDI -I ../../../../Source -I ../../../../Source/UIComponents -I ../../../../Source/Core -I ../../../../Source/Plugin -I ../../../../Source/Application -I ../../../../Source/Lua -I ../../../../Source/Lua/lua
  TARGET := Ctrlr-$(ARCH)
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/CtrlrUtilitiesGUI_4d233a31.o \
  $(OBJDIR)/CtrlrSysexProcessorOwned_b505063d.o \
  $(OBJDIR)/CtrlrFontManager_54d87888.o \
  $(OBJDIR)/CtrlrIDManager_f212d9c.o \
  $(OBJDIR)/CtrlrLog_50d9896e.o \
  $(OBJDIR)/CtrlrManager_ea5c8368.o \
  $(OBJDIR)/CtrlrManagerInstance_3849b69d.o \
  $(OBJDIR)/CtrlrManagerVst_43428ed9.o \
  $(OBJDIR)/CtrlrModulator_46c05ee8.o \
  $(OBJDIR)/CtrlrModulatorProcessor_7fe26354.o \
  $(OBJDIR)/CtrlrPanelUndoManager_d8053dcb.o \
  $(OBJDIR)/CtrlrEvaluationScopes_156ffc41.o \
  $(OBJDIR)/CtrlrPanel_bc84f48.o \
  $(OBJDIR)/CtrlrPanelFileOperations_281288b0.o \
  $(OBJDIR)/CtrlrPanelMIDIInputThread_483dbcd5.o \
  $(OBJDIR)/CtrlrPanelMIDISnapshot_fe24244d.o \
  $(OBJDIR)/CtrlrPanelProcessor_e852def4.o \
  $(OBJDIR)/CtrlrPanelResource_d3aa6d76.o \
  $(OBJDIR)/CtrlrPanelResourceManager_36b815e1.o \
  $(OBJDIR)/CtrlrProperties_e6224b53.o \
  $(OBJDIR)/CtrlrSysexProcessor_2314a152.o \
  $(OBJDIR)/CtrlrSysexToken_edd240b9.o \
  $(OBJDIR)/CtrlrUpdateManager_a061528e.o \
  $(OBJDIR)/CtrlrUtilities_b0fa9e74.o \
  $(OBJDIR)/CtrlrStandaloneApplication_a59f41f6.o \
  $(OBJDIR)/CtrlrStandaloneWindow_cb00a214.o \
  $(OBJDIR)/stdafx_b1a20461.o \
  $(OBJDIR)/LXmlElement_f51e885.o \
  $(OBJDIR)/LThread_5c655aaa.o \
  $(OBJDIR)/LThreadWithProgressWindow_a962c8ed.o \
  $(OBJDIR)/LAudioThumbnail_55fa4156.o \
  $(OBJDIR)/LSparseSet_87c3cd0c.o \
  $(OBJDIR)/CtrlrWrap_382e7425.o \
  $(OBJDIR)/LAlertWindow_465bd516.o \
  $(OBJDIR)/LAffineTransform_2319dc77.o \
  $(OBJDIR)/LAttributedString_db4a72d9.o \
  $(OBJDIR)/LAudioFile_c2b0295c.o \
  $(OBJDIR)/LAudioFormat_bf375797.o \
  $(OBJDIR)/LAudioSampleBuffer_4938306a.o \
  $(OBJDIR)/LBigInteger_cd31b13e.o \
  $(OBJDIR)/LBubbleMessageComponent_3f076002.o \
  $(OBJDIR)/LColour_f601596c.o \
  $(OBJDIR)/LComboBox_fd631dbd.o \
  $(OBJDIR)/LColourGradient_2f12e5bc.o \
  $(OBJDIR)/LComponent_c76bde67.o \
  $(OBJDIR)/LComponentPeer_7b1a09e9.o \
  $(OBJDIR)/LDrawable_623b547e.o \
  $(OBJDIR)/LExpression_88737ab8.o \
  $(OBJDIR)/LFile_b805f7dc.o \
  $(OBJDIR)/LFont_f9a86d2f.o \
  $(OBJDIR)/LGlobalFunctions_ba343b62.o \
  $(OBJDIR)/LGlyphArrangement_55693f1e.o \
  $(OBJDIR)/LGraphics_a64ebfeb.o \
  $(OBJDIR)/LImage_657eee45.o \
  $(OBJDIR)/LInputStream_796e1d94.o \
  $(OBJDIR)/LKeyPress_ea4d5a04.o \
  $(OBJDIR)/LJustification_1a98a75c.o \
  $(OBJDIR)/LLabel_759d4f5e.o \
  $(OBJDIR)/LLine_2ab6b654.o \
  $(OBJDIR)/LLookAndFeel_2f64a028.o \
  $(OBJDIR)/LMemoryBlock_bf2138b6.o \
  $(OBJDIR)/LMemoryInputStream_656eca93.o \
  $(OBJDIR)/LMidiMessage_7531a950.o \
  $(OBJDIR)/LModifierKeys_3e79f94b.o \
  $(OBJDIR)/LMouseEvent_ae81d695.o \
  $(OBJDIR)/LPath_2d70ea05.o \
  $(OBJDIR)/LPoint_f71777fa.o \
  $(OBJDIR)/LPopupMenu_987c3e95.o \
  $(OBJDIR)/LRandom_a9eb2ce3.o \
  $(OBJDIR)/LRange_6d09bd27.o \
  $(OBJDIR)/LRectangle_be30e5d9.o \
  $(OBJDIR)/LRelativeCoordinate_8f7e4484.o \
  $(OBJDIR)/LResult_80f0d33d.o \
  $(OBJDIR)/LSlider_e4f58201.o \
  $(OBJDIR)/LString_45435131.o \
  $(OBJDIR)/LTextEditor_762fe41a.o \
  $(OBJDIR)/LTime_680b44ad.o \
  $(OBJDIR)/LTimer_9d03472f.o \
  $(OBJDIR)/LURL_d54a4599.o \
  $(OBJDIR)/LValue_6c32db5b.o \
  $(OBJDIR)/LValueTree_87eff119.o \
  $(OBJDIR)/LZipFile_9ce5b2e7.o \
  $(OBJDIR)/CtrlrLuaAudioConverter_9ced0adb.o \
  $(OBJDIR)/CtrlrLuaCustomComponent_32c93605.o \
  $(OBJDIR)/CtrlrLuaLookAndFeel_fceaeef7.o \
  $(OBJDIR)/CtrlrLuaManager_5810d0a6.o \
  $(OBJDIR)/CtrlrLuaModulator_66e250e8.o \
  $(OBJDIR)/CtrlrLuaMultiTimer_5dca06fd.o \
  $(OBJDIR)/CtrlrLuaObject_b5e6b930.o \
  $(OBJDIR)/CtrlrLuaObjectWrapper_7f5b96cd.o \
  $(OBJDIR)/CtrlrLuaPanel_8a5b287d.o \
  $(OBJDIR)/CtrlrLuaPanelCanvas_e2d997f5.o \
  $(OBJDIR)/CtrlrLuaPanelCanvasLayer_aa926a26.o \
  $(OBJDIR)/CtrlrLuaPanelEditor_2edd318a.o \
  $(OBJDIR)/CtrlrLuaUtils_293d10aa.o \
  $(OBJDIR)/CtrlrLuaBigInteger_d3efa115.o \
  $(OBJDIR)/CtrlrLuaComponentAnimator_a379a037.o \
  $(OBJDIR)/CtrlrLuaFile_e08e54f3.o \
  $(OBJDIR)/CtrlrLuaMemoryBlock_902143bf.o \
  $(OBJDIR)/CtrlrLuaRectangle_849a1f22.o \
  $(OBJDIR)/class_7f21c0dd.o \
  $(OBJDIR)/class_info_44cb3c9a.o \
  $(OBJDIR)/class_registry_4824b529.o \
  $(OBJDIR)/class_rep_8d5435bb.o \
  $(OBJDIR)/create_class_b8c3d9fa.o \
  $(OBJDIR)/error_935a216d.o \
  $(OBJDIR)/exception_handler_1ec3ddbf.o \
  $(OBJDIR)/function_9cb00bdd.o \
  $(OBJDIR)/inheritance_f17c372f.o \
  $(OBJDIR)/link_compatibility_8e43bc70.o \
  $(OBJDIR)/lua_1fbf8c9d.o \
  $(OBJDIR)/object_rep_52fbed22.o \
  $(OBJDIR)/open_cd335d4f.o \
  $(OBJDIR)/pcall_535c3f33.o \
  $(OBJDIR)/scope_fb3187b9.o \
  $(OBJDIR)/stack_content_by_name_fad5e85b.o \
  $(OBJDIR)/weak_ref_50b7c951.o \
  $(OBJDIR)/wrapper_base_6c697482.o \
  $(OBJDIR)/CtrlrLuaMethod_e854dc6f.o \
  $(OBJDIR)/CtrlrLuaMethodManager_3a1a8cc8.o \
  $(OBJDIR)/CtrlrLuaMethodManagerCalls_c7bf9bb7.o \
  $(OBJDIR)/CtrlrMidiMessageEx_ddf364c1.o \
  $(OBJDIR)/CtrlrMIDITransaction_54a29e25.o \
  $(OBJDIR)/CtrlrMidiDevice_859d4f59.o \
  $(OBJDIR)/CtrlrMidiDeviceManager_d5a0de9e.o \
  $(OBJDIR)/CtrlrMidiInputComparator_51adcd67.o \
  $(OBJDIR)/CtrlrMidiInputComparatorMulti_aee497dc.o \
  $(OBJDIR)/CtrlrMidiInputComparatorSingle_1c507c4f.o \
  $(OBJDIR)/CtrlrMIDILibraryRequest_1d9ac64f.o \
  $(OBJDIR)/CtrlrMIDILibrary_c0bb646a.o \
  $(OBJDIR)/CtrlrMidiMessage_58a157ae.o \
  $(OBJDIR)/CtrlrOwnedMidiMessage_76feb583.o \
  $(OBJDIR)/libr-bfd_f5e18fb4.o \
  $(OBJDIR)/libr_e9fa1d21.o \
  $(OBJDIR)/CtrlrLinux_891d1366.o \
  $(OBJDIR)/CtrlrMac_55cf0d81.o \
  $(OBJDIR)/CtrlrNative_d4f61d2f.o \
  $(OBJDIR)/CtrlrWindows_d7428a35.o \
  $(OBJDIR)/CtrlrProcessor_1100dce8.o \
  $(OBJDIR)/CtrlrProcessorEditorForLive_e59e666a.o \
  $(OBJDIR)/CtrlrAbout_18fdd38c.o \
  $(OBJDIR)/CtrlrDocumentPanel_929b23dc.o \
  $(OBJDIR)/CtrlrEditor_9def7b64.o \
  $(OBJDIR)/CtrlrEditorApplicationCommands_4671257e.o \
  $(OBJDIR)/CtrlrEditorApplicationCommandsHandlers_606bd687.o \
  $(OBJDIR)/CtrlrEditorApplicationCommandsMenus_7bb32260.o \
  $(OBJDIR)/CtrlrLookAndFeel_6692d7b1.o \
  $(OBJDIR)/CtrlrSettings_7ee9629a.o \
  $(OBJDIR)/CtrlrButton_bea1a45d.o \
  $(OBJDIR)/CtrlrCustomButtonInternal_52f32d8b.o \
  $(OBJDIR)/CtrlrHyperlink_3eeb68e5.o \
  $(OBJDIR)/CtrlrImageButton_153336ec.o \
  $(OBJDIR)/CtrlrToggleButton_c9c63251.o \
  $(OBJDIR)/CtrlrCombo_5229199f.o \
  $(OBJDIR)/CtrlrComponent_39b6278e.o \
  $(OBJDIR)/CtrlrComponentBubble_b187cb7a.o \
  $(OBJDIR)/CtrlrComponentTypeManager_ddf3b5af.o \
  $(OBJDIR)/CtrlrCustomComponent_a77769d.o \
  $(OBJDIR)/CtrlrFilmStripPainter_73f10450.o \
  $(OBJDIR)/CtrlrGroup_32821e65.o \
  $(OBJDIR)/CtrlrTabsComponent_6616ae05.o \
  $(OBJDIR)/CtrlrImage_366001b6.o \
  $(OBJDIR)/CtrlrLabel_467e62cf.o \
  $(OBJDIR)/CtrlrLCDLabel_2ac15b76.o \
  $(OBJDIR)/CtrlrFixedImageSlider_75038da4.o \
  $(OBJDIR)/CtrlrFixedSlider_699aa063.o \
  $(OBJDIR)/CtrlrImageSlider_35266d8a.o \
  $(OBJDIR)/CtrlrSlider_22b8e8bd.o \
  $(OBJDIR)/CtrlrSliderInternal_b65dd51a.o \
  $(OBJDIR)/CtrlrFileListBox_99e71cd1.o \
  $(OBJDIR)/CtrlrListBox_8b28dd6d.o \
  $(OBJDIR)/CtrlrMidiKeyboard_c15d02d2.o \
  $(OBJDIR)/CtrlrWaveform_4915e3e7.o \
  $(OBJDIR)/CtrlrXYModulator_327a5f2e.o \
  $(OBJDIR)/CtrlrXYSurface_2ece156c.o \
  $(OBJDIR)/CtrlrArrow_1c791f44.o \
  $(OBJDIR)/CtrlrComponentSelection_b1d830ba.o \
  $(OBJDIR)/CtrlrLogViewer_61075cf5.o \
  $(OBJDIR)/CtrlrLuaConsole_70f9824e.o \
  $(OBJDIR)/CtrlrLuaCodeTokeniser_e22d95d3.o \
  $(OBJDIR)/CtrlrLuaMethodCodeEditor_94898995.o \
  $(OBJDIR)/CtrlrLuaMethodCodeEditorSettings_5be9f058.o \
  $(OBJDIR)/CtrlrLuaMethodEditArea_d6845c92.o \
  $(OBJDIR)/CtrlrLuaMethodEditor_7c70c6c8.o \
  $(OBJDIR)/CtrlrLuaMethodEditorTabs_9f9d2de6.o \
  $(OBJDIR)/CtrlrLuaMethodFind_e941a694.o \
  $(OBJDIR)/CtrlrMethodEditorTabCloseButton_15d68b8b.o \
  $(OBJDIR)/CtrlrMIDIBuffer_8a274ae5.o \
  $(OBJDIR)/CtrlrMIDIBufferEditor_370fe5f2.o \
  $(OBJDIR)/CtrlrMIDILibraryEditor_837e6cd.o \
  $(OBJDIR)/CtrlrMIDICalculator_ebca78a7.o \
  $(OBJDIR)/CtrlrMIDIMon_e8a545d1.o \
  $(OBJDIR)/CtrlrViewport_7e02dc41.o \
  $(OBJDIR)/CtrlrPanelMIDIToolbar_2522e231.o \
  $(OBJDIR)/CtrlrPanelCanvas_248178b.o \
  $(OBJDIR)/CtrlrPanelCanvasHandlers_1eaa6b94.o \
  $(OBJDIR)/CtrlrPanelCanvasLayer_b7523850.o \
  $(OBJDIR)/CtrlrPanelCanvasLayers_36a8df6d.o \
  $(OBJDIR)/CtrlrPanelComponentProperties_8d398a07.o \
  $(OBJDIR)/CtrlrPanelEditor_4e4bb120.o \
  $(OBJDIR)/CtrlrPanelLayerList_64b0b886.o \
  $(OBJDIR)/CtrlrPanelLayerListItem_1a2585b9.o \
  $(OBJDIR)/CtrlrPanelModulatorList_515624.o \
  $(OBJDIR)/CtrlrPanelModulatorListTree_9f51df62.o \
  $(OBJDIR)/CtrlrPanelProperties_92abdae6.o \
  $(OBJDIR)/CtrlrPanelResourceEditor_6fc1b9ce.o \
  $(OBJDIR)/CtrlrPanelUtilities_a6075081.o \
  $(OBJDIR)/CtrlrPanelViewport_7f185c59.o \
  $(OBJDIR)/CtrlrModulatorListProperty_417f3f84.o \
  $(OBJDIR)/CtrlrTimestampProperty_5aa7a6d.o \
  $(OBJDIR)/CtrlrBooleanPropertyComponent_696ccd48.o \
  $(OBJDIR)/CtrlrButtonPropertyComponent_b941f3b8.o \
  $(OBJDIR)/CtrlrChoicePropertyComponent_3c8068a9.o \
  $(OBJDIR)/CtrlrColourPropertyComponent_b131615e.o \
  $(OBJDIR)/CtrlrExpressionProperty_98008635.o \
  $(OBJDIR)/CtrlrFilePropertyComponent_9cf08eee.o \
  $(OBJDIR)/CtrlrFontPropertyComponent_fb3309fb.o \
  $(OBJDIR)/CtrlrLuaMethodProperty_c1c1bd0.o \
  $(OBJDIR)/CtrlrMultiMidiPropertyComponent_2f5c07f6.o \
  $(OBJDIR)/CtrlrPropertyComponent_808f8d8a.o \
  $(OBJDIR)/CtrlrSliderPropertyComponent_3cfad569.o \
  $(OBJDIR)/CtrlrSysExEditor_8120b80f.o \
  $(OBJDIR)/CtrlrSysExFormulaEditor_4a7f649b.o \
  $(OBJDIR)/CtrlrSysExPropertyComponent_54ec74d0.o \
  $(OBJDIR)/CtrlrTextPropertyComponent_43b7a7dd.o \
  $(OBJDIR)/CtrlrUnknownPropertyComponent_48ed5666.o \
  $(OBJDIR)/CtrlrTextEditor_ee695525.o \
  $(OBJDIR)/CtrlrValueMap_c807d756.o \
  $(OBJDIR)/CtrlrValueTreeEditor_71d292fb.o \
  $(OBJDIR)/CtrlrChildWindow_ca5e1fdd.o \
  $(OBJDIR)/CtrlrChildWindowContainer_92d8566e.o \
  $(OBJDIR)/CtrlrChildWindowContent_23e81066.o \
  $(OBJDIR)/CtrlrDialogWindow_fd7eda91.o \
  $(OBJDIR)/CtrlrManagerWindowManager_237c1a29.o \
  $(OBJDIR)/CtrlrPanelWindowManager_c51c89b2.o \
  $(OBJDIR)/BinaryData_f3ae2c2f.o \
  $(OBJDIR)/juce_audio_basics_49fc64dc.o \
  $(OBJDIR)/juce_audio_devices_4221f29a.o \
  $(OBJDIR)/juce_audio_formats_70a33c3a.o \
  $(OBJDIR)/juce_audio_processors_bd1ca294.o \
  $(OBJDIR)/juce_audio_utils_fd7e75a.o \
  $(OBJDIR)/juce_core_62c225be.o \
  $(OBJDIR)/juce_data_structures_2dd916fa.o \
  $(OBJDIR)/juce_events_632f8332.o \
  $(OBJDIR)/juce_graphics_3c1b7996.o \
  $(OBJDIR)/juce_gui_basics_657c2612.o \
  $(OBJDIR)/juce_gui_extra_c674b41a.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking Ctrlr_Standalone
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning Ctrlr_Standalone
	@$(CLEANCMD)

strip:
	@echo Stripping Ctrlr_Standalone
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/CtrlrUtilitiesGUI_4d233a31.o: ../../../../Source/Core/CtrlrUtilitiesGUI.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrUtilitiesGUI.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrSysexProcessorOwned_b505063d.o: ../../../../Source/Core/CtrlrSysexProcessorOwned.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrSysexProcessorOwned.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrFontManager_54d87888.o: ../../../../Source/Core/CtrlrFontManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrFontManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrIDManager_f212d9c.o: ../../../../Source/Core/CtrlrIDManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrIDManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLog_50d9896e.o: ../../../../Source/Core/CtrlrLog.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLog.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrManager_ea5c8368.o: ../../../../Source/Core/CtrlrManager/CtrlrManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrManagerInstance_3849b69d.o: ../../../../Source/Core/CtrlrManager/CtrlrManagerInstance.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrManagerInstance.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrManagerVst_43428ed9.o: ../../../../Source/Core/CtrlrManager/CtrlrManagerVst.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrManagerVst.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrModulator_46c05ee8.o: ../../../../Source/Core/CtrlrModulator/CtrlrModulator.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrModulator.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrModulatorProcessor_7fe26354.o: ../../../../Source/Core/CtrlrModulator/CtrlrModulatorProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrModulatorProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelUndoManager_d8053dcb.o: ../../../../Source/Core/CtrlrPanel/CtrlrPanelUndoManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelUndoManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrEvaluationScopes_156ffc41.o: ../../../../Source/Core/CtrlrPanel/CtrlrEvaluationScopes.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrEvaluationScopes.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanel_bc84f48.o: ../../../../Source/Core/CtrlrPanel/CtrlrPanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelFileOperations_281288b0.o: ../../../../Source/Core/CtrlrPanel/CtrlrPanelFileOperations.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelFileOperations.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelMIDIInputThread_483dbcd5.o: ../../../../Source/Core/CtrlrPanel/CtrlrPanelMIDIInputThread.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelMIDIInputThread.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelMIDISnapshot_fe24244d.o: ../../../../Source/Core/CtrlrPanel/CtrlrPanelMIDISnapshot.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelMIDISnapshot.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelProcessor_e852def4.o: ../../../../Source/Core/CtrlrPanel/CtrlrPanelProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelResource_d3aa6d76.o: ../../../../Source/Core/CtrlrPanel/CtrlrPanelResource.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelResource.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelResourceManager_36b815e1.o: ../../../../Source/Core/CtrlrPanel/CtrlrPanelResourceManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelResourceManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrProperties_e6224b53.o: ../../../../Source/Core/CtrlrProperties.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrProperties.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrSysexProcessor_2314a152.o: ../../../../Source/Core/CtrlrSysexProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrSysexProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrSysexToken_edd240b9.o: ../../../../Source/Core/CtrlrSysexToken.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrSysexToken.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrUpdateManager_a061528e.o: ../../../../Source/Core/CtrlrUpdateManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrUpdateManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrUtilities_b0fa9e74.o: ../../../../Source/Core/CtrlrUtilities.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrUtilities.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrStandaloneApplication_a59f41f6.o: ../../../../Source/Core/StandaloneWrapper/CtrlrStandaloneApplication.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrStandaloneApplication.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrStandaloneWindow_cb00a214.o: ../../../../Source/Core/StandaloneWrapper/CtrlrStandaloneWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrStandaloneWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/stdafx_b1a20461.o: ../../../../Source/Core/stdafx.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling stdafx.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LXmlElement_f51e885.o: ../../../../Source/Lua/JuceClasses/LXmlElement.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LXmlElement.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LThread_5c655aaa.o: ../../../../Source/Lua/JuceClasses/LThread.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LThread.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LThreadWithProgressWindow_a962c8ed.o: ../../../../Source/Lua/JuceClasses/LThreadWithProgressWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LThreadWithProgressWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LAudioThumbnail_55fa4156.o: ../../../../Source/Lua/JuceClasses/LAudioThumbnail.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LAudioThumbnail.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LSparseSet_87c3cd0c.o: ../../../../Source/Lua/JuceClasses/LSparseSet.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LSparseSet.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrWrap_382e7425.o: ../../../../Source/Lua/JuceClasses/CtrlrWrap.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrWrap.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LAlertWindow_465bd516.o: ../../../../Source/Lua/JuceClasses/LAlertWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LAlertWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LAffineTransform_2319dc77.o: ../../../../Source/Lua/JuceClasses/LAffineTransform.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LAffineTransform.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LAttributedString_db4a72d9.o: ../../../../Source/Lua/JuceClasses/LAttributedString.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LAttributedString.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LAudioFile_c2b0295c.o: ../../../../Source/Lua/JuceClasses/LAudioFile.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LAudioFile.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LAudioFormat_bf375797.o: ../../../../Source/Lua/JuceClasses/LAudioFormat.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LAudioFormat.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LAudioSampleBuffer_4938306a.o: ../../../../Source/Lua/JuceClasses/LAudioSampleBuffer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LAudioSampleBuffer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LBigInteger_cd31b13e.o: ../../../../Source/Lua/JuceClasses/LBigInteger.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LBigInteger.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LBubbleMessageComponent_3f076002.o: ../../../../Source/Lua/JuceClasses/LBubbleMessageComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LBubbleMessageComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LColour_f601596c.o: ../../../../Source/Lua/JuceClasses/LColour.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LColour.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LComboBox_fd631dbd.o: ../../../../Source/Lua/JuceClasses/LComboBox.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LComboBox.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LColourGradient_2f12e5bc.o: ../../../../Source/Lua/JuceClasses/LColourGradient.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LColourGradient.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LComponent_c76bde67.o: ../../../../Source/Lua/JuceClasses/LComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LComponentPeer_7b1a09e9.o: ../../../../Source/Lua/JuceClasses/LComponentPeer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LComponentPeer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LDrawable_623b547e.o: ../../../../Source/Lua/JuceClasses/LDrawable.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LDrawable.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LExpression_88737ab8.o: ../../../../Source/Lua/JuceClasses/LExpression.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LExpression.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LFile_b805f7dc.o: ../../../../Source/Lua/JuceClasses/LFile.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LFile.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LFont_f9a86d2f.o: ../../../../Source/Lua/JuceClasses/LFont.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LFont.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LGlobalFunctions_ba343b62.o: ../../../../Source/Lua/JuceClasses/LGlobalFunctions.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LGlobalFunctions.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LGlyphArrangement_55693f1e.o: ../../../../Source/Lua/JuceClasses/LGlyphArrangement.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LGlyphArrangement.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LGraphics_a64ebfeb.o: ../../../../Source/Lua/JuceClasses/LGraphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LGraphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LImage_657eee45.o: ../../../../Source/Lua/JuceClasses/LImage.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LImage.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LInputStream_796e1d94.o: ../../../../Source/Lua/JuceClasses/LInputStream.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LInputStream.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LKeyPress_ea4d5a04.o: ../../../../Source/Lua/JuceClasses/LKeyPress.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LKeyPress.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LJustification_1a98a75c.o: ../../../../Source/Lua/JuceClasses/LJustification.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LJustification.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LLabel_759d4f5e.o: ../../../../Source/Lua/JuceClasses/LLabel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LLabel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LLine_2ab6b654.o: ../../../../Source/Lua/JuceClasses/LLine.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LLine.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LLookAndFeel_2f64a028.o: ../../../../Source/Lua/JuceClasses/LLookAndFeel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LLookAndFeel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LMemoryBlock_bf2138b6.o: ../../../../Source/Lua/JuceClasses/LMemoryBlock.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LMemoryBlock.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LMemoryInputStream_656eca93.o: ../../../../Source/Lua/JuceClasses/LMemoryInputStream.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LMemoryInputStream.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LMidiMessage_7531a950.o: ../../../../Source/Lua/JuceClasses/LMidiMessage.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LMidiMessage.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LModifierKeys_3e79f94b.o: ../../../../Source/Lua/JuceClasses/LModifierKeys.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LModifierKeys.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LMouseEvent_ae81d695.o: ../../../../Source/Lua/JuceClasses/LMouseEvent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LMouseEvent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LPath_2d70ea05.o: ../../../../Source/Lua/JuceClasses/LPath.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LPath.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LPoint_f71777fa.o: ../../../../Source/Lua/JuceClasses/LPoint.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LPoint.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LPopupMenu_987c3e95.o: ../../../../Source/Lua/JuceClasses/LPopupMenu.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LPopupMenu.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LRandom_a9eb2ce3.o: ../../../../Source/Lua/JuceClasses/LRandom.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LRandom.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LRange_6d09bd27.o: ../../../../Source/Lua/JuceClasses/LRange.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LRange.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LRectangle_be30e5d9.o: ../../../../Source/Lua/JuceClasses/LRectangle.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LRectangle.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LRelativeCoordinate_8f7e4484.o: ../../../../Source/Lua/JuceClasses/LRelativeCoordinate.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LRelativeCoordinate.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LResult_80f0d33d.o: ../../../../Source/Lua/JuceClasses/LResult.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LResult.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LSlider_e4f58201.o: ../../../../Source/Lua/JuceClasses/LSlider.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LSlider.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LString_45435131.o: ../../../../Source/Lua/JuceClasses/LString.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LString.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LTextEditor_762fe41a.o: ../../../../Source/Lua/JuceClasses/LTextEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LTextEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LTime_680b44ad.o: ../../../../Source/Lua/JuceClasses/LTime.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LTime.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LTimer_9d03472f.o: ../../../../Source/Lua/JuceClasses/LTimer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LTimer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LURL_d54a4599.o: ../../../../Source/Lua/JuceClasses/LURL.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LURL.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LValue_6c32db5b.o: ../../../../Source/Lua/JuceClasses/LValue.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LValue.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LValueTree_87eff119.o: ../../../../Source/Lua/JuceClasses/LValueTree.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LValueTree.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LZipFile_9ce5b2e7.o: ../../../../Source/Lua/JuceClasses/LZipFile.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LZipFile.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaAudioConverter_9ced0adb.o: ../../../../Source/Lua/CtrlrLuaAudioConverter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaAudioConverter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaCustomComponent_32c93605.o: ../../../../Source/Lua/CtrlrLuaCustomComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaCustomComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaLookAndFeel_fceaeef7.o: ../../../../Source/Lua/CtrlrLuaLookAndFeel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaLookAndFeel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaManager_5810d0a6.o: ../../../../Source/Lua/CtrlrLuaManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaModulator_66e250e8.o: ../../../../Source/Lua/CtrlrLuaModulator.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaModulator.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaMultiTimer_5dca06fd.o: ../../../../Source/Lua/CtrlrLuaMultiTimer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaMultiTimer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaObject_b5e6b930.o: ../../../../Source/Lua/CtrlrLuaObject.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaObject.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaObjectWrapper_7f5b96cd.o: ../../../../Source/Lua/CtrlrLuaObjectWrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaObjectWrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaPanel_8a5b287d.o: ../../../../Source/Lua/CtrlrLuaPanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaPanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaPanelCanvas_e2d997f5.o: ../../../../Source/Lua/CtrlrLuaPanelCanvas.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaPanelCanvas.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaPanelCanvasLayer_aa926a26.o: ../../../../Source/Lua/CtrlrLuaPanelCanvasLayer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaPanelCanvasLayer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaPanelEditor_2edd318a.o: ../../../../Source/Lua/CtrlrLuaPanelEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaPanelEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaUtils_293d10aa.o: ../../../../Source/Lua/CtrlrLuaUtils.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaUtils.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaBigInteger_d3efa115.o: ../../../../Source/Lua/Deprecated/CtrlrLuaBigInteger.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaBigInteger.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaComponentAnimator_a379a037.o: ../../../../Source/Lua/Deprecated/CtrlrLuaComponentAnimator.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaComponentAnimator.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaFile_e08e54f3.o: ../../../../Source/Lua/Deprecated/CtrlrLuaFile.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaFile.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaMemoryBlock_902143bf.o: ../../../../Source/Lua/Deprecated/CtrlrLuaMemoryBlock.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaMemoryBlock.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaRectangle_849a1f22.o: ../../../../Source/Lua/Deprecated/CtrlrLuaRectangle.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaRectangle.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/class_7f21c0dd.o: ../../../../Source/Lua/luabind/src/class.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling class.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/class_info_44cb3c9a.o: ../../../../Source/Lua/luabind/src/class_info.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling class_info.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/class_registry_4824b529.o: ../../../../Source/Lua/luabind/src/class_registry.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling class_registry.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/class_rep_8d5435bb.o: ../../../../Source/Lua/luabind/src/class_rep.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling class_rep.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/create_class_b8c3d9fa.o: ../../../../Source/Lua/luabind/src/create_class.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling create_class.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/error_935a216d.o: ../../../../Source/Lua/luabind/src/error.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling error.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/exception_handler_1ec3ddbf.o: ../../../../Source/Lua/luabind/src/exception_handler.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling exception_handler.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/function_9cb00bdd.o: ../../../../Source/Lua/luabind/src/function.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling function.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/inheritance_f17c372f.o: ../../../../Source/Lua/luabind/src/inheritance.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling inheritance.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/link_compatibility_8e43bc70.o: ../../../../Source/Lua/luabind/src/link_compatibility.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling link_compatibility.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/lua_1fbf8c9d.o: ../../../../Source/Lua/luabind/src/lua.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling lua.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/object_rep_52fbed22.o: ../../../../Source/Lua/luabind/src/object_rep.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling object_rep.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/open_cd335d4f.o: ../../../../Source/Lua/luabind/src/open.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling open.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pcall_535c3f33.o: ../../../../Source/Lua/luabind/src/pcall.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pcall.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/scope_fb3187b9.o: ../../../../Source/Lua/luabind/src/scope.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling scope.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/stack_content_by_name_fad5e85b.o: ../../../../Source/Lua/luabind/src/stack_content_by_name.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling stack_content_by_name.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/weak_ref_50b7c951.o: ../../../../Source/Lua/luabind/src/weak_ref.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling weak_ref.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/wrapper_base_6c697482.o: ../../../../Source/Lua/luabind/src/wrapper_base.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling wrapper_base.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaMethod_e854dc6f.o: ../../../../Source/Lua/Methods/CtrlrLuaMethod.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaMethod.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaMethodManager_3a1a8cc8.o: ../../../../Source/Lua/Methods/CtrlrLuaMethodManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaMethodManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaMethodManagerCalls_c7bf9bb7.o: ../../../../Source/Lua/Methods/CtrlrLuaMethodManagerCalls.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaMethodManagerCalls.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMidiMessageEx_ddf364c1.o: ../../../../Source/MIDI/CtrlrMidiMessageEx.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMidiMessageEx.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMIDITransaction_54a29e25.o: ../../../../Source/MIDI/CtrlrMIDITransaction.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMIDITransaction.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMidiDevice_859d4f59.o: ../../../../Source/MIDI/CtrlrMidiDevice.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMidiDevice.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMidiDeviceManager_d5a0de9e.o: ../../../../Source/MIDI/CtrlrMidiDeviceManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMidiDeviceManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMidiInputComparator_51adcd67.o: ../../../../Source/MIDI/CtrlrMidiInputComparator.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMidiInputComparator.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMidiInputComparatorMulti_aee497dc.o: ../../../../Source/MIDI/CtrlrMidiInputComparatorMulti.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMidiInputComparatorMulti.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMidiInputComparatorSingle_1c507c4f.o: ../../../../Source/MIDI/CtrlrMidiInputComparatorSingle.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMidiInputComparatorSingle.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMIDILibraryRequest_1d9ac64f.o: ../../../../Source/MIDI/CtrlrMIDILibrary/CtrlrMIDILibraryRequest.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMIDILibraryRequest.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMIDILibrary_c0bb646a.o: ../../../../Source/MIDI/CtrlrMIDILibrary/CtrlrMIDILibrary.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMIDILibrary.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMidiMessage_58a157ae.o: ../../../../Source/MIDI/CtrlrMidiMessage.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMidiMessage.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrOwnedMidiMessage_76feb583.o: ../../../../Source/MIDI/CtrlrOwnedMidiMessage.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrOwnedMidiMessage.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/libr-bfd_f5e18fb4.o: ../../../../Source/Native/Linux/libr-bfd.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling libr-bfd.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/libr_e9fa1d21.o: ../../../../Source/Native/Linux/libr.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling libr.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLinux_891d1366.o: ../../../../Source/Native/CtrlrLinux.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLinux.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMac_55cf0d81.o: ../../../../Source/Native/CtrlrMac.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMac.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrNative_d4f61d2f.o: ../../../../Source/Native/CtrlrNative.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrNative.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrWindows_d7428a35.o: ../../../../Source/Native/CtrlrWindows.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrWindows.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrProcessor_1100dce8.o: ../../../../Source/Plugin/CtrlrProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrProcessorEditorForLive_e59e666a.o: ../../../../Source/Plugin/CtrlrProcessorEditorForLive.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrProcessorEditorForLive.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrAbout_18fdd38c.o: ../../../../Source/UIComponents/CtrlrAbout.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrAbout.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrDocumentPanel_929b23dc.o: ../../../../Source/UIComponents/CtrlrApplicationWindow/CtrlrDocumentPanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrDocumentPanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrEditor_9def7b64.o: ../../../../Source/UIComponents/CtrlrApplicationWindow/CtrlrEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrEditorApplicationCommands_4671257e.o: ../../../../Source/UIComponents/CtrlrApplicationWindow/CtrlrEditorApplicationCommands.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrEditorApplicationCommands.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrEditorApplicationCommandsHandlers_606bd687.o: ../../../../Source/UIComponents/CtrlrApplicationWindow/CtrlrEditorApplicationCommandsHandlers.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrEditorApplicationCommandsHandlers.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrEditorApplicationCommandsMenus_7bb32260.o: ../../../../Source/UIComponents/CtrlrApplicationWindow/CtrlrEditorApplicationCommandsMenus.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrEditorApplicationCommandsMenus.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLookAndFeel_6692d7b1.o: ../../../../Source/UIComponents/CtrlrApplicationWindow/CtrlrLookAndFeel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLookAndFeel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrSettings_7ee9629a.o: ../../../../Source/UIComponents/CtrlrApplicationWindow/CtrlrSettings.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrSettings.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrButton_bea1a45d.o: ../../../../Source/UIComponents/CtrlrComponents/Buttons/CtrlrButton.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrButton.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrCustomButtonInternal_52f32d8b.o: ../../../../Source/UIComponents/CtrlrComponents/Buttons/CtrlrCustomButtonInternal.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrCustomButtonInternal.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrHyperlink_3eeb68e5.o: ../../../../Source/UIComponents/CtrlrComponents/Buttons/CtrlrHyperlink.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrHyperlink.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrImageButton_153336ec.o: ../../../../Source/UIComponents/CtrlrComponents/Buttons/CtrlrImageButton.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrImageButton.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrToggleButton_c9c63251.o: ../../../../Source/UIComponents/CtrlrComponents/Buttons/CtrlrToggleButton.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrToggleButton.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrCombo_5229199f.o: ../../../../Source/UIComponents/CtrlrComponents/CtrlrCombo.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrCombo.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrComponent_39b6278e.o: ../../../../Source/UIComponents/CtrlrComponents/CtrlrComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrComponentBubble_b187cb7a.o: ../../../../Source/UIComponents/CtrlrComponents/CtrlrComponentBubble.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrComponentBubble.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrComponentTypeManager_ddf3b5af.o: ../../../../Source/UIComponents/CtrlrComponents/CtrlrComponentTypeManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrComponentTypeManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrCustomComponent_a77769d.o: ../../../../Source/UIComponents/CtrlrComponents/CtrlrCustomComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrCustomComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrFilmStripPainter_73f10450.o: ../../../../Source/UIComponents/CtrlrComponents/CtrlrFilmStripPainter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrFilmStripPainter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrGroup_32821e65.o: ../../../../Source/UIComponents/CtrlrComponents/Groups/CtrlrGroup.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrGroup.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrTabsComponent_6616ae05.o: ../../../../Source/UIComponents/CtrlrComponents/Groups/CtrlrTabsComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrTabsComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrImage_366001b6.o: ../../../../Source/UIComponents/CtrlrComponents/Labels/CtrlrImage.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrImage.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLabel_467e62cf.o: ../../../../Source/UIComponents/CtrlrComponents/Labels/CtrlrLabel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLabel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLCDLabel_2ac15b76.o: ../../../../Source/UIComponents/CtrlrComponents/Labels/CtrlrLCDLabel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLCDLabel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrFixedImageSlider_75038da4.o: ../../../../Source/UIComponents/CtrlrComponents/Sliders/CtrlrFixedImageSlider.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrFixedImageSlider.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrFixedSlider_699aa063.o: ../../../../Source/UIComponents/CtrlrComponents/Sliders/CtrlrFixedSlider.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrFixedSlider.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrImageSlider_35266d8a.o: ../../../../Source/UIComponents/CtrlrComponents/Sliders/CtrlrImageSlider.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrImageSlider.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrSlider_22b8e8bd.o: ../../../../Source/UIComponents/CtrlrComponents/Sliders/CtrlrSlider.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrSlider.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrSliderInternal_b65dd51a.o: ../../../../Source/UIComponents/CtrlrComponents/Sliders/CtrlrSliderInternal.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrSliderInternal.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrFileListBox_99e71cd1.o: ../../../../Source/UIComponents/CtrlrComponents/Specials/CtrlrFileListBox.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrFileListBox.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrListBox_8b28dd6d.o: ../../../../Source/UIComponents/CtrlrComponents/Specials/CtrlrListBox.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrListBox.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMidiKeyboard_c15d02d2.o: ../../../../Source/UIComponents/CtrlrComponents/Specials/CtrlrMidiKeyboard.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMidiKeyboard.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrWaveform_4915e3e7.o: ../../../../Source/UIComponents/CtrlrComponents/Specials/CtrlrWaveform.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrWaveform.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrXYModulator_327a5f2e.o: ../../../../Source/UIComponents/CtrlrComponents/Specials/CtrlrXYModulator.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrXYModulator.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrXYSurface_2ece156c.o: ../../../../Source/UIComponents/CtrlrComponents/Specials/CtrlrXYSurface.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrXYSurface.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrArrow_1c791f44.o: ../../../../Source/UIComponents/CtrlrComponents/Statics/CtrlrArrow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrArrow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrComponentSelection_b1d830ba.o: ../../../../Source/UIComponents/CtrlrComponentSelection.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrComponentSelection.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLogViewer_61075cf5.o: ../../../../Source/UIComponents/CtrlrLogViewer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLogViewer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaConsole_70f9824e.o: ../../../../Source/UIComponents/CtrlrLua/CtrlrLuaConsole.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaConsole.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaCodeTokeniser_e22d95d3.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaCodeTokeniser.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaCodeTokeniser.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaMethodCodeEditor_94898995.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodCodeEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaMethodCodeEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaMethodCodeEditorSettings_5be9f058.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodCodeEditorSettings.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaMethodCodeEditorSettings.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaMethodEditArea_d6845c92.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditArea.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaMethodEditArea.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaMethodEditor_7c70c6c8.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaMethodEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaMethodEditorTabs_9f9d2de6.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodEditorTabs.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaMethodEditorTabs.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaMethodFind_e941a694.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrLuaMethodFind.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaMethodFind.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMethodEditorTabCloseButton_15d68b8b.o: ../../../../Source/UIComponents/CtrlrLua/MethodEditor/CtrlrMethodEditorTabCloseButton.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMethodEditorTabCloseButton.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMIDIBuffer_8a274ae5.o: ../../../../Source/UIComponents/CtrlrMIDI/CtrlrMIDIBuffer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMIDIBuffer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMIDIBufferEditor_370fe5f2.o: ../../../../Source/UIComponents/CtrlrMIDI/CtrlrMIDIBufferEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMIDIBufferEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMIDILibraryEditor_837e6cd.o: ../../../../Source/UIComponents/CtrlrMIDI/CtrlrMIDILibraryEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMIDILibraryEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMIDICalculator_ebca78a7.o: ../../../../Source/UIComponents/CtrlrMIDI/CtrlrMIDICalculator.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMIDICalculator.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMIDIMon_e8a545d1.o: ../../../../Source/UIComponents/CtrlrMIDI/CtrlrMIDIMon.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMIDIMon.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrViewport_7e02dc41.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrViewport.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrViewport.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelMIDIToolbar_2522e231.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelMIDIToolbar.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelMIDIToolbar.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelCanvas_248178b.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelCanvas.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelCanvas.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelCanvasHandlers_1eaa6b94.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelCanvasHandlers.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelCanvasHandlers.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelCanvasLayer_b7523850.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelCanvasLayer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelCanvasLayer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelCanvasLayers_36a8df6d.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelCanvasLayers.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelCanvasLayers.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelComponentProperties_8d398a07.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelComponentProperties.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelComponentProperties.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelEditor_4e4bb120.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelLayerList_64b0b886.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelLayerList.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelLayerList.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelLayerListItem_1a2585b9.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelLayerListItem.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelLayerListItem.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelModulatorList_515624.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelModulatorList.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelModulatorList.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelModulatorListTree_9f51df62.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelModulatorListTree.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelModulatorListTree.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelProperties_92abdae6.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelProperties.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelProperties.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelResourceEditor_6fc1b9ce.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelResourceEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelResourceEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelUtilities_a6075081.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelUtilities.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelUtilities.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelViewport_7f185c59.o: ../../../../Source/UIComponents/CtrlrPanel/CtrlrPanelViewport.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelViewport.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrModulatorListProperty_417f3f84.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrModulatorListProperty.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrModulatorListProperty.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrTimestampProperty_5aa7a6d.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrTimestampProperty.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrTimestampProperty.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrBooleanPropertyComponent_696ccd48.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrBooleanPropertyComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrBooleanPropertyComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrButtonPropertyComponent_b941f3b8.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrButtonPropertyComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrButtonPropertyComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrChoicePropertyComponent_3c8068a9.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrChoicePropertyComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrChoicePropertyComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrColourPropertyComponent_b131615e.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrColourPropertyComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrColourPropertyComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrExpressionProperty_98008635.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrExpressionProperty.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrExpressionProperty.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrFilePropertyComponent_9cf08eee.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrFilePropertyComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrFilePropertyComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrFontPropertyComponent_fb3309fb.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrFontPropertyComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrFontPropertyComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrLuaMethodProperty_c1c1bd0.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrLuaMethodProperty.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrLuaMethodProperty.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrMultiMidiPropertyComponent_2f5c07f6.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrMultiMidiPropertyComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrMultiMidiPropertyComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPropertyComponent_808f8d8a.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrPropertyComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPropertyComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrSliderPropertyComponent_3cfad569.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrSliderPropertyComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrSliderPropertyComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrSysExEditor_8120b80f.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrSysExEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrSysExEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrSysExFormulaEditor_4a7f649b.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrSysExFormulaEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrSysExFormulaEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrSysExPropertyComponent_54ec74d0.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrSysExPropertyComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrSysExPropertyComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrTextPropertyComponent_43b7a7dd.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrTextPropertyComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrTextPropertyComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrUnknownPropertyComponent_48ed5666.o: ../../../../Source/UIComponents/CtrlrPropertyEditors/CtrlrUnknownPropertyComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrUnknownPropertyComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrTextEditor_ee695525.o: ../../../../Source/UIComponents/CtrlrTextEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrTextEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrValueMap_c807d756.o: ../../../../Source/UIComponents/CtrlrValueMap.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrValueMap.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrValueTreeEditor_71d292fb.o: ../../../../Source/UIComponents/CtrlrValueTreeEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrValueTreeEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrChildWindow_ca5e1fdd.o: ../../../../Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrChildWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrChildWindowContainer_92d8566e.o: ../../../../Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindowContainer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrChildWindowContainer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrChildWindowContent_23e81066.o: ../../../../Source/UIComponents/CtrlrWindowManagers/CtrlrChildWindowContent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrChildWindowContent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrDialogWindow_fd7eda91.o: ../../../../Source/UIComponents/CtrlrWindowManagers/CtrlrDialogWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrDialogWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrManagerWindowManager_237c1a29.o: ../../../../Source/UIComponents/CtrlrWindowManagers/CtrlrManagerWindowManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrManagerWindowManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CtrlrPanelWindowManager_c51c89b2.o: ../../../../Source/UIComponents/CtrlrWindowManagers/CtrlrPanelWindowManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CtrlrPanelWindowManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_f3ae2c2f.o: ../../../Standalone/JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_49fc64dc.o: ../../../../Juce/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_4221f29a.o: ../../../../Juce/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_70a33c3a.o: ../../../../Juce/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_bd1ca294.o: ../../../../Juce/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_utils_fd7e75a.o: ../../../../Juce/modules/juce_audio_utils/juce_audio_utils.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_utils.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_62c225be.o: ../../../../Juce/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_2dd916fa.o: ../../../../Juce/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_632f8332.o: ../../../../Juce/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_3c1b7996.o: ../../../../Juce/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_657c2612.o: ../../../../Juce/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_c674b41a.o: ../../../../Juce/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
