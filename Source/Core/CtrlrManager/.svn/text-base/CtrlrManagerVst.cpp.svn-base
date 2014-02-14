#include "stdafx.h"
#include "CtrlrManagerVst.h"
#include "CtrlrIDs.h"
#include "CtrlrLog.h"
#include "CtrlrManager.h"

CtrlrManagerVst::CtrlrManagerVst(CtrlrManager &_owner) : owner(_owner)
{
}

CtrlrManagerVst::~CtrlrManagerVst()
{
}

const int CtrlrManagerVst::size ()
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

	removeIfAlreadyThere (mod);
	vsti.addUsingDefaultSort (idx);
	map.insert (CtrlrVstPair(idx,mod));
}

void CtrlrManagerVst::removeIfAlreadyThere(CtrlrModulator *mod)
{
	for (CtrlrVstMapIterator it=map.begin(); it!=map.end(); ++it)
	{
		if (it->second == mod)
		{
			vsti.removeFirstMatchingValue (it->first);
			map.erase (it);
			return;
		}
	}
}

CtrlrModulator *CtrlrManagerVst::get(const int idx)
{
	CtrlrVstMapIterator it = map.find (idx);

	if (it != map.end())
		return (it->second);
	else
		return (nullptr);
}

const int CtrlrManagerVst::getFirstFree()
{
	return ((int)map.size());
}

const int CtrlrManagerVst::getLargestIndex()
{
	return (vsti.getLast());
}

void CtrlrManagerVst::dump()
{
	_DBG("CtrlrManagerVst::dump");

	_DBG("---------- modulators by vst indexes ----------");

	for (CtrlrVstMapIterator it=map.begin(); it!=map.end(); ++it)
	{
		_DBG("["+STR(it->first)+"]: "+it->second->getName());
	}

	_DBG("\t largest index "+STR(getLargestIndex()));
	_DBG("---------- modulators by vst indexes ----------");
}
