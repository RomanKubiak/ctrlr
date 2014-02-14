#include "stdafx.h"
#include "CtrlrMIDITransaction.h"
#include "CtrlrMIDILibrary/CtrlrMIDILibrary.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "Lua/CtrlrLuaManager.h"
#include "Lua/JuceClasses/LMemoryBlock.h"

CtrlrMIDITransaction::CtrlrMIDITransaction (CtrlrMIDILibrary &_owner)
	: owner(_owner), transactionState(Ids::trans)
{
	transactionState.addListener (this);
}

CtrlrMIDITransaction::~CtrlrMIDITransaction()
{
	_TRANS("["+getName()+"] end");
	transactionState.removeListener (this);
}

void CtrlrMIDITransaction::restoreState (const ValueTree &savedState)
{
	ScopedWriteLock slw(transactionLock);
	restoreProperties (savedState, transactionState);
}

void CtrlrMIDITransaction::setTransactionItem(ValueTree _transactionItem)
{
	ScopedWriteLock slw(transactionLock);
	transactionItem = _transactionItem;
}

ValueTree &CtrlrMIDITransaction::getTransactionItem()
{
	ScopedReadLock slr(transactionLock);
	return (transactionItem);
}

void CtrlrMIDITransaction::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	ScopedWriteLock slw(transactionLock);

	if (property == Ids::name)
	{
		name = getProperty(property);
	}
	else if (property == Ids::timeout)
	{
		timeout = getProperty(property);
	}
	else if (property.toString().startsWith("transReq"))
	{
		if (property == Ids::transReqFormulaPrefix || property == Ids::transReqFormulaSuffix)
		{
			constructRequest();
		}
	}
	else if (property.toString().startsWith("transResp"))
	{
		constructResponseMask();

		if (property == Ids::transRespFormulaPrefix)
		{
			responsePrefixLength = getDataLengthFromFormula(getProperty(property));
		}
		else if (property == Ids::transRespDataLen)
		{
			responseDataLength = (int)getProperty(property);
		}
		else if (property == Ids::transRespDataCheck)
		{
			setHasDataCheck(getProperty(property));
		}
		else if (property == Ids::transRespSizeCheck)
		{
			setHasSizeCheck(getProperty(property));
		}
		else if (property == Ids::transRespExists)
		{
			setHasResponse ((bool)getProperty(property));
		}
	}
	else if (property.toString().startsWith("transConf"))
	{
		constructConfirmation();
	}
	else if (property == Ids::luaTransProcess)
	{
		luaTransProcessCbk 		= owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaTransDataUnpack)
	{
		luaTransDataUnpackCbk 	= owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaTransRequest)
	{
		luaTransRequestCbk 		= owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaTransDataPack)
	{
		luaTransDataPackCbk		= owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaTransRequestData)
	{
		luaTransRequestDataCbk		= owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaTransResponseData)
	{
		luaTransResponseDataCbk		= owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaTransConfData)
	{
		luaTransConfDataCbk		= owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaTransTimeout)
	{
		luaTransTimeoutCbk		= owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::luaTransNameData)
	{
		luaTransNameDataCbk		= owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::transReqExists)
	{
		hasRequest = getProperty(property);
	}
	else if (property == Ids::transRespExists)
	{
		hasResponse = getProperty(property);
	}
}

const String CtrlrMIDITransaction::getName()
{
	ScopedReadLock slr(transactionLock);
	return (name);
}

const int CtrlrMIDITransaction::getTimeout()
{
	ScopedReadLock slr(transactionLock);
	return (timeout);
}

const bool CtrlrMIDITransaction::getHasResponse()
{
	ScopedReadLock slr(transactionLock);
	return (hasResponse);
}

void CtrlrMIDITransaction::setHasResponse(const bool _hasResponse)
{
	ScopedReadLock slr(transactionLock);
	hasResponse = _hasResponse;
}

void CtrlrMIDITransaction::setTimeout (const int _timeout)
{
	ScopedWriteLock slr(transactionLock);
	timeout = _timeout;
}

void CtrlrMIDITransaction::setHasDataCheck(const bool _hasDataCheck)
{
	ScopedReadLock slr(transactionLock);
	hasDataCheck = _hasDataCheck;
}

const bool CtrlrMIDITransaction::getHasDataCheck()
{
	ScopedReadLock slr(transactionLock);
	return (hasDataCheck);
}

void CtrlrMIDITransaction::setHasSizeCheck(const bool _hasSizeCheck)
{
	ScopedReadLock slr(transactionLock);
	hasSizeCheck = _hasSizeCheck;
}

const bool CtrlrMIDITransaction::getHasSizeCheck()
{
	ScopedReadLock slr(transactionLock);
	return (hasSizeCheck);
}

const size_t CtrlrMIDITransaction::getResponsePrefixLength()
{
	ScopedReadLock slr(transactionLock);
	return (responsePrefixLength);
}

const size_t CtrlrMIDITransaction::getResponseDataLength()
{
	ScopedReadLock slr(transactionLock);
	return (responseDataLength);
}

MemoryBlock CtrlrMIDITransaction::getResponseReceived()
{
	ScopedReadLock slr(transactionLock);
	return (responseReceived);
}

MemoryBlock CtrlrMIDITransaction::getRequest()
{
	ScopedReadLock slr(transactionLock);
	return (requestToSend);
}

MemoryBlock CtrlrMIDITransaction::getResponseMask()
{
	ScopedReadLock slr(transactionLock);
	return (expectedResponseMask);
}

const String CtrlrMIDITransaction::getAdditionalExitData()
{
	ScopedReadLock slr(transactionLock);
	return (additionalExitData);
}

void CtrlrMIDITransaction::setAdditionalExitData(const String &_additionalExitData)
{
	ScopedReadLock slr(transactionLock);
	additionalExitData = _additionalExitData;
}

void CtrlrMIDITransaction::setResponseReceived(const MidiMessage &response)
{
	ScopedWriteLock slw(transactionLock);
	responseReceived = MemoryBlock(response.getRawData(), response.getRawDataSize());
}

void CtrlrMIDITransaction::setResponseReceived(const MemoryBlock &response)
{
	ScopedWriteLock slw(transactionLock);
	responseReceived = response;
}

void CtrlrMIDITransaction::setRequest(const MidiMessage &request)
{
	ScopedWriteLock slw(transactionLock);
	requestToSend = MemoryBlock(request.getRawData(), request.getRawDataSize());
}

void CtrlrMIDITransaction::setRequest(const MemoryBlock &request)
{
	ScopedWriteLock slw(transactionLock);
	requestToSend = request;
}

void CtrlrMIDITransaction::setResponseMask(const MemoryBlock &responseMask)
{
	ScopedWriteLock slw(transactionLock);
	expectedResponseMask = responseMask;
}

const MemoryBlock CtrlrMIDITransaction::getFormulaAsMemoryBlock(const String &formula)
{
	if (formula.isEmpty())
	{
		return (MemoryBlock());
	}

	CtrlrOwnedMidiMessage m(owner.getOwner());
	m.setProperty (Ids::midiMessageType, SysEx);

	if (formula.endsWithIgnoreCase ("f7"))
	{
		m.setProperty (Ids::midiMessageSysExFormula, formula);
		m.setValue (0);
		return (m.getData());
	}
	else
	{
		m.setProperty (Ids::midiMessageSysExFormula, formula+" f7");
		m.setValue (0);
		return (MemoryBlock(m.getData().getData(), m.getData().getSize()-1));
	}
}

const MemoryBlock CtrlrMIDITransaction::getDataFromResponse(const MidiMessage &messageToExtractFrom)
{
	MemoryBlock returnData;
	MemoryBlock temp(messageToExtractFrom.getRawData(), messageToExtractFrom.getRawDataSize());

	returnData.copyFrom (temp.getData(), getResponsePrefixLength(), getResponseDataLength());
	return (returnData);
}

MemoryBlock CtrlrMIDITransaction::getDataFromCurrentResponse()
{
	MemoryBlock returnData;

	if (responseReceived.getSize() > 0)
	{
		returnData.copyFrom (responseReceived.getData(), getResponsePrefixLength(), getResponseDataLength());
	}

	return (returnData);
}

const size_t CtrlrMIDITransaction::getDataLengthFromFormula(const String &formula)
{
	MemoryBlock bl;
	bl.loadFromHexString (formula);
	return (bl.getSize());
}

const bool CtrlrMIDITransaction::compareMemoryWithWildcard(const MidiMessage &midi, const MemoryBlock &memory)
{
	const uint8 *responsePtr = midi.getRawData();

	for (size_t i=0; i<memory.getSize(); i++)
	{
		if (memory[i] == 0xff)
			continue;

		if (*(responsePtr+i) != memory[i])
			return (false);
	}

	return (true);
}

ValueTree CtrlrMIDITransaction::createEmptyTransactionTree(const String &transactionName)
{
	ValueTree transaction(Ids::trans);
	transaction.setProperty (Ids::name, transactionName.isEmpty() ? "Transaction" : transactionName, nullptr);
	transaction.setProperty (Ids::timeout, 2000, nullptr);
	transaction.setProperty (Ids::transCap, "midiLibraryProgram", nullptr);
	transaction.setProperty (Ids::transModIdxProp, "modulatorCustomIndex", nullptr);
	
	transaction.setProperty (Ids::transReqExists, false, nullptr);
	transaction.setProperty (Ids::transReqFormulaPrefix, "F7", nullptr);
	transaction.setProperty (Ids::transReqFormulaSuffix, "F7", nullptr);
	transaction.setProperty (Ids::transReqDataLen, 0, nullptr);
	transaction.setProperty (Ids::transReqNameOffset, 0, nullptr);
	transaction.setProperty (Ids::transReqNameLen, 0, nullptr);

	transaction.setProperty (Ids::transRespExists, false, nullptr);
	transaction.setProperty (Ids::transRespFormulaPrefix, "F0", nullptr);
	transaction.setProperty (Ids::transRespFormulaSuffix, "F7", nullptr);
	transaction.setProperty (Ids::transRespDataCheck, true, nullptr);
	transaction.setProperty (Ids::transRespSizeCheck, true, nullptr);
	transaction.setProperty (Ids::transRespDataLen, 0, nullptr);
	transaction.setProperty (Ids::transRespNameOffset, 0, nullptr);
	transaction.setProperty (Ids::transRespNameLen, 0, nullptr);

	transaction.setProperty (Ids::transConfExists, false, nullptr);
	transaction.setProperty (Ids::transConfFormulaPrefix, "F0", nullptr);
	transaction.setProperty (Ids::transConfFormulaSuffix, "F7", nullptr);
	transaction.setProperty (Ids::transConfDataLen, 0, nullptr);

	transaction.setProperty (Ids::luaTransDataUnpack, String::empty, nullptr);
	transaction.setProperty (Ids::luaTransDataPack, String::empty, nullptr);
	transaction.setProperty (Ids::luaTransNameData, String::empty, nullptr);
	transaction.setProperty (Ids::luaTransRequestData, String::empty, nullptr);
	transaction.setProperty (Ids::luaTransResponseData, String::empty, nullptr);
	transaction.setProperty (Ids::luaTransConfData, String::empty, nullptr);
	transaction.setProperty (Ids::luaTransProcess, String::empty, nullptr);
	transaction.setProperty (Ids::luaTransRequest, String::empty, nullptr);
	transaction.setProperty (Ids::luaTransTimeout, String::empty, nullptr);
	transaction.setProperty (Ids::luaTransInfo, String::empty, nullptr);
	return (transaction);
}

void CtrlrMIDITransaction::constructRequest()
{
	MemoryBlock request;

	MemoryBlock prefix 	= getFormulaAsMemoryBlock(getProperty(Ids::transReqFormulaPrefix));
	MemoryBlock data   	= getRequestDataAsMemoryBlock();
	MemoryBlock suffix 	= getFormulaAsMemoryBlock(getProperty(Ids::transReqFormulaSuffix));
	MemoryBlock name 	= getNameAsMemoryBlock();

	if (data.getSize() < name.getSize())
	{
		TRANS("["+getName()+"] CtrlrMIDITransaction::constructRequest data block will not fit name");
	}

	if (prefix.getSize() > 0)
	{
		request.append (prefix.getData(), prefix.getSize());
	}

	if (data.getSize() > 0)
	{
		request.append (data.getData(), data.getSize());
	}

	if (suffix.getSize() > 0)
	{
		request.append (suffix.getData(), suffix.getSize());
	}

	setRequest (request);
}

void CtrlrMIDITransaction::constructResponseMask()
{
	MemoryBlock responseMask;

	MemoryBlock prefix 	= getFormulaAsMemoryBlock(getProperty(Ids::transRespFormulaPrefix));
	MemoryBlock data((int)getProperty(Ids::transRespDataLen), true);
	MemoryBlock suffix 	= getFormulaAsMemoryBlock(getProperty(Ids::transRespFormulaSuffix));
	MemoryBlock name	= getNameAsMemoryBlock();

	if (data.getSize() < name.getSize())
	{
		TRANS("["+getName()+"] CtrlrMIDITransaction::constructResponseMask data block will not fit name");
	}

	if (prefix.getSize() > 0)
	{
		responseMask.append (prefix.getData(), prefix.getSize());
	}

	if (data.getSize() > 0)
	{
		responseMask.append (data.getData(), data.getSize());
	}

	if (suffix.getSize() > 0)
	{
		responseMask.append (suffix.getData(), suffix.getSize());
	}

	setResponseMask (responseMask);
}

void CtrlrMIDITransaction::constructConfirmation()
{
	MemoryBlock request;

	MemoryBlock prefix 	= getFormulaAsMemoryBlock(getProperty(Ids::transConfFormulaPrefix));
	MemoryBlock data   	= getConfirmationDataAsMemoryBlock();
	MemoryBlock suffix 	= getFormulaAsMemoryBlock(getProperty(Ids::transConfFormulaSuffix));

	if (prefix.getSize() > 0)
	{
		request.append (prefix.getData(), prefix.getSize());
	}

	if (data.getSize() > 0)
	{
		request.append (data.getData(), data.getSize());
	}

	if (suffix.getSize() > 0)
	{
		request.append (suffix.getData(), suffix.getSize());
	}

	setRequest (request);
}

MemoryBlock CtrlrMIDITransaction::getRequestDataAsMemoryBlock()
{
	MemoryBlock result((int)getProperty(Ids::transReqDataLen), true);

	if (luaTransRequestDataCbk)
	{
		if (luaTransRequestDataCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (luaTransRequestDataCbk, this, &result);
		}
	}

	if ((int)getProperty(Ids::transRespDataLen) > 0)
	{
		/* We need to gather panel data now */
	}

	return (result);
}

MemoryBlock CtrlrMIDITransaction::getConfirmationDataAsMemoryBlock()
{
	MemoryBlock result;

	if (luaTransConfDataCbk)
	{
		if (luaTransConfDataCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (luaTransConfDataCbk, this, &result);
		}
	}

	return (result);
}

MemoryBlock CtrlrMIDITransaction::getNameAsMemoryBlock()
{
	MemoryBlock result (name.toUTF8().getAddress(), strlen(name.toUTF8()));

	if (luaTransNameDataCbk)
	{
		if (luaTransNameDataCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (luaTransNameDataCbk, this, &result);
		}
	}
	else
	{
		if (!owner.getName(getTransactionItem()).isEmpty())
		{
			result = stringToMemoryBlock (owner.getName(getTransactionItem()));
		}
		else
		{
		}
	}

	_TRANS("["+getName()+"] aquiring data for name ["+dumpMemoryBlock(result)+"]");
	return (result);
}

const bool CtrlrMIDITransaction::sendRequest()
{
	ScopedWriteLock slr(transactionLock);

	_TRANS("["+getName()+"] send request");

	if (!hasRequest)
	{
		_TRANS("["+getName()+"] no request defined, exiting");
		return (true);
	}

	if (luaTransRequestCbk)
	{
		if (luaTransRequestCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (luaTransRequestCbk, this);
		}
	}

	if (requestToSend.getSize() <= 0)
	{
		WARN("Transaction \""+getName()+"\" invalid request data");
		return (false);
	}
	else
	{
		_TRANS("["+getName()+"] request data: ("+STR((int)requestToSend.getSize())+")[" + dumpMemoryBlock(requestToSend)+"]");
		owner.getOwner().sendMidi(MidiMessage(requestToSend.getData(), requestToSend.getSize()),0);

		if (getHasResponse())
		{
			_TRANS("["+getName()+"] timeout for response is: "+STR(getTimeout()));
			startTimer (getTimeout());
		}
		else
		{
			_TRANS("["+getName()+"] no response to expect, transaction is finished");
			sendChangeMessage();
			return (true);
		}

		_TRANS("["+getName()+"] request sent");
		return (true);
	}
}

void CtrlrMIDITransaction::checkPossibleResponse(const MidiMessage &responseToCheck)
{
	ScopedReadLock slr(transactionLock);

	_TRANS("["+getName()+"] check if response is for us");
	_TRANS("["+getName()+"] expecting size: "+STR((int)expectedResponseMask.getSize()));

	if (responseToCheck.getRawDataSize() == expectedResponseMask.getSize())
	{
		_TRANS("["+getName()+"] response matches size");

		if (!getHasDataCheck())
		{
			triggerAsyncUpdate();
			return;
		}

		if (getHasDataCheck() && compareMemoryWithWildcard (responseToCheck, expectedResponseMask))
		{
			triggerAsyncUpdate();
			return;
		}
	}
}

void CtrlrMIDITransaction::handleAsyncUpdate()
{
	_TRANS("["+getName()+"] processing response");

	if (!hasResponse)
	{
		_TRANS("["+getName()+"] no response defined, exiting");
		return;
	}

	if (luaTransProcessCbk)
	{
		if (luaTransProcessCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (luaTransProcessCbk, this);
		}
	}
	else
	{
		_TRANS("["+getName()+"] no lua process handler, doing static processing");
		MemoryBlock modulatorData = getDataFromCurrentResponse();
		//owner.getOwner().setModulatorValuesFromData ();
	}
}

void CtrlrMIDITransaction::timerCallback()
{
	_TRANS("["+getName()+"] timeout");
	stopTimer();

	if (luaTransTimeoutCbk)
	{
		if (luaTransTimeoutCbk->isValid())
		{

			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (luaTransTimeoutCbk, this);
		}
	}
	else
	{
		WARN("Transaction \""+getName()+"\" has timed out\n"+getAdditionalExitData());
		sendChangeMessage();
	}
}

void CtrlrMIDITransaction::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrMIDITransaction>("CtrlrMIDITransaction")
			.def("getName", &CtrlrMIDITransaction::getName)
			.def("setRequest", (void (CtrlrMIDITransaction::*)(const MidiMessage &)) &CtrlrMIDITransaction::setRequest)
			.def("setRequest", (void (CtrlrMIDITransaction::*)(const MemoryBlock &)) &CtrlrMIDITransaction::setRequest)
			.def("setTimout", &CtrlrMIDITransaction::setTimeout)
			.def("getTimeout", &CtrlrMIDITransaction::getTimeout)
			.def("getTransactionItem", &CtrlrMIDITransaction::getTransactionItem)
			.def("setResponseReceived", (void (CtrlrMIDITransaction::*)(const MidiMessage &)) &CtrlrMIDITransaction::setResponseReceived)
			.def("setResponseReceived", (void (CtrlrMIDITransaction::*)(const MemoryBlock &)) &CtrlrMIDITransaction::setResponseReceived)
			.def("getResponseReceived", &CtrlrMIDITransaction::getResponseReceived)
			.def("setResponseMask", &CtrlrMIDITransaction::setResponseMask)
			.def("getResponseMask", &CtrlrMIDITransaction::getResponseMask)
			.def("getDataFromResponse", &CtrlrMIDITransaction::getDataFromResponse)
			.def("getFormulaAsMemoryBlock", &CtrlrMIDITransaction::getFormulaAsMemoryBlock)
			.def("setAdditionalExitData", &CtrlrMIDITransaction::setAdditionalExitData)
			.def("getAdditionalExitData", &CtrlrMIDITransaction::getAdditionalExitData)
	];
}
