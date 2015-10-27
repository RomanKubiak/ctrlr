#include "stdafx.h"
#include "CtrlrPanelOSC.h"
#include "CtrlrMacros.h"
#include "CtrlrUtilities.h"

CtrlrPanelOSC::CtrlrPanelOSC(CtrlrPanel &_owner)
	: owner(_owner), Thread("CtrlrPanelOSC thread")
{
}

void CtrlrPanelOSC::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
}

void CtrlrPanelOSC::run()
{
}

Result CtrlrPanelOSC::startServer ()
{
	loServerHandle = lo_server_new_with_proto (loPort, loProtocol, errorHandler);

	lo_server_add_method (loServerHandle, NULL, NULL, messageHandler, this);

	loServerDescriptor = lo_server_get_socket_fd(loServerHandle);

	if (loServerDescriptor < 0)
	{
		return (Result::fail("Failed to create OSC server socket"));
	}

	return (Result::ok());
}

void CtrlrPanelOSC::errorHandler(int num, const char *m, const char *path)
{
}

void CtrlrPanelOSC::messageHandler(const char *path, const char *types, lo_arg **argv,
									int argc, void *data, void *user_data)
{
}
