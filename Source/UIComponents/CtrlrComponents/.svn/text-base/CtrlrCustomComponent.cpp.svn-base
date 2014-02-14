#include "stdafx.h"
#include "CtrlrLuaManager.h"
#include "CtrlrCustomComponent.h"
#include "CtrlrProcessor.h"
#include "CtrlrPanel/CtrlrPanel.h"

CtrlrCustomComponent::CtrlrCustomComponent(CtrlrModulator &_owner) 
	: CtrlrComponent(_owner)
{
	setWantsKeyboardFocus (true);
	
	setProperty(Ids::uiCustomResizedCallback, "");
	setProperty(Ids::uiCustomPaintCallback, "");
	setProperty(Ids::uiCustomPaintOverChildrenCallback, "");
	setProperty(Ids::uiCustomMouseDownCallback, "");
	setProperty(Ids::uiCustomMouseUpCallback, "");
	setProperty(Ids::uiCustomMouseEnterCallback, "");
	setProperty(Ids::uiCustomMouseExitCallback, "");
	setProperty(Ids::uiCustomMouseMoveCallback, "");
	setProperty(Ids::uiCustomMouseDragCallback, "");
	setProperty(Ids::uiCustomKeyDownCallback, "");
	setProperty(Ids::uiCustomMouseDoubleClickCallback, "");
	setProperty(Ids::uiCustomMouseWheelMoveCallback, "");

	setSize (64,64);
}

CtrlrCustomComponent::~CtrlrCustomComponent()
{
}

void CtrlrCustomComponent::paint (Graphics &g)
{
	if (paintCbk && !paintCbk.wasObjectDeleted())
	{
		if (paintCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (paintCbk, this, g);
		}
	}
}

bool CtrlrCustomComponent::keyPressed (const KeyPress &key, Component *originatingComponent)
{
	return (false);
}

bool CtrlrCustomComponent::keyStateChanged (bool isKeyDown, Component *originatingComponent)
{
	return (false);
}

void CtrlrCustomComponent::paintOverChildren(Graphics &g)
{
	if (paintOverChildrenCbk && !paintOverChildrenCbk.wasObjectDeleted())
	{
		if (paintOverChildrenCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (paintOverChildrenCbk, this, g);
		}
	}
}

void CtrlrCustomComponent::resized()
{
	if (resizedCbk && !resizedCbk.wasObjectDeleted())
	{
		if (resizedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (resizedCbk, this);
		}
	}
	CtrlrComponent::resized();
}

void CtrlrCustomComponent::mouseMove (const MouseEvent &e)
{
	if (mouseMoveCbk && !mouseMoveCbk.wasObjectDeleted())
	{
		if (mouseMoveCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (mouseMoveCbk, this, e);
		}
	}
}

void CtrlrCustomComponent::mouseDown (const MouseEvent &e)
{
	if (mouseDownCbk && !mouseDownCbk.wasObjectDeleted())
	{
		if (mouseDownCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (mouseDownCbk, this, e);
		}
	}
}

void CtrlrCustomComponent::mouseUp (const MouseEvent &e)
{
	if (mouseUpCbk && !mouseUpCbk.wasObjectDeleted())
	{
		if (mouseUpCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (mouseUpCbk, this, e);
		}
	}
}

void CtrlrCustomComponent::mouseDrag (const MouseEvent &e)
{
	if (mouseDragCbk && !mouseDragCbk.wasObjectDeleted())
	{
		if (mouseDragCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (mouseDragCbk, this, e);
		}
	}
}

void CtrlrCustomComponent::mouseEnter (const MouseEvent &e)
{
	if (mouseEnterCbk && !mouseEnterCbk.wasObjectDeleted())
	{
		if (mouseEnterCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (mouseEnterCbk, this, e);
		}
	}
}

void CtrlrCustomComponent::mouseExit (const MouseEvent &e)
{
	if (mouseExitCbk && !mouseExitCbk.wasObjectDeleted())
	{
		if (mouseExitCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (mouseExitCbk, this, e);
		}
	}
}

const double CtrlrCustomComponent::getComponentMaxValue()
{
	return (127);
}

const String CtrlrCustomComponent::getComponentText()
{
	return (String::empty);
}

void CtrlrCustomComponent::setComponentText (const String &componentText)
{
}

void CtrlrCustomComponent::setComponentValue (const double newValue, const bool sendChangeMessage)
{
}

const double CtrlrCustomComponent::getComponentValue()
{
	return (1);
}

const int CtrlrCustomComponent::getComponentMidiValue()
{
	return (1);
}

void CtrlrCustomComponent::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiCustomResizedCallback)
	{
		if (isInvalidMethodName (getProperty(property)))
			return;

		resizedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiCustomPaintCallback)
	{
		if (isInvalidMethodName (getProperty(property)))
			return;

		paintCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiCustomMouseEnterCallback)
	{
		if (isInvalidMethodName (getProperty(property)))
			return;

		mouseEnterCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiCustomMouseExitCallback)
	{
		if (isInvalidMethodName (getProperty(property)))
			return;

		mouseExitCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiCustomMouseDownCallback)
	{
		if (isInvalidMethodName (getProperty(property)))
			return;

		mouseDownCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiCustomMouseUpCallback)
	{
		if (isInvalidMethodName (getProperty(property)))
			return;

		mouseUpCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiCustomMouseDragCallback)
	{
		if (isInvalidMethodName (getProperty(property)))
			return;

		mouseDragCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiCustomMouseMoveCallback)
	{
		if (isInvalidMethodName (getProperty(property)))
			return;

		mouseMoveCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiCustomMouseDoubleClickCallback)
	{
		if (isInvalidMethodName (getProperty(property)))
			return;

		mouseDoubleClickCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiCustomMouseWheelMoveCallback)
	{
		if (isInvalidMethodName (getProperty(property)))
			return;

		mouseWheelMoveCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}

	CtrlrComponent::valueTreePropertyChanged(treeWhosePropertyHasChanged, property);
	CtrlrComponent::resized();
}

void CtrlrCustomComponent::valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded)
{
}

void CtrlrCustomComponent::restoreState (const ValueTree &savedState)
{
	CtrlrComponent::restoreState (savedState);
}

void CtrlrCustomComponent::mouseDoubleClick (const MouseEvent &e)
{
	if (mouseDoubleClickCbk && !mouseDoubleClickCbk.wasObjectDeleted())
	{
		if (mouseDoubleClickCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (mouseDoubleClickCbk, this, e);
		}
	}
}

void CtrlrCustomComponent::mouseWheelMove (const MouseEvent &e, const MouseWheelDetails& wheel)
{
	if (mouseWheelMoveCbk && !mouseWheelMoveCbk.wasObjectDeleted())
	{
		if (mouseWheelMoveCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (mouseWheelMoveCbk, this, e, wheel.deltaX, wheel.deltaY);
		}
	}
}