#ifndef __CTRLR_MANAGER_VST__
#define __CTRLR_MANAGER_VST__

#include "CtrlrModulator/CtrlrModulator.h"
class CtrlrManager;

typedef std::pair<const int,CtrlrModulator*>					CtrlrVstPair;
typedef std::multimap<const int,CtrlrModulator*>				CtrlrVstMap;
typedef std::multimap<const int,CtrlrModulator*>::iterator		CtrlrVstMapIterator;

class CtrlrManagerVst
{
	public:
		CtrlrManagerVst(CtrlrManager &_owner);
		~CtrlrManagerVst();
		void remove(CtrlrModulator *mod);
		CtrlrModulator* get(const int idx);
		const int getFirstFree();
		const int size();
		const int getLargestIndex();
		void set(CtrlrModulator *mod, const int idx = 0);
		void dumpDebugData();
		void removeIfAlreadyThere(CtrlrModulator *mod);
		JUCE_LEAK_DETECTOR(CtrlrManagerVst)

	private:
		Array<int> vsti;
		CtrlrManager &owner;
		CtrlrVstMap map;
};

#endif
