#include "stdafx.h"
#include "CtrlrPanelOSC.h"
#include "CtrlrMacros.h"
#include "CtrlrUtilities.h"
#include "CtrlrIDs.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "Methods/CtrlrLuaMethodManager.h"
#include "CtrlrLuaManager.h"

static bool serverFailed = false;
static String serverFailureMessge;
static String serverFailurePath;

CtrlrPanelOSC::CtrlrPanelOSC(CtrlrPanel &_owner)
	: owner(_owner), Thread("CtrlrPanelOSC thread")
{
}

CtrlrPanelOSC::~CtrlrPanelOSC()
{
	if (isThreadRunning())
	{
		stopThread(1500);
	}
}

void CtrlrPanelOSC::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::panelOSCEnabled)
	{
		if ((bool)owner.getProperty(property))
		{
			const Result res = startServer();
			if (!res.wasOk())
			{
				_WRN("Unable to start OSC server: " + res.getErrorMessage());
				return;
			}
		}
		else
		{
			stopServer();
		}
	}
	else if (property == Ids::panelOSCProtocol)
	{
		loProtocol = owner.getProperty(property);
	}
	else if (property == Ids::luaPanelOSCReceived)
	{
		if (owner.getProperty(property) == String::empty)
			return;

		luaPanelOSCReceivedCbk = owner.getCtrlrLuaManager().getMethodManager().getMethod(owner.getProperty(property));
	}
}

void CtrlrPanelOSC::run()
{
	fd_set rfds;
	struct timeval tv;
	int retval;

	for (;;)
	{
		FD_ZERO(&rfds);
		FD_SET(loServerDescriptor, &rfds);
		tv.tv_sec = 0;
		tv.tv_usec = 250000;

		retval = select(loServerDescriptor + 1, &rfds, NULL, NULL, &tv);

		if (threadShouldExit())
			return;

		if (retval == -1)
		{
			_ERR("CtrlrPanelOSC::run select(): \"" + _STR(strerror(errno)) + "\"");
			return;
		}
		else if (retval > 0)
		{
			if (FD_ISSET(loServerDescriptor, &rfds))
			{
				lo_server_recv_noblock(loServerHandle, 0);
			}
		}
		else if (retval == 0)
		{
			/* timeout */
		}
	}
}

Result CtrlrPanelOSC::startServer()
{
	_DBG("CtrlrPanelOSC::startServer port:"+owner.getProperty(Ids::panelOSCPort).toString()+" proto:"+_STR(loProtocol));

	loServerHandle = lo_server_new_with_proto (owner.getProperty(Ids::panelOSCPort).toString().getCharPointer(), loProtocol, errorHandler);

	if (serverFailed)
	{
		return (Result::fail("Can't create new OSC server \""+serverFailureMessge+"\", path \""+serverFailurePath+"\""));
	}

	lo_server_add_method (loServerHandle, NULL, NULL, (lo_method_handler) &messageHandler, this);

	loServerDescriptor = lo_server_get_socket_fd(loServerHandle);

	if (loServerDescriptor < 0)
	{
		return (Result::fail("Failed to create OSC server socket"));
	}

	startThread();
	return (Result::ok());
}

void CtrlrPanelOSC::stopServer()
{
	if (isThreadRunning())
	{
		signalThreadShouldExit();
		stopThread(1500);
		lo_server_del_method(loServerHandle, NULL, NULL);
		lo_server_free(loServerHandle);
	}
}

void CtrlrPanelOSC::handleAsyncUpdate()
{
	for (int i=0; i<messageQueue.size(); i++)
	{
		luabind::object luaArguments = luabind::newtable(owner.getCtrlrLuaManager().getLuaState());

        for (int j=0; j<messageQueue[i].getArguments().size(); j++)
		{
			luaArguments[j] = messageQueue[i].getArguments()[j];
		}

		if (luaPanelOSCReceivedCbk)
		{
			owner.getCtrlrLuaManager().getMethodManager().call (luaPanelOSCReceivedCbk, messageQueue[i].getPath(), messageQueue[i].getTypes(), luaArguments);
		}
	}

	messageQueue.clear();
}

void CtrlrPanelOSC::queueMessage(const char *path, const char *types, lo_arg **argv, int argc)
{
	CtrlrOSCMessage message;
	message.setPath(path);
	message.setTypes(types);

	for (int i=0; i<argc; i++)
		message.addArgument(*argv[i]);

	messageQueue.add (message);
	triggerAsyncUpdate();
}

void CtrlrPanelOSC::errorHandler(int num, const char *m, const char *path)
{
	serverFailureMessge = m;
	serverFailurePath = path;
	serverFailed = true;
}

void CtrlrPanelOSC::messageHandler(const char *path, const char *types, lo_arg **argv,
									int argc, lo_message msg, void *user_data)
{
	CtrlrPanelOSC *panelOSC = (CtrlrPanelOSC *)user_data;

	panelOSC->queueMessage(path,types,argv,argc);
}
