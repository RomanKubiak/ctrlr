#include "stdafx.h"
#include "CtrlrLuaManager.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrLuaObjectWrapper.h"
#include "CtrlrComponents/Specials/CtrlrWaveform.h"
#include "CtrlrComponents/Labels/CtrlrLabel.h"
#include "CtrlrComponents/Labels/CtrlrLCDLabel.h"
#include "CtrlrComponents/Buttons/CtrlrToggleButton.h"
#include "CtrlrComponents/Buttons/CtrlrButton.h"
#include "CtrlrComponents/Buttons/CtrlrImageButton.h"
#include "CtrlrComponents/CtrlrCombo.h"
#include "CtrlrComponents/Specials/CtrlrListBox.h"
#include "CtrlrComponents/Specials/CtrlrFileListBox.h"
#include "JuceClasses/LMemoryBlock.h"
#include "CtrlrComponents/Sliders/CtrlrSlider.h"
#include "CtrlrComponents/Sliders/CtrlrFixedSlider.h"
#include "CtrlrComponents/Sliders/CtrlrImageSlider.h"
#include "CtrlrComponents/Sliders/CtrlrFixedImageSlider.h"

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
		if (luaPanelGlobalChangedCbk->isValid())
		{
			getCtrlrLuaManager().getMethodManager().call (luaPanelGlobalChangedCbk, index, value);
		}
	}
}

/** @brief Get the value of a global variable

	@param	index	the global variable index 0-16
*/
const int CtrlrPanel::getGlobalVariable (const int index)
{
	return (globalVariables[index]);
}

/** @brief Get a modulator by it's index (this is the VST index property)

	@param	index	the index of the modulator to fetch
*/
CtrlrModulator* CtrlrPanel::getModulatorByIndex (const int index)
{
	if (ctrlrModulators [index] == nullptr)
	{
		_LERR("CtrlrPanel::getModulatorByIndex failed to fetch modulator index=" + String(index));
		return (owner.getInvalidModulator());
	}

	return (ctrlrModulators [index]);
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
const int CtrlrPanel::getNumModulators()
{
	return (ctrlrModulators.size());
}

luabind::object CtrlrPanel::getModulatorsWithPropertyLua (const String &propertyName, const String &propertyValue)
{
	using namespace luabind;
	object table = newtable (getCtrlrLuaManager().getLuaState());

	for (int i=0; i<ctrlrModulators.size(); i++)
	{
		if (ctrlrModulators[i]->getProperty(propertyName).toString() == propertyValue)
		{
			table[i+1] = ctrlrModulators[i];
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

	for (int i=0; i<ctrlrModulators.size(); i++)
	{
		if (ctrlrModulators[i]->getName().matchesWildcard (wildcardMatch, ignoreCase))
		{
			table[i+1] = ctrlrModulators[i];
		}
		else
		{
			table[i+1] = 0;
		}
	}

	return (table);
}

luabind::object CtrlrPanel::getModulatorsWildcardLua (const String &wildcardMatch, const String &propertyToMatch, const bool ignoreCase)
{
	using namespace luabind;
	object table = newtable (getCtrlrLuaManager().getLuaState());

	for (int i=0; i<ctrlrModulators.size(); i++)
	{
		if (ctrlrModulators[i]->getProperty(propertyToMatch).toString().matchesWildcard (wildcardMatch, ignoreCase))
		{
			table[i+1] = ctrlrModulators[i];
		}
		else
		{
			table[i+1] = 0;
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

	for (int i=0; i<getNumModulators(); i++)
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

LMemoryBlock CtrlrPanel::getModulatorValuesAsData(const ValueTree &programTree, const String &propertyToIndexBy, const CtrlrByteEncoding byteEncoding, const int bytesPerValue, const bool useMappedValues)
{
	MemoryBlock modulatorData (getNumModulators() * bytesPerValue, true);
	uint32 truncateTo = getNumModulators() * bytesPerValue;
	uint32 modulatorValue;

	for (int i=0; i<getNumModulators(); i++)
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
    for (unsigned int index=0; index<dataSource.getSize() / bytesPerValue; index++)
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

ValueTree CtrlrPanel::createProgramFromData(const MemoryBlock &dataSource, const String &propertyToIndexBy, const CtrlrByteEncoding byteEncoding, int propertyOffset, int bytesPerValue, const bool useMappedValues)
{
	ValueTree program = getCtrlrMIDILibrary().createEmptyProgramTree();
	return (program.createCopy());
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
			.def("setModulatorValuesFromData", &CtrlrPanel::setModulatorValuesFromData)
			.def("createProgramFromData", &CtrlrPanel::createProgramFromData)
			.def("getLibrary", &CtrlrPanel::getCtrlrMIDILibrary)
			.def("getCtrlrMIDILibrary", &CtrlrPanel::getCtrlrMIDILibrary)
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
	];
}
