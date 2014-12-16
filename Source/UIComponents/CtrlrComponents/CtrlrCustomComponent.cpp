#include "stdafx.h"
#include "CtrlrLuaManager.h"
#include "CtrlrCustomComponent.h"
#include "CtrlrProcessor.h"
#include "CtrlrPanel/CtrlrPanel.h"

CtrlrCustomComponent::CtrlrCustomComponent(CtrlrModulator &_owner)
	: CtrlrComponent(_owner), isADragAndDropContainer(false)
{
	setProperty(Ids::uiCustomResizedCallback, COMBO_ITEM_NONE);
	setProperty(Ids::uiCustomPaintCallback, COMBO_ITEM_NONE);
	setProperty(Ids::uiCustomPaintOverChildrenCallback, COMBO_ITEM_NONE);
	setProperty(Ids::uiCustomMouseDownCallback, COMBO_ITEM_NONE);
	setProperty(Ids::uiCustomMouseUpCallback, COMBO_ITEM_NONE);
	setProperty(Ids::uiCustomMouseEnterCallback, COMBO_ITEM_NONE);
	setProperty(Ids::uiCustomMouseExitCallback, COMBO_ITEM_NONE);
	setProperty(Ids::uiCustomMouseMoveCallback, COMBO_ITEM_NONE);
	setProperty(Ids::uiCustomMouseDragCallback, COMBO_ITEM_NONE);
	setProperty(Ids::uiCustomKeyDownCallback, COMBO_ITEM_NONE);
	setProperty(Ids::uiCustomKeyStateChangedCallback, COMBO_ITEM_NONE);
	setProperty(Ids::uiCustomMouseDoubleClickCallback, COMBO_ITEM_NONE);
	setProperty(Ids::uiCustomMouseWheelMoveCallback, COMBO_ITEM_NONE);

	setProperty(Ids::uiCustomStartDraggingCallback, COMBO_ITEM_NONE);
	setProperty(Ids::uiCustomIsInterestedInDragSourceCallback, COMBO_ITEM_NONE);
	setProperty(Ids::uiCustomItemDragEnterCallback, COMBO_ITEM_NONE);
	setProperty(Ids::uiCustomItemDragMoveCallback, COMBO_ITEM_NONE);
	setProperty(Ids::uiCustomItemDragExitCallback, COMBO_ITEM_NONE);
	setProperty(Ids::uiCustomItemDroppedCallback, COMBO_ITEM_NONE);

	setProperty(Ids::uiCustomDragAndDropTarget, false);
	setProperty(Ids::uiCustomDragAndDropContainer, false);
	setProperty(Ids::uiCustomDrawDragImageWhenOver, false);
	setProperty(Ids::uiCustomAllowExternalDrags, false);

    setProperty(Ids::uiCustomMouseDownGrabsFocus, false);
    setProperty(Ids::uiCustomWantsKeyboardFocus, false);
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
    if (keyPressedCbk && !keyPressedCbk.wasObjectDeleted())
	{
		if (keyPressedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (keyPressedCbk, this, key, originatingComponent);
		}
	}
	return (false);
}

bool CtrlrCustomComponent::keyStateChanged (bool isKeyDown, Component *originatingComponent)
{
    if (keyStateChangedCbk && !keyStateChangedCbk.wasObjectDeleted())
	{
		if (keyStateChangedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (keyStateChangedCbk, this, isKeyDown, originatingComponent);
		}
	}
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
    _DBG("CtrlrCustomComponent::mouseDrag");
	if (isADragAndDropContainer)
	{
		if (dadStartCbk && !dadStartCbk.wasObjectDeleted())
		{
			if (dadStartCbk->isValid())
			{
			    DragAndDropContainer* const dragContainer = DragAndDropContainer::findParentDragContainerFor (this);
			    if (dragContainer)
                {
                    DragAndDropSourceDetails details = owner.getOwner().getCtrlrLuaManager().getMethodManager().callWithRet (dadStartCbk, this, e);
                    Point<int> offset(details.getImageOffsetX(), details.getImageOffsetY());
                    dragContainer->startDragging (details.getDescription(), this, details.getDragImage(), true, &offset);
                }
			}
		}
	}

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
    _DBG("CtrlrCustomComponent::mouseEnter");
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

double CtrlrCustomComponent::getComponentMaxValue()
{
	return (127);
}

const String CtrlrCustomComponent::getComponentText()
{
    if (getTextCbk && !getTextCbk.wasObjectDeleted())
	{
		if (getTextCbk->isValid())
		{
			return (owner.getOwner().getCtrlrLuaManager().getMethodManager().callWithRetString (getTextCbk, this));
		}
	}

	return (String::empty);
}

void CtrlrCustomComponent::setComponentText (const String &componentText)
{
    if (setTextCbk && !setTextCbk.wasObjectDeleted())
	{
		if (setTextCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (setTextCbk, this, componentText);
		}
	}
}

void CtrlrCustomComponent::setComponentValue (const double newValue, const bool sendChangeMessage)
{
    if (setValueCbk && !setValueCbk.wasObjectDeleted())
	{
		if (setValueCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (setValueCbk, this, newValue, sendChangeMessage);
		}
	}
}

double CtrlrCustomComponent::getComponentValue()
{
	if (getValueCbk && !getValueCbk.wasObjectDeleted())
	{
		if (getValueCbk->isValid())
		{
			return (owner.getOwner().getCtrlrLuaManager().getMethodManager().call (getValueCbk, this));
		}
	}

	return (0);
}

int CtrlrCustomComponent::getComponentMidiValue()
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
	else if (property == Ids::uiCustomKeyDownCallback)
	{
		if (isInvalidMethodName (getProperty(property)))
			return;

		keyPressedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiCustomKeyStateChangedCallback)
	{
		if (isInvalidMethodName (getProperty(property)))
			return;

		keyStateChangedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiCustomMouseDownGrabsFocus)
    {
        setMouseClickGrabsKeyboardFocus ((bool)getProperty(property));
    }
    else if (property == Ids::uiCustomWantsKeyboardFocus)
    {
        setWantsKeyboardFocus ((bool)getProperty(property));

        if (getWantsKeyboardFocus())
        {
            addKeyListener (this);
        }
    }
    else if (property == Ids::uiCustomSetText)
    {
        if (isInvalidMethodName (getProperty(property)))
			return;

		setTextCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
    }
    else if (property == Ids::uiCostomGetText)
    {
        if (isInvalidMethodName (getProperty(property)))
			return;

		getTextCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
    }
    else if (property == Ids::uiCustomSetValue)
    {
        if (isInvalidMethodName (getProperty(property)))
			return;

		setValueCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
    }
    else if (property == Ids::uiCustomGetValue)
    {
        if (isInvalidMethodName (getProperty(property)))
			return;

		getValueCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
    }
	else if (property == Ids::uiCustomStartDraggingCallback)
    {
        if (isInvalidMethodName (getProperty(property)))
			return;

		dadStartCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
    }
	else if (property == Ids::uiCustomIsInterestedInDragSourceCallback)
    {
        if (isInvalidMethodName (getProperty(property)))
			return;

		dadIsInterestedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
    }
	else if (property == Ids::uiCustomItemDragEnterCallback)
    {
        if (isInvalidMethodName (getProperty(property)))
			return;

		dadEnterCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
    }
	else if (property == Ids::uiCustomItemDragMoveCallback)
    {
        if (isInvalidMethodName (getProperty(property)))
			return;

		dadMoveCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
    }
	else if (property == Ids::uiCustomItemDragExitCallback)
    {
        if (isInvalidMethodName (getProperty(property)))
			return;

		dadExitCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
    }
	else if (property == Ids::uiCustomItemDroppedCallback)
    {
        if (isInvalidMethodName (getProperty(property)))
			return;

		dadDroppedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
    }
	else if (property == Ids::uiCustomDragAndDropContainer)
	{
		isADragAndDropContainer = (bool) getProperty(property);
	}
    else
    {
        CtrlrComponent::valueTreePropertyChanged(treeWhosePropertyHasChanged, property);
        CtrlrComponent::resized();
    }
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

bool CtrlrCustomComponent::isInterestedInDragSource (const SourceDetails& dragSourceDetails)
{
	if (dadIsInterestedCbk && !dadIsInterestedCbk.wasObjectDeleted())
	{
		if (dadIsInterestedCbk->isValid())
		{
			return (owner.getOwner().getCtrlrLuaManager().getMethodManager().callWithRet (dadIsInterestedCbk, this, DragAndDropSourceDetails (dragSourceDetails)) ? true : false);
		}
	}
	return (false);
}

void CtrlrCustomComponent::itemDragEnter (const SourceDetails &dragSourceDetails)
{
	if (dadEnterCbk && !dadEnterCbk.wasObjectDeleted())
	{
		if (dadEnterCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (dadEnterCbk, this, DragAndDropSourceDetails (dragSourceDetails));
		}
	}
}

void CtrlrCustomComponent::itemDragMove (const SourceDetails &dragSourceDetails)
{
    _DBG("CtrlrCustomComponent::itemDragMove");
	if (dadMoveCbk && !dadMoveCbk.wasObjectDeleted())
	{
		if (dadMoveCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (dadMoveCbk, this, DragAndDropSourceDetails (dragSourceDetails));
		}
	}
}

void CtrlrCustomComponent::itemDragExit (const SourceDetails &dragSourceDetails)
{
	if (dadExitCbk && !dadExitCbk.wasObjectDeleted())
	{
		if (dadExitCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (dadExitCbk, this, DragAndDropSourceDetails (dragSourceDetails));
		}
	}
}

void CtrlrCustomComponent::itemDropped (const SourceDetails& dragSourceDetails)
{
	if (dadDroppedCbk && !dadDroppedCbk.wasObjectDeleted())
	{
		if (dadDroppedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (dadDroppedCbk, this, DragAndDropSourceDetails (dragSourceDetails));
		}
	}
}

bool CtrlrCustomComponent::shouldDrawDragImageWhenOver ()
{
	return ((bool)getProperty(Ids::uiCustomDrawDragImageWhenOver));
}

bool CtrlrCustomComponent::isInterestedInFileDrag (const StringArray& files)
{
    return (true);
}

bool CtrlrCustomComponent::isInterestedInTextDrag (const String& text)
{
    return (true);
}

void CtrlrCustomComponent::fileDragEnter (const StringArray& files, int x, int y)
{
}

void CtrlrCustomComponent::fileDragMove (const StringArray& files, int x, int y)
{
}

void CtrlrCustomComponent::fileDragExit (const StringArray& files)
{
}

void CtrlrCustomComponent::filesDropped (const StringArray& files, int x, int y)
{
}

void CtrlrCustomComponent::textDragEnter (const String& text, int x, int y)
{
}

void CtrlrCustomComponent::textDragMove (const String& text, int x, int y)
{
}

void CtrlrCustomComponent::textDragExit (const String& text)
{
}

void CtrlrCustomComponent::textDropped (const String& text, int x, int y)
{
}
