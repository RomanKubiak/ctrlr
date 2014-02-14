#ifndef __CTRLR_SYSEX_PROCESSOR_OWNED__
#define __CTRLR_SYSEX_PROCESSOR_OWNED__

#include "CtrlrSysexProcessor.h"

class CtrlrSysexProcessorOwned : public CtrlrSysexProcessor
{
	public:
		CtrlrSysexProcessorOwned(CtrlrPanel &_owner);
		~CtrlrSysexProcessorOwned();
		void sysexProcessPrograms(const Array<CtrlrSysexToken> &tokens, MidiMessage &m);
		Array <int,CriticalSection> &getGlobalVariables();
		const double getValueFromSysExData (const Array<CtrlrSysexToken> &tokens, const MidiMessageEx &message);

	private:
		CtrlrPanel &owner;
};

#endif
