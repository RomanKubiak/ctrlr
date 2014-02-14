#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrMidiDeviceManager.h"
#include "CtrlrProcessor.h"
#include "CtrlrMacros.h"
#include "CtrlrMidiDevice.h"
#include "CtrlrLog.h"
#include "CtrlrUtilities.h"

CtrlrMidiDeviceManager::CtrlrMidiDeviceManager(CtrlrManager &_owner) 
	:	managerTree(Ids::midiDeviceManager),
		owner(_owner)
{
	inDevs.clear();
	outDevs.clear();
	refreshDevices();
}

CtrlrMidiDeviceManager::~CtrlrMidiDeviceManager()
{	
	processingListeners.clear();
	inDevs.clear();
	outDevs.clear();
}

const int CtrlrMidiDeviceManager::getNumDevices(const DeviceType type)
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

const String CtrlrMidiDeviceManager::getDeviceName(const int idx, const DeviceType type)
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

const bool CtrlrMidiDeviceManager::isDeviceOpened(const int idx, const DeviceType type)
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

const bool CtrlrMidiDeviceManager::toggleDevice (const int idx, const DeviceType type, const bool state)
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

void CtrlrMidiDeviceManager::restoreState (const ValueTree &savedState)
{
}

CtrlrMidiDevice *CtrlrMidiDeviceManager::getDeviceByName(const String name, const DeviceType type, const bool openIfClosed)
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

CtrlrMidiDevice *CtrlrMidiDeviceManager::getDeviceByIndex(const int idx, const DeviceType type)
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

void CtrlrMidiDeviceManager::reloadComboContents (ComboBox &comboToUpdate, const DeviceType type)
{
//	refreshDevices();  //This worked, but it would never send output to the "new" device, even though it found it.
	comboToUpdate.clear();
	if (type == outputDevice)
	{ 
		comboToUpdate.addItem (COMBO_NONE_ITEM, 1);
		for (int i=0; i<outDevs.size(); i++)
		{
			comboToUpdate.addItem (outDevs[i]->getProperty(Ids::name).toString(), i+2);
		}
	}
	else if (type == controllerDevice || type == inputDevice)
	{
		comboToUpdate.addItem (COMBO_NONE_ITEM, 1);
		for (int i=0; i<inDevs.size(); i++)
		{		
			comboToUpdate.addItem (inDevs[i]->getProperty(Ids::name).toString(), i+2);
		}
	}
}

const StringArray CtrlrMidiDeviceManager::getManagedDevices(const DeviceType type)
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

void CtrlrMidiDeviceManager::refreshDevices()
{
//	inDevs.clear();
//	outDevs.clear();

	StringArray in		= MidiInput::getDevices();
	StringArray out		= MidiOutput::getDevices();

	for (int i=0; i<inDevs.size(); i++)
	{
		while ( (i != inDevs.size()) && !in.contains( inDevs[i]->getName() ) )
			inDevs.remove(i);
		in.removeString( inDevs[i]->getName() );
	}
	for (int i=0; i<in.size(); i++)
	{
		inDevs.add (new CtrlrMidiDevice (*this, i, in[i], inputDevice));
	}

	for (int i=0; i<outDevs.size(); i++)
	{
		while ( (i != outDevs.size()) && !out.contains( outDevs[i]->getName() ) )
			outDevs.remove(i);
		out.removeString ( outDevs[i]->getName() );
	}
	for (int i=0; i<out.size(); i++)
	{
		outDevs.add (new CtrlrMidiDevice (*this, i, out[i], outputDevice));
	}
}

void CtrlrMidiDeviceManager::removeListenerFromAllDevices (CtrlrMidiDevice::Listener *l)
{
	for (int i=0; i<inDevs.size(); i++)
	{
		getDeviceByIndex(i,inputDevice)->removeDeviceListener (l);
	}
}

void CtrlrMidiDeviceManager::processBlock (MidiBuffer& midiMessages)
{
	if (midiMessages.getNumEvents() > 0)
	{
		processingListeners.call (&CtrlrMidiDevice::Listener::handleMIDIFromHost, midiMessages);
	}
}