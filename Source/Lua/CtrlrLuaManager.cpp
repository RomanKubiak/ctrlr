#include "stdafx.h"
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

#define LUA_USBLIBNAME "usb"
LUALIB_API int luaopen_usb(lua_State *L);


void CtrlrLuaManager::createLuaState()
{
	luaState 		= luaL_newstate();
	luaL_openlibs(luaState);

	// don't try to load standard libs again, here this will crash!!!



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
	_DBG("CtrlrLuaManager::wrapCtrlrClasses");
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
/*
 * dump_stack(ls);
 */
static void dump_stack(lua_State *L)
{
	int i;
	int top = lua_gettop(L);
	printf("\n#### BOS ####\n");
	for(i = top; i >= 1; i--)
	{
		int t = lua_type(L, i);
		switch(t)
		{
		case LUA_TSTRING:
			printf("%i (%i) = `%s'", i, i - (top + 1), lua_tostring(L, i));
			break;

		case LUA_TBOOLEAN:
			printf("%i (%i) = %s", i, i - (top + 1), lua_toboolean(L, i) ? "true" : "false");
			break;

		case LUA_TNUMBER:
			printf("%i (%i) = %g", i, i - (top + 1), lua_tonumber(L, i));
			break;

		default:
			printf("%i (%i) = %s", i, i - (top + 1), lua_typename(L, t));
			break;
		}
		printf("\n");
	}
	printf("#### EOS ####\n");
	printf("\n");
}

CtrlrLuaMethod::Type CtrlrLuaManager::runCode (const String &code, const String name)
{
	if (luaState && !isLuaDisabled())
	{
		//std::clog << "Executing Lua code " << (const char *) name.toUTF8() << std::endl;

		if (luaL_loadbuffer(luaState, code.toUTF8(), std::strlen(code.toUTF8()), name.isEmpty() ? "_runtime" : name.toUTF8())
			|| lua_pcall(luaState, 0, 0, 0))
		{
			const char* a = lua_tostring(luaState, -1);
			_LERR("ERROR: " + String(a));
			lastError = "ERROR: " + String(a);
			lua_pop(luaState, 1);
			return (CtrlrLuaMethod::ERROR);
		} else if (!name.isEmpty()) {
			//std::clog << code << std::endl;
			lua_getglobal(luaState,name.toUTF8());
			//dump_stack(luaState);
			int type = lua_type(luaState,1);
			lua_pop(luaState,1);
			switch (type) {
			case CtrlrLuaMethod::NONE:
			case CtrlrLuaMethod::NIL:
				{
					String errstring = "ERROR: The code for function or variable " + name
						+ " does not define " + name + ".";
					_LERR(errstring);
					lastError = std::move(errstring);
					break;
				}
			case  CtrlrLuaMethod::BOOLEAN:
			case  CtrlrLuaMethod::LIGHTUSERDATA:
			case  CtrlrLuaMethod::NUMBER:
			case  CtrlrLuaMethod::STRING:
			case  CtrlrLuaMethod::TABLE:
			case  CtrlrLuaMethod::USERDATA:
			case  CtrlrLuaMethod::THREAD:
			case  CtrlrLuaMethod::FUNCTION:
			break;
			default:
				type = CtrlrLuaMethod::UNKNOWN;
			}
			return ((CtrlrLuaMethod::Type)type);
		}

		return (CtrlrLuaMethod::SCRIPT);
	}
	else
	{
		return (CtrlrLuaMethod::DISABLED);
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

//
void CtrlrPanelCanvas::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrPanelCanvas, bases<Component> >("CtrlrPanelCanvas")
			.def("getLayerByName", &CtrlrPanelCanvas::getLayerByName)
		.def("getLayer", &CtrlrPanelCanvas::getLayer)
		.def("getLayerFromArray", &CtrlrPanelCanvas::getLayerFromArray)
		.def("getNumLayers", &CtrlrPanelCanvas::getNumLayers)
		.def("getLayerName", &CtrlrPanelCanvas::getLayerName)
		.def("setCustomLookAndFeel", (void (CtrlrPanelCanvas::*)(const luabind::object &)) &CtrlrPanelCanvas::setCustomLookAndFeel)
		];
}

//

/** @brief Move the layer up one step

*/
void CtrlrPanelCanvasLayer::moveUp()
{
	owner.moveLayer (this, true);
}

/** @brief Move the layer down one step

*/
void CtrlrPanelCanvasLayer::moveDown()
{
	owner.moveLayer (this, false);
}

void CtrlrPanelCanvasLayer::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrPanelCanvasLayer, bases<Component, CtrlrLuaObject> >("CtrlrPanelCanvasLayer")
			.def("moveUp", &CtrlrPanelCanvasLayer::moveUp)
		.def("moveDown", &CtrlrPanelCanvasLayer::moveDown)
		.def("setCustomLookAndFeel", (void (CtrlrPanelCanvasLayer::*)(const luabind::object &)) &CtrlrPanelCanvasLayer::setCustomLookAndFeel)
		];
}

//


/** @brief Set a value to a global variables

@param	index	the global variable index 0-16
@param	value	the value of the variable
*/
void CtrlrPanel::setGlobalVariable(const int index, const int value)
{
	if (index >= globalVariables.size() || index < 0)
	{
		// _LERR("CtrlrPanel::setGlobalVariable index out of bounds("+String(index)+")");
		return;
	}

	globalVariables.set (index, value);

	if (index<64)
	{
		setProperty (Ids::panelGlobalVariables, globalsToString(globalVariables));
	}

	if (luaPanelGlobalChangedCbk && !luaPanelGlobalChangedCbk.wasObjectDeleted())
	{
		if (luaPanelGlobalChangedCbk->isCallable())
		{
			getCtrlrLuaManager().getMethodManager().call (luaPanelGlobalChangedCbk, index, value);
		}
	}
}

/** @brief Get the value of a global variable

@param	index	the global variable index 0-16
*/
int CtrlrPanel::getGlobalVariable (const int index)
{
	return (globalVariables[index]);
}

/** @brief Get a modulator by it's index (this is the VST index property)

@param	index	the index of the modulator to fetch
*/
CtrlrModulator* CtrlrPanel::getModulatorByIndex (const int index)
{
	if (ctrlrModulators[index] == nullptr)
	{
		_LERR("CtrlrPanel::getModulatorByIndex failed to fetch modulator index=" + String(index));
		return (owner.getInvalidModulator());
	}

	return (ctrlrModulators[index]);
}

CtrlrComponent *CtrlrPanel::getComponent(const String &modulatorName)
{
	CtrlrModulator *m = getModulator(modulatorName);
	if (m)
	{
		if (m->getComponent())
		{
			return (m->getComponent());
		}
	}

	return (owner.getInvalidModulator()->getComponent());
}

/** @brief Get the amount of modulators in the panel

*/
int CtrlrPanel::getNumModulators()
{
	return (ctrlrModulators.size());
}

luabind::object CtrlrPanel::getModulatorsWithPropertyLua (const String &propertyName, const String &propertyValue)
{
	using namespace luabind;
	object table = newtable (getCtrlrLuaManager().getLuaState());

	for (int i = 0; i<ctrlrModulators.size(); i++)
	{
		if (ctrlrModulators[i]->getProperty(propertyName).toString() == propertyValue)
		{
			table[i + 1] = ctrlrModulators[i];
		}
	}

	return (table);
}

/** @brief Get a a modulator with a specified property set to a specified value

@param	propertyName	the property name to look for
@param	propertyValue	value (string) of the property
*/
CtrlrModulator *CtrlrPanel::getModulatorWithProperty (const String &propertyName, const String &propertyValue)
{
	if (propertyName.length() > 512 || propertyValue.length() > 512)
	{
		_WRN("CtrlrPanel::getModulatorWithProperty looks like the propertyName or the propertyValue are longer then 512 bytes, that might indicate a bad call");
	}

	Array <CtrlrModulator*> ret = getModulatorsWithProperty (propertyName, propertyValue);

	if (ret.size() == 0)
	{
		return (owner.getInvalidModulator());
	}
	else
	{
		return (ret[0]);
	}
}

/** @brief Get a a modulator with a specified property set to a specified value

@param	propertyName	the property name to look for
@param	propertyValue	value (numeric) of the property
*/
CtrlrModulator *CtrlrPanel::getModulatorWithProperty (const String &propertyName, const int propertyValue)
{
	if (propertyName.length() > 512)
	{
		_WRN("CtrlrPanel::getModulatorWithProperty looks like the propertyName is longer then 512 bytes, that might indicate a bad call");
	}

	Array <CtrlrModulator*> ret = getModulatorsWithProperty (propertyName, propertyValue);

	if (ret.size() == 0)
	{
		return (owner.getInvalidModulator());
	}
	else
	{
		return (ret[0]);
	}
}

/** @brief Get a list of modulators using a wildcard applied to their names

@param	wildcardMatch	the wildcard to use
@param	ignoreCase		ignore case when matching
*/
luabind::object CtrlrPanel::getModulatorsWildcardLua (const String &wildcardMatch, const bool ignoreCase)
{
	using namespace luabind;
	object table = newtable (getCtrlrLuaManager().getLuaState());

	for (int i = 0; i<ctrlrModulators.size(); i++)
	{
		if (ctrlrModulators[i]->getName().matchesWildcard (wildcardMatch, ignoreCase))
		{
			table[i + 1] = ctrlrModulators[i];
		}
		else
		{
			table[i + 1] = 0;
		}
	}

	return (table);
}

luabind::object CtrlrPanel::getModulatorsWildcardLua (const String &wildcardMatch, const String &propertyToMatch, const bool ignoreCase)
{
	using namespace luabind;
	object table = newtable (getCtrlrLuaManager().getLuaState());

	for (int i = 0; i<ctrlrModulators.size(); i++)
	{
		if (ctrlrModulators[i]->getProperty(propertyToMatch).toString().matchesWildcard (wildcardMatch, ignoreCase))
		{
			table[i + 1] = ctrlrModulators[i];
		}
		else
		{
			table[i + 1] = 0;
		}
	}

	return (table);
}

/** @brief Send a midi message

@param	midiMessage the midi message to send
*/
void CtrlrPanel::sendMidiNow (CtrlrMidiMessage &midiMessage)
{
	sendMidi (midiMessage, 0);
}

/** @brief Get a component as a Waveform component

@param	The name of the component to find
@return	If the component is found and is a Waveform component it is returned, otherwise null
*/

CtrlrWaveform *CtrlrPanel::getWaveformComponent(const String &componentName)
{
	CtrlrModulator *m = getModulator(componentName);
	if (m)
	{
		if (m->getComponent())
		{
			return (dynamic_cast<CtrlrWaveform*>(m->getComponent()));
		}
	}
	return (nullptr);
}

CtrlrLabel *CtrlrPanel::getLabelComponent(const String &componentName)
{
	CtrlrModulator *m = getModulator(componentName);
	if (m)
	{
		if (m->getComponent())
		{
			return (dynamic_cast<CtrlrLabel*>(m->getComponent()));
		}
	}
	return (nullptr);
}

CtrlrLCDLabel *CtrlrPanel::getLCDLabelComponent(const String &componentName)
{
	CtrlrModulator *m = getModulator(componentName);
	if (m)
	{
		if (m->getComponent())
		{
			return (dynamic_cast<CtrlrLCDLabel*>(m->getComponent()));
		}
	}
	return (nullptr);
}

CtrlrToggleButton *CtrlrPanel::getToggleButtonComponent (const String &componentName)
{
	CtrlrModulator *m = getModulator(componentName);
	if (m)
	{
		if (m->getComponent())
		{
			return (dynamic_cast<CtrlrToggleButton*>(m->getComponent()));
		}
	}
	return (nullptr);
}

CtrlrButton *CtrlrPanel::getButtonComponent (const String &componentName)
{
	CtrlrModulator *m = getModulator(componentName);
	if (m)
	{
		if (m->getComponent())
		{
			return (dynamic_cast<CtrlrButton*>(m->getComponent()));
		}
	}
	return (nullptr);
}

CtrlrImageButton *CtrlrPanel::getImageButtonComponent (const String &componentName)
{
	CtrlrModulator *m = getModulator(componentName);
	if (m)
	{
		if (m->getComponent())
		{
			return (dynamic_cast<CtrlrImageButton*>(m->getComponent()));
		}
	}
	return (nullptr);
}

CtrlrCombo *CtrlrPanel::getComboComponent (const String &componentName)
{
	CtrlrModulator *m = getModulator(componentName);
	if (m)
	{
		if (m->getComponent())
		{
			return (dynamic_cast<CtrlrCombo*>(m->getComponent()));
		}
	}
	return (nullptr);
}

CtrlrListBox *CtrlrPanel::getListBoxComponent (const String &componentName)
{
	CtrlrModulator *m = getModulator(componentName);

	if (m)
	{
		if (m->getComponent())
		{
			return (dynamic_cast<CtrlrListBox*>(m->getComponent()));
		}
	}
	return (nullptr);
}

CtrlrFileListBox *CtrlrPanel::getFileListBoxComponent (const String &componentName)
{
	CtrlrModulator *m = getModulator(componentName);

	if (m)
	{
		if (m->getComponent())
		{
			return (dynamic_cast<CtrlrFileListBox*>(m->getComponent()));
		}
	}
	return (nullptr);
}

CtrlrSlider *CtrlrPanel::getSliderComponent (const String &componentName)
{
	CtrlrModulator *m = getModulator(componentName);

	if (m)
	{
		if (m->getComponent())
		{
			return (dynamic_cast<CtrlrSlider*>(m->getComponent()));
		}
	}
	return (nullptr);
}

CtrlrImageSlider *CtrlrPanel::getImageSliderComponent (const String &componentName)
{
	CtrlrModulator *m = getModulator(componentName);

	if (m)
	{
		if (m->getComponent())
		{
			return (dynamic_cast<CtrlrImageSlider*>(m->getComponent()));
		}
	}
	return (nullptr);
}

CtrlrFixedSlider *CtrlrPanel::getFixedSliderComponent (const String &componentName)
{
	CtrlrModulator *m = getModulator(componentName);

	if (m)
	{
		if (m->getComponent())
		{
			return (dynamic_cast<CtrlrFixedSlider*>(m->getComponent()));
		}
	}
	return (nullptr);
}

CtrlrFixedImageSlider *CtrlrPanel::getFixedImageSliderComponent (const String &componentName)
{
	CtrlrModulator *m = getModulator(componentName);

	if (m)
	{
		if (m->getComponent())
		{
			return (dynamic_cast<CtrlrFixedImageSlider*>(m->getComponent()));
		}
	}
	return (nullptr);
}

LMemoryBlock CtrlrPanel::getModulatorValuesAsData(const String &propertyToIndexBy, const CtrlrByteEncoding byteEncoding, const int bytesPerValue, const bool useMappedValues)
{
	MemoryBlock modulatorData (getNumModulators() * bytesPerValue, true);
	uint32 truncateTo = getNumModulators() * bytesPerValue;
	uint32 modulatorValue;

	for (int i = 0; i<getNumModulators(); i++)
	{
		const int index = getModulatorByIndex(i)->getProperty(propertyToIndexBy);

		if (index >= 0)
		{
			if (useMappedValues)
				modulatorValue = getModulatorByIndex(i)->getValueMapped();
			else
				modulatorValue = getModulatorByIndex(i)->getValueNonMapped();

			modulatorData.setBitRange (index * (bytesPerValue * 8), bytesPerValue * 8, modulatorValue);
		}
		else
		{
			truncateTo--;
		}
	}

	modulatorData.setSize (truncateTo, false);
	return (modulatorData);
}

LMemoryBlock CtrlrPanel::getModulatorValuesAsData(const String &propertyToIndexBy,
	const CtrlrByteEncoding byteEncoding,
	const int propertyValueStart,
	const int howMany,
	const int bytesPerValue,
	const bool useMappedValues)
{
	MemoryBlock modulatorData (getNumModulators() * bytesPerValue, true);
	uint32 truncateTo = getNumModulators() * bytesPerValue;
	uint32 modulatorValue;

	for (int i = 0; i<getNumModulators(); i++)
	{
		const int index = getModulatorByIndex(i)->getProperty(propertyToIndexBy);

		if (index >= propertyValueStart && index < howMany)
		{
			if (useMappedValues)
				modulatorValue = getModulatorByIndex(i)->getValueMapped();
			else
				modulatorValue = getModulatorByIndex(i)->getValueNonMapped();

			modulatorData.setBitRange (index * (bytesPerValue * 8), bytesPerValue * 8, modulatorValue);
		}
		else
		{
			truncateTo--;
		}
	}

	modulatorData.setSize (truncateTo, false);
	return (modulatorData);
}

LMemoryBlock CtrlrPanel::getModulatorValuesAsData(const ValueTree &programTree, const String &propertyToIndexBy, const CtrlrByteEncoding byteEncoding, const int bytesPerValue, const bool useMappedValues)
{
	MemoryBlock modulatorData (getNumModulators() * bytesPerValue, true);
	uint32 truncateTo = getNumModulators() * bytesPerValue;
	uint32 modulatorValue;

	for (int i = 0; i<getNumModulators(); i++)
	{
		const int index = getModulatorByIndex(i)->getProperty(propertyToIndexBy);

		if (index >= 0)
		{
			if (useMappedValues)
				modulatorValue = getModulatorByIndex(i)->getValueMapped();
			else
				modulatorValue = getModulatorByIndex(i)->getValueNonMapped();

			modulatorData.setBitRange (index * (bytesPerValue * 8), bytesPerValue * 8, modulatorValue);
		}
		else
		{
			truncateTo--;
		}
	}

	modulatorData.setSize (truncateTo, false);
	return (modulatorData);
}

void CtrlrPanel::setModulatorValuesFromData (const MemoryBlock &dataSource, const String &propertyToIndexBy, const CtrlrByteEncoding byteEncoding, int propertyOffset, int bytesPerValue, const bool useMappedValues)
{
	for (unsigned int index = 0; index<dataSource.getSize() / bytesPerValue; index++)
	{
		CtrlrModulator *m = getModulatorWithProperty (propertyToIndexBy, propertyOffset + index);
		if (m)
		{
			const int v = dataSource.getBitRange (index * bytesPerValue * 8, bytesPerValue * 8);

			if (!m->isStatic())
			{
				if (useMappedValues)
					m->setValueMapped (v, false, true);
				else
					m->setValueNonMapped (v, false, true);
			}
		}
	}
}

void CtrlrPanel::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrPanel, CtrlrLuaObject>("CtrlrPanel")
			.def("getModulatorByName", &CtrlrPanel::getModulator)
		.def("getModulator", &CtrlrPanel::getModulator)
		.def("getModulatorByIndex", &CtrlrPanel::getModulatorByIndex)
		.def("getNumModulators", &CtrlrPanel::getNumModulators)
		.def("sendMidiMessageNow", (void (CtrlrPanel::*)(CtrlrMidiMessage &)) &CtrlrPanel::sendMidiNow)
		.def("sendMidi", (void (CtrlrPanel::*)(CtrlrMidiMessage &, double)) &CtrlrPanel::sendMidi)
		.def("sendMidi", (void (CtrlrPanel::*)(const MidiMessage &, double)) &CtrlrPanel::sendMidi)
		.def("sendMidi", (void (CtrlrPanel::*)(const MidiBuffer &, double)) &CtrlrPanel::sendMidi)
		.def("getPanelEditor", &CtrlrPanel::getPanelEditor)
		.def("getRestoreState", &CtrlrPanel::getRestoreState)
		.def("getBootstrapState", &CtrlrPanel::getBootstrapState)
		.def("isRestoring", &CtrlrPanel::getRestoreState)
		.def("setRestoreState", &CtrlrPanel::setRestoreState)
		.def("setProgramState", &CtrlrPanel::setProgramState)
		.def("getProgramState", &CtrlrPanel::getProgramState)
		.def("getComponent", &CtrlrPanel::getComponent)
		.def("getGlobalVariable", &CtrlrPanel::getGlobalVariable)
		.def("setGlobalVariable", &CtrlrPanel::setGlobalVariable)
		.def("getCanvas", &CtrlrPanel::getCanvas)
		.def("getWaveformComponent", &CtrlrPanel::getWaveformComponent)
		.def("getWaveform", &CtrlrPanel::getWaveformComponent)
		.def("getLabelComponent", &CtrlrPanel::getLabelComponent)
		.def("getLabel", &CtrlrPanel::getLabelComponent)
		.def("getLCDLabelComponent", &CtrlrPanel::getLCDLabelComponent)
		.def("getLCDLabel", &CtrlrPanel::getLCDLabelComponent)
		.def("getToggleButtonComponent", &CtrlrPanel::getToggleButtonComponent)
		.def("getToggleButton", &CtrlrPanel::getToggleButtonComponent)
		.def("getImageButtonComponent", &CtrlrPanel::getImageButtonComponent)
		.def("getImageButton", &CtrlrPanel::getImageButtonComponent)
		.def("getButtonComponent", &CtrlrPanel::getButtonComponent)
		.def("getButton", &CtrlrPanel::getButtonComponent)
		.def("getComboComponent", &CtrlrPanel::getComboComponent)
		.def("getCombo", &CtrlrPanel::getComboComponent)
		.def("getListBoxComponent", &CtrlrPanel::getListBoxComponent)
		.def("getListBox", &CtrlrPanel::getListBoxComponent)
		.def("getFileListBoxComponent", &CtrlrPanel::getFileListBoxComponent)
		.def("getFileListBox", &CtrlrPanel::getFileListBoxComponent)
		.def("getSliderComponent", &CtrlrPanel::getSliderComponent)
		.def("getSlider", &CtrlrPanel::getSliderComponent)
		.def("getFixedImageSliderComponent", &CtrlrPanel::getFixedImageSliderComponent)
		.def("getFixedImageSlider", &CtrlrPanel::getFixedImageSliderComponent)
		.def("getFixedSliderComponent", &CtrlrPanel::getFixedSliderComponent)
		.def("getFixedSlider", &CtrlrPanel::getFixedSliderComponent)
		.def("getImageSliderComponent", &CtrlrPanel::getImageSliderComponent)
		.def("getImageSlider", &CtrlrPanel::getImageSliderComponent)
		.def("getModulatorWithProperty", (CtrlrModulator *(CtrlrPanel::*)(const String &, const int)) &CtrlrPanel::getModulatorWithProperty)
		.def("getModulatorWithProperty", (CtrlrModulator *(CtrlrPanel::*)(const String &, const String &)) &CtrlrPanel::getModulatorWithProperty)
		.def("getModulatorsWithProperty", &CtrlrPanel::getModulatorsWithPropertyLua)
		.def("getModulatorsWildcard", (luabind::object (CtrlrPanel::*)(const String &, const bool))&CtrlrPanel::getModulatorsWildcardLua)
		.def("getModulatorsWildcard", (luabind::object (CtrlrPanel::*)(const String &, const String &, const bool))&CtrlrPanel::getModulatorsWildcardLua)
		.def("getInputComparator", &CtrlrPanel::getInputComparator)
		.def("getModulatorValuesAsData", (LMemoryBlock (CtrlrPanel::*)(const String &, const CtrlrByteEncoding, const int, const bool))&CtrlrPanel::getModulatorValuesAsData)
		.def("getModulatorValuesAsData", (LMemoryBlock (CtrlrPanel::*)(const ValueTree &, const String &, const CtrlrByteEncoding, const int, const bool))&CtrlrPanel::getModulatorValuesAsData)
		.def("getModulatorValuesAsData", (LMemoryBlock (CtrlrPanel::*)(const String &, const CtrlrByteEncoding, const int, const int, const int, const bool))&CtrlrPanel::getModulatorValuesAsData)
		.def("setModulatorValuesFromData", &CtrlrPanel::setModulatorValuesFromData)
		.def("dumpDebugData", &CtrlrPanel::dumpDebugData)
		.enum_("CtrlrPanelFileType")
		[
			value("PanelFileXML", 0),
			value("PanelFileXMLCompressed", 1),
			value("PanelFileBinary", 2),
			value("PanelFileBinaryCompressed", 3),
			value("PanelFileExport", 4)
		]
	.enum_("CtrlrNotificationType")
		[
			value("NotifySuccess", (uint8)NotifySuccess),
			value("NotifyFailure", (uint8)NotifyFailure),
			value("NotifyInformation", (uint8)NotifyInformation),
			value("NotifyWarning", (uint8)NotifyWarning)
		]
	.enum_("CtrlrByteEncoding")
		[
			value("EncodeNormal", (uint8)EncodeNormal),
			value("EncodeMSBFirst", (uint8)EncodeMSBFirst),
			value("EncodeLSBFirst", (uint8)EncodeLSBFirst),
			value("EncodeDSI", (uint8)EncodeDSI)
		]
	.enum_("CtrlrByteSplit")
		[
			value("SplitNone", (uint8)SplitNone),
			value("Split4Bits", (uint8)Split4Bits),
			value("Split7Bits", (uint8)Split7Bits),
			value("Split8Bits", (uint8)Split8Bits)
		]
	.enum_("CtrlrInstance")
		[
			value("InstanceSingle", (uint8)InstanceSingle),
			value("InstanceMulti", (uint8)InstanceMulti),
			value("InstanceSingleRestriced", (uint8)InstanceSingleRestriced),
			value("InstanceSingleEngine", (uint8)InstanceSingleEngine),
			value("InstanceMultiEngine", (uint8)InstanceMultiEngine),
			value("InstanceSingleRestrictedEngine", (uint8)InstanceSingleRestrictedEngine)
		]
		];
}

//

CtrlrLuaMultiTimer::CtrlrLuaMultiTimer()
{
}

CtrlrLuaMultiTimer::~CtrlrLuaMultiTimer()
{
}

void CtrlrLuaMultiTimer::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrLuaMultiTimer>("CtrlrLuaMultiTimer")
			.def("setCallback", &CtrlrLuaMultiTimer::setCallback)
		.def("startTimer", &CtrlrLuaMultiTimer::startTimer)
		.def("isRegistered", &CtrlrLuaMultiTimer::isRegistered)
		.def("stopTimer", &CtrlrLuaMultiTimer::stopTimer)
		.def("isTimerRunning", &CtrlrLuaMultiTimer::isTimerRunning)
		.def("getTimerInterval", &CtrlrLuaMultiTimer::getTimerInterval)
		];
}

void CtrlrLuaMultiTimer::setCallback (const int timerId, luabind::object callback)
{
	LuaTimerCallback c;
	c.o = callback;
	c.isValid = true;
	callbacks.set (timerId, c);
}

void CtrlrLuaMultiTimer::startTimer (const int timerId, const int interval)
{
	MultiTimer::startTimer (timerId, interval);
}

void CtrlrLuaMultiTimer::timerCallback(int timerId)
{
	if (callbacks.contains (timerId))
	{
		if (callbacks[timerId].isValid)
		{
			try
			{
				luabind::call_function <void>(callbacks[timerId].o, timerId);
			}
			catch (const luabind::error &e)
			{
				LuaTimerCallback cb = callbacks[timerId];
				cb.isValid = false;

				callbacks.set (timerId, cb);
				const char* a = lua_tostring(e.state(), -1);
				AlertWindow::showMessageBox (AlertWindow::WarningIcon, "Timer callback error, timer id that failed was: " + String(timerId), String(e.what()) + "\n" + String(a) + "\n\nCallback disabled");
			}
		}
	}
}

const bool CtrlrLuaMultiTimer::isRegistered(const int timerId)
{
	return (callbacks.contains (timerId));
}

void CtrlrLuaMultiTimer::stopTimer (const int timerId)
{
	MultiTimer::stopTimer (timerId);
}

const bool CtrlrLuaMultiTimer::isTimerRunning (const int timerId)
{
	return (MultiTimer::isTimerRunning(timerId));
}

const int CtrlrLuaMultiTimer::getTimerInterval(const int timerId)
{
	return (MultiTimer::getTimerInterval(timerId));
}

//


void CtrlrModulator::setValue(const int newValue, const bool force)
{
	processor.setValueGeneric (CtrlrModulatorValue (newValue, CtrlrModulatorValue::changedByLua), force, false);
}

/** @brief Set the value of the modulator

@param newValue the new value for the modualtor
*/
void CtrlrModulator::setValue(const int newValue, const bool force, const bool mute)
{
	processor.setValueGeneric (CtrlrModulatorValue (newValue, CtrlrModulatorValue::changedByLua), force, mute);
}

void CtrlrModulator::setValueMapped (const int newValue, const bool force, const bool mute)
{
	processor.setMappedValue (CtrlrModulatorValue (newValue, CtrlrModulatorValue::changedByLua), force, mute);
}

void CtrlrModulator::setValueNonMapped (const int newValue, const bool force, const bool mute)
{
	processor.setValueGeneric (CtrlrModulatorValue (newValue, CtrlrModulatorValue::changedByLua), force, mute);
}

void CtrlrModulator::setModulatorValue(const int newValue, bool vst, bool midi, bool ui)
{
	processor.setValueGeneric (CtrlrModulatorValue (newValue, CtrlrModulatorValue::changedByLua), true, !midi);
}

int CtrlrModulator::getValueMapped() const
{
	return (processor.getValueMapped());
}

int CtrlrModulator::getValueNonMapped() const
{
	return (getModulatorValue());
}

int CtrlrModulator::getMaxMapped()
{
	return (processor.getValueMap().getMappedMax());
}

int CtrlrModulator::getMaxNonMapped()
{
	return (getMaxModulatorValue());
}

int CtrlrModulator::getMinMapped()
{
	return (processor.getValueMap().getMappedMin());
}

int CtrlrModulator::getMinNonMapped()
{
	return (getMinModulatorValue());
}

void CtrlrModulator::setValueMappedCompat (const int newValue, const bool force)
{
	setValueMapped (newValue, force);
}

void CtrlrModulator::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrModulator, CtrlrLuaObject>("CtrlrModulator")
			.def("getValue", &CtrlrModulator::getModulatorValue)
		.def("setValue", (void (CtrlrModulator::*)(const int, const bool))&CtrlrModulator::setValue)
		.def("setValue", (void (CtrlrModulator::*)(const int, const bool, const bool))&CtrlrModulator::setValue)
		.def("setValueMapped", &CtrlrModulator::setValueMapped)
		.def("setValueMapped", &CtrlrModulator::setValueMappedCompat)
		.def("setValueNonMapped", &CtrlrModulator::setValueNonMapped)
		.def("getVstIndex", &CtrlrModulator::getVstIndex)
		.def("getMaxModulatorValue", &CtrlrModulator::getMaxModulatorValue)
		.def("getMaxMapped", &CtrlrModulator::getMaxMapped)
		.def("getMaxNonMapped", &CtrlrModulator::getMaxNonMapped)
		.def("getMinMapped", &CtrlrModulator::getMinMapped)
		.def("getMinNonMapped", &CtrlrModulator::getMinNonMapped)
		.def("getMinModulatorValue", &CtrlrModulator::getMinModulatorValue)
		.def("getComponent", &CtrlrModulator::getComponent)
		.def("getRestoreState", &CtrlrModulator::getRestoreState)
		.def("isRestoring", &CtrlrModulator::getRestoreState)
		.def("setRestoreState", &CtrlrModulator::setRestoreState)
		.def("getMidiMessage", (CtrlrMidiMessage &(CtrlrModulator::*)(void))&CtrlrModulator::getMidiMessagePtr)
		.def("getMidiMessage", (CtrlrMidiMessage &(CtrlrModulator::*)(const CtrlrMIDIDeviceType))&CtrlrModulator::getMidiMessagePtr)
		.def("getName", &CtrlrModulator::getName)
		.def("getValueMapped", &CtrlrModulator::getValueMapped)
		.def("getValueNonMapped", &CtrlrModulator::getValueNonMapped)
		.def("getModulatorValue", &CtrlrModulator::getModulatorValue)
		.def("setModulatorValue", &CtrlrModulator::setModulatorValue)
		.def("getLuaName", &CtrlrModulator::getName)
		.def("getModulatorName", &CtrlrModulator::getName)
		//.def("getProperty", (const var &(CtrlrModulator::*)(const Identifier&) const)&CtrlrModulator::getProperty)
		.enum_("CtrlrModulatorValue")
		[
			value("initialValue", 0),
			value("changedByHost", 1),
			value("changedByMidiIn", 2),
			value("changedByMidiController", 3),
			value("changedByGUI", 4),
			value("changedByLua", 5),
			value("changedByProgram", 6),
			value("changedByLink", 7),
			value("changeByUnknown", 8)
		]
		];

}

//

void CtrlrCustomComponent::wrapForLua(lua_State *L)
{
	using namespace luabind;
	module(L)
		[
			class_<CtrlrCustomComponent, CtrlrComponent>("CtrlrCustomComponent")
			,
		class_<DragAndDropSourceDetails>("DragAndDropSourceDetails")
		.def(constructor<const String &, Component *, int, int>())
		.def(constructor<const String &, Image, int, int>())
		.def(constructor<>())
		.def("getDescription", &DragAndDropSourceDetails::getDescription)
		.def("getSourceComponent", &DragAndDropSourceDetails::getSourceComponent)
		.def("getLocalPositionX", &DragAndDropSourceDetails::getLocalPositionX)
		.def("getLocalPositionY", &DragAndDropSourceDetails::getLocalPositionY)
		];
}

//

void CtrlrPanelEditor::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
		[
			class_<CtrlrPanelEditor, CtrlrLuaObject>("CtrlrPanelEditor")
			.def("getWidth", &CtrlrPanelEditor::getWidth)
		.def("getHeight", &CtrlrPanelEditor::getHeight)
		.def("getCanvas", &CtrlrPanelEditor::getCanvas)
		];
}
