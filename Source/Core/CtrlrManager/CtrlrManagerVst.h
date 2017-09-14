#ifndef __CTRLR_MANAGER_VST__
#define __CTRLR_MANAGER_VST__

#include <map>
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
		int getFirstFree();
		int size();
		int getLargestIndex();
		void set(CtrlrModulator *mod, const int idx = -1);
		void dumpDebugData();
		void removeIfAlreadyThere(CtrlrModulator *mod);
		bool isAlreadyIndexed(CtrlrModulator *mod);
		JUCE_LEAK_DETECTOR(CtrlrManagerVst)

	private:
		Array<int> vstIndexes;
		CtrlrManager &owner;
		CtrlrVstMap map;
};

#endif
