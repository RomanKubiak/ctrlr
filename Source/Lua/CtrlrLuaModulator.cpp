#include "stdafx_luabind.h"
#include "CtrlrLuaManager.h"
#include "CtrlrLog.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrComponents/CtrlrComponent.h"

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
