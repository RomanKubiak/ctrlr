#include "stdafx.h"
#include "CtrlrLuaManager.h"
#include "CtrlrMIDILibrary.h"
#include "CtrlrUtilities.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrProperties.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrLog.h"
#include "CtrlrWindowManagers/CtrlrManagerWindowManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "JuceClasses/LMemoryBlock.h"
#include "CtrlrTextEditor.h"

CtrlrMIDILibrary::CtrlrMIDILibrary(CtrlrPanel &_owner)
	: 	owner(_owner),
		libraryTree(Ids::midiLibrary),
		snapshotsTree(Ids::midiLibrarySnapshots),
		firmwareTree(Ids::midiLibraryFirmware),
		editBufferTree(Ids::midiLibraryEditBuffer),
		transactions(Ids::midiLibraryTransactions),
		midiProgramNumber(0),
		midiBankNumber(0)
{
	factoryReset();
}

CtrlrMIDILibrary::~CtrlrMIDILibrary()
{
	getRoot().removeListener (this);
}

void CtrlrMIDILibrary::factoryReset()
{
	getRoot().removeListener (this);
	getRoot().removeAllChildren(nullptr);
	getRoot().removeAllProperties(nullptr);

	setProperty (Ids::uuid, Uuid().toString(), false);
	setProperty (Ids::luaTransInfo, COMBO_ITEM_NONE);

    setProperty (Ids::midiLibraryParameterIndexProperty, "modulatorCustomIndex");
	setProperty (Ids::midiLibraryMidiProgramChangeControl, false);
	setProperty (Ids::midiLibrarySendSnapAfterPChg, false);
	setProperty (Ids::midiLibraryDefaultBankName, "New Bank - %H:%M:%S");
	setProperty (Ids::midiLibraryDefaultProgramName, "New Program - %H:%M:%S");
	setProperty (Ids::midiLibraryDefaultSnapshotName, "Snapshot - %H:%M:%S");
	setProperty (Ids::midiLibraryCustomRequests, String::empty);

	getRoot().addListener (this);

	transactions = ValueTree(Ids::midiLibraryTransactions);
	transactions.setProperty (Ids::name, "Transactions", nullptr);
	snapshotsTree.setProperty (Ids::name, "Snapshots", nullptr);
	editBufferTree.setProperty (Ids::name, "Edit buffer", nullptr);
	firmwareTree.setProperty (Ids::name, "Firmware", nullptr);

	getRoot().addChild (snapshotsTree, -1, nullptr);
	getRoot().addChild (firmwareTree, -1, nullptr);
	getRoot().addChild (editBufferTree, -1, nullptr);
	getRoot().addChild (transactions, -1, nullptr);

	attachStandardTransactions();
}

void CtrlrMIDILibrary::restoreState (const ValueTree &savedState)
{
	if (savedState.isValid())
	{
		getRoot().removeAllChildren(0);

		for (int i=0; i<savedState.getNumChildren(); i++)
		{
			getRoot().addChild (savedState.getChild(i).createCopy(), -1, 0);
		}

		getSnapshots()		= getRoot().getChildWithName (Ids::midiLibrarySnapshots);
		getFirmware()		= getRoot().getChildWithName (Ids::midiLibraryFirmware);
		getTransactions()	= getRoot().getChildWithName (Ids::midiLibraryTransactions);

		restoreProperties(savedState, getRoot());
		sendChangeMessage();
	}
}

void CtrlrMIDILibrary::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (!treeWhosePropertyHasChanged.hasType(Ids::midiLibrary))
		return;

	if (property == Ids::midiLibraryBank)
	{
		setCurrentBank(Uuid(getProperty(property)));
	}
	else if (property == Ids::midiLibraryProgram)
	{
		setCurrentProgram (Uuid(getProperty(property)), InheritFromLibrary);
	}
	else if (property == Ids::midiLibrarySnapshot)
	{
		setCurrentSnapshot (Uuid(getProperty(property)), InheritFromLibrary);
	}
	else if ((property == Ids::lsb || property == Ids::msb) && treeWhosePropertyHasChanged.hasType (Ids::midiLibraryBank))
	{
		BigInteger bi;
		bi.setBitRangeAsInt (0, 7, (int)treeWhosePropertyHasChanged.getProperty(Ids::lsb));
		bi.setBitRangeAsInt (7, 7, (int)treeWhosePropertyHasChanged.getProperty(Ids::msb));
		treeWhosePropertyHasChanged.setProperty (Ids::value, (int)bi.getBitRangeAsInt (0, 14), nullptr);
	}
}

ValueTree &CtrlrMIDILibrary::getSnapshots()
{
	return (snapshotsTree);
}

ValueTree &CtrlrMIDILibrary::getFirmware()
{
	return (firmwareTree);
}

/** Banks
 */
const int CtrlrMIDILibrary::getNumBanks()
{
	int bankCount = 0;

	for (int i=0; i<getRoot().getNumChildren(); i++)
	{
		if (isBank (getRoot().getChild (i)))
		{
			bankCount++;
		}
	}

	return (bankCount);
}

ValueTree CtrlrMIDILibrary::getBank(const Uuid &uuid)
{
	for (int i=0; i<getRoot().getNumChildren(); i++)
	{
		if (isBank (getRoot().getChild (i)) && getUuid(getRoot().getChild (i)) == uuid)
		{
			return (getRoot().getChild(i));
		}
	}

	return (getRoot());
}

ValueTree &CtrlrMIDILibrary::getRoot()
{
	return (libraryTree);
}

/**
 *   Banks
 */

void CtrlrMIDILibrary::setCurrentBank(const Uuid &uuid)
{
	_DBG("CtrlrMIDILibrary::setCurrentBank uuid="+uuid.toString());

	if (uuid == getUuid(getRoot()))
	{
		setCurrentBank (getRoot());
		return;
	}

	setCurrentBank (getRoot().getChildWithProperty(Ids::uuid, uuid.toString()));
}

void CtrlrMIDILibrary::setCurrentBankFromMenu(const int menuItemId)
{
	_DBG("CtrlrMIDILibrary::setCurrentBankFromMenu menuItemId="+STR(menuItemId));

	if (menuItemId == 0)
	{
		setProperty (Ids::midiLibraryBank, getUuid(getRoot()).toString());
		return;
	}

	for (int i=0; i<getRoot().getNumChildren(); i++)
	{
		if (i == (menuItemId-1) && isBank(getRoot().getChild(i)))
		{
			setProperty (Ids::midiLibraryBank, getRoot().getChild(i).getProperty(Ids::uuid));
		}
	}
}

void CtrlrMIDILibrary::setCurrentBank(ValueTree bank)
{
	_DBG("CtrlrMIDILibrary::setCurrentBank from data type="+bank.getType().toString());
	if (isBank(bank))
	{
		currentBank 		= bank;
		midiBankNumber		= getNumber(bank);
		midiBankNumberLSB	= getLSB(bank);
		midiBankNumberMSB	= getMSB(bank);
	}
	else
	{
		currentBank = ValueTree();
		_WRN("CtrlrMIDILibrary::setCurrentBank bank data is invalid");
	}

	listeners.call (&CtrlrMIDILibrary::Listener::programListChanged);
}

void CtrlrMIDILibrary::setCurrentSnapshotFromMenu(const int menuItemId)
{
	_DBG("CtrlrMIDILibrary::setCurrentSnapshotFromMenu menuItemId="+STR(menuItemId));

	for (int i=0; i<getSnapshots().getNumChildren(); i++)
	{
		if (menuItemId == i && isProgram(getSnapshots().getChild(i)))
		{
			setProperty (Ids::midiLibrarySnapshot, getSnapshots().getChild(i).getProperty(Ids::uuid));
		}
	}
}

ValueTree &CtrlrMIDILibrary::getCurrentBank()
{
	return (currentBank);
}

ValueTree &CtrlrMIDILibrary::getTransactions()
{
	return (transactions);
}

const String CtrlrMIDILibrary::getBankName(const Uuid &uuid)
{
	return (getBank(uuid).getProperty(Ids::name));
}

const String CtrlrMIDILibrary::getCurrentBankName()
{
	if (getCurrentBank() == getRoot())
	{
		return ("Library root");
	}
	else
	{
		return (getCurrentBank().getProperty(Ids::name));
	}
}

const String CtrlrMIDILibrary::getBankDescription(const Uuid &bankUuid)
{
	return (getBank(bankUuid).getProperty(Ids::description));
}

/** Programs
 */

void CtrlrMIDILibrary::setCurrentProgramFromMenu(const int menuItemId)
{
	if (getCurrentBank().isValid())
	{
		for (int i=0; i<getCurrentBank().getNumChildren(); i++)
		{
			if (i == menuItemId && isProgram(getCurrentBank().getChild(i)))
			{
				setProperty (Ids::midiLibraryProgram, getCurrentBank().getChild(i).getProperty(Ids::uuid));
			}
		}
	}
}

void CtrlrMIDILibrary::setCurrentProgram(const Uuid &uuid, const MidiProgramChangeControl midiProgramChangeControl, const bool changePanelState, const bool setAsCurrentProgram)
{
	ValueTree program = getCurrentBank().getChildWithProperty(Ids::uuid, uuid.toString());

    if (isProgram(program))
		setCurrentProgram (program, midiProgramChangeControl, changePanelState, setAsCurrentProgram);
	else
		_WRN("CtrlrMIDILibrary::setCurrentProgram no program with UUID="+uuid.toString());
}

void CtrlrMIDILibrary::setProgram (const ValueTree &item)
{
	owner.setProgram (item, (bool)getProperty (Ids::midiLibrarySendSnapAfterPChg));
	listeners.call (&CtrlrMIDILibrary::Listener::programListChanged);
}

void CtrlrMIDILibrary::setCurrentProgram(ValueTree program, const MidiProgramChangeControl midiProgramChangeControl, const bool changePanelState, const bool setAsCurrentProgram)
{
	if (isProgram(program))
	{
		if (setAsCurrentProgram)
		{
			midiProgramNumber	= getNumber(program);
			currentProgram 		= program;
		}

		if (midiProgramChangeControl == SendProgramChange
			|| (midiProgramChangeControl == InheritFromLibrary && (bool)getProperty(Ids::midiLibraryMidiProgramChangeControl)))
		{
            sendMidiProgramChange();
		}

		if (changePanelState)
		{
			setProgram (program);
		}
	}
	else
	{
		currentProgram 		= ValueTree();
		midiProgramNumber	= 0;

		_WRN("CtrlrMIDILibrary::setCurrentProgram program data not valid");
	}
}

void CtrlrMIDILibrary::setCurrentSnapshot(ValueTree snapshotTree, const MidiProgramChangeControl midiProgramChangeControl)
{
	if (isProgram(snapshotTree))
	{
		currentSnapshot = snapshotTree;

		if (midiProgramChangeControl == SendProgramChange
			|| (midiProgramChangeControl == InheritFromLibrary && (bool)getProperty(Ids::midiLibraryMidiProgramChangeControl)))
		{
            sendMidiProgramChange();
		}

		setProgram (snapshotTree);

		listeners.call (&CtrlrMIDILibrary::Listener::programListChanged);
	}
	else
	{
		currentSnapshot = ValueTree();
	}
}

void CtrlrMIDILibrary::savePanelStateToCurrentProgram()
{
	if (isProgram(getCurrentProgram()))
	{
		owner.getProgram (getCurrentProgram());
	}
}

void CtrlrMIDILibrary::sendMidiProgramChange()
{
	_DBG("CtrlrMIDILibrary::sendMidiProgramChange");
}

ValueTree CtrlrMIDILibrary::getCurrentProgram()
{
	return (currentProgram);
}

ValueTree CtrlrMIDILibrary::getCurrentSnapshot()
{
	return (currentSnapshot);
}

const Uuid CtrlrMIDILibrary::getCurrentProgramUuid()
{
	return (getUuid(getCurrentProgram()));
}

ValueTree CtrlrMIDILibrary::getEditBuffer()
{
	return (getRoot().getChildWithName(Ids::midiLibraryEditBuffer));
}

ValueTree CtrlrMIDILibrary::getProgram(const Uuid &bankUuid, const Uuid &programUuid)
{
	return (getBank(bankUuid).getChildWithProperty(Ids::uuid, programUuid.toString()));
}

ValueTree CtrlrMIDILibrary::getSnapshot(const Uuid &snapshotUuid)
{
    return (getSnapshots().getChildWithProperty(Ids::uuid, snapshotUuid.toString()));
}

const int CtrlrMIDILibrary::getNumPrograms(const Uuid &bankUuid)
{
	int programCount = 0;
	for (int i=0; i<getBank(bankUuid).getNumChildren(); i++)
	{
		if (isProgram(getBank(bankUuid).getChild (i)))
		{
			programCount++;
		}
	}

	return (programCount);
}

const String CtrlrMIDILibrary::getProgramName(const Uuid &bankUuid, const Uuid &programUuid)
{
	return (getProgram(bankUuid, programUuid).getProperty(Ids::name));
}

const String CtrlrMIDILibrary::getProgramDescription(const Uuid &bankUuid, const Uuid &programUuid)
{
	return (getProgram(bankUuid, programUuid).getProperty(Ids::description));
}

const int CtrlrMIDILibrary::getCurrentProgramMIDINumber(const int suggestedProgramNumber)
{
	if (suggestedProgramNumber >= 0)
		return (suggestedProgramNumber);
	else
		return (midiProgramNumber);
}

const int CtrlrMIDILibrary::getCurrentBankMIDINumber(const int suggestedBankNumber)
{
	if (suggestedBankNumber >= 0)
		return (suggestedBankNumber);
	else
		return ((int)getCurrentBank().getProperty(Ids::number));
}

void CtrlrMIDILibrary::addNewProgram (const String programName, const int number, ValueTree unitToAddTo)
{
	ValueTree program = createEmptyProgramTree();

	program.addChild (owner.getProgram(), -1, nullptr);

	program.setProperty (Ids::name, getDefaultProgramName(programName), nullptr);
	program.setProperty (Ids::description, String::empty, nullptr);
	program.setProperty (Ids::number, getCurrentProgramMIDINumber(number), nullptr);
	program.setProperty (Ids::uuid, Uuid().toString(), nullptr);

	if (unitToAddTo.isValid())
	{
		unitToAddTo.addChild (program, -1, 0);
	}
	else
	{
		if (isBank(getCurrentBank()))
		{
			getCurrentBank().addChild (program, -1, 0);
		}
		else
		{
			getRoot().addChild (program, -1, 0);
		}
	}

	listeners.call (&CtrlrMIDILibrary::Listener::programListChanged);
}

ValueTree CtrlrMIDILibrary::createEmptyProgramTree()
{
    ValueTree program(Ids::midiLibraryProgram);
	program.setProperty (Ids::name, "Program", nullptr);
	program.setProperty (Ids::description, String::empty, nullptr);
	program.setProperty (Ids::number, 0, nullptr);
	program.setProperty (Ids::midiLibraryCanGetItem, true, nullptr);
	program.setProperty (Ids::midiLibraryCanSendItem, true, nullptr);
	program.setProperty (Ids::uuid, Uuid().toString(), nullptr);

	return (program);
}

void CtrlrMIDILibrary::addNewCustomData (const String dataName, const int number, ValueTree unitToAddTo)
{
	ValueTree data(Ids::midiLibraryData);
	data.setProperty (Ids::name, dataName, nullptr);
	data.setProperty (Ids::description, String::empty, nullptr);
	data.setProperty (Ids::number, number, nullptr);
	data.setProperty (Ids::midiLibraryCanGetItem, true, nullptr);
	data.setProperty (Ids::midiLibraryCanSendItem, true, nullptr);
	data.setProperty (Ids::uuid, Uuid().toString(), nullptr);

	if (unitToAddTo.isValid())
	{
		unitToAddTo.addChild (data, -1, nullptr);
	}
	else
	{
		getRoot().addChild (data, -1, nullptr);
	}
}

void CtrlrMIDILibrary::addNewTransaction (const String transactionName, ValueTree unitToAddTo)
{
	ValueTree transaction = CtrlrMIDITransaction::createEmptyTransactionTree(transactionName);

	if (unitToAddTo.isValid())
	{
		unitToAddTo.addChild (transaction, -1, nullptr);
	}
}

void CtrlrMIDILibrary::addNewBank (const String bankName, const String bankDescription, const int number, const int lsb, const int msb, ValueTree unitToAddTo)
{
	ValueTree b(Ids::midiLibraryBank);
	b.setProperty (Ids::name, getDefaultBankName (bankName), 0);
	b.setProperty (Ids::description, bankDescription, 0);
	b.setProperty (Ids::lsb, lsb, nullptr);
	b.setProperty (Ids::msb, msb, nullptr);
	b.setProperty (Ids::number, getCurrentBankMIDINumber (number), nullptr);
	b.setProperty (Ids::midiLibraryCanGetItem, true, nullptr);
	b.setProperty (Ids::midiLibraryCanSendItem, true, nullptr);
	b.setProperty (Ids::uuid, Uuid().toString(), nullptr);

	if (unitToAddTo.isValid())
	{
		unitToAddTo.addChild (b, -1, nullptr);
	}
	else
	{
		getRoot().addChild(b, -1, nullptr);
	}

	listeners.call (&CtrlrMIDILibrary::Listener::programListChanged);
}

bool CtrlrMIDILibrary::isCurrentProgram(const ValueTree item)
{
	return (item == currentProgram ? true : false);
}

void CtrlrMIDILibrary::attachItemToPopupMenu(const ValueTree &itemToAttach, PopupMenu &m, int &itemOffset)
{
	if (isContainer (itemToAttach))
	{
        PopupMenu subMenu;

        for (int topLevelIndex=0; topLevelIndex<itemToAttach.getNumChildren(); topLevelIndex++)
		{
			attachItemToPopupMenu (itemToAttach.getChild(topLevelIndex), subMenu, itemOffset);
		}

        m.addSubMenu (itemToAttach.getProperty(Ids::name).toString(), subMenu, true);
	}
	else
	{
		m.addItem (itemOffset++, itemToAttach.getProperty(Ids::name).toString(), (!itemToAttach.hasType(Ids::midiLibraryData) && (bool)itemToAttach.getProperty(Ids::midiLibraryCanSendItem)), isCurrentProgram(itemToAttach));
	}
}

void CtrlrMIDILibrary::attachToPopupMenu(PopupMenu &m)
{
	int itemOffset = MENU_OFFSET_PROGRAM_LIST;

    for (int topLevelIndex=0; topLevelIndex<getRoot().getNumChildren(); topLevelIndex++)
	{
		attachItemToPopupMenu (getRoot().getChild(topLevelIndex), m, itemOffset);
	}
}

void CtrlrMIDILibrary::attachCustomRequests(PopupMenu &m)
{
	if (getProperty(Ids::midiLibraryCustomRequests).toString().length() > 0)
	{
		StringArray menuEntries = StringArray::fromTokens (getProperty(Ids::midiLibraryCustomRequests).toString(), "\n", "\"\'");

		for (int i=0; i<menuEntries.size(); i++)
		{
			m.addItem (MENU_OFFSET_CUSTOM_REQUESTS + i, menuEntries[i]);
		}
	}
}

void CtrlrMIDILibrary::setProgram (const int programMenuIndex)
{
	ValueTree program = getProgramForMenuIndex (programMenuIndex);

	if (program.isValid())
	{
		setProgram (program);
	}
}

ValueTree CtrlrMIDILibrary::scanChildrenForMenuIndex(ValueTree item, int itemIndexToFind, int &currentIndex)
{
	_DBG("CtrlrMIDILibrary::scanChildrenForMenuIndex");
	if (isContainer (item))
	{
		_DBG("\tcontainer ["+item.getType().toString()+"]");
		ValueTree child;

		for (int topLevelIndex=0; topLevelIndex<item.getNumChildren(); topLevelIndex++)
		{
			child = scanChildrenForMenuIndex (item.getChild(topLevelIndex), itemIndexToFind, currentIndex);

			if (child.isValid())
			{
				_DBG("\t\tvalid child found ["+child.getType().toString()+"] parent:["+child.getParent().getType().toString()+"]");
				return (child);
			}

			currentIndex++;
		}
	}

	if (itemIndexToFind == currentIndex)
	{
		_DBG("\t\titemIndexToFind == currentIndex ["+item.getType().toString()+"]");
		return (item);
	}
	else
	{
		return (ValueTree());
	}
}

ValueTree CtrlrMIDILibrary::getProgramForMenuIndex(const int itemIndexToFind)
{
	_DBG("CtrlrMIDILibrary::getProgramForMenuIndex itemIndexToFind="+STR(itemIndexToFind));

	int currentIndex = MENU_OFFSET_PROGRAM_LIST;

	_DBG("\tcurrentIndex="+STR(currentIndex));
	ValueTree item;

    for (int topLevelIndex=0; topLevelIndex<getRoot().getNumChildren(); topLevelIndex++)
	{
		item = scanChildrenForMenuIndex (getRoot().getChild(topLevelIndex), itemIndexToFind, currentIndex);

		if (isProgram(item))
		{
			return (item);
		}
	}

	return (item);
}

void CtrlrMIDILibrary::snapshot()
{
    ValueTree snapshotTree = createEmptyProgramTree();

    snapshotTree.setProperty (Ids::time, Time::getCurrentTime().toMilliseconds(), nullptr);
    snapshotTree.setProperty (Ids::name, getDefaultSnapshotName(), nullptr);
    snapshotTree.setProperty (Ids::uuid, Uuid().toString(), nullptr);
	snapshotTree.addChild (owner.getProgram(), -1, nullptr);

	if (getSnapshots().isValid())
	{
		if (getSnapshots().isValid())
		{
			getSnapshots().addChild (snapshotTree, -1, nullptr);
		}
	}
}

int CtrlrMIDILibrary::getListenerInputMidiChannel()
{
	return (0);
}

void CtrlrMIDILibrary::processMidi (MidiBuffer &incommingData)
{
	MidiBuffer::Iterator it(incommingData);
	MidiMessage midiMessage;
	int samplePosition;

	ScopedLock sl(transactionQueue.getLock());

	while (it.getNextEvent (midiMessage, samplePosition))
	{
		for (int i=0; i<transactionQueue.size(); i++)
		{
			transactionQueue[i]->checkPossibleResponse (midiMessage);
		}
	}
}

void CtrlrMIDILibrary::handleAsyncUpdate()
{
}

void CtrlrMIDILibrary::changeListenerCallback(ChangeBroadcaster *changeSource)
{
	CtrlrMIDITransaction *transaction = dynamic_cast<CtrlrMIDITransaction*>(changeSource);

	if (transaction != nullptr)
	{
		ScopedLock sl(transactionQueue.getLock());
		transactionQueue.removeObject (transaction);
	}
}

void CtrlrMIDILibrary::timerCallback(int timerId)
{
}

void CtrlrMIDILibrary::importFromFile(const File &fileToImport, ValueTree itemSelected)
{
}

bool CtrlrMIDILibrary::isProgram(const ValueTree tree)
{
	return (tree.hasType (Ids::midiLibraryProgram));
}

bool CtrlrMIDILibrary::isBank(const ValueTree tree)
{
	return ((bool)tree.hasType (Ids::midiLibraryBank) || (bool)tree.hasType(Ids::midiLibrary));
}

bool CtrlrMIDILibrary::isRoot(const ValueTree tree)
{
	return (tree.hasType(Ids::midiLibrary));
}

bool CtrlrMIDILibrary::isCustomData(const ValueTree tree)
{
	return (tree.hasType (Ids::midiLibraryData));
}

bool CtrlrMIDILibrary::isFirmware(const ValueTree tree)
{
	return (tree.hasType (Ids::midiLibraryFirmware));
}

bool CtrlrMIDILibrary::isEditBuffer(const ValueTree item)
{
	return (item.hasType (Ids::midiLibraryEditBuffer));
}

bool CtrlrMIDILibrary::isContainer(const ValueTree item)
{
    if (item.hasType(Ids::midiLibrary)
		|| item.hasType(Ids::midiLibraryBank)
		|| item.hasType(Ids::midiLibrarySnapshots)
		|| item.hasType(Ids::midiLibraryTransactions))
    {
        return (true);
    }

    return (false);
}

bool CtrlrMIDILibrary::isItem(const ValueTree item)
{
    if (item.hasType (Ids::midiLibraryProgram)
		|| item.hasType (Ids::midiLibraryData)
		|| item.hasType (Ids::midiLibraryFirmware)
		|| item.hasType (Ids::midiLibraryEditBuffer))
    {
        return (true);
    }

    return (false);
}

bool CtrlrMIDILibrary::isTransaction(const ValueTree item)
{
	if (item.hasType(Ids::trans))
		return (true);

	return (false);
}

void CtrlrMIDILibrary::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrMIDILibrary, CtrlrLuaObject>("CtrlrMIDILibrary")
			.def("addNewBank", &CtrlrMIDILibrary::addNewBank)
			.def("addNewProgram", &CtrlrMIDILibrary::addNewProgram)
			.def("addNewCustomData", &CtrlrMIDILibrary::addNewCustomData)
            .def("getCurrentBankMIDINumber", &CtrlrMIDILibrary::getCurrentBankMIDINumber)
            .def("getCurrentProgramMIDINumber", &CtrlrMIDILibrary::getCurrentProgramMIDINumber)
            .def("getProgramName", &CtrlrMIDILibrary::getProgramName)
            .def("getNumBanks", &CtrlrMIDILibrary::getNumBanks)
            .def("getNumPrograms", &CtrlrMIDILibrary::getNumPrograms)
            .def("getBankName", &CtrlrMIDILibrary::getBankName)
            .def("getBankDescription", &CtrlrMIDILibrary::getBankDescription)
            .def("getProgramDescription", &CtrlrMIDILibrary::getProgramDescription)
            .def("getEditBuffer", &CtrlrMIDILibrary::getEditBuffer)
            .def("getFirmware", &CtrlrMIDILibrary::getFirmware)
            .def("getSnapshots", &CtrlrMIDILibrary::getSnapshots)
			.scope
			[
				def("isProgram", &CtrlrMIDILibrary::isProgram),
				def("isBank", &CtrlrMIDILibrary::isBank),
				def("isCustomData", &CtrlrMIDILibrary::isCustomData),
				def("isFirmware", &CtrlrMIDILibrary::isFirmware),
				def("isContainer", &CtrlrMIDILibrary::isContainer),
				def("isItem", &CtrlrMIDILibrary::isItem),
				def("isEditBuffer", &CtrlrMIDILibrary::isEditBuffer)
			]
	];
}

String CtrlrMIDILibrary::getItemName(const int itemId)
{
	switch (itemId)
	{
		case Program:
			return ("Program");
		case Bank:
			return ("Bank");
		case Folder:
			return ("Folder");
		case Firmware:
			return ("Firmware");
		case Identity:
			return ("Identity");
		case Waveform:
			return ("Waveform");
		case Data:
			return ("Data");
		case CtrlrEditor::doIdentityRequest:
			return ("REQUEST Identity");
		case CtrlrEditor::doEditBufferRequest:
			return ("REQUEST edit buffer");
		case CtrlrEditor::doAllProgramsRequest:
			return ("REQUEST all programs");
		case CtrlrEditor::showMidiLibrary:
			return ("Program manager");
		case CtrlrEditor::doSnapshotStore:
			return ("Save snapshot");
		case CtrlrEditor::doSendSnapshot:
			return ("SEND snapshot");
		case CtrlrEditor::doPrevProgram:
			return ("Previous program");
		case CtrlrEditor::doNextProgram:
			return ("Next program");
		case CtrlrEditor::doPrevBank:
			return ("Previous bank");
		case CtrlrEditor::doNextBank:
			return ("Next bank");
		default:
			break;
	}

	return ("Unknown_"+STR(itemId));
}

Image CtrlrMIDILibrary::getItemIcon(const int itemId)
{
	switch ((Item)itemId)
	{
		case Program:
			return (IMAGE(ico_document_png));

		case Bank:
			return (IMAGE(ico_folder_png));

		case Folder:
			return (IMAGE(ico_folder_alt_png));

		case Firmware:
			return (IMAGE(ico_firmware_png));

		case Identity:
			return (IMAGE(ico_unit_alt_png));

		default:
			break;
	}

	return (IMAGE(ico_unknown_png));
}

void CtrlrMIDILibrary::addListener (CtrlrMIDILibrary::Listener *listenerToAdd)
{
	listeners.add (listenerToAdd);
}

void CtrlrMIDILibrary::removeListener (CtrlrMIDILibrary::Listener *listenerToRemove)
{
	listeners.remove (listenerToRemove);
}

PopupMenu CtrlrMIDILibrary::getProgramMenu()
{
	PopupMenu m;
	if (getCurrentBank().isValid())
	{
		for (int i=0; i<getCurrentBank().getNumChildren(); i++)
		{
			if (isProgram(getCurrentBank().getChild(i)))
				m.addItem (i+1, getCurrentBank().getChild(i).getProperty(Ids::name), true, getCurrentProgram() == getCurrentBank().getChild(i));
		}
	}
	return (m);
}

PopupMenu CtrlrMIDILibrary::getBankMenu()
{
	PopupMenu m;
	m.addItem (1, "-- Library root", true, getCurrentBank() == getRoot());

	for (int i=0; i<getRoot().getNumChildren(); i++)
	{
		if (isBank(getRoot().getChild(i)))
		{
			m.addItem (i+2, getRoot().getChild(i).getProperty(Ids::name), true, getCurrentBank() == getRoot().getChild(i));
		}
	}
	return (m);
}

PopupMenu CtrlrMIDILibrary::getSnapshotMenu()
{
	PopupMenu m;

	for (int i=0; i<getSnapshots().getNumChildren(); i++)
	{
		if (isProgram(getSnapshots().getChild(i)))
		{
			m.addItem (i+1, getSnapshots().getChild(i).getProperty(Ids::name), true, getCurrentSnapshot() == getSnapshots().getChild(i));
		}
	}
	return (m);
}

const String CtrlrMIDILibrary::getDefaultProgramName(const String &suggestedProgramName)
{
	if (!suggestedProgramName.isEmpty())
	{
		return (suggestedProgramName);
	}
	else
	{
		return (Time::getCurrentTime().formatted (getProperty(Ids::midiLibraryDefaultProgramName).toString()));
	}
}

const String CtrlrMIDILibrary::getDefaultBankName(const String &suggestedBankName)
{
	if (!suggestedBankName.isEmpty())
	{
		return (suggestedBankName);
	}
	else
	{
		return (Time::getCurrentTime().formatted (getProperty(Ids::midiLibraryDefaultBankName).toString()));
	}
}

const String CtrlrMIDILibrary::getDefaultSnapshotName()
{
	return (Time::getCurrentTime().formatted (getProperty(Ids::midiLibraryDefaultSnapshotName).toString()));
}

void CtrlrMIDILibrary::setCurrentSnapshot(const Uuid &uuid, const MidiProgramChangeControl midiProgramChangeControl)
{
    ValueTree snap = getSnapshots().getChildWithProperty(Ids::uuid, uuid.toString());

    if (isProgram(snap))
		setCurrentSnapshot (snap,midiProgramChangeControl);
	else
		_WRN("CtrlrMIDILibrary::setCurrentSnapshot no snapshot with UUID="+uuid.toString());
}

void CtrlrMIDILibrary::deleteCurrentProgram()
{
	if (isProgram (getCurrentProgram()))
	{
		ValueTree parent = getCurrentProgram().getParent();

		if (parent.isValid())
		{
			parent.removeChild (getCurrentProgram(), nullptr);
			currentProgram = ValueTree();
		}

		listeners.call (&CtrlrMIDILibrary::Listener::programListChanged);
	}
}

void CtrlrMIDILibrary::deleteCurrentBank()
{
	if (isBank (getCurrentBank()) && getRoot() != getCurrentBank())
	{
		ValueTree parent = getCurrentBank().getParent();
		if (parent.isValid())
		{
			parent.removeChild (getCurrentBank(), nullptr);

			setProperty (Ids::midiLibraryBank, String::empty, false);
		}

		listeners.call (&CtrlrMIDILibrary::Listener::programListChanged);
	}
}

void CtrlrMIDILibrary::deleteCurrentSnapshot()
{
	if (getCurrentSnapshot().isValid())
	{
		ValueTree parent = getCurrentSnapshot().getParent();

		if (parent.isValid())
		{
			parent.removeChild (getCurrentSnapshot(), nullptr);
			currentSnapshot = ValueTree();
		}

		listeners.call (&CtrlrMIDILibrary::Listener::programListChanged);
	}
}

const String CtrlrMIDILibrary::getName(const ValueTree &vt)
{
	return (vt.getProperty(Ids::name).toString());
}

const int CtrlrMIDILibrary::getNumber(const ValueTree &vt)
{
	return (vt.getProperty(Ids::number, -1));
}

const int CtrlrMIDILibrary::getLSB(const ValueTree &vt)
{
	return (vt.getProperty(Ids::lsb, -1));
}

const int CtrlrMIDILibrary::getMSB(const ValueTree &vt)
{
	return (vt.getProperty(Ids::msb, -1));
}

const Uuid CtrlrMIDILibrary::getUuid(const ValueTree &vt)
{
	return (Uuid(vt.getProperty(Ids::uuid)));
}

void CtrlrMIDILibrary::queueTransaction(ValueTree transactionState, ValueTree transactionItem)
{
	_TRANS("["+getName(transactionState)+"] creating");
	CtrlrMIDITransaction *transaction = new CtrlrMIDITransaction(*this);
	transaction->setTransactionItem (transactionItem);
	transaction->restoreState (transactionState);
	transaction->addChangeListener (this);

	{
		ScopedLock sl(transactionQueue.getLock());
		transactionQueue.add (transaction);
	}

	if (!transaction->sendRequest())
	{
		_TRANS("["+transaction->getName()+"] sending request failed, removing from queue");
        ScopedLock sl(transactionQueue.getLock());
        transactionQueue.removeObject (transaction);
	}
}

CtrlrMIDITransaction *CtrlrMIDILibrary::getTransactionByName(const String &transactionName)
{
	ScopedLock sl(transactionQueue.getLock());
	for (int i=0; i<transactionQueue.size(); i++)
	{
		if (transactionQueue[i]->getName() == transactionName)
			return (transactionQueue[i]);
	}
	return (nullptr);
}

void CtrlrMIDILibrary::attachStandardTransactions()
{
	ScopedPointer <XmlElement> root(nullptr);
	ValueTree builtInTransactions;

	if (File (owner.getProperty(Ids::midiLibraryTransactionsFile)).existsAsFile())
	{
		root = XmlDocument::parse (File(owner.getProperty(Ids::midiLibraryTransactionsFile)));
	}
	else
	{
		root = XmlDocument::parse (String::createStringFromData (BinaryData::CtrlrMIDITransactions_xml, BinaryData::CtrlrMIDITransactions_xmlSize));
	}

	if (root)
	{
		builtInTransactions = ValueTree::fromXml(*root);

		if (getTransactions().isValid())
		{
            for (int i=0; i<builtInTransactions.getNumChildren(); i++)
			{
				getTransactions().addChild (builtInTransactions.getChild(i).createCopy(), -1, nullptr);
			}
		}
	}
}

const bool CtrlrMIDILibrary::transactionCanHandle(const ValueTree &transactionState, const ValueTree transactionItem)
{
	if (transactionState.isValid() && transactionState.hasType(Ids::trans))
	{
		if (luaTransInfoCbk)
		{
			if (luaTransInfoCbk->isValid())
			{
				const int ret = owner.getCtrlrLuaManager().getMethodManager().callWithRet (luaTransInfoCbk, transactionState, transactionItem);
				if (ret < 0)
				{
					_WRN("CtrlrMIDILibrary::transactionCanHandle luaTransInfoCbk defined but failed to execute");
				}
				else
				{
					return (ret ? true : false);
				}
			}
		}
		else
		{
			return (transactionCanHandleType(transactionState, transactionItem));
		}
	}

	return (false);
}

const bool CtrlrMIDILibrary::transactionCanHandleType(const ValueTree &transactionState, const ValueTree transactionItem)
{
	StringArray types = StringArray::fromTokens (transactionState.getProperty(Ids::transCap).toString(), ",; ", "\"\'");
	for (int i=0; i<types.size(); i++)
	{
		if (types[i] == transactionItem.getType().toString())
			return (true);
	}

	return (false);
}

void CtrlrMIDILibrary::getTransactionMenu(PopupMenu &m, ValueTree transactionItem)
{
	if (isTransaction(transactionItem) || transactionItem == getTransactions())
		return;

	m.addSectionHeader ("Transactions");

	for (int i=0; i<getTransactions().getNumChildren(); i++)
	{
		if (transactionCanHandle (getTransactions().getChild(i), transactionItem))
		{
			m.addItem (i + MENU_TRANSACTIONS_START, getName(getTransactions().getChild(i)), true);
		}
	}
}

void CtrlrMIDILibrary::handleTransactionMenu(ValueTree transactionItem, const int resultId)
{
	if (getTransactions().getChild(resultId - MENU_TRANSACTIONS_START).isValid())
	{
        queueTransaction (getTransactions().getChild(resultId - MENU_TRANSACTIONS_START), transactionItem);
	}
}
