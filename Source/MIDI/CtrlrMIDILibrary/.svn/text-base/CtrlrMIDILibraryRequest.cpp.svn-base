#include "stdafx.h"
#include "CtrlrMIDILibraryRequest.h"

CtrlrMIDILibraryRequest::CtrlrMIDILibraryRequest(const CtrlrMIDILibraryAction _currentAction, const CtrlrMidiMessage _requestData, const CtrlrMIDILibraryStatus _status)
	:	data(_requestData), 
		currentAction(_currentAction), 
		status(_status),
		createdTime(Time::getCurrentTime()), 
		delay(0), 
		expectedPrefixSize(0), 
		timeout(1500), 
		matchSize(true), 
		matchPrefix(true),
		customRequestIndex(-1),
		programNumber(0),
		bankNumber(0)
{
	timestamp = Time::getHighResolutionTicks();
}

CtrlrMIDILibraryRequest::CtrlrMIDILibraryRequest(const CtrlrMIDILibraryRequest &other)
	:	currentAction(other.currentAction), 
		data(other.data), 
		status(other.status),
		createdTime(other.createdTime), 
		delay(other.delay), 
		expectedPrefixSize(other.expectedPrefixSize),
		timeout(other.timeout), 
		responseData(other.responseData), 
		timestamp(other.timestamp),
		index(other.index), 
		item(other.item), 
		dataFile(other.dataFile), 
		matchSize(other.matchSize), 
		matchPrefix(other.matchPrefix),
		customRequestIndex(other.customRequestIndex),
		programNumber(other.programNumber),
		bankNumber(other.bankNumber)
{
	expectedPrefix = MemoryBlock (other.expectedPrefix);
}

CtrlrMIDILibraryRequest::CtrlrMIDILibraryRequest(const CtrlrMIDILibraryRequest &other, const MidiMessage _response)
	:	currentAction(other.currentAction), 
		data(other.data), 
		status(other.status),
		createdTime(other.createdTime), 
		delay(other.delay), 
		expectedPrefixSize(other.expectedPrefixSize),
		timeout(other.timeout), 
		responseData(_response), 
		timestamp(other.timestamp),
		index(other.index), 
		item(other.item), 
		dataFile(other.dataFile), 
		matchSize(other.matchSize), 
		matchPrefix(other.matchPrefix),
		customRequestIndex(other.customRequestIndex),
		programNumber(other.programNumber),
		bankNumber(other.bankNumber)
{
	expectedPrefix = MemoryBlock (other.expectedPrefix);
}

CtrlrMIDILibraryRequest::CtrlrMIDILibraryRequest(const CtrlrMIDILibraryAction _currentAction, ValueTree _item, const int _customRequestIndex)
	:	currentAction(_currentAction), 
		status(ExecStop),
		createdTime(Time::getCurrentTime()), 
		delay(0), 
		expectedPrefixSize(0),
		timeout(1500), 
		timestamp(-1), 
		index(-1), 
		item(_item), 
		matchSize(true), 
		matchPrefix(true),
		customRequestIndex(_customRequestIndex),
		programNumber(0),
		bankNumber(0)
{
}

CtrlrMIDILibraryRequest::CtrlrMIDILibraryRequest (const CtrlrMidiMessage &_requestData, const CtrlrMIDILibraryAction _currentAction, ValueTree _item, const int _customRequestIndex, const CtrlrMIDILibraryStatus _status)
	:	currentAction(_currentAction), 
		status(ExecStop),
		createdTime(Time::getCurrentTime()), 
		delay(0), 
		expectedPrefixSize(0),
		timeout(1500), 
		timestamp(-1), 
		index(-1), 
		item(_item), 
		matchSize(true), 
		matchPrefix(true),
		customRequestIndex(_customRequestIndex),
		programNumber(0),
		bankNumber(0),
		data(_requestData)
{
}

const bool CtrlrMIDILibraryRequest::operator== (const CtrlrMIDILibraryRequest& other) const noexcept
{
	if (other.timestamp == timestamp)
		return (true);

	return (false);
}

void CtrlrMIDILibraryRequest::setRequestData(const CtrlrMidiMessage _requestData)
{
	data = _requestData;
}

const CtrlrMidiMessage CtrlrMIDILibraryRequest::getRequestData() const
{
	return (data);
}

void CtrlrMIDILibraryRequest::setExpectedPrefix(const MemoryBlock _expectedPrefix, const int _expectedPrefixSize)
{
	expectedPrefix		= _expectedPrefix;
	expectedPrefixSize	= (_expectedPrefixSize ? _expectedPrefixSize : (int)expectedPrefix.getSize());
}

const MemoryBlock CtrlrMIDILibraryRequest::getExpectedPrefix() const
{
	return (expectedPrefix);
}

const int CtrlrMIDILibraryRequest::getExpectedPrefixSize() const
{
	return (expectedPrefixSize);
}

void CtrlrMIDILibraryRequest::setResponseData(const CtrlrMidiMessage _responseData)
{
	responseData = _responseData;
}

const CtrlrMidiMessage CtrlrMIDILibraryRequest::getResponseData() const
{
	return (responseData);
}

void CtrlrMIDILibraryRequest::setTimeout(const double _timeout)
{
	timeout = _timeout;
}

const double CtrlrMIDILibraryRequest::getTimeout() const
{
	return (timeout);
}

void CtrlrMIDILibraryRequest::setDelay(const double _delay)
{
	delay = _delay;
}

const double CtrlrMIDILibraryRequest::getDelay() const
{
	return (delay);
}

void CtrlrMIDILibraryRequest::setCurrentAction(const CtrlrMIDILibraryAction _currentAction)
{
	currentAction = _currentAction;
}

const CtrlrMIDILibraryAction CtrlrMIDILibraryRequest::getCurrentAction() const
{
	return (currentAction);
}

void CtrlrMIDILibraryRequest::setNextAction(const CtrlrMIDILibraryAction _nextAction)
{
	nextAction = _nextAction;
}

const CtrlrMIDILibraryAction CtrlrMIDILibraryRequest::getNextAction() const
{
	return (nextAction);
}

void CtrlrMIDILibraryRequest::setItemToReferTo(ValueTree _item)
{
	item = _item;
}

ValueTree CtrlrMIDILibraryRequest::getItemToReferTo() const
{
	return (item);
}

void CtrlrMIDILibraryRequest::setDataFile(const File _dataFile)
{
	dataFile = _dataFile;
}

const File CtrlrMIDILibraryRequest::getDataFile() const
{
	return (dataFile);
}

void CtrlrMIDILibraryRequest::setStatus(const CtrlrMIDILibraryStatus _status)
{
	status = _status;
}

const CtrlrMIDILibraryStatus CtrlrMIDILibraryRequest::getStatus() const
{
	return (status);
}

void CtrlrMIDILibraryRequest::setIndex(const int _index)
{
	index = _index;
}

const int CtrlrMIDILibraryRequest::getIndex() const
{
	return (index);
}

void CtrlrMIDILibraryRequest::setErrorMessage (const String _errorMessage)
{
	errorMessage = _errorMessage;
}

const String CtrlrMIDILibraryRequest::getErrorMessage() const
{
	return (errorMessage);
}

const Time CtrlrMIDILibraryRequest::getCreatedTime() const
{
	return (createdTime);
}

void CtrlrMIDILibraryRequest::setMatchSize(const bool _matchSize)
{
	matchSize = _matchSize;
}

const bool CtrlrMIDILibraryRequest::getMatchSize() const
{
	return (matchSize);
}

void CtrlrMIDILibraryRequest::setMatchPrefix(const bool _matchPrefix)
{
	matchPrefix = _matchPrefix;
}

const bool CtrlrMIDILibraryRequest::getMatchPrefix() const
{
	return (matchPrefix);
}

const int CtrlrMIDILibraryRequest::getCustomRequestIndex() const
{
	return (customRequestIndex);
}

void CtrlrMIDILibraryRequest::setCustomRequestIndex(const int _customRequestIndex)
{
	customRequestIndex = _customRequestIndex;
}

void CtrlrMIDILibraryRequest::setProgramNumber(const int _programNumber)
{
	programNumber = _programNumber;
}

void CtrlrMIDILibraryRequest::setBankNumber(const int _bankNumber)
{
	bankNumber = _bankNumber;
}

const int CtrlrMIDILibraryRequest::getProgramNumber() const
{
	return (programNumber);
}

const int CtrlrMIDILibraryRequest::getBankNumber() const
{
	return (bankNumber);
}