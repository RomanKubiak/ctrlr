#include "stdafx.h"
#include "CtrlrMidiInputComparatorSingle.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "JuceClasses/LMemoryBlock.h"

CtrlrMidiInputComparatorSingle::CtrlrMidiInputComparatorSingle(CtrlrPanel &_owner)
	: owner(_owner), cacheSize(32)
{
	clear();
}

CtrlrMidiInputComparatorSingle::~CtrlrMidiInputComparatorSingle()
{
	clear();
}

void CtrlrMidiInputComparatorSingle::clear()
{
	mapCC.clear();
	mapAftertouch.clear();
	mapPitchWheel.clear(); 
	mapProgramChange.clear();
	mapNoteOn.clear();
	mapNoteOff.clear();
	mapChannelPressure.clear();
	mapSysEx.clear();
	mapNull.clear();
	cacheCC.clear();
	cacheAftertouch.clear();
	cachePitchWheel.clear();
	cacheProgramChange.clear();
	cacheNoteOn.clear();
	cacheNoteOff.clear();
	cacheChannelPressure.clear();
	cacheSysEx.clear();
	cacheNull.clear();
	messageContainer.clear();
}

CtrlrMidiMap &CtrlrMidiInputComparatorSingle::getMap(const CtrlrMidiMessageType t)
{
	switch (t)
	{
	case CC:
		return (mapCC);
	case PitchWheel:
		return (mapPitchWheel);
	case NoteOn:
		return (mapNoteOn);
	case NoteOff:
		return (mapNoteOff);
	case Aftertouch:
		return (mapAftertouch);
	case ProgramChange:
		return (mapProgramChange);
	case ChannelPressure:
		return (mapChannelPressure);
	default:
		return (mapNull);
	}
}

Array<CtrlrCacheDataSingle> &CtrlrMidiInputComparatorSingle::getCache(const CtrlrMidiMessageType t)
{
	switch (t)
	{
	case CC:
		return (cacheCC);
	case PitchWheel:
		return (cachePitchWheel);
	case NoteOn:
		return (cacheNoteOn);
	case NoteOff:
		return (cacheNoteOff);
	case Aftertouch:
		return (cacheAftertouch);
	case ProgramChange:
		return (cacheProgramChange);
	case ChannelPressure:
		return (cacheChannelPressure);
	default:
		return (cacheNull);
	}
}

void CtrlrMidiInputComparatorSingle::addMatchTarget (CtrlrModulator *m)
{	
	const CtrlrMidiMessageType type = getMidiTypeFromModulator(m);

	if (type == SysEx)
	{
		addMatchTargetSysEx(m);
		return;
	}

	CtrlrMidiMap &map		= getMap(type);
	CtrlrMidiMapIterator it = map.find(getMidiNumberFromModulator(m));

	if (it == map.end())
	{
		map.insert (CtrlrMidiMapPair(getMidiNumberFromModulator(m),m));
	}
	else
	{
		map[getMidiNumberFromModulator(m)].targets.add (m);
	}
}

void CtrlrMidiInputComparatorSingle::addMatchTargetSysEx (CtrlrModulator *m)
{
	BigInteger bi = memoryToBits(m->getMidiMessage().getMidiPattern());

	CtrlrMultiMidiMapIterator it = mapSysEx.find(bi);

	if (it == mapSysEx.end())
	{
		mapSysEx.insert (CtrlrMultiMidiMapPair(bi,m));
	}
	else
	{
		mapSysEx[bi].targets.add (m);
	}
}

void CtrlrMidiInputComparatorSingle::match (const MidiMessage &m)
{
	messageContainer			= m;
	CtrlrMidiMessageType type	= midiMessageToType(m);
	int channel					= m.getChannel();
	int number					= getMidiNumberFromMidiMessage(m);

	if (cacheMatch(type, number, channel))
	{
		return;
	}

	if (type == SysEx)
	{
		matchSysEx(m);		
		return;
	}

	CtrlrMidiMap &map = getMap(type);

	if (map.size() != 0)
	{
		CtrlrMidiMapIterator it = map.find (number);

		if (it != map.end())
		{
			for (int i=0; i < (*it).second.targets.size(); i++)
			{
				if (m.getChannel() == (*it).second.targets[i]->getMidiMessage().getChannel())
				{
					(*it).second.targets[i]->getProcessor().setValueFromMIDI (messageContainer);

					updateCache (type, it);
				}
			}
		}
	}
}

void CtrlrMidiInputComparatorSingle::matchSysEx(const MidiMessage &m)
{
	BigInteger bi = memoryToBits(MemoryBlock(m.getRawData(), m.getRawDataSize()));

	CtrlrMultiMidiMapIterator it;

	for (it=mapSysEx.begin(); it != mapSysEx.end(); it++)
	{
		if (compareMemory ((*it).first.toMemoryBlock(), messageContainer.getData()))
		{
			for (int i=0; i < (*it).second.targets.size(); i++)
			{
				(*it).second.targets[i]->getProcessor().setValueFromMIDI (messageContainer);
			}

			updateCacheSysEx (it);
			break;
		}
	}
}

void CtrlrMidiInputComparatorSingle::updateCache (const CtrlrMidiMessageType t, CtrlrMidiMapIterator &it)
{
	CtrlrCacheDataSingle c((*it).first, (*it).second);
	Array<CtrlrCacheDataSingle>	&cache = getCache(t);

	if (cache.contains (c))
	{
		if (cache.indexOf (c) == 0)
			return;
		else
		{
			cache.swap (cache.indexOf(c), 0);
		}
	}
	else
	{
		cache.insert (0, c);
		cache.resize (cacheSize);
	}
}

void CtrlrMidiInputComparatorSingle::updateCacheSysEx (CtrlrMultiMidiMapIterator &it)
{
	CtrlrCacheDataMulti c((*it).first, (*it).second);
	if (cacheSysEx.contains (c))
	{
		if (cacheSysEx.indexOf (c) == 0)
			return;
		else
		{
			cacheSysEx.swap (cacheSysEx.indexOf(c), 0);
		}
	}
	else
	{
		cacheSysEx.insert (0, c);
		cacheSysEx.resize (cacheSize);
	}
}

const bool CtrlrMidiInputComparatorSingle::cacheMatch(CtrlrMidiMessageType type, const int number, const int channel)
{
	if (type == SysEx)
	{
		return (cacheMatchSysEx());
	}

	Array<CtrlrCacheDataSingle>	&cache	= getCache(type);

	for (int i=0; i<cache.size(); i++)
	{
		if (cache[i].key == number)
		{
			for (int j=0; j<cache[i].mapData.targets.size(); j++)
			{
				if (cache[i].mapData.targets[j]->getMidiMessage().getChannel() == channel)
				{
					cache[i].mapData.targets[j]->getProcessor().setValueFromMIDI (messageContainer);
					return (true);
				}
				else
				{
					return (false);
				}
			}
		}
		else
		{
			return (false);
		}
	}
	return (false);
}

const bool CtrlrMidiInputComparatorSingle::cacheMatchSysEx ()
{
	for (int i=0; i<cacheSysEx.size(); i++)
	{
		if (compareMemory(cacheSysEx[i].key.toMemoryBlock(), messageContainer.getData()))
		{
			for (int j=0; j<cacheSysEx[i].mapData.targets.size(); j++)
			{
				cacheSysEx[i].mapData.targets[j]->getProcessor().setValueFromMIDI (messageContainer);
			}

			return (true);
		}
	}
	return (false);
}

const String CtrlrMidiInputComparatorSingle::dumpTableContents()
{
	String ret;

	for (int i=0; i<kMidiMessageType; i++)
	{
		CtrlrMidiMap &map = getMap((const CtrlrMidiMessageType)i);

		if (&map != &mapNull)
		{
			ret << "\n\nMAP type: " << midiMessageTypeToString((const CtrlrMidiMessageType)i) << ", size=" << STR((uint32)map.size());
			ret << "\n*****************************************************************************\n";
		
			for(CtrlrMidiMapIterator itr = map.begin(); itr != map.end(); ++itr)
			{
				ret << "\n\tindex=" << String(itr->first) << " targets=" << String(itr->second.targets.size());
				for (int j=0; j<itr->second.targets.size(); j++)
				{
					ret << "\n\t\ttarget=" << itr->second.targets[j]->getName();
				}
			}
			ret << "\n*****************************************************************************\n";
		}
	}

	ret << "\n\nMAP SysEx " << "size=" << STR((uint32)mapSysEx.size());
	ret << "\n*****************************************************************************\n";
	for(CtrlrMultiMidiMapIterator itr = mapSysEx.begin(); itr != mapSysEx.end(); ++itr)
	{
		MemoryBlock bl = itr->first.toMemoryBlock();
		ret << "\n\tindex=" << String::toHexString (bl.getData(), bl.getSize(), 1) << " targets=" << String(itr->second.targets.size());
		for (int j=0; j<itr->second.targets.size(); j++)
		{
			ret << "\n\t\ttarget=" << itr->second.targets[j]->getName();
		}
	}
	ret << "\n*****************************************************************************\n";
	return (ret);
}