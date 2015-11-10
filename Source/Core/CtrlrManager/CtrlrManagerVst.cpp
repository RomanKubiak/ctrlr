#include "stdafx.h"
#include "CtrlrManagerVst.h"
#include "CtrlrIDs.h"
#include "CtrlrLog.h"
#include "CtrlrManager.h"

CtrlrManagerVst::CtrlrManagerVst(CtrlrManager &_owner) : owner(_owner)
{
	_DBG("CtrlrManagerVst::ctor");
}

CtrlrManagerVst::~CtrlrManagerVst()
{
	_DBG("CtrlrManagerVst::dtor");
}

int CtrlrManagerVst::size ()
{
	return ((int)map.size());
}

void CtrlrManagerVst::remove(CtrlrModulator *mod)
{
	removeIfAlreadyThere (mod);
}

void CtrlrManagerVst::set(CtrlrModulator *mod, const int idx)
{
	if ((bool)mod->getProperty (Ids::modulatorVstExported) == false)
	{
		return;
	}

    if (isAlreadyIndexed(mod) && idx == -1)
	{
		return;
	}

	removeIfAlreadyThere (mod);
	vstIndexes.addUsingDefaultSort (idx);
	map.insert (CtrlrVstPair(idx,mod));
}

bool CtrlrManagerVst::isAlreadyIndexed(CtrlrModulator *mod)
{
    for (CtrlrVstMapIterator it=map.begin(); it!=map.end(); ++it)
	{
		if (it->second == mod)
		{
			return (true);
		}
	}
	return (false);
}

void CtrlrManagerVst::removeIfAlreadyThere(CtrlrModulator *mod)
{
	for (CtrlrVstMapIterator it=map.begin(); it!=map.end(); ++it)
	{
		if (it->second == mod)
		{
			vstIndexes.removeFirstMatchingValue (it->first);
			map.erase (it);
			return;
		}
	}
}

CtrlrModulator *CtrlrManagerVst::get(const int idx)
{
	CtrlrVstMapIterator it = map.find (idx);

	if (it != map.end())
	{
		return (it->second);
	}
	else
	{
		return (nullptr);
	}
}

int CtrlrManagerVst::getFirstFree()
{
    /* kamder fix */
    if (vstIndexes.size() == 0)
		return (0);

	return (vstIndexes.getLast() + 1);
}

int CtrlrManagerVst::getLargestIndex()
{
	return (vstIndexes.getLast());
}

void CtrlrManagerVst::dumpDebugData()
{
	_DBG("CtrlrManagerVst::dumpDebugData");

	_DBG("---------- modulators by vst indexes ----------");

	for (CtrlrVstMapIterator it=map.begin(); it!=map.end(); ++it)
	{
		_DBG("["+STR(it->first)+"]: "+it->second->getName());
	}

	_DBG("\t largest index "+STR(getLargestIndex()));
	_DBG("---------- modulators by vst indexes ----------");
}
