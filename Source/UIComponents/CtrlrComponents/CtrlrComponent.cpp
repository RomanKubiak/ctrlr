#include "stdafx_luabind.h"
#include "CtrlrComponent.h"
#include "CtrlrIDs.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrFontManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrLuaManager.h"
#include "CtrlrComponentSelection.h"
#include "CtrlrUtilitiesGUI.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrComponents/Groups/CtrlrGroup.h"
#include "CtrlrComponents/Groups/CtrlrTabsComponent.h"
#include "JuceClasses/LLookAndFeel.h"

/*#include "CtrlrMacros.h"
#include "CtrlrProcessor.h"
#include "CtrlrLuaManager.h"
#include "CtrlrUtilitiesGUI.h"
#include "../CtrlrComponentSelection.h"
#include "CtrlrManager/CtrlrManager.h"
#include "Groups/CtrlrTabsComponent.h"
#include "Groups/CtrlrGroup.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrLog.h"
#include "Lua/JuceClasses/LLookAndFeel.h"
*/

/** Border implementation */
CtrlrComponentResizableBorder::CtrlrComponentResizableBorder(CtrlrComponent *_owner, ComponentBoundsConstrainer *constrainer)
			: ResizableBorderComponent(_owner, constrainer), owner(_owner)
{
	setLookAndFeel (this);
}

void CtrlrComponentResizableBorder::paint (Graphics &g)
{
	if (owner->getRestoreState())
		return;

	ResizableBorderComponent::paint (g);
}

void CtrlrComponentResizableBorder::drawResizableFrame (Graphics& g, int w, int h, const BorderSize<int> &bSize)
{
	g.setColour (Colours::orange.withAlpha (0.4f));
	g.fillRect (0, 0, w, bSize.getTop());
	g.fillRect (0, 0, bSize.getLeft(), h);
	g.fillRect (0, h - bSize.getBottom(), w, bSize.getBottom());
	g.fillRect (w - bSize.getRight(), 0, bSize.getRight(), h);
	g.drawRect (bSize.getLeft() - 1, bSize.getTop() - 1,
				w - bSize.getRight() - bSize.getLeft() + 2,
				h - bSize.getTop() - bSize.getBottom() + 2);
}

/** */

CtrlrComponent::CtrlrComponent(CtrlrModulator &_owner)
	:	selectionBorder(this, 0),
		componentTree(Ids::component),
		owner(_owner),
		restoreStateInProgress(true),
		glowEffect(nullptr),
		shadowEffect(nullptr),
		snapDimSize(0)
{
	owner.getModulatorTree().addChild (componentTree, -1, nullptr);
	componentTree.addListener (this);

	selectionBorder.setBorderThickness (BorderSize<int>(6));
	selectionBorder.setAlwaysOnTop (true);
	selectionBorder.addComponentListener (this);
	selectionBorder.addMouseListener (this, true);
	addChildComponent (&selectionBorder, -1);

	componentNameLabel.setText (getVisibleName(), dontSendNotification);
	componentNameLabel.setJustificationType (Justification::centred);
	componentNameLabel.addMouseListener(this, true);
	addChildComponent (&componentNameLabel);

	setProperty (Ids::componentLabelPosition, "top");
	setProperty (Ids::componentLabelJustification, "centred");
	setProperty (Ids::componentLabelHeight, "14");
	setProperty (Ids::componentLabelWidth, 0);
	setProperty (Ids::componentLabelVisible, true);
	setProperty (Ids::componentLabelAlwaysOnTop, true);
	setProperty (Ids::componentSentBack, false);
	setProperty (Ids::componentLabelColour, "0xff000000");
	setProperty (Ids::componentLabelFont, FONT2STR (Font(12)));
	setProperty (Ids::componentVisibleName, owner.getProperty(Ids::name));
	setProperty (Ids::componentMouseCursor, (int)MouseCursor::NormalCursor);
	setProperty (Ids::componentGroupName, String::empty);
	setProperty (Ids::componentGroupped, false);
	setProperty (Ids::componentSnapSize, 0);
	setProperty (Ids::componentIsLocked, false);
	setProperty (Ids::componentDisabled, false);
	setProperty (Ids::componentRadioGroupId, 0);
	setProperty (Ids::componentRadioGroupNotifyMidi, true);
	setProperty (Ids::componentVisibility, true);
	setProperty (Ids::componentEffect, 0);
	setProperty (Ids::componentEffectRadius, 1);
	setProperty (Ids::componentEffectColour, "0xff000000");
	setProperty (Ids::componentEffectOffsetX, 0);
	setProperty (Ids::componentEffectOffsetY, 0);
	setProperty (Ids::componentExcludedFromLabelDisplay, false);
	setProperty (Ids::componentValueDecimalPlaces, 0);
	setProperty (Ids::componentLuaMouseMoved, COMBO_ITEM_NONE);
	setProperty (Ids::componentLuaMouseDown, COMBO_ITEM_NONE);
	setProperty (Ids::componentLuaMouseDrag, COMBO_ITEM_NONE);
	setProperty (Ids::componentLuaMouseDoubleClick, COMBO_ITEM_NONE);
}

CtrlrComponent::~CtrlrComponent()
{
	if (shadowEffect)
	{
		delete (shadowEffect.release());
	}
	if (glowEffect)
	{
		delete (glowEffect.release());
	}

	componentTree.removeListener (this);
	masterReference.clear();
}

void CtrlrComponent::resized()
{
	const int w = getWidth();
	const int h = getHeight();

	if (!getTransform().isIdentity())
		return;

	if ((bool)getProperty(Ids::componentLabelVisible) == true)
	{
		if (getProperty(Ids::componentLabelPosition).toString() == Ids::top.toString())
		{
			componentNameLabel.setBounds (	0,
										0,
										(int)getProperty(Ids::componentLabelWidth)	? (int)getProperty(Ids::componentLabelWidth) : w,
										(int)getProperty(Ids::componentLabelHeight)	? (int)getProperty(Ids::componentLabelHeight) : h);
		}
		else if (getProperty(Ids::componentLabelPosition) == Ids::bottom.toString())
		{
			componentNameLabel.setBounds (	0,
										h-(int)((int)getProperty(Ids::componentLabelHeight)		? (int)getProperty(Ids::componentLabelHeight) : h),
										(int)getProperty(Ids::componentLabelWidth)	? (int)getProperty(Ids::componentLabelWidth) : w,
										(int)getProperty(Ids::componentLabelHeight)	? (int)getProperty(Ids::componentLabelHeight) : h);
		}
		else if (getProperty(Ids::componentLabelPosition) == Ids::left.toString())
		{
			componentNameLabel.setBounds (	0,
										(h/2)-((int)getProperty(Ids::componentLabelHeight)/2),
										(int)getProperty(Ids::componentLabelWidth)	? (int)getProperty(Ids::componentLabelWidth) : w,
										(int)getProperty(Ids::componentLabelHeight)	? (int)getProperty(Ids::componentLabelHeight) : h);
		}
		else if (getProperty(Ids::componentLabelPosition) == Ids::right.toString())
		{
			componentNameLabel.setBounds (	(int)(w-(int)(getProperty(Ids::componentLabelWidth) ? (int)getProperty(Ids::componentLabelWidth) : w)),
										(h/2)-((int)getProperty(Ids::componentLabelHeight)/2),
										(int)getProperty(Ids::componentLabelWidth)  ? (int)getProperty(Ids::componentLabelWidth) : w,
										(int)getProperty(Ids::componentLabelHeight) ? (int)getProperty(Ids::componentLabelHeight) : h);
		}
	}

	const Rectangle<int> bounds = getBounds ();
	setProperty (Ids::componentRectangle, getBoundsInParent().toString(), true);

	if (snapDimSize>0)
	{
		setSize (snapDim(w), snapDim(h));
	}

	if (restoreStateInProgress == false)
	{
		selectionBorder.setBounds (0, 0, w, h);
	}
}

void CtrlrComponent::mouseDoubleClick(const MouseEvent &e)
{
    if (mouseDoubleClickCbk && !mouseDoubleClickCbk.wasObjectDeleted())
	{
		if (mouseDoubleClickCbk->isValid())
		{
			owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().call (mouseDoubleClickCbk, this, e);
		}
	}
}

void CtrlrComponent::mouseDown(const MouseEvent &e)
{
    if (mouseDownCbk && !mouseDownCbk.wasObjectDeleted())
	{
		if (mouseDownCbk->isValid())
		{
			owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().call (mouseDownCbk, this, e);
		}
	}
}

int CtrlrComponent::snapDim(int dim)
{
	if (snapDimSize <= 0)
		return (dim);

	dim = ((dim + snapDimSize * 1024 + snapDimSize / 2) / snapDimSize - 1024) * snapDimSize;
	return (dim);
}

void CtrlrComponent::moved()
{
	if (!getTransform().isIdentity())
		return;

	setProperty (Ids::componentRectangle, getBoundsInParent().toString(), true);
}

void CtrlrComponent::mouseMove (const MouseEvent &e)
{
	if (mouseMoveCbk && !mouseMoveCbk.wasObjectDeleted())
	{
		if (mouseMoveCbk->isValid())
		{
			owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().call (mouseMoveCbk, this, e);
		}
	}
}

void CtrlrComponent::mouseDrag (const MouseEvent &e)
{
    if (mouseDragCbk && !mouseDragCbk.wasObjectDeleted())
	{
		if (mouseDragCbk->isValid())
		{
			owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().call (mouseDragCbk, this, e);
		}
	}
}

void CtrlrComponent::componentMovedOrResized (Component &component, bool wasMoved, bool wasResized)
{
	CtrlrComponent::resized();
}

void CtrlrComponent::addAndMakeVisible (Component *child, int zOrder)
{
	Component::addAndMakeVisible (child, zOrder);
	child->addMouseListener (this, true);
	child->addComponentListener (this);
}

void CtrlrComponent::visibilityChanged()
{
}

void CtrlrComponent::changeListenerCallback (ChangeBroadcaster* source)
{
	CtrlrComponentSelection *selection = dynamic_cast<CtrlrComponentSelection *>(source);

	if (selection != 0)
	{
		if (selection->isSelected (this))
		{
			if ((bool)getProperty(Ids::componentIsLocked) == true)
				return;
			selectionBorder.setVisible (true);
		}
		else
		{
			selectionBorder.setVisible (false);
		}

		CtrlrComponent::resized();
	}
}

UndoManager* CtrlrComponent::getUndoManager() const
{
	return (owner.getOwnerPanel().getPanelUndoManager());
}

void CtrlrComponent::restoreState (const ValueTree &savedState)
{
	restoreStateInProgress = true;

	restoreProperties (savedState, componentTree, nullptr);

	for (int i=0; i<savedState.getNumChildren(); i++)
	{
		componentTree.addChild (savedState.getChild(i).createCopy(), -1, 0);
	}

	restoreStateInProgress = false;
	resized();
}

Rectangle<int> CtrlrComponent::getUsableRect()
{
	Rectangle<int> r = Component::getLocalBounds();
	if ((bool)getProperty(Ids::componentLabelVisible) == false)
	{
		return (r);
	}

	if (getProperty(Ids::componentLabelPosition) == Ids::top.toString())
	{
		return (r.removeFromBottom(componentNameLabel.getHeight()).withTop(componentNameLabel.getHeight()));
	}

	if (getProperty(Ids::componentLabelPosition) == Ids::bottom.toString())
	{
		return (r.withHeight(r.getHeight()-componentNameLabel.getHeight()));
	}

	if (getProperty(Ids::componentLabelPosition) == Ids::left.toString())
	{
		return (r.withLeft (componentNameLabel.getWidth()).withWidth(r.getWidth() - componentNameLabel.getWidth()));
	}

	if (getProperty(Ids::componentLabelPosition) == Ids::right.toString())
	{
		r.removeFromRight (componentNameLabel.getWidth());
		return (r);
	}
	return (r);
}

void CtrlrComponent::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::componentVisibleName)
	{
		componentNameLabel.setText (getVisibleName(), dontSendNotification);
	}
	else if (	property == Ids::componentLabelPosition
		||	property == Ids::componentLabelHeight
		||	property == Ids::componentLabelWidth
		||	property == Ids::componentLabelVisible
		||	property == Ids::componentLabelAlwaysOnTop
		||  property == Ids::componentSentBack
		||  property == Ids::componentLabelJustification)
	{
		componentNameLabel.setSize (getWidth(), getProperty(Ids::componentLabelHeight));
		componentNameLabel.setVisible (getProperty(Ids::componentLabelVisible));
		componentNameLabel.setAlwaysOnTop (getProperty(Ids::componentLabelAlwaysOnTop));
		componentNameLabel.setText (getVisibleName(), dontSendNotification);
		componentNameLabel.setJustificationType (justificationFromProperty(getProperty(Ids::componentLabelJustification)));
		if ((bool)getProperty(Ids::componentLabelAlwaysOnTop) == false)
		{
			componentNameLabel.toBack ();
		}
		else
		{
			componentNameLabel.toFront(false);
		}
	}
	else if (property == Ids::componentMouseCursor)
	{
		setMouseCursor((MouseCursor::StandardCursorType)(int)getProperty(property));
		for (int i=0; i<getNumChildComponents(); i++)
		{
			getChildComponent(i)->setMouseCursor((MouseCursor::StandardCursorType)(int)getProperty(property));
		}
	}
	else if (property == Ids::componentLabelColour)
	{
		componentNameLabel.setColour (Label::textColourId, VAR2COLOUR(getProperty(Ids::componentLabelColour)));
	}
	else if (property == Ids::componentLabelFont)
	{
		componentNameLabel.setFont (getFontManager().getFontFromString (getProperty(Ids::componentLabelFont)));
	}
	else if (property == Ids::componentRectangle)
	{
		setBounds (VAR2RECT(getProperty(property)));
	}
	else if (property == Ids::componentRadioGroupId)
	{
		owner.getOwnerPanel().setRadioGroupId(this, getProperty(property));
	}
	else if (property == Ids::componentGroupped)
	{
		setGroupped ((bool)getProperty (property));
	}
	else if (property == Ids::componentEffect ||
		property == Ids::componentEffectColour ||
		property == Ids::componentEffectOffsetX ||
		property == Ids::componentEffectOffsetY ||
		property == Ids::componentEffectRadius)
	{
		setEffect();
	}
	else if (property == Ids::componentVisibility)
	{
		if ((bool)owner.getOwnerPanel().getEditor()->getProperty (Ids::uiPanelEditMode) == true)
		{
			if ((bool)getProperty(property) == false)
			{
				setAlpha (0.5f);
			}
			else
			{
				setAlpha (1.0f);
				setVisible (true);
			}
		}
		else
		{
			setAlpha (1.0f);
			setVisible ((bool)getProperty(property));
		}
	}
	else if (property == Ids::componentSnapSize)
	{
		snapDimSize = getProperty(property);
	}
	else if (property == Ids::componentDisabled)
	{
		for (int i=0; i<getNumChildComponents(); i++)
		{
			getChildComponent(i)->setEnabled (!getProperty(property));
		}
	}
	else if (property == Ids::componentLuaMouseMoved)
	{
		if (isInvalidMethodName (getProperty(property)))
			return;

		mouseMoveCbk = owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::componentLuaMouseDown)
	{
		if (isInvalidMethodName (getProperty(property)))
			return;

		mouseDownCbk = owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::componentLuaMouseDrag)
	{
		if (isInvalidMethodName (getProperty(property)))
			return;

		mouseDragCbk = owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::componentLuaMouseDoubleClick)
	{
		if (isInvalidMethodName (getProperty(property)))
			return;

		mouseDoubleClickCbk = owner.getOwnerPanel().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	if (restoreStateInProgress == false)
	{
		repaint();
		resized();
	}
}

void CtrlrComponent::setEffect()
{
	if (getProperty(Ids::componentEffect) == "No Effect")
	{
		setComponentEffect (nullptr);
	}

	if (getProperty(Ids::componentEffect) == "Shadow")
	{
		if (shadowEffect == nullptr)
		{
			shadowEffect = new DropShadowEffect();
		}

		DropShadow ds;
		ds.colour = VAR2COLOUR(getProperty(Ids::componentEffectColour));
		ds.offset = Point<int> (getProperty(Ids::componentEffectOffsetX), getProperty(Ids::componentEffectOffsetY));
		ds.radius = getProperty(Ids::componentEffectRadius);

		shadowEffect->setShadowProperties (ds);
		setComponentEffect (shadowEffect);
	}

	if (getProperty(Ids::componentEffect) == "Glow")
	{
		glowEffect = new GlowEffect();
		glowEffect->setGlowProperties (getProperty(Ids::componentEffectRadius), VAR2COLOUR(getProperty(Ids::componentEffectColour)));
		setComponentEffect (glowEffect);
	}
}

void CtrlrComponent::setProperty (const Identifier& name, const var &newValue, const bool isUndoable)
{
	if (isUndoable)
	{
		componentTree.setProperty (name, newValue, getUndoManager());
	}
	else
	{
		componentTree.setProperty (name, newValue, 0);
	}
}

void CtrlrComponent::removeProperty (const Identifier &name)
{
	componentTree.removeProperty(name, getUndoManager());
}

const String CtrlrComponent::getVisibleName()
{
	if (getProperty(Ids::componentVisibleName).toString() != String::empty)
	{
		return (getProperty(Ids::componentVisibleName));
	}
	else
	{
		return (owner.getProperty(Ids::name));
	}
}

const String CtrlrComponent::getComponentGroup()
{
	return (getProperty(Ids::componentGroupName));
}

const String CtrlrComponent::getComponentTab()
{
	return (getProperty(Ids::componentTabName));
}

void CtrlrComponent::setComponentTab (const String &newTab)
{
	if (newTab == String::empty)
	{
		componentTree.removeProperty(Ids::componentTabName, 0);
		componentTree.removeProperty(Ids::componentTabId, 0);
	}
	else
	{
		setProperty (Ids::componentTabName, newTab, false);
	}
}

void CtrlrComponent::setGroupped (const bool addToGroup)
{
	CtrlrGrouppingComponent *groupComponent 	= nullptr;
	int groupSubIndex							= getProperty (Ids::componentTabId);

	if (addToGroup)
	{
		/* we need to find the group component based on it's name */
        groupComponent = dynamic_cast <CtrlrGrouppingComponent*> (owner.getOwnerPanel().getComponent (getProperty(Ids::componentGroupName)));

        if (groupComponent == nullptr)
			groupComponent = dynamic_cast <CtrlrGrouppingComponent*> (owner.getOwnerPanel().getComponent (getProperty(Ids::componentTabName)));
	}
	else
	{
		/* we already are a member of a group, we can just fetch it
			as it's our parent at some point */
		groupComponent = findParentComponentOfClass<CtrlrGroup>();

		if (groupComponent == nullptr)
			groupComponent = findParentComponentOfClass<CtrlrTabsComponent>();
	}

	if (groupComponent != nullptr)
	{
		groupComponent->setOwned (this, groupSubIndex, addToGroup);
	}
}

void CtrlrComponent::removeFromTab ()
{
	CtrlrModulator *tabsModulator = owner.getOwnerPanel().getModulator(getProperty(Ids::componentTabName));
	if (tabsModulator)
	{
		CtrlrTabsComponent *tabsComponent = dynamic_cast<CtrlrTabsComponent*>(tabsModulator->getComponent());
		if (tabsComponent)
		{
			tabsComponent->setOwned (this, getProperty(Ids::componentTabId), false);
		}
	}
}

int CtrlrComponent::snapPosition (int pos, int snapSize, const bool allowSnap)
{
	if (snapSize <= 0 || allowSnap == false)
		return pos;

	pos = ((pos + snapSize * 1024 + snapSize / 2) / snapSize - 1024) * snapSize;
    return pos;
}

int CtrlrComponent::getComponentRadioGroupId()
{
	return (getProperty(Ids::componentRadioGroupId));
}

void CtrlrComponent::panelEditModeChanged(const bool isInEditMode)
{
	if (isInEditMode)
	{
		if ((bool)getProperty(Ids::componentVisibility) == false)
		{
			setVisible (true);
			if (owner.getOwnerPanel().getEditor())
				setAlpha ((float)owner.getOwnerPanel().getEditor()->getProperty(Ids::uiPanelInvisibleComponentAlpha));
			else
				setAlpha(0.5f);
		}

		if (owner.getOwnerPanel().getEditor())
		{
			if ((bool)owner.getOwnerPanel().getEditor()->getProperty (Ids::uiPanelDisabledOnEdit) == true)
			{
				for (int i=0; i<getNumChildComponents(); i++)
				{
					if (getChildComponent(i) == &selectionBorder || getChildComponent(i) == &componentNameLabel)
						continue;

					getChildComponent(i)->setEnabled (false);
				}
			}
		}
	}
	else
	{
		setVisible ((bool)getProperty(Ids::componentVisibility));
		if ((bool)owner.getOwnerPanel().getEditor()->getProperty (Ids::uiPanelDisabledOnEdit) == true)
		{
			for (int i=0; i<getNumChildComponents(); i++)
			{
				if (getChildComponent(i) == &selectionBorder || getChildComponent(i) == &componentNameLabel)
					continue;

				getChildComponent(i)->setEnabled (true);
			}
		}
	}
}

const String CtrlrComponent::getTextForValue(const double value)
{
	if ((int)getProperty(Ids::componentValueDecimalPlaces) > 0)
		return (String(value, getProperty(Ids::componentValueDecimalPlaces)));
	else
		return (String((int)value));
}

void CtrlrComponent::setComponentMidiValue (const int newValue, const bool sendChangeMessage)
{
	setComponentValue (newValue, sendChangeMessage);
}

int CtrlrComponent::getComponentMidiValue ()
{
	return (getComponentValue());
}

bool CtrlrComponent::getRestoreState()
{
	return (restoreStateInProgress);
}

CtrlrFontManager &CtrlrComponent::getFontManager()
{
	return (owner.getOwnerPanel().getCtrlrManagerOwner().getFontManager());
}

double CtrlrComponent::getMaximum()
{
	return (owner.getMaxModulatorValue());
}

double CtrlrComponent::getMinimum()
{
	return (owner.getMinModulatorValue());
}

void CtrlrComponent::setCustomLookAndFeel (LookAndFeelBase *customLookAndFeel)
{
    setLookAndFeel (customLookAndFeel);
    customLookAndFeelChanged(customLookAndFeel);
}

void CtrlrComponent::setCustomLookAndFeel (const luabind::object &_customLookAndFeel)
{
    try
    {
        setCustomLookAndFeel (luabind::object_cast <LookAndFeelBase*> (_customLookAndFeel));
    }
    catch (luabind::error &e)
    {
        _WRN("Unable to cast passed LookAndFeel object to anything usable: "+_STR(e.what()));
    }
}

bool CtrlrComponent::isInternal()
{
	if (!componentTree.hasProperty(Ids::componentInternalFunction))
		return (false);

	if (getProperty(Ids::componentInternalFunction, String::empty) != COMBO_ITEM_NONE)
		return (true);

	return (false);
}

void CtrlrComponent::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrComponent, bases<CtrlrLuaObject, Component> >("CtrlrComponent")
			.def("repaint", (void (Component::*)()) &Component::repaint)
			.def("getWidth", &Component::getWidth)
			.def("getHeight", &Component::getHeight)
			.def("setSize", &Component::setSize)
			.def("getX", &Component::getX)
			.def("getY", &Component::getY)
			.def("isVisible", &Component::isVisible)
			.def("setVisible", &Component::setVisible)
			.def("isMouseButtonDown", &Component::isMouseButtonDown)
			.def("isMouseOver", &Component::isMouseOver)
			.def("isMouseOverOrDragging", &Component::isMouseOverOrDragging)
			.def("keyPressed", &Component::keyPressed)
			.def("getBounds", &Component::getBounds)
			.def("getRect", &CtrlrComponent::getBounds)
			//.def("setBounds", (void (Component::*)(const Rectangle<int> &) )&CtrlrComponent::setBounds)
			.def("setBounds", (void (Component::*)(int, int, int, int))&CtrlrComponent::setBounds)
			.def("getComponentText", &CtrlrComponent::getComponentText)
			.def("setComponentText", &CtrlrComponent::setComponentText)
			.def("setTransform", &Component::setTransform)
			.def("getTransform", &Component::getTransform)
			.def("click", &CtrlrComponent::click)
			.def("setComponentValue", &CtrlrComponent::setComponentValue)
			.def("setValue", &CtrlrComponent::setComponentValue)
			.def("getComponentValue", &CtrlrComponent::getComponentValue)
			.def("getValue", &CtrlrComponent::getComponentValue)
			.def("setComponentMidiValue", &CtrlrComponent::setComponentMidiValue)
			.def("setMidiValue", &CtrlrComponent::setComponentMidiValue)
			.def("getComponentMidiValue", &CtrlrComponent::getComponentMidiValue)
			.def("getMidiValue", &CtrlrComponent::getComponentMidiValue)
			.def("getMaximum", &CtrlrComponent::getMaximum)
			.def("getMinimum", &CtrlrComponent::getMinimum)
			.def("getTextForValue", &CtrlrComponent::getTextForValue)
			.def("getOwner", &CtrlrComponent::getOwner)
			.def("setCustomLookAndFeel", (void (CtrlrComponent::*)(const luabind::object &)) &CtrlrComponent::setCustomLookAndFeel)
	];
}
