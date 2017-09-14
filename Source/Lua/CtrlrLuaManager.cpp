#include "stdafx_luabind.h"
#include "CtrlrLuaManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrLuaMultiTimer.h"
#include "CtrlrLuaObject.h"
#include "CtrlrProperties.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanelCanvasLayer.h"
#include "CtrlrLuaObjectWrapper.h"
#include "CtrlrMidiInputComparator.h"
#include "CtrlrPanel/CtrlrPanelResourceManager.h"
#include "MIDI/CtrlrMidiInputComparator.h"
#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrComponents/Specials/CtrlrWaveform.h"
#include "CtrlrComponents/Specials/CtrlrListBox.h"
#include "CtrlrComponents/Specials/CtrlrFileListBox.h"
#include "CtrlrComponents/CtrlrCustomComponent.h"
#include "CtrlrComponents/CtrlrCombo.h"
#include "CtrlrComponents/Labels/CtrlrLabel.h"
#include "CtrlrComponents/Labels/CtrlrLCDLabel.h"
#include "CtrlrComponents/Buttons/CtrlrToggleButton.h"
#include "CtrlrComponents/Buttons/CtrlrButton.h"
#include "CtrlrComponents/Buttons/CtrlrImageButton.h"
#include "CtrlrComponents/Groups/CtrlrGroup.h"
#include "CtrlrComponents/Sliders/CtrlrFixedImageSlider.h"
#include "CtrlrComponents/Sliders/CtrlrFixedSlider.h"
#include "CtrlrComponents/Sliders/CtrlrImageSlider.h"
#include "CtrlrComponents/Sliders/CtrlrSlider.h"
#include "CtrlrValueMap.h"
#include "JuceClasses/LAudioFormat.h"
#include "JuceClasses/LGlobalFunctions.h"
#include "CtrlrLuaUtils.h"
#include "CtrlrLuaMultiTimer.h"
#include "CtrlrLuaAudioConverter.h"
#include "CtrlrLuaDebugger.h"

// Deprecated classes
#include "Deprecated/CtrlrLuaBigInteger.h"
#include "Deprecated/CtrlrLuaFile.h"
#include "Deprecated/CtrlrLuaMemoryBlock.h"
#include "Deprecated/CtrlrLuaRectangle.h"
#include "Deprecated/CtrlrLuaComponentAnimator.h"

#include "luabind/class_info.hpp"

CtrlrLuaManager::CtrlrLuaManager(CtrlrPanel &_owner)
	:	owner(_owner),
		luaManagerTree(Ids::luaManager),
		luaAudioFormatManager(nullptr),
		ctrlrLuaDebugger(nullptr),
		utils(nullptr),
		audioConverter(nullptr),
		luaStateAudio(nullptr),
		luaState(nullptr)
{
	methodManager			= new CtrlrLuaMethodManager(*this);
	
	if ((bool)owner.getCtrlrManagerOwner().getProperty(Ids::ctrlrLuaDisabled))
	{
		_INF("CtrlrLuaManager::ctor, lua is disabled");
		luaManagerTree.addChild(methodManager->getManagerTree(), -1, 0);
		return;
	}

	createLuaState();
	createLuaStateAudio();

	luaManagerTree.addListener (this);

	multiTimer				= new CtrlrLuaMultiTimer();
	luaAudioFormatManager	= new LAudioFormatManager();
	audioConverter			= new CtrlrLuaAudioConverter();
	utils					= new CtrlrLuaUtils();

	LGlobalFunctions::wrapForLua(luaState);
	LGlobalFunctions::wrapForLua(luaStateAudio);

	wrapCore(luaState);
	wrapJuceClasses(luaState);

	wrapCore(luaStateAudio);
	wrapJuceClasses(luaStateAudio);

	wrapCtrlrClasses(luaState);
	assignDefaultObjects(luaState);

    ctrlrLuaDebugger        = new CtrlrLuaDebugger (*this);

	luaManagerTree.addChild (methodManager->getManagerTree(), -1, 0);
}

CtrlrLuaManager::~CtrlrLuaManager()
{
	deleteAndZero (methodManager);

	if (luaState)
	{
		deleteAndZero (utils);
		deleteAndZero (audioConverter);
		luaManagerTree.removeListener (this);
		deleteAndZero (multiTimer);
		deleteAndZero (luaAudioFormatManager);
		lua_close(luaState);
		lua_close(luaStateAudio);
		deleteAndZero (ctrlrLuaDebugger);
	}
}

void CtrlrLuaManager::createLuaState()
{
	luaState 		= luaL_newstate();
	luaL_openlibs(luaState);
	
    lua_pushcfunction(luaState, luaopen_base);
    lua_pushliteral(luaState, "base");
    lua_call(luaState, 1, 0);

    lua_pushcfunction(luaState, luaopen_table);
    lua_pushliteral(luaState, "table");
    lua_call(luaState, 1, 0);

    lua_pushcfunction(luaState, luaopen_string);
    lua_pushliteral(luaState, "string");
    lua_call(luaState, 1, 0);

    lua_pushcfunction(luaState, luaopen_math);
    lua_pushliteral(luaState, "math");
    lua_call(luaState, 1, 0);

    lua_pushcfunction(luaState, luaopen_io);
    lua_pushliteral(luaState, "io");
    lua_call(luaState, 1, 0);

    lua_pushcfunction(luaState, luaopen_debug);
    lua_pushliteral(luaState, "debug");
    lua_call(luaState, 1, 0);

    lua_pushcfunction(luaState, luaopen_package);
    lua_pushliteral(luaState, "package");
    lua_call(luaState, 1, 0);

    lua_pushcfunction(luaState, luaopen_os);
    lua_pushliteral(luaState, "os");
    lua_call(luaState, 1, 0);

    lua_pushcfunction(luaState, luaopen_bit);
    lua_pushliteral(luaState, "bit");
    lua_call(luaState, 1, 0);
	
    lua_pushcfunction(luaState, luaopen_usb);
    lua_pushliteral(luaState, "usb");
    lua_call(luaState, 1, 0);

	using namespace luabind;
    open(luaState);

	luabind::bind_class_info(luaState);

	set_pcall_callback (add_file_and_line);
}

void CtrlrLuaManager::createLuaStateAudio()
{
	luaStateAudio 		= luaL_newstate();

    lua_pushcfunction(luaStateAudio, luaopen_base);
    lua_pushliteral(luaStateAudio, "base");
    lua_call(luaStateAudio, 1, 0);

    lua_pushcfunction(luaStateAudio, luaopen_table);
    lua_pushliteral(luaStateAudio, "table");
    lua_call(luaStateAudio, 1, 0);

    lua_pushcfunction(luaStateAudio, luaopen_string);
    lua_pushliteral(luaStateAudio, "string");
    lua_call(luaStateAudio, 1, 0);

    lua_pushcfunction(luaStateAudio, luaopen_math);
    lua_pushliteral(luaStateAudio, "math");
    lua_call(luaStateAudio, 1, 0);

    lua_pushcfunction(luaStateAudio, luaopen_debug);
    lua_pushliteral(luaStateAudio, "debug");
    lua_call(luaStateAudio, 1, 0);

    lua_pushcfunction(luaStateAudio, luaopen_package);
    lua_pushliteral(luaStateAudio, "package");
    lua_call(luaStateAudio, 1, 0);

	lua_pushcfunction(luaState, luaopen_bit);
	lua_pushliteral(luaState, "bit");
	lua_call(luaState, 1, 0);

    using namespace luabind;
    open(luaStateAudio);
	luabind::bind_class_info(luaStateAudio);

	set_pcall_callback (add_file_and_line);
}

CtrlrLuaMethodManager &CtrlrLuaManager::getMethodManager()
{
	return (*methodManager);
}

void CtrlrLuaManager::wrapUtilities(lua_State* L)
{
	if (methodManager)
	{
		methodManager->wrapUtilities();
	}
}

void CtrlrLuaManager::wrapCore (lua_State* L)
{
	using namespace luabind;

	CtrlrLuaObject::wrapForLua (L);

	module(L)
    [
		class_<CtrlrLuaObjectWrapper>("CtrlrLuaObjectWrapper")
			.def(constructor<luabind::object const&>())
			.def(constructor<>())
			.def("getObject", &CtrlrLuaObjectWrapper::getObject)
    ];
}

void CtrlrLuaManager::wrapCtrlrClasses(lua_State* L)
{
	CtrlrValueMap::wrapForLua (L);
	CtrlrModulator::wrapForLua (L);
	CtrlrPanel::wrapForLua (L);
	CtrlrMidiMessage::wrapForLua (L);
	CtrlrLuaUtils::wrapForLua (L);
	CtrlrPanelEditor::wrapForLua (L);
	CtrlrPanelCanvas::wrapForLua (L);
	CtrlrLuaMultiTimer::wrapForLua (L);
	CtrlrPanelResourceManager::wrapForLua (L);
	CtrlrPanelCanvasLayer::wrapForLua (L);
	CtrlrLuaAudioConverter::wrapForLua (L);
	CtrlrLuaBigInteger::wrapForLua (L);
	CtrlrLuaMemoryBlock::wrapForLua (L);
	CtrlrLuaRectangle::wrapForLua (L);
	CtrlrLuaComponentAnimator::wrapForLua (L);
	CtrlrComponent::wrapForLua (L);
	CtrlrMIDIDevice::wrapForLua (L);
	CtrlrMIDIDeviceManager::wrapForLua (L);

	CtrlrCustomComponent::wrapForLua (L);
	CtrlrToggleButton::wrapForLua (L);
	CtrlrButton::wrapForLua (L);
	CtrlrImageButton::wrapForLua (L);
	CtrlrLabel::wrapForLua (L);
	CtrlrLCDLabel::wrapForLua (L);
	CtrlrWaveform::wrapForLua (L);
	CtrlrCombo::wrapForLua (L);
	CtrlrListBox::wrapForLua (L);
	CtrlrFileListBox::wrapForLua (L);
	CtrlrFixedImageSlider::wrapForLua (L);
	CtrlrImageSlider::wrapForLua (L);
	CtrlrFixedSlider::wrapForLua (L);
	CtrlrSlider::wrapForLua (L);
	CtrlrGroup::wrapForLua (L);
}

void CtrlrLuaManager::assignDefaultObjects(lua_State* L)
{
	luabind::globals(L)["panel"]					= &owner;
	luabind::globals(L)["utils"]					= utils;
	luabind::globals(L)["timer"]					= multiTimer;
	luabind::globals(L)["afm"]						= luaAudioFormatManager;
	luabind::globals(L)["atc"]						= &owner.getCtrlrManagerOwner().getAudioThumbnailCache();
	luabind::globals(L)["converter"]				= audioConverter;
	luabind::globals(L)["resources"]				= &owner.getResourceManager();
	luabind::globals(L)["native"]                   = CtrlrNative::getNativeObject(owner.getCtrlrManagerOwner());
	luabind::globals(L)["devices"]                  = &owner.getCtrlrManagerOwner().getCtrlrMIDIDeviceManager();
}

void CtrlrLuaManager::restoreState (const ValueTree &savedState)
{
	if (savedState.isValid())
	{
		if (savedState.getChildWithName(Ids::luaManagerMethods).isValid())
		{
			methodManager->restoreState (savedState.getChildWithName(Ids::luaManagerMethods));
		}
	}

	methodManager->wrapUtilities();
}

void CtrlrLuaManager::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
}

int func_panic(lua_State *L)
{
	String err;
	err << lua_tostring(L, -1);
	lua_getglobal(L, "ERROR");
	return(0);
}

bool CtrlrLuaManager::runCode (const String &code, const String name)
{
	if (luaState && !isLuaDisabled())
	{
		if (luaL_loadbuffer(luaState, code.toUTF8(), std::strlen(code.toUTF8()), name.isEmpty() ? "_runtime" : name.toUTF8())
			|| lua_pcall(luaState, 0, 0, 0))
		{
			const char* a = lua_tostring(luaState, -1);
			_LERR("ERROR: " + String(a));
			lastError = "ERROR: " + String(a);
			lua_pop(luaState, 1);
			return (false);
		}

		return (true);
	}
	else
	{
		return (false);
	}
}

void CtrlrLuaManager::log(const String &message)
{
	if (CtrlrLog::ctrlrLog != nullptr)
		CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::Info);
}

CtrlrLuaDebugger &CtrlrLuaManager::getDebugger()
{
    return (*ctrlrLuaDebugger);
}

const bool CtrlrLuaManager::isLuaDisabled()
{
	return ((bool)owner.getCtrlrManagerOwner().getProperty(Ids::ctrlrLuaDisabled));
}