#ifndef CTRLR_MIDI_TRANSACTION_H
#define CTRLR_MIDI_TRANSACTION_H

#include "CtrlrMacros.h"
#include "Lua/Methods/CtrlrLuaMethod.h"

class CtrlrMIDILibrary;

class CtrlrMIDITransaction : public ValueTree::Listener, public AsyncUpdater, public Timer, public ChangeBroadcaster
{
	public:
		CtrlrMIDITransaction (CtrlrMIDILibrary &_owner);
		~CtrlrMIDITransaction();
		void setProperty (const Identifier& name, const var &newValue, const bool isUndoable=false)		{ transactionState.setProperty (name, newValue, 0); }
		const var &getProperty (const Identifier& name) const											{ return transactionState.getProperty (name); }
		const var getProperty (const Identifier& name, const var &defaultReturnValue) const				{ return transactionState.getProperty (name, defaultReturnValue); }
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
		void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
		void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
		void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
		void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
		void restoreState (const ValueTree &savedState);
		const String getName();
		const bool getHasResponse();
		void setHasResponse(const bool _hasResponse);
		void setHasDataCheck(const bool _hasDataCheck);
		const bool getHasDataCheck();
		void setHasSizeCheck(const bool _hasSizeCheck);
		const bool getHasSizeCheck();
		const String getAdditionalExitData();
		void setAdditionalExitData(const String &_additionalExitData);
		const int getTimeout();
		void setTimeout (const int _timeout);
		void constructRequest();
		void constructResponseMask();
		void constructConfirmation();
		void handleAsyncUpdate();
		void timerCallback();
		const MemoryBlock getFormulaAsMemoryBlock(const String &formula);
		const MemoryBlock getDataFromResponse(const MidiMessage &messageToExtractFrom);
		const size_t getResponsePrefixLength();
		const size_t getResponseDataLength();
		const size_t getDataLengthFromFormula(const String &formula);
		MemoryBlock getResponseReceived();
		MemoryBlock getRequest();
		MemoryBlock getResponseMask();
		void setResponseReceived(const MidiMessage &response);
		void setResponseReceived(const MemoryBlock &response);
		void setRequest(const MidiMessage &request);
		void setRequest(const MemoryBlock &request);
		void setResponseMask(const MemoryBlock &responseMask);
		void checkPossibleResponse(const MidiMessage &responseToCheck);
		const bool sendRequest();
		void setTransactionItem(ValueTree _transactionItem);
		ValueTree &getTransactionItem();
		const bool canHandleItem(const ValueTree _transactionItem=ValueTree::invalid);
		const bool canHandleItemType(const Identifier &itemType);
		MemoryBlock getRequestDataAsMemoryBlock();
		MemoryBlock getConfirmationDataAsMemoryBlock();
		MemoryBlock getNameAsMemoryBlock();
		MemoryBlock getDataFromCurrentResponse();

		static const bool compareMemoryWithWildcard(const MidiMessage &midi, const MemoryBlock &memory);
		static ValueTree createEmptyTransactionTree(const String &transactionName);
		static void wrapForLua (lua_State *L);

		JUCE_LEAK_DETECTOR(CtrlrMIDITransaction)

	private:
		CtrlrMIDILibrary &owner;
		ReadWriteLock transactionLock;
		String name;
		Time startTime, endTime;
		bool hasSizeCheck, hasDataCheck, hasRequest, hasResponse, hasStaticDataConstruction;
		int timeout;
		size_t responsePrefixLength, responseDataLength;
		MemoryBlock expectedResponseMask, requestToSend, responseReceived;
		ValueTree transactionState;
		ValueTree transactionItem;
		String additionalExitData;
		WeakReference <CtrlrLuaMethod> 	luaTransProcessCbk,
										luaTransDataUnpackCbk,
										luaTransRequestCbk,
										luaTransDataPackCbk,
										luaTransRequestDataCbk,
										luaTransConfDataCbk,
										luaTransResponseDataCbk,
										luaTransTimeoutCbk,
										luaTransNameDataCbk;
};

#endif
