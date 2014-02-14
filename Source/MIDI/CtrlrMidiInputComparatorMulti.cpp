#include "stdafx.h"
#include "CtrlrMidiInputComparatorMulti.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "JuceClasses/LMemoryBlock.h"

CtrlrMidiInputComparatorMulti::CtrlrMidiInputComparatorMulti(CtrlrPanel &_owner)
	: owner(_owner), cacheSize(32)
{
	clear();
}

CtrlrMidiInputComparatorMulti::~CtrlrMidiInputComparatorMulti()
{
	clear();
}

void CtrlrMidiInputComparatorMulti::clear()
{
	for (int i=0;i<kMidiMessageType;i++)
		messageTypesContainer.set (i,0);

	cache.clear();
	map.clear();
	messageContainer.clear();
	messageSizeContainer.clear();
	cache.ensureStorageAllocated(cacheSize);
}

void CtrlrMidiInputComparatorMulti::addMatchTarget (CtrlrModulator *m)
{
	for (int i=0; i<m->getMidiMessage().getNumMessages(); i++)
	{
		messageTypesContainer.set(midiMessageToType(m->getMidiMessage().getReference(i).m), 1);
	}

	if (!messageSizeContainer.contains(m->getMidiMessage().getData().getSize()))
	{
		messageSizeContainer.addSorted (messageSizeContainerSorter, m->getMidiMessage().getData().getSize());
	}

	BigInteger bi = memoryToBits(m->getMidiMessage().getMidiPattern());

	CtrlrMultiMidiMapIterator it = map.find(bi);

	if (it == map.end())
	{
		map.insert (CtrlrMultiMidiMapPair(bi,m));
	}
	else
	{
		map[bi].targets.add (m);
	}
}

void CtrlrMidiInputComparatorMulti::match (const MidiMessage &m)
{
	bool match = false;
	startTimer (200);

	if (!basicMatch(m))
	{
		updateState(match);
		return;
	}

	if (cacheMatch())
	{
		updateState(match);
		return;
	}

	BigInteger bi = memoryToBits(messageContainer.getData());
	CtrlrMultiMidiMapIterator it;

	for (it=map.begin(); it != map.end(); it++)
	{
		if (compareMemory ((*it).first.toMemoryBlock(), messageContainer.getData()))
		{
			match = true;

			for (int i=0; i < (*it).second.targets.size(); i++)
			{
				(*it).second.targets[i]->getProcessor().setValueFromMIDI (messageContainer);
			}

			updateCache (it);
			break;
		}
	}
	updateState(match);
}

const bool CtrlrMidiInputComparatorMulti::basicMatch(const MidiMessage &m)
{
	if (messageTypesContainer[midiMessageToType(m)] == 0)
	{
		return (false);
	}

	messageContainer.addMidiMessage (m);

	if (!messageSizeContainer.contains(messageContainer.getData().getSize()))
	{
		return (false);
	}

	return (true);
}

const bool CtrlrMidiInputComparatorMulti::cacheMatch ()
{
	bool match = false;

	for (int i=0; i<cache.size(); i++)
	{
		if (compareMemory(cache[i].key.toMemoryBlock(), messageContainer.getData()))
		{
			match = true;

			for (int j=0; j<cache[i].mapData.targets.size(); j++)
			{
				cache[i].mapData.targets[j]->getProcessor().setValueFromMIDI (messageContainer);
			}

			break;
		}
	}

	return (match);
}

void CtrlrMidiInputComparatorMulti::updateState(const bool match)
{
	if (messageContainer.getData().getSize() >= messageSizeContainer.getLast() || match)
	{
		messageContainer.clear();
	}
}

void CtrlrMidiInputComparatorMulti::updateCache (CtrlrMultiMidiMapIterator &it)
{
	CtrlrCacheDataMulti c((*it).first, (*it).second);
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

void CtrlrMidiInputComparatorMulti::timerCallback()
{
	messageContainer.clear();
	stopTimer();
}

const String CtrlrMidiInputComparatorMulti::dumpTableContents()
{
	return (String::empty);
}