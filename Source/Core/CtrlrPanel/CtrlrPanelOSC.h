#ifndef CTRLR_PANEL_OSC
#define CTRLR_PANEL_OSC

#include "CtrlrOSC.h"
#include "CtrlrLuaObject.h"
#include "Methods/CtrlrLuaMethod.h"

class CtrlrPanel;

class CtrlrPanelOSC : public Thread, public ValueTree::Listener, public AsyncUpdater
{
	public:
		CtrlrPanelOSC(CtrlrPanel &_owner);
		~CtrlrPanelOSC();
		void run();
		Result startServer();
		void stopServer();
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &/*treeWhoseChildHasChanged*/){}
		void valueTreeParentChanged (ValueTree &/*treeWhoseParentHasChanged*/){}
		void valueTreeChildAdded (ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenAdded*/){}
		void valueTreeChildRemoved (ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenRemoved*/, int){}
		void valueTreeChildOrderChanged (ValueTree& /*parentTreeWhoseChildrenHaveMoved*/, int, int){}
		void handleAsyncUpdate();
		void queueMessage(const char *path, const char *types, lo_arg **argv, int argc);
		static void errorHandler(int num, const char *m, const char *path);
		static void messageHandler(const char *path, const char *types, lo_arg **argv,
									int argc, void *data, void *user_data);

	private:
		CtrlrPanel &owner;
		WeakReference <CtrlrLuaMethod> luaPanelOSCReceivedCbk;
		Array <CtrlrOSCMessage, CriticalSection> messageQueue;
		lo_server loServerHandle;
		int loServerDescriptor;
		int loProtocol;
		int loPort;
};
#endif
