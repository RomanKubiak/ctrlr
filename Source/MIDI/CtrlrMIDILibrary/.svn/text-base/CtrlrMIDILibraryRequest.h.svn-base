#ifndef __CTRLR_MIDI_LIBRARY_REQUEST__
#define __CTRLR_MIDI_LIBRARY_REQUEST__


#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrMidiMessage.h"
#include "CtrlrMidiDevice.h"

enum CtrlrMIDILibraryAction
{
	SendProgram,
	SendEditBuffer,
	SendBank,
	SendCustomData,
	SendFirmware,
	SendName,
	SendCustom,
	SendAllPrograms,

	RequestProgram,
	RequestEditBuffer,
	RequestBank,
	RequestCustomData,
	RequestFirmware,
	RequestName,
	RequestIdentity,
	RequestCustom,
	RequestAllPrograms,

	ProcessProgram,
	ProcessEditBuffer,
	ProcessBank,
	ProcessCustomData,
	ProcessFirmware,
	ProcessName,
	ProcessIdentity,
	ProcessUnknown,
	ProcessCustom,
	ProcessAllPrograms,

	ConfirmProgram,
	ConfirmEditBuffer,
	ConfirmBank,
	ConfirmCustomData,
	ConfirmFirmware,
	ConfirmName,
	ConfirmCustom,
	ConfirmAllPrograms,

	ActionUndefined
};

enum CtrlrMIDILibraryStatus
{
	ExecContinue,
	ExecStop,
	ExecCant,
	ExecReroute
};

class CtrlrMIDILibraryRequest
{
	public:
		CtrlrMIDILibraryRequest(const CtrlrMIDILibraryAction _currentAction, const CtrlrMidiMessage _requestData, const CtrlrMIDILibraryStatus _status=ExecStop);
		CtrlrMIDILibraryRequest(const CtrlrMIDILibraryRequest &other);
		CtrlrMIDILibraryRequest(const CtrlrMIDILibraryRequest &other, const MidiMessage _response);
		CtrlrMIDILibraryRequest(const CtrlrMIDILibraryAction _currentAction=ActionUndefined, ValueTree _item=ValueTree(), const int _customRequestIndex=-1);
		CtrlrMIDILibraryRequest(const CtrlrMidiMessage &_requestData, const CtrlrMIDILibraryAction _currentAction=ActionUndefined, ValueTree _item=ValueTree(), const int _customRequestIndex=-1, const CtrlrMIDILibraryStatus _status=ExecContinue);
		const bool operator== (const CtrlrMIDILibraryRequest& other) const noexcept;

		void setRequestData(const CtrlrMidiMessage _requestData);
		const CtrlrMidiMessage getRequestData() const;
		void setExpectedPrefix(const MemoryBlock _expectedPrefix, const int _expectedPrefixSize = 0);
		const MemoryBlock getExpectedPrefix() const;
		const int getExpectedPrefixSize() const;
		void setResponseData(const CtrlrMidiMessage _responseData);
		const CtrlrMidiMessage getResponseData() const;
		void setTimeout(const double _timeout = 1500);
		const double getTimeout() const;
		void setDelay(const double _delay = -1);
		const double getDelay() const;
		void setCurrentAction(const CtrlrMIDILibraryAction _currentAction);
		const CtrlrMIDILibraryAction getCurrentAction() const;
		void setNextAction(const CtrlrMIDILibraryAction _nextAction);
		const CtrlrMIDILibraryAction getNextAction() const;
		void setItemToReferTo(ValueTree _item = ValueTree());
		ValueTree getItemToReferTo() const;
		void setDataFile(const File _dataFile = File::nonexistent);
		const File getDataFile() const;
		void setStatus(const CtrlrMIDILibraryStatus _status = ExecStop);
		const CtrlrMIDILibraryStatus getStatus() const;
		void setIndex(const int _index = -1);
		const int getIndex() const;
		void setErrorMessage (const String _errorMessage);
		const String getErrorMessage() const;
		const Time getCreatedTime() const;
		void setMatchSize(const bool _matchSize);
		const bool getMatchSize() const;
		void setMatchPrefix(const bool _matchPrefix);
		const bool getMatchPrefix() const;
		const int getCustomRequestIndex() const;
		void setCustomRequestIndex(const int _customRequestIndex);
		void setProgramNumber(const int _programNumber);
		void setBankNumber(const int _bankNumber);
		const int getProgramNumber() const;
		const int getBankNumber() const;

	private:
		CtrlrMidiMessage			data, responseData;
		MemoryBlock					expectedPrefix;				// This is a MemoryBlock, a prefix will not be a valid MidiMessage, so this would cause assertions
		int							expectedPrefixSize, index, customRequestIndex;
		double						timeout, delay, timestamp;
		bool 						matchSize, matchPrefix;
		CtrlrMIDILibraryStatus		status;
		CtrlrMIDILibraryAction 		currentAction, nextAction;
		Time						createdTime;
		String						errorMessage;
		ValueTree					item;
		File						dataFile;
		int							programNumber, bankNumber;
};

#endif