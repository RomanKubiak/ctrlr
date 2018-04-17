#include "stdafx.h"
#include "LJuce.h"
#include "CtrlrMacros.h"
#include "CtrlrLog.h"
#include "CtrlrUtilities.h"
#include "luabind/object_fwd.hpp"
/*
void LAsyncUpdater::handleAsyncUpdate()
{
}

void LAsyncUpdater::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<LAsyncUpdater>("AsyncUpdater")
            .def("triggerAsyncUpdate", &AsyncUpdater::triggerAsyncUpdate)
            .def("cancelPendingUpdate", &AsyncUpdater::cancelPendingUpdate)
            .def("handleUpdateNowIfNeeded", &AsyncUpdater::handleUpdateNowIfNeeded)
            .def("isUpdatePending", &AsyncUpdater::isUpdatePending)
            .def("handleAsyncUpdate", &LAsyncUpdater::handleAsyncUpdate)
	];
}

void LBigInteger::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
			class_<BigInteger>("JUCEBigInteger")
		,
			class_<LBigInteger,BigInteger>("BigInteger")
				.def(constructor<>())
				.def(constructor<int>())
				.def(const_self + BigInteger ())
				.def(const_self - BigInteger ())
				.def(const_self * BigInteger ())
				.def(const_self / BigInteger ())
				.def(const_self < BigInteger ())
				.def(const_self <= BigInteger ())
				.def(const_self == BigInteger ())
				//.def("xor", &LBigInteger::xor)
				//.def("and", &LBigInteger::and)
				//.def("or", &LBigInteger::or)
				.def("swapWith", &BigInteger::swapWith)
				.def("isZero", &BigInteger::isZero)
				.def("isOne", &BigInteger::isOne)
				.def("toInteger", &BigInteger::toInteger)
				.def("clear", &BigInteger::clear)
				.def("clearBit", &BigInteger::clearBit)
				.def("setBit", (void (BigInteger::*)(int))&BigInteger::setBit)
				.def("setBit", (void (BigInteger::*)(int,bool))&BigInteger::setBit)
				.def("setRange", &BigInteger::setRange)
				.def("insertBit", &BigInteger::insertBit)
				.def("getBitRange", &BigInteger::getBitRange)
				.def("getBitRangeAsInt", &BigInteger::getBitRangeAsInt)
				.def("setBitRangeAsInt", &BigInteger::setBitRangeAsInt)
				.def("shiftBits", &BigInteger::shiftBits)
				.def("countNumberOfSetBits", &BigInteger::countNumberOfSetBits)
				.def("findNextSetBit", &BigInteger::findNextSetBit)
				.def("findNextClearBit", &BigInteger::findNextClearBit)
				.def("getHighestBit", &BigInteger::getHighestBit)
				.def("compare", &BigInteger::compare)
				.def("compareAbsolute", &BigInteger::compareAbsolute)
				.def("divideBy", &BigInteger::divideBy)
				.def("findGreatestCommonDivisor", &BigInteger::findGreatestCommonDivisor)
				.def("exponentModulo", &BigInteger::exponentModulo)
				.def("inverseModulo", &BigInteger::inverseModulo)
				.def("isNegative", &BigInteger::isNegative)
				.def("setNegative", &BigInteger::setNegative)
				.def("negate", &BigInteger::negate)
				.def("toString", &BigInteger::toString)
				.def("parseString", &BigInteger::parseString)
				.def("toMemoryBlock", &BigInteger::toMemoryBlock)
				.def("loadFromMemoryBlock", &BigInteger::loadFromMemoryBlock)
	];
}
*/

LMemoryBlock::LMemoryBlock(const String &hexData)
{
	MemoryBlock::loadFromHexString (hexData);
}

LMemoryBlock::LMemoryBlock(luabind::object const& table)
	: MemoryBlock(luaArrayTomemoryBlock(table))
{
}

LMemoryBlock LMemoryBlock::fromLuaTable (luabind::object const& table)
{
	return (luaArrayTomemoryBlock(table));
}

LMemoryBlock::LMemoryBlock (const void *dataToInitialiseFrom, size_t sizeInBytes)
	: MemoryBlock (dataToInitialiseFrom, sizeInBytes)
{
}

char LMemoryBlock::operator [] (const int offset) const noexcept
{
	return (*((uint8 *)getData()+offset));
}

void LMemoryBlock::insertIntoTable(luabind::object const& table)
{
	if (luabind::type(table) == LUA_TTABLE)
	{
		uint8 *ptr = (uint8 *)MemoryBlock::getData();

		for (unsigned int i=0; i<MemoryBlock::getSize(); i++)
		{
			table[i+1] = (uint8)*(ptr+i);
		}
	}
}

void LMemoryBlock::createFromTable(luabind::object const &table)
{
	for(luabind::iterator i(table), end; i != end; i++)
	{
		const uint8 v = luabind::object_cast<uint8>(*i);
		MemoryBlock::append (&v, 1);
	}
}

void LMemoryBlock::toLuaTable(luabind::object tableToWriteTo)
{
	for (int i=0; i<getSize(); i++)
	{
		tableToWriteTo[i+1] = getByte(i);
	}
}

uint8 LMemoryBlock::getByte(const int position) const
{
	uint8 *ptr = (uint8 *)getData();

	if (getSize() >= position)
		return (*(ptr + position));

	return (0);
}

LMemoryBlock LMemoryBlock::getRange(const int startingPosition, const int numBytes) const
{
	MemoryBlock bl;

	if (getSize() >= (startingPosition + numBytes))
	{
		bl.append ((uint8 *)getData() + startingPosition, numBytes);
	}
	return (bl);
}

String LMemoryBlock::toHexString(const int groupSize)
{
	return (String::toHexString(getData(), getSize(), groupSize));
}

void LMemoryBlock::insert (MemoryBlock &dataToInsert, int insertPosition)
{
	MemoryBlock::insert (dataToInsert.getData(), dataToInsert.getSize(), insertPosition);
}

void LMemoryBlock::insert (MemoryBlock &dataToInsert, int dataSize, int insertPosition)
{
	MemoryBlock::insert (dataToInsert.getData(), dataSize, insertPosition);
}

void LMemoryBlock::append (MemoryBlock &dataToAppend)
{
	MemoryBlock::append (dataToAppend.getData(), dataToAppend.getSize());
}

void LMemoryBlock::copyFrom(MemoryBlock &dataToCopy, int destinationOffset, int numBytes)
{
	MemoryBlock::copyFrom(dataToCopy.getData(), destinationOffset, numBytes);
}

void LMemoryBlock::copyTo(MemoryBlock &dataToCopy, int sourceOffset, int numBytes)
{
	MemoryBlock::copyTo(dataToCopy.getData(), sourceOffset, numBytes);
}

void LMemoryBlock::replaceWith(MemoryBlock &dataToReplace)
{
	MemoryBlock::replaceWith (dataToReplace.getData(), dataToReplace.getSize());
}

void LMemoryBlock::setByte (const int bytePosition, const uint8 byteValue)
{
	if (getSize() >= bytePosition)
	{
		*((uint8 *)getData() + bytePosition) = byteValue;
	}
}

double LMemoryBlock::getSize() const noexcept
{
	return ((double)MemoryBlock::getSize());
}

void LMemoryBlock::removeSection(const int startByte, const int dataSize)
{
    MemoryBlock::removeSection (startByte, dataSize);
}

int LMemoryBlock::getBitRange (int bitRangeStart, int numBits)
{
    return (MemoryBlock::getBitRange(bitRangeStart, numBits));
}

void LMemoryBlock::setBitRange(int bitRangeStart, int numBits, int binaryNumberToApply)
{
    return (MemoryBlock::setBitRange(bitRangeStart, numBits, binaryNumberToApply));
}

void LMemoryBlock::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<MemoryBlock>("JMemoryBlock")
		,
		class_<LMemoryBlock,bases<MemoryBlock> >("MemoryBlock")
				.def(constructor<>())
				//.def(constructor<const size_t,bool>())
				.def(constructor<const MemoryBlock &>())
				.def(constructor<luabind::object const&>())
				.def(constructor<const String &>())
				.def("insertIntoTable", &LMemoryBlock::insertIntoTable)
				.def("createFromTable", &LMemoryBlock::createFromTable)
				.def("getByte", &LMemoryBlock::getByte)
				.def("setByte", &LMemoryBlock::setByte)
				.def("getRange", &LMemoryBlock::getRange)
				.def("toHexString", &LMemoryBlock::toHexString)
				//.def("getData", (void *(MemoryBlock::*) (void) const noexcept) &MemoryBlock::getData)
				.def("getSize", &LMemoryBlock::getSize)
				.def("setSize", &MemoryBlock::setSize)
				.def("ensureSize", &MemoryBlock::ensureSize)
				.def("fillWith", &MemoryBlock::fillWith)
				.def("append", &LMemoryBlock::append)
				.def("replaceWith", &LMemoryBlock::replaceWith)
				.def("insert", (void (LMemoryBlock::*) (MemoryBlock &, int)) &LMemoryBlock::insert)
				.def("insert", (void (LMemoryBlock::*) (MemoryBlock &, int, int)) &LMemoryBlock::insert)
				.def("removeSection", &LMemoryBlock::removeSection)
				.def("copyFrom", &LMemoryBlock::copyFrom)
				.def("copyTo", &LMemoryBlock::copyTo)
				.def("swapWith", &MemoryBlock::swapWith)
		.def("toString", &MemoryBlock::toString)
				.def("loadFromHexString", &MemoryBlock::loadFromHexString)
				.def("setBitRange", &LMemoryBlock::setBitRange)
				.def("getBitRange", &LMemoryBlock::getBitRange)
				.def("toBase64Encoding", &MemoryBlock::toBase64Encoding)
				.def("fromBase64Encoding", &MemoryBlock::fromBase64Encoding)
				.def("toLuaTable", &LMemoryBlock::toLuaTable)
				.scope
				[
					def("fromLuaTable", &LMemoryBlock::fromLuaTable)
				]
	];
}
/*
void LMemoryInputStream::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<MemoryInputStream>("MemoryInputStream")
	];
}
int LSparseSet::get(int index)
{
	SparseSet<int> *s = dynamic_cast <SparseSet<int> *>(this);
	return ((*s)[index]);
}

void LSparseSet::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<SparseSet<int> >("JSparseSet")
		,
		class_<LSparseSet, bases<SparseSet<int> > >("SparseSet")
				.def(constructor<const SparseSet<int> &>())
				.def(constructor<>())
				.def("clear", &SparseSet<int>::clear)
				.def("isEmpty", &SparseSet<int>::isEmpty)
				.def("size", &SparseSet<int>::size)
				.def("contains", &SparseSet<int>::contains)
				.def("getNumRanges", &SparseSet<int>::getNumRanges)
				.def("getRange", &SparseSet<int>::getRange)
				.def("getTotalRange", &SparseSet<int>::getTotalRange)
				.def("addRange", &SparseSet<int>::addRange)
				.def("removeRange", &SparseSet<int>::removeRange)
				.def("invertRange", &SparseSet<int>::invertRange)
				.def("overlapsRange", &SparseSet<int>::overlapsRange)
				.def("containsRange", &SparseSet<int>::containsRange)
				.def("get", &LSparseSet::get)
	];
}

LThread::LThread(const String &threadName) : Thread(threadName)
{
}

void LThread::run()
{
	if (functionToRunOnThread.is_valid())
	{
		luabind::call_function<void>(functionToRunOnThread);
	}
}

void LThread::setThreadFunction(luabind::object const& _functionToRunOnThread)
{
	functionToRunOnThread = _functionToRunOnThread;
}

void LThread::startThread()
{
	Thread::startThread();
}

void LThread::startThread(int priority)
{
	Thread::startThread(priority);
}

bool LThread::isThreadRunning()
{
	return (Thread::isThreadRunning());
}

void LThread::signalThreadShouldExit()
{
	Thread::signalThreadShouldExit();
}

bool LThread::threadShoudExit() const
{
	return (Thread::threadShouldExit());
}

bool LThread::waitForThreadToExit(int timeOutMilliseconds) const
{
	return (Thread::waitForThreadToExit(timeOutMilliseconds));
}

bool LThread::setPriority(int priority)
{
	return (Thread::setPriority(priority));
}

void LThread::setAffinityMask(int affMask)
{
	Thread::setAffinityMask(affMask);
}

bool LThread::wait(int timeOutMilliseconds) const
{
	return (Thread::wait(timeOutMilliseconds));
}

void LThread::notify() const
{
	Thread::notify();
}

int LThread::getThreadId() const noexcept
{
    int *id = static_cast<int*>(Thread::getThreadId());

	return (*id);
}

const String &LThread::getThreadName() const
{
	return (Thread::getThreadName());
}

void LThread::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<LThread>("Thread")
			.def(constructor<const String &>())
			.def("setThreadFunction", &LThread::setThreadFunction)
			.def("startThread", (void (LThread::*)(void))&LThread::startThread)
			.def("startThread", (void (LThread::*)(int))&LThread::startThread)
			.def("isThreadRunning", &LThread::isThreadRunning)
			.def("signalThreadShouldExit", &LThread::signalThreadShouldExit)
			.def("threadShoudExit", &LThread::threadShoudExit)
			.def("waitForThreadToExit", &LThread::waitForThreadToExit)
			.def("setPriority", (void (LThread::*)(int))&LThread::setPriority)
			.def("setAffinityMask", &LThread::setAffinityMask)
			.def("wait", &LThread::wait)
			.def("notify", &LThread::notify)
			.def("getThreadId", &LThread::getThreadId)
			.def("getThreadName", &LThread::getThreadName)
		,
		class_<CriticalSection>("CriticalSection")
			.def(constructor<>())
			.def("enter", &CriticalSection::enter)
			.def("tryEnter", &CriticalSection::tryEnter)
			.def("exit", &CriticalSection::exit)
		,
		class_<ScopedLock>("ScopedLock")
			.def(constructor<CriticalSection &>())
		,
		class_<ScopedUnlock>("ScopedUnlock")
			.def(constructor<CriticalSection &>())
		,
		class_<ScopedTryLock>("ScopedTryLock")
			.def(constructor<CriticalSection &>())
			.def("isLocked", &ScopedTryLock::isLocked)
	];
}

LThreadWithProgressWindow::LThreadWithProgressWindow(const String &windowTitle, bool hasProgressBar, bool hasCancelButton, int timeOutMsWhenCancelling, const String &cancelButtonText)
	: ThreadWithProgressWindow(windowTitle, hasProgressBar, hasCancelButton, timeOutMsWhenCancelling, cancelButtonText, nullptr)
{
}

LThreadWithProgressWindow::~LThreadWithProgressWindow()
{
}

void LThreadWithProgressWindow::run()
{
	try
	{
		if (functionToRunOnThread.is_valid())
		{
			luabind::call_function<void>(functionToRunOnThread);
		}
	}
	catch (luabind::error& e)
	{
		_ERR("ThreadWithProgressWindow function set to run inside thread causes problems ["+STR(e.what())+"]");
	}
}

void LThreadWithProgressWindow::setThreadFunction(luabind::object const& _functionToRunOnThread)
{
	functionToRunOnThread = _functionToRunOnThread;
}

void LThreadWithProgressWindow::setProgress(double newProgress)
{
	ThreadWithProgressWindow::setProgress(newProgress);
}

void LThreadWithProgressWindow::setStatusMessage(const String &newStatusMessage)
{
	ThreadWithProgressWindow::setStatusMessage(newStatusMessage);
}

void LThreadWithProgressWindow::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<ThreadWithProgressWindow> ("JThreadWithProgressWindow")
		,
		class_<Thread>("JThread")
		,
		class_<LThreadWithProgressWindow,bases<Thread,ThreadWithProgressWindow> >("ThreadWithProgressWindow")
			.def(constructor<const String &, bool, bool, int, const String &>())
			.def("runThread", &ThreadWithProgressWindow::runThread)
			.def("setThreadFunction", &LThreadWithProgressWindow::setThreadFunction)
			.def("wait", &Thread::wait)
			.def("setProgress", &LThreadWithProgressWindow::setProgress)
			.def("setStatusMessage", &LThreadWithProgressWindow::setStatusMessage)
	];
}

*/