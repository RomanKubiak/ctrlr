#include "stdafx.h"
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
#include "CtrlrLuaLookAndFeel.h"
#include "CtrlrPanel/CtrlrPanelResourceManager.h"
#include "MIDI/CtrlrMidiInputComparator.h"
#include "MIDI/CtrlrMIDILibrary/CtrlrMIDILibrary.h"
#include "MIDI/CtrlrMIDITransaction.h"
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

#include "CtrlrComponents/Sliders/CtrlrFixedImageSlider.h"
#include "CtrlrComponents/Sliders/CtrlrFixedSlider.h"
#include "CtrlrComponents/Sliders/CtrlrImageSlider.h"
#include "CtrlrComponents/Sliders/CtrlrSlider.h"

#include "JuceClasses/LAudioFormat.h"

// Deprecated classes
#include "Deprecated/CtrlrLuaBigInteger.h"
#include "Deprecated/CtrlrLuaFile.h"
#include "Deprecated/CtrlrLuaMemoryBlock.h"
#include "Deprecated/CtrlrLuaRectangle.h"
#include "Deprecated/CtrlrLuaComponentAnimator.h"

CtrlrLuaManager::CtrlrLuaManager(CtrlrPanel &_owner)
	:	owner(_owner),
		luaManagerTree(Ids::luaManager),
		luaAudioFormatManager(nullptr)
{
	if ((bool)owner.getCtrlrManager().getProperty (Ids::ctrlrLuaDisabled))
	{
		_INF("CtrlrLuaManager::ctor, lua is disabled");
	}

	luaState = lua_open();
	luaopen_base(luaState);
    luaopen_table(luaState);
    luaopen_string(luaState);
    luaopen_math(luaState);

	using namespace luabind;
    open(luaState);
	luabind::bind_class_info(luaState);
	set_pcall_callback (add_file_and_line);

	luaManagerTree.addListener (this);

	multiTimer				= new CtrlrLuaMultiTimer();
	methodManager			= new CtrlrLuaMethodManager(*this);
	luaAudioFormatManager	= new LAudioFormatManager();

	{
		createAudioThreadState();

		wrapBasicIO (luaState);
		wrapCore (luaState);
		wrapJuceClasses (luaState);
		wrapCtrlrClasses (luaState);
	}

	{
		assignDefaultObjects (luaState);
	}

	luaManagerTree.addChild (methodManager->getManagerTree(), -1, 0);
}

CtrlrLuaManager::~CtrlrLuaManager()
{
	deleteAndZero (methodManager);
	luaManagerTree.removeListener (this);
	deleteAndZero (multiTimer);
	deleteAndZero (luaAudioFormatManager);
	lua_close(luaState);
	lua_close(audioThreadState);
}

void CtrlrLuaManager::createAudioThreadState()
{
	audioThreadState = lua_open();
	luaopen_base(audioThreadState);
    luaopen_table(audioThreadState);
    luaopen_string(audioThreadState);
    luaopen_math(audioThreadState);

	using namespace luabind;
    open(audioThreadState);

	wrapBasicIO(audioThreadState);
	wrapJuceCoreClasses(audioThreadState);
}

void CtrlrLuaManager::console (const String &arg)
{
	_LUA(removeInvalidChars(arg, true));
}

void CtrlrLuaManager::debug (const String &arg)
{
	_LUA(arg);
}

void CtrlrLuaManager::sleep (const int milliseconds)
{
	Thread::sleep(milliseconds);
}

std::string CtrlrLuaManager::stringToLua (const String &string)
{
	return (string.toUTF8().getAddress());
}

const String CtrlrLuaManager::toJuceString (const std::string &arg)
{
	return (String(arg.c_str()));
}

const double CtrlrLuaManager::int64ToDouble(const int64 value)
{
	return ((double)value);
}

const int CtrlrLuaManager::int64ToInt(const int64 value)
{
	return ((int)value);
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
		/*for (int i=0; i<methodManager->getNumUtilities(); i++)
		{
			const String u = methodManager->getUtility(i);

			if (!u.isEmpty())
			{
				if (!runCode(u))
				{
					_WRN ("CtrlrLuaManager::wrapUtilities failed to compile utility: \"" + methodManager->getUtilityName(i) + "\"" );
				}
			}
		}*/
	}
}

void CtrlrLuaManager::assert_()
{
	jassertfalse; // LUA CALLED THIS
}

void CtrlrLuaManager::wrapBasicIO (lua_State* L)
{
	using namespace luabind;

	module(L)
    [
		def("assert", &CtrlrLuaManager::assert_),
		def("debug", &CtrlrLuaManager::debug),
		def("sleep", &CtrlrLuaManager::sleep)
	];
}

void CtrlrLuaManager::wrapCore (lua_State* L)
{
	using namespace luabind;

	CtrlrLuaObject::wrapForLua (L);

	module(L)
    [
		def("console", &CtrlrLuaManager::console),
		def("J", (const String (*) (const std::string &)) &CtrlrLuaManager::toJuceString),
		def("L", &CtrlrLuaManager::stringToLua),
		def("int64ToDouble", &CtrlrLuaManager::int64ToDouble),
		def("int64ToInt", &CtrlrLuaManager::int64ToInt),
		def("log", &CtrlrLuaManager::log),

		class_<CtrlrLuaObjectWrapper>("CtrlrLuaObjectWrapper")
				.def(constructor<luabind::object const&>())
				.def(constructor<>())
				.def("getObject", &CtrlrLuaObjectWrapper::getObject)
    ];
}

void CtrlrLuaManager::wrapCtrlrClasses(lua_State* L)
{
	CtrlrModulator::wrapForLua (L);
	CtrlrPanel::wrapForLua (L);
	CtrlrMidiInputComparator::wrapForLua (L);
	CtrlrMidiMessage::wrapForLua (L);
	CtrlrLuaUtils::wrapForLua (L);
	CtrlrPanelEditor::wrapForLua (L);
	CtrlrPanelCanvas::wrapForLua (L);
	CtrlrLuaMultiTimer::wrapForLua (L);
	CtrlrPanelResourceManager::wrapForLua (L);
	CtrlrPanelCanvasLayer::wrapForLua (L);
	CtrlrLuaAudioConverter::wrapForLua (L);
	CtrlrLuaLookAndFeel::wrapForLua (L);
	CtrlrLuaBigInteger::wrapForLua (L);
	CtrlrLuaMemoryBlock::wrapForLua (L);
	CtrlrLuaRectangle::wrapForLua (L);
	CtrlrLuaComponentAnimator::wrapForLua (L);
	CtrlrComponent::wrapForLua (L);
	CtrlrMIDITransaction::wrapForLua (L);
	CtrlrMIDILibrary::wrapForLua (L);

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
}

void CtrlrLuaManager::assignDefaultObjects(lua_State* L)
{
	luabind::globals(L)["panel"]					= &owner;
	luabind::globals(L)["utils"]					= &utils;
	luabind::globals(L)["timer"]					= multiTimer;
	luabind::globals(L)["afm"]						= luaAudioFormatManager;
	luabind::globals(L)["atc"]						= &owner.getOwner().getAudioThumbnailCache();
	luabind::globals(L)["converter"]				= &audioConverter;
	luabind::globals(L)["resources"]				= &owner.getResourceManager();
	luabind::globals(L)["library"]					= &owner.getCtrlrMIDILibrary();
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

bool CtrlrLuaManager::runCode (const String &code)
{
	if (luaL_loadbuffer(luaState, code.toUTF8(), std::strlen(code.toUTF8()), code.toUTF8())
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

void CtrlrLuaManager::log(const String &message)
{
	if (CtrlrLog::ctrlrLog != nullptr)
		CtrlrLog::ctrlrLog->logMessage(message, CtrlrLog::Info);
}
