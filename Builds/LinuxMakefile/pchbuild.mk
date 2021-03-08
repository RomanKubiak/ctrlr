
CFLAGS   = -g -pg    -fno-omit-frame-pointer -fno-common
CXXFLAGS = $(CFLAGS)
JUCE_LDFLAGS= 


include Makefile

$(OBJECTS_STANDALONE_PLUGIN) $(RESOURCES) $(OBJECTS_SHARED_CODE): ../../Source/Core/stdafx.h.gch ../../Source/Core/stdafx_luabind.h.gch


$(JUCE_OUTDIR)/stdafx.h.gch: ../../Source/Core/stdafx.h
	@mkdir -p $(JUCE_OUTDIR)
	@echo "CTRLR[linux]: Compile PCH"
	@echo "stadfx.h"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) \
		-MF "$(JUCE_OUTDIR)/stdafx.h.d" \
		-o "$(JUCE_OUTDIR)/stdafx.h.gch" -c "../../Source/Core/stdafx.h"

../../Source/Core/stdafx.h.gch: clean.stamp $(JUCE_OUTDIR)/stdafx.h.gch
	$(V_AT)if ! cmp "$(JUCE_OUTDIR)/stdafx.h.gch" "../../Source/Core/stdafx.h.gch"; \
	then  \
		cp  "$(JUCE_OUTDIR)/stdafx.h.gch" "../../Source/Core/stdafx.h.gch" ; \
	fi

$(JUCE_OUTDIR)/stdafx_luabind.h.gch: ../../Source/Core/stdafx_luabind.h
	@mkdir -p $(JUCE_OUTDIR)
	@echo "CTRLR[linux]: Compile PCH"
	@echo "stdafx_luabind.h"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) \
		-MF "$(JUCE_OUTDIR)/stdafx_luabind.h.d" \
		-o "$(JUCE_OUTDIR)/stdafx_luabind.h.gch" -c "../../Source/Core/stdafx_luabind.h"

../../Source/Core/stdafx_luabind.h.gch: clean.stamp $(JUCE_OUTDIR)/stdafx_luabind.h.gch
	$(V_AT)if ! cmp "$(JUCE_OUTDIR)/stdafx_luabind.h.gch" "../../Source/Core/stdafx_luabind.h.gch" ; \
	then  \
		cp  "$(JUCE_OUTDIR)/stdafx_luabind.h.gch" "../../Source/Core/stdafx_luabind.h.gch" ; \
	fi

clean-$(CONFIG).stamp:
	for d in Release Debug ; do \
	if test \( "clean-$$d.stamp" -nt "$@" \) -o \( ! -f "clean-$$d.stamp" \) ; then touch "$@" ; fi ; \
		echo "cleaning because of clean-$$d.stamp -nt $@ \) -o \( ! -f clean-$$d.stamp \)" ; \
		$(MAKE) clean ; \
	done

clean.stamp: Makefile clean-$(CONFIG).stamp
	touch clean.stamp

-include $(JUCE_OUTDIR)/stdafx_luabind.h.d
-include $(JUCE_OUTDIR)/stdafx.h.d

test: $(JUCE_OUTDIR)/test

#TEST_LDFLAGS =  $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE)
unloaded_objects = \
	build/intermediate/Debug/class_51e55959.o \
	build/intermediate/Debug/class_info_e81f919e.o \
	build/intermediate/Debug/class_registry_cf7ee82d.o \
	build/intermediate/Debug/class_rep_ab5f3037.o \
	build/intermediate/Debug/create_class_d856fdfe.o \
	build/intermediate/Debug/error_661db9e9.o \
	build/intermediate/Debug/exception_handler_385a9c3b.o \
	build/intermediate/Debug/function_745dd1e1.o \
	build/intermediate/Debug/function_introspection_294a989d.o \
	build/intermediate/Debug/inheritance_b8b282ab.o \
	build/intermediate/Debug/link_compatibility_a784cd74.o \
	build/intermediate/Debug/lua51compat_d51520f7.o \
	build/intermediate/Debug/object_rep_f6504226.o \
	build/intermediate/Debug/open_479cc553.o \
	build/intermediate/Debug/operator_7af940ad.o \
	build/intermediate/Debug/pcall_261fd7af.o \
	build/intermediate/Debug/scope_cdf52035.o \
	build/intermediate/Debug/set_package_preload_b16d8e94.o \
	build/intermediate/Debug/shared_ptr_converter_474758be.o \
	build/intermediate/Debug/stack_content_by_name_d5b108d7.o \
	build/intermediate/Debug/weak_ref_28658f55.o \
	build/intermediate/Debug/wrapper_base_8bfc9886.o \
	build/intermediate/Debug/compat_9b146423.o \
	build/intermediate/Debug/core_27542800.o \
	build/intermediate/Debug/darwin_usb_8122958d.o \
	build/intermediate/Debug/descriptor_ef0446d0.o \
	build/intermediate/Debug/enums_2b775c5b.o \
	build/intermediate/Debug/hotplug_1fb630e4.o \
	build/intermediate/Debug/io_997ddac7.o \
	build/intermediate/Debug/linux_udev_8d6fd84c.o \
	build/intermediate/Debug/linux_usbfs_39f3530f.o \
	build/intermediate/Debug/poll_posix_5f7c8864.o \
	build/intermediate/Debug/poll_windows_ffaf3564.o \
	build/intermediate/Debug/strerror_2ffe76d8.o \
	build/intermediate/Debug/structs_24498007.o \
	build/intermediate/Debug/sync_432cc3fc.o \
	build/intermediate/Debug/threads_posix_c92ae076.o \
	build/intermediate/Debug/threads_windows_b727d0f6.o \
	build/intermediate/Debug/usb_96e926cd.o \
	build/intermediate/Debug/windows_usb_3c8c6a11.o \
	build/intermediate/Debug/lua_260ca39c.o \
	build/intermediate/Debug/keys_f237af18.o \
	build/intermediate/Debug/libr-bfd_fc7a9004.o \
	build/intermediate/Debug/libr_d73fc571.o \
	build/intermediate/Debug/CtrlrManager_f2f12d08.o \
	build/intermediate/Debug/CtrlrManagerInstance_44eac03d.o \
	build/intermediate/Debug/CtrlrManagerVst_cf4a0139.o \
	build/intermediate/Debug/CtrlrModulator_3ba73888.o \
	build/intermediate/Debug/CtrlrModulatorProcessor_9c865db4.o \
	build/intermediate/Debug/CtrlrEvaluationScopes_91b73ea1.o \
	build/intermediate/Debug/CtrlrPanel_4772c8e8.o \
	build/intermediate/Debug/CtrlrPanelFileOperations_9097aa50.o \
	build/intermediate/Debug/CtrlrPanelMIDIInputThread_f05ccf35.o \
	build/intermediate/Debug/CtrlrPanelMIDISnapshot_ac52ded.o \
	build/intermediate/Debug/CtrlrPanelProcessor_90473954.o \
	build/intermediate/Debug/CtrlrPanelResource_c8914716.o \
	build/intermediate/Debug/CtrlrPanelResourceManager_ded72841.o \
	build/intermediate/Debug/CtrlrPanelSchemeMigration_35bff32b.o \
	build/intermediate/Debug/CtrlrPanelUndoManager_544c802b.o \
	build/intermediate/Debug/CtrlrStandaloneApplication_2835f456.o \
	build/intermediate/Debug/CtrlrStandaloneWindow_42dbf3b4.o \
	build/intermediate/Debug/CtrlrFontManager_edb07ae8.o \
	build/intermediate/Debug/CtrlrIDManager_40d647fc.o \
	build/intermediate/Debug/CtrlrLog_cd89ebce.o \
	build/intermediate/Debug/CtrlrProperties_eb107cf3.o \
	build/intermediate/Debug/CtrlrSysexProcessor_bc5102f2.o \
	build/intermediate/Debug/CtrlrSysexProcessorOwned_1864a89d.o \
	build/intermediate/Debug/CtrlrSysexToken_f2c07259.o \
	build/intermediate/Debug/CtrlrUtilities_e2afb8d4.o \
	build/intermediate/Debug/CtrlrUtilitiesGUI_cf4b83d1.o \
	build/intermediate/Debug/stdafx_a1c77ec1.o \
	build/intermediate/Debug/stdafx_luabind_6366fab7.o \
	build/intermediate/Debug/CtrlrLuaBigInteger_5ff71375.o \
	build/intermediate/Debug/CtrlrLuaComponentAnimator_bfec1d7.o \
	build/intermediate/Debug/CtrlrLuaFile_1a330f53.o \
	build/intermediate/Debug/CtrlrLuaMemoryBlock_85081d5f.o \
	build/intermediate/Debug/CtrlrLuaRectangle_baaae0c2.o \
	build/intermediate/Debug/LAudio_273674e0.o \
	build/intermediate/Debug/LComponents_6368b696.o \
	build/intermediate/Debug/LCore_60dceadf.o \
	build/intermediate/Debug/LGraphics_349e924b.o \
	build/intermediate/Debug/LJuce_5bd1d72d.o \
	build/intermediate/Debug/LMemory_dc39a081.o \
	build/intermediate/Debug/CtrlrLuaMethod_23ff560f.o \
	build/intermediate/Debug/CtrlrLuaMethodManager_c621ff28.o \
	build/intermediate/Debug/CtrlrLuaMethodManagerCalls_d460a557.o \
	build/intermediate/Debug/CtrlrLuaAudioConverter_d897847b.o \
	build/intermediate/Debug/CtrlrLuaDebugger_36763bb2.o \
	build/intermediate/Debug/CtrlrLuaManager_89c5eb06.o \
	build/intermediate/Debug/CtrlrLuaObject_85f4d2d0.o \
	build/intermediate/Debug/CtrlrLuaObjectWrapper_dab692d.o \
	build/intermediate/Debug/CtrlrLuaPanelCanvasLayer_a584fbc6.o \
	build/intermediate/Debug/CtrlrLuaUtils_3835430a.o \
	build/intermediate/Debug/CtrlrMIDIDevice_275facd9.o \
	build/intermediate/Debug/CtrlrMIDIDeviceManager_d382511e.o \
	build/intermediate/Debug/CtrlrMIDIFilter_9c3df8fb.o \
	build/intermediate/Debug/CtrlrMidiInputComparator_b50d6fc7.o \
	build/intermediate/Debug/CtrlrMidiInputComparatorMulti_a3cb717c.o \
	build/intermediate/Debug/CtrlrMidiInputComparatorSingle_c444d6af.o \
	build/intermediate/Debug/CtrlrMidiMessage_f1795a0e.o \
	build/intermediate/Debug/CtrlrMidiMessageEx_a0d44f21.o \
	build/intermediate/Debug/CtrlrOwnedMidiMessage_b2a92f23.o \
	build/intermediate/Debug/CtrlrLinux_981545c6.o \
	build/intermediate/Debug/CtrlrMac_67f057e1.o \
	build/intermediate/Debug/CtrlrNative_a50436cf.o \
	build/intermediate/Debug/CtrlrWindows_8f7a495.o \
	build/intermediate/Debug/CtrlrProcessor_a9d8df48.o \
	build/intermediate/Debug/CtrlrProcessorEditorForLive_da85400a.o \
	build/intermediate/Debug/CtrlrDocumentPanel_a034ed7c.o \
	build/intermediate/Debug/CtrlrEditor_794f45c4.o \
	build/intermediate/Debug/CtrlrEditorApplicationCommands_a8897f1e.o \
	build/intermediate/Debug/CtrlrEditorApplicationCommandsHandlers_9fe09027.o \
	build/intermediate/Debug/CtrlrEditorApplicationCommandsMenus_98f1ccc0.o \
	build/intermediate/Debug/CtrlrSettings_18014fa.o \
	build/intermediate/Debug/CtrlrButton_4f3b25fd.o \
	build/intermediate/Debug/CtrlrCustomButtonInternal_1d79572b.o \
	build/intermediate/Debug/CtrlrHyperlink_769f0345.o \
	build/intermediate/Debug/CtrlrImageButton_2e69b94c.o \
	build/intermediate/Debug/CtrlrToggleButton_d75ffbf1.o \
	build/intermediate/Debug/CtrlrGroup_20cf8805.o \
	build/intermediate/Debug/CtrlrTabsComponent_73b077a5.o \
	build/intermediate/Debug/CtrlrImage_24ad6b56.o \
	build/intermediate/Debug/CtrlrLabel_34cbcc6f.o \
	build/intermediate/Debug/CtrlrLCDLabel_ad580dd6.o \
	build/intermediate/Debug/CtrlrFixedImageSlider_275f8744.o \
	build/intermediate/Debug/CtrlrFixedSlider_82d122c3.o \
	build/intermediate/Debug/CtrlrImageSlider_4e5cefea.o \
	build/intermediate/Debug/CtrlrSlider_b3526a5d.o \
	build/intermediate/Debug/CtrlrSliderInternal_c4abb6ba.o \
	build/intermediate/Debug/CtrlrFileListBox_a780e671.o \
	build/intermediate/Debug/CtrlrListBox_5b68770d.o \
	build/intermediate/Debug/CtrlrMidiKeyboard_66fc6d32.o \
	build/intermediate/Debug/CtrlrProgressBar_be7eb366.o \
	build/intermediate/Debug/CtrlrWaveform_80c97e47.o \
	build/intermediate/Debug/CtrlrXYModulator_401428ce.o \
	build/intermediate/Debug/CtrlrXYSurface_ed8dc70c.o \
	build/intermediate/Debug/CtrlrArrow_f7d8e9a4.o \
	build/intermediate/Debug/CtrlrCombo_d9a943ff.o \
	build/intermediate/Debug/CtrlrComponent_565a21ee.o \
	build/intermediate/Debug/CtrlrComponentLuaRegistration_c369de8d.o \
	build/intermediate/Debug/CtrlrComponentTypeManager_eb8d7f4f.o \
	build/intermediate/Debug/CtrlrCustomComponent_8d0e28fd.o \
	build/intermediate/Debug/CtrlrFilmStripPainter_44309df0.o \
	build/intermediate/Debug/CtrlrLuaCodeTokeniser_f07b7773.o \
	build/intermediate/Debug/CtrlrLuaMethodCodeEditor_2dacc3f5.o \
	build/intermediate/Debug/CtrlrLuaMethodCodeEditorSettings_3cdccab8.o \
	build/intermediate/Debug/CtrlrLuaMethodDebuggerControls_6e517932.o \
	build/intermediate/Debug/CtrlrLuaMethodDebuggerInfo_e4ac56aa.o \
	build/intermediate/Debug/CtrlrLuaMethodDebuggerPrompt_18948aa0.o \
	build/intermediate/Debug/CtrlrLuaMethodDebuggerStackTrace_5f5a64d9.o \
	build/intermediate/Debug/CtrlrLuaMethodDebuggerVars_901d2128.o \
	build/intermediate/Debug/CtrlrLuaMethodEditArea_91f2aef2.o \
	build/intermediate/Debug/CtrlrLuaMethodEditor_22103128.o \
	build/intermediate/Debug/CtrlrLuaMethodEditorConsole_27c91699.o \
	build/intermediate/Debug/CtrlrLuaMethodEditorTabs_38c06846.o \
	build/intermediate/Debug/CtrlrLuaMethodFind_27828f4.o \
	build/intermediate/Debug/CtrlrMethodEditorTabCloseButton_77eee52b.o \
	build/intermediate/Debug/CtrlrLuaConsole_ed40c4ae.o \
	build/intermediate/Debug/CtrlrMIDIBuffer_96c85485.o \
	build/intermediate/Debug/CtrlrMIDICalculator_478db247.o \
	build/intermediate/Debug/CtrlrMIDIMon_9099a031.o \
	build/intermediate/Debug/CtrlrMIDISettingsDevices_266f355f.o \
	build/intermediate/Debug/CtrlrMIDISettingsDialog_46327210.o \
	build/intermediate/Debug/CtrlrMIDISettingsRouting_44fccc8.o \
	build/intermediate/Debug/CtrlrPanelCanvas_6acd392b.o \
	build/intermediate/Debug/CtrlrPanelCanvasHandlers_af43ed34.o \
	build/intermediate/Debug/CtrlrPanelCanvasLayer_3ae11ab0.o \
	build/intermediate/Debug/CtrlrPanelCanvasLayers_24f6490d.o \
	build/intermediate/Debug/CtrlrPanelComponentProperties_a6700c67.o \
	build/intermediate/Debug/CtrlrPanelEditor_b6d0d2c0.o \
	build/intermediate/Debug/CtrlrPanelFindProperty_6784c901.o \
	build/intermediate/Debug/CtrlrPanelLayerList_8154b2e6.o \
	build/intermediate/Debug/CtrlrPanelLayerListItem_f5855019.o \
	build/intermediate/Debug/CtrlrPanelModulatorList_dbb12084.o \
	build/intermediate/Debug/CtrlrPanelModulatorListTree_d70579c2.o \
	build/intermediate/Debug/CtrlrPanelProperties_a872c86.o \
	build/intermediate/Debug/CtrlrPanelResourceEditor_5b3b6e.o \
	build/intermediate/Debug/CtrlrPanelUtilities_c2ab4ae1.o \
	build/intermediate/Debug/CtrlrPanelViewport_dadb95f9.o \
	build/intermediate/Debug/CtrlrViewport_fa4a1ea1.o \
	build/intermediate/Debug/CtrlrPropertyComponent_8edd6f2a.o \
	build/intermediate/Debug/CtrlrChildWindow_4cf4d23d.o \
	build/intermediate/Debug/CtrlrChildWindowContainer_4534500e.o \
	build/intermediate/Debug/CtrlrChildWindowContent_3235f206.o \
	build/intermediate/Debug/CtrlrDialogWindow_cdbe7431.o \
	build/intermediate/Debug/CtrlrManagerWindowManager_d5d813c9.o \
	build/intermediate/Debug/CtrlrPanelWindowManager_d36a6b52.o \
	build/intermediate/Debug/CtrlrAbout_dbdebdec.o \
	build/intermediate/Debug/CtrlrComponentSelection_86f225a.o \
	build/intermediate/Debug/CtrlrLogViewer_9aac1755.o \
	build/intermediate/Debug/CtrlrTextEditor_e95be6c5.o \
	build/intermediate/Debug/CtrlrValueMap_3b250f6.o \
	build/intermediate/Debug/CtrlrValueTreeEditor_fdda055b.o \
	build/intermediate/Debug/BinaryData_ce4232d4.o \
	build/intermediate/Debug/include_juce_audio_basics_8a4e984a.o \
	build/intermediate/Debug/include_juce_audio_devices_63111d02.o \
	build/intermediate/Debug/include_juce_audio_formats_15f82001.o \
	build/intermediate/Debug/include_juce_audio_plugin_client_utils_e32edaee.o \
	build/intermediate/Debug/include_juce_audio_processors_10c03666.o \
	build/intermediate/Debug/include_juce_audio_utils_9f9fb2d6.o 
TEST_LDFLAGS = \
	build/intermediate/Debug/include_juce_core_f26d17db.o \
	-Lbuild \
	-lasound \
	-lfreetype \
	-fvisibility=hidden \
	-lrt \
	-ldl \
	-lpthread \
	-lcurl \
#\
	-ltsan  \
	-ludev \
	-l:libbfd.a \
	-liberty \
	-lz \
	-lX11 

orig_TEST_LDFLAGS = \
	build/intermediate/Debug/include_juce_core_f26d17db.o \
	-ltsan  \
	-Lbuild \
	-lasound \
	-lfreetype \
	-lcurl \
	-fvisibility=hidden \
	-lrt \
	-ldl \
	-lpthread \
	-ludev \
	-l:libbfd.a \
	-liberty \
	-lz \
	-lX11 

others = \
	build/intermediate/Debug/include_juce_data_structures_7471b1e3.o \
	build/intermediate/Debug/include_juce_events_fd7d695.o \
	build/intermediate/Debug/include_juce_graphics_f817e147.o \
	build/intermediate/Debug/include_juce_gui_basics_e3f79785.o \
	build/intermediate/Debug/include_juce_gui_extra_6dee1c1a.o \
	nix

# 175 190 198 203



$(JUCE_OUTDIR)/test: test.cpp
	@echo '$(OBJECTS_SHARED_CODE)' |sed 's/^/\t/ ; s/ / \\\n\t/g'| tee test.shardeobjects
	@echo 'TEST_LDFLAGS=$(TEST_LDFLAGS)'
	@echo 'JUCE_LDFLGAS=$(JUCE_LDFLAGS) $(JUCE_LDFLAGS_STANDALONE_PLUGIN) $(RESOURCES) $(TARGET_ARCH)'
	@mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) \
		-o $(JUCE_OUTDIR)/test.o -c test.cpp
	$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/test $(JUCE_OUTDIR)/test.o $(TEST_LDFLAGS) $(RESOURCES) $(TARGET_ARCH)

printlinkcommand:
	echo "$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/$(JUCE_TARGET_STANDALONE_PLUGIN) $(OBJECTS_STANDALONE_PLUGIN) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_LDFLAGS) $(JUCE_LDFLAGS_STANDALONE_PLUGIN) $(RESOURCES) $(TARGET_ARCH)"

