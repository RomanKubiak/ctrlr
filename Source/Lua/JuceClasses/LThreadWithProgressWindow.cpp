#include "stdafx.h"
#include "LThreadWithProgressWindow.h"

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
