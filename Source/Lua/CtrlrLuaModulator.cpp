#include "stdafx.h"
#include "CtrlrLuaManager.h"
#include "CtrlrLog.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrComponents/CtrlrComponent.h"

void CtrlrModulator::setValue(const int newValue, const bool force)
{
	processor.setValueFromGUI (newValue, force, false);
}

/** @brief Set the value of the modulator

	@param newValue the new value for the modualtor
*/
void CtrlrModulator::setValue(const int newValue, const bool force, const bool mute)
{
	processor.setValueFromGUI (newValue, force, mute);
}

void CtrlrModulator::setValueMapped (const int newValue, const bool force, const bool mute)
{
	processor.setMappedValue (newValue, force, mute);
}

void CtrlrModulator::setValueNonMapped (const int newValue, const bool force, const bool mute)
{
	processor.setValueFromGUI (newValue, force, mute);
}

/** @brief Set the modulator value only the midi parameter works

	@param newValue		the new value for the modualtor
	@param vst			unused
	@param midi			if false midi message will not be sent
	@param ui			unused
*/
void CtrlrModulator::setModulatorValue(const int newValue, bool vst, bool midi, bool ui)
{
	processor.setValueFromGUI (newValue, true, !midi);
	processor.handleUpdateNowIfNeeded();
}

const int CtrlrModulator::getValueMapped() const
{
	return (processor.getValueMapped());
}

const int CtrlrModulator::getValueNonMapped() const
{
	return (getModulatorValue());
}

const int CtrlrModulator::getMaxMapped()
{
	return (processor.getValueMap().getMappedMax());
}

const int CtrlrModulator::getMaxNonMapped()
{
	return (getMaxModulatorValue());
}

const int CtrlrModulator::getMinMapped()
{
	return (processor.getValueMap().getMappedMin());
}

const int CtrlrModulator::getMinNonMapped()
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
			.def("getMidiMessage", &CtrlrModulator::getMidiMessagePtr)
			.def("getName", &CtrlrModulator::getName)
			.def("getValueMapped", &CtrlrModulator::getValueMapped)
			.def("getValueNonMapped", &CtrlrModulator::getValueNonMapped)
			.def("getModulatorValue", &CtrlrModulator::getModulatorValue)
			.def("setModulatorValue", &CtrlrModulator::setModulatorValue)
			.def("getLuaName", &CtrlrModulator::getName)
			.def("getModulatorName", &CtrlrModulator::getName)
	];

}