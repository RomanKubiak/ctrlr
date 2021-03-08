#include "stdafx.h"
#include "stdafx_luabind.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrMIDIDeviceManager.h"
#include "CtrlrProcessor.h"
#include "CtrlrMacros.h"
#include "CtrlrMIDIDevice.h"
#include "CtrlrLog.h"
#include "CtrlrUtilities.h"
#include "CtrlrPanel/CtrlrPanel.h"

CtrlrMIDIDeviceManager::CtrlrMIDIDeviceManager(CtrlrManager &_owner)
	:	managerTree(Ids::midiDeviceManager),
		owner(_owner)
{
	inDevs.clear();
	outDevs.clear();
	refreshDevices();
}

CtrlrMIDIDeviceManager::~CtrlrMIDIDeviceManager()
{
	processingListeners.clear();
	inDevs.clear();
	outDevs.clear();
}

int CtrlrMIDIDeviceManager::getNumDevices(const CtrlrMIDIDeviceType type)
{
	if (type == outputDevice)
	{
		return (outDevs.size());
	}
	else if (type == controllerDevice || type == inputDevice)
	{
		return (inDevs.size());
	}

	return (0);
}

const String CtrlrMIDIDeviceManager::getDeviceName(const int idx, const CtrlrMIDIDeviceType type)
{
	if (type == outputDevice && outDevs[idx])
	{
		return (outDevs[idx]->getName());
	}
	else if (type == inputDevice && inDevs[idx])
	{
		return (inDevs[idx]->getName());
	}
	else if (type == controllerDevice && inDevs[idx])
	{
		return (inDevs[idx]->getName());
	}
	return (COMBO_NONE_ITEM);
}

bool CtrlrMIDIDeviceManager::isDeviceOpened(const int idx, const CtrlrMIDIDeviceType type)
{
	if (type == outputDevice)
	{
		return (outDevs[idx]->getProperty(Ids::midiDevState));
	}
	else if (inDevs[idx])
	{
		return (inDevs[idx]->getProperty(Ids::midiDevState));
	}

	return (false);
}

bool CtrlrMIDIDeviceManager::toggleDevice (const int idx, const CtrlrMIDIDeviceType type, const bool state)
{
	owner.sendChangeMessage();

	if (state)
	{
		if (type == outputDevice)
		{
			if (outDevs[idx])
			{
				return (outDevs[idx]->openDevice());
			}
		}
		else if (type == inputDevice || type == controllerDevice)
		{
			if (inDevs[idx])
			{
				return (inDevs[idx]->openDevice());
			}
		}
	}
	else
	{
		if (type == outputDevice)
		{
			if (outDevs[idx])
			{
				outDevs[idx]->closeDevice();
				return (true);
			}
		}
		else if (type == inputDevice || type == controllerDevice)
		{
			if (inDevs[idx])
			{
				inDevs[idx]->closeDevice();
				return (true);
			}
		}
	}

	return (false);
}

void CtrlrMIDIDeviceManager::restoreState (const ValueTree &savedState)
{
}

CtrlrMIDIDevice *CtrlrMIDIDeviceManager::getDeviceByName(const String name, const CtrlrMIDIDeviceType type, const bool openIfClosed)
{
	if (type == outputDevice)
	{
		for (int i=0; i<outDevs.size(); i++)
		{
			if (outDevs[i]->getName() == name)
			{
				if (openIfClosed)
				{
					if (!outDevs[i]->openDevice())
					{
						_WRN("CtrlrMidiDeviceManager::getDeviceByName OUT \""+name+"\" failed to open");
					}
				}
				return (outDevs[i]);
			}
		}
	}

	if (type == inputDevice)
	{
		for (int i=0; i<inDevs.size(); i++)
		{
			if (inDevs[i]->getName() == name)
			{
				if (openIfClosed)
				{
					if (!inDevs[i]->openDevice())
					{
						_WRN("CtrlrMidiDeviceManager::getDeviceByName IN \""+name+"\" failed to open");
					}
				}
				return (inDevs[i]);
			}
		}
	}

	if (type == controllerDevice)
	{
		for (int i=0; i<inDevs.size(); i++)
		{
			if (inDevs[i]->getName() == name)
			{
				if (openIfClosed)
				{
					if (!inDevs[i]->openDevice())
					{
						_WRN("CtrlrMidiDeviceManager::getDeviceByName CONTROL \""+name+"\" failed to open");
					}
				}
				return (inDevs[i]);
			}
		}
	}

	return (nullptr);
}

CtrlrMIDIDevice *CtrlrMIDIDeviceManager::getDeviceByIndex(const int idx, const CtrlrMIDIDeviceType type)
{
	if (type == outputDevice)
	{
		return (outDevs[idx]);
	}
	else if (type == controllerDevice || type == inputDevice)
	{
		return (inDevs[idx]);
	}

	return (nullptr);
}

void CtrlrMIDIDeviceManager::reloadComboContents (ComboBox &comboToUpdate, const CtrlrMIDIDeviceType type, CtrlrPanel *panel)
{
//	refreshDevices();  //This worked, but it would never send output to the "new" device, even though it found it.
	comboToUpdate.clear();
	if (type == outputDevice)
	{
		comboToUpdate.addItem (COMBO_NONE_ITEM, 1);

		for (int i=0; i<outDevs.size(); i++)
		{
			comboToUpdate.addItem (outDevs[i]->getProperty(Ids::name).toString(), i+2);

			if (panel)
			{
				if (outDevs[i]->getProperty(Ids::name).toString() == panel->getProperty(Ids::panelMidiOutputDevice).toString())
				{
					comboToUpdate.setSelectedId (i+2);
				}
			}
		}
	}
	else if (type == controllerDevice)
	{
		comboToUpdate.addItem (COMBO_NONE_ITEM, 1);

		for (int i=0; i<inDevs.size(); i++)
		{
			comboToUpdate.addItem (inDevs[i]->getProperty(Ids::name).toString(), i+2);

			if (panel)
			{
				if (inDevs[i]->getProperty(Ids::name).toString() == panel->getProperty(Ids::panelMidiControllerDevice).toString())
				{
					comboToUpdate.setSelectedId (i+2);
				}
			}
		}
	}
	else if (type == inputDevice)
	{
		comboToUpdate.addItem (COMBO_NONE_ITEM, 1);

		for (int i=0; i<inDevs.size(); i++)
		{
			comboToUpdate.addItem (inDevs[i]->getProperty(Ids::name).toString(), i+2);

			if (panel)
			{
				if (inDevs[i]->getProperty(Ids::name).toString() == panel->getProperty(Ids::panelMidiInputDevice).toString())
				{
					comboToUpdate.setSelectedId (i+2);
				}
			}
		}
	}
}

const StringArray CtrlrMIDIDeviceManager::getManagedDevices(const CtrlrMIDIDeviceType type)
{
	StringArray list;
	list.clear();
//	refreshDevices();  //This worked, but it would never send output to the "new" device, even though it found it.
	if (type == outputDevice)
	{
		for (int i=0; i<outDevs.size(); i++)
		{
			list.add (outDevs[i]->getProperty(Ids::name));
		}
	}
	else if (type == controllerDevice || type == inputDevice)
	{
		for (int i=0; i<inDevs.size(); i++)
		{
			list.add (inDevs[i]->getProperty(Ids::name));
		}
	}
	return (list);
}

void CtrlrMIDIDeviceManager::refreshDevices()
{
	inDevs.clear();
	outDevs.clear();

	juce::Array<juce::MidiDeviceInfo> in		= MidiInput::getAvailableDevices();
	juce::Array<juce::MidiDeviceInfo> out		= MidiOutput::getAvailableDevices();

	/*for (int i=0; i<inDevs.size(); i++)
	{
		while ( (i != inDevs.size()) && !in.contains( inDevs[i]->getName() ) )
			inDevs.remove(i);
		in.removeString( inDevs[i]->getName() );
	}*/
	for (int i=0; i<in.size(); i++)
	{
		inDevs.add (new CtrlrMIDIDevice (*this, i, in[i].name, in[i].identifier, inputDevice));
	}

	/*for (int i=0; i<outDevs.size(); i++)
	{
		while ( (i != outDevs.size()) && !out.contains( outDevs[i]->getName() ) )
			outDevs.remove(i);
		out.removeString ( outDevs[i]->getName() );
	}*/
	for (int i=0; i<out.size(); i++)
	{
		outDevs.add (new CtrlrMIDIDevice (*this, i, out[i].name, out[i].identifier, outputDevice));
	}
}

void CtrlrMIDIDeviceManager::removeListenerFromAllDevices (CtrlrMIDIDevice::Listener *l)
{
	for (int i=0; i<inDevs.size(); i++)
	{
		getDeviceByIndex(i,inputDevice)->removeDeviceListener (l);
	}
}

void CtrlrMIDIDeviceManager::processBlock (MidiBuffer& midiMessages)
{
	if (midiMessages.getNumEvents() > 0)
	{
		processingListeners.call (&CtrlrMIDIDevice::Listener::handleMIDIFromHost, midiMessages);
	}
}

void CtrlrMIDIDeviceManager::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrMIDIDeviceManager>("CtrlrMIDIDeviceManager")
			.def("getNumDevices", &CtrlrMIDIDeviceManager::getNumDevices)
			.def("getDeviceName", &CtrlrMIDIDeviceManager::getDeviceName)
			.def("isDeviceOpened", &CtrlrMIDIDeviceManager::isDeviceOpened)
			.def("getDeviceByIndex", &CtrlrMIDIDeviceManager::getDeviceByIndex)
			.def("getDeviceByName", &CtrlrMIDIDeviceManager::getDeviceByName)
			.def("getManagedDevices", &CtrlrMIDIDeviceManager::getManagedDevices)
			.def("refreshDevices", &CtrlrMIDIDeviceManager::refreshDevices)
			.enum_("CtrlrMIDIDeviceType")
			[
				value("outputDevice", outputDevice),
				value("inputDevice", inputDevice),
				value("controllerDevice", controllerDevice),
				value("hostInputDevice", hostInputDevice),
				value("hostOutputDevice", hostOutputDevice),
				value("oscInputDevice", oscInputDevice),
				value("oscOutputDevice", oscOutputDevice),
				value("serialDevice", serialDevice)
			]
			.enum_("DeviceState")
			[
				value("closed", CtrlrMIDIDeviceManager::closed),
				value("opened", CtrlrMIDIDeviceManager::opened),
				value("error", CtrlrMIDIDeviceManager::error)
			]
	];
}
