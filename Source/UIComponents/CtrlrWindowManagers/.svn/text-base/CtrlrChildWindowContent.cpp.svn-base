#include "stdafx.h"
#include "CtrlrUtilities.h"
#include "CtrlrMacros.h"
#include "CtrlrChildWindowContent.h"
#include "CtrlrChildWindowContainer.h"
#include "CtrlrLog.h"
#include "CtrlrIDs.h"
#include "CtrlrChildWindow.h"

CtrlrChildWindowContent::CtrlrChildWindowContent() 
	:	container(nullptr), 
		componentTree(Ids::uiChildWindowContentState)
{
}

CtrlrChildWindowContent::~CtrlrChildWindowContent()
{
}

ValueTree &CtrlrChildWindowContent::saveState()
{
	return (componentTree);
}

void CtrlrChildWindowContent::setContainer(CtrlrChildWindowContainer *_container)
{
	container = _container;
}

String CtrlrChildWindowContent::getContentName()
{
	return ("Unknown");
}