#include "stdafx.h"
#pragma warning(disable:4244)
#include "CtrlrLuaManager.h"
#include "CtrlrPanelCanvas.h"
#include "CtrlrMacros.h"
#include "CtrlrPanelEditor.h"
#include "CtrlrProcessor.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrComponents/CtrlrComponentTypeManager.h"
#include "CtrlrComponents/Groups/CtrlrTabsComponent.h"
#include "CtrlrComponents/Groups/CtrlrGroup.h"
#include "CtrlrComponents/CtrlrCustomComponent.h"
#include "CtrlrLog.h"

CtrlrPanelCanvas::CtrlrPanelCanvas (CtrlrPanelEditor &_owner)
	: owner(_owner),
      ctrlrPanelCanvasResizableBorder (0)
{

    addAndMakeVisible (ctrlrPanelCanvasResizableBorder = new ResizableBorderComponent (this, 0));
    ctrlrPanelCanvasResizableBorder->setName ("ctrlrPanelCanvasResizableBorder");

	ctrlrPanelCanvasResizableBorder->setAlwaysOnTop (true);
	initLayers();

    if (getOwner().getSelection())
        getOwner().getSelection()->addChangeListener (this);

	getOwner().getPanelEditorTree().addListener (this);
    setSize (600, 400);
}

CtrlrPanelCanvas::~CtrlrPanelCanvas()
{
	for (int i=0; i<getOwner().getOwner().getModulators().size(); i++)
	{
		if (getOwner().getOwner().getModulators() [i])
		{
			if (getOwner().getOwner().getModulators() [i]->getComponent())
			{
				CtrlrComponent *c = getOwner().getOwner().getModulators() [i]->getComponent();
				removeComponent (c, false);
			}
		}
	}

	getOwner().getPanelEditorTree().removeListener (this);
    deleteAndZero (ctrlrPanelCanvasResizableBorder);
}

//==============================================================================
void CtrlrPanelCanvas::paint (Graphics& g)
{
	if (paintCbk && !paintCbk.wasObjectDeleted())
	{
		if (paintCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (paintCbk, this, g);

			return;
		}
	}

	gradientFromProperty(g, getBounds(), getOwner().getObjectTree(), Ids::uiPanelBackgroundGradientType, Ids::uiPanelBackgroundColour1, Ids::uiPanelBackgroundColour2);
	g.fillAll();

	Colour c = VAR2COLOUR (getOwner().getProperty (Ids::uiPanelBackgroundColour1, "ffffffff"));

	if (ctrlrPanelBackgroundImage.isValid())
	{
		if ((int)getOwner().getProperty (Ids::uiPanelImageLayout) == 8192)
		{
			g.setTiledImageFill (ctrlrPanelBackgroundImage, 0, 0, (float)getOwner().getProperty (Ids::uiPanelImageAlpha)/255.0f);
			g.fillAll();
		}
		else
		{
			g.drawImageWithin (ctrlrPanelBackgroundImage,
								0,
								0,
								getWidth(),
								getHeight(),
								RectanglePlacement((int)getOwner().getProperty (Ids::uiPanelImageLayout)));
		}
	}
	if (getOwner().getProperty (Ids::uiPanelEditMode))
	{
		const int snapSize = (int)getOwner().getProperty (Ids::uiPanelSnapSize, 8);
		if (snapSize > 0)
		{
			backgroundFill = Image (Image::ARGB, snapSize, snapSize, true);
			Graphics g1(backgroundFill);
			Colour col2 = c.contrasting();

			if (snapSize > 2)
			{
				g1.setColour (col2.withAlpha (0.1f));
				g1.drawRect (0, 0, snapSize + 1, snapSize + 1);
			}

			g1.setColour (col2.withAlpha (0.35f));
			g1.setPixel (0, 0);

			if (backgroundFill.isValid())
			{
				g.setTiledImageFill (backgroundFill, 0, 0, 1.0f);
				g.fillAll();
			}
		}
	}
    //[/UserPaint]
}

void CtrlrPanelCanvas::resized()
{
    ctrlrPanelCanvasResizableBorder->setBounds (-8, -8, getWidth() + 8, getHeight() + 8);

	if (getTransform() == AffineTransform::identity)
		setProperty (Ids::uiPanelCanvasRectangle, getBounds().toString());

	layersResize();

	if (resizedCbk && !resizedCbk.wasObjectDeleted())
	{
		if (resizedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (resizedCbk, &owner.getOwner());
		}
	}
}

void CtrlrPanelCanvas::mouseDown (const MouseEvent& e)
{
	if (dynamic_cast<CtrlrCustomComponent*>(e.eventComponent) && e.mods.isPopupMenu())
	{
		return;
	}

	if (e.mods.isLeftButtonDown())
	{
		if (e.eventTime.toMilliseconds() == lastLMBMouseEventTime)
		{
			return;
		}
		else
		{
			lastLMBMouseEventTime = e.eventTime.toMilliseconds();
		}
	}

	if (e.mods.isRightButtonDown())
	{
		if (e.eventTime.toMilliseconds() == lastRMBMouseEventTime)
		{
			return;
		}
		else
		{
			lastRMBMouseEventTime = e.eventTime.toMilliseconds();
		}
	}

	componentWasDragged		= false;
	const bool editMode		= getOwner().getProperty(Ids::uiPanelEditMode);

    if (getOwner().getSelection())
    {
        if (getOwner().getSelection()->getNumSelected() > 1 && e.mods.isPopupMenu() && editMode)
        {
            handleRightClickOnMultiSelection(e);
            return;
        }
    }

	if (isLayer(e.eventComponent) && e.mods.isPopupMenu())
	{
		handleRightClickOnCanvas(e);
	}

	if (!isLayer(e.eventComponent) && !editMode && e.mods.isPopupMenu())
	{
		handleRightClickOnCanvas(e);
	}

	if (!isLayer(e.eventComponent) && editMode && e.mods.isPopupMenu())
	{
		handleRightClickOnComponent(e);
	}

	if (isLayer(e.eventComponent) && !e.mods.isPopupMenu() && editMode)
	{
        if (getOwner().getSelection())
            getOwner().getSelection()->deselectAll();

		addChildComponent (&lassoComponent);
        lassoComponent.beginLasso (e, this);

		sendChangeMessage();
	}

	if ( !isLayer(e.eventComponent) && editMode && !e.mods.isCommandDown() && !e.mods.isShiftDown() && !e.mods.isPopupMenu())
	{
		if (dynamic_cast<ResizableBorderComponent*>(e.eventComponent) == 0)
		{
			CtrlrComponent *c = findEventComponent(e);

			if (c && getOwner().getSelection())
			{
				getOwner().getSelection()->selectOnly (c);
				getOwner().getSelection()->dispatchPendingMessages();
				startDraggingSelection();
			}
		}
	}

	if (!isLayer(e.eventComponent) && editMode && e.mods.isCommandDown())
	{
		handleLeftClickOnComponent(e);
	}
	if (!isLayer(e.eventComponent) && editMode && e.mods.isShiftDown())
	{
		startDraggingSelection();
	}
}

void CtrlrPanelCanvas::mouseDrag (const MouseEvent& e)
{
	const bool editMode = (bool)getOwner().getProperty(Ids::uiPanelEditMode);

	if (isLayer(e.eventComponent) && editMode)
	{
		lassoComponent.dragLasso (e);
	}
	if (!isLayer(e.eventComponent) && editMode && getOwner().getSelection())
	{
		if (getOwner().getSelection()->getNumSelected() > 1)
		{
			if (e.mods.isShiftDown())
			{
				dragSelectedComps (e.getDistanceFromDragStartX(), e.getDistanceFromDragStartY(), (bool)getProperty(Ids::uiPanelSnapActive));
			}
			else
			{
				return;
			}
		}

		if (dynamic_cast<ResizableBorderComponent*>(e.eventComponent) == 0 && getOwner().getSelection())
		{
			getOwner().getSelection()->sendChangeMessage();
			dragSelectedComps (e.getDistanceFromDragStartX(), e.getDistanceFromDragStartY(), (bool)getProperty(Ids::uiPanelSnapActive));
		}
	}
}

void CtrlrPanelCanvas::mouseUp (const MouseEvent& e)
{
	lassoComponent.endLasso();
}

void CtrlrPanelCanvas::editMenuCopy(const MouseEvent *e)
{
    if (getOwner().getSelection() == nullptr)
        return;

	ValueTree clipboardTree(Ids::uiPanelClipboardTree);
	RectangleList<int> list;

	for (int i=0; i<getOwner().getSelection()->getNumSelected(); i++)
	{
		CtrlrModulator &m = getOwner().getSelection()->getSelectedItem(i)->getOwner();
		clipboardTree.addChild (m.getModulatorTree().createCopy(), -1, nullptr);

		list.add (m.getComponent()->getBounds());
	}

	clipboardTree.setProperty ("selectionRect", list.getBounds().toString(),0);
	SystemClipboard::copyTextToClipboard (XML2STR(clipboardTree));
}

void CtrlrPanelCanvas::cut()
{
	editMenuCopy(nullptr);
	editMenuDelete();
}

void CtrlrPanelCanvas::copy()
{
	editMenuCopy(nullptr);
}

void CtrlrPanelCanvas::paste()
{
	editMenuPaste();
}

bool CtrlrPanelCanvas::keyPressed (const KeyPress& key, Component* originatingComponent)
{
	moveSelectionBy (1, keyPressToDirection(key));
	if (key == KeyPress::deleteKey)
	{
		editMenuDelete();
		return (true);
	}
	if (key.getTextDescription() == "ctrl + C")
	{
		copy();
		return (true);
	}
	if (key.getTextDescription() == "ctrl + V")
	{
		paste();
		return (true);
	}
	if (key.getTextDescription() == "ctrl + X")
	{
		cut();
		return (true);
	}
    return false;
}

void CtrlrPanelCanvas::changeListenerCallback (ChangeBroadcaster* source)
{
}

CtrlrModulator *CtrlrPanelCanvas::addModulator(const Identifier &componentType)
{
	CtrlrModulator *ctrlrModualtor = getPanel().createNewModulator(componentType);
	return (ctrlrModualtor);
}

void CtrlrPanelCanvas::removeModulator(CtrlrModulator *m, const bool sendNotificationForEachElement)
{
	removeComponent (m->getComponent(), sendNotificationForEachElement);
}

void CtrlrPanelCanvas::removeComponent(CtrlrComponent *c, const bool sendNotificationForEachElement)
{
	if (c == nullptr || c == 0)
		return;

	if (CtrlrComponentTypeManager::isGroupingComponent(c))
	{
		removeComponentsInGroup(c, sendNotificationForEachElement);
	}

    if (getOwner().getSelection())
        getOwner().getSelection()->removeChangeListener(c);

	CtrlrModulator *componentOwner = &c->getOwner();

	if (c)
	{
		getOwner().getOwner().removeModulator (componentOwner);
	}

	if (c)
	{
		getPanel().removeModulator (componentOwner);
	}

	if (sendNotificationForEachElement && getOwner().getSelection())
	{
		getOwner().getSelection()->deselectAll();
		sendChangeMessage();
	}
}

void CtrlrPanelCanvas::removeComponentsInGroup(CtrlrComponent *c, const bool sendNotificationForEachElement)
{
}

CtrlrComponent *CtrlrPanelCanvas::attach(CtrlrComponent *ctrlrComponent, Component *componentToAddTo, const bool force)
{
	ctrlrComponent->addKeyListener (this);
	ctrlrComponent->addMouseListener (this, true);
    if (getOwner().getSelection())
        getOwner().getSelection()->addChangeListener (ctrlrComponent);
	addAndMakeVisibleNg (ctrlrComponent, componentToAddTo, force);
	return (ctrlrComponent);
}

CtrlrComponent *CtrlrPanelCanvas::addNewComponent (const Identifier &componentType, const Point<int> insertAt, Component *componentToAddTo)
{
	CtrlrModulator *modulator		= addModulator(componentType);
	modulator->setComponentType (componentType, false);

	CtrlrComponent *ctrlrComponent	= modulator->getComponent();

	if (ctrlrComponent != 0)
	{
		ctrlrComponent->setTopLeftPosition (insertAt.getX(), insertAt.getY());
		return (attach (ctrlrComponent, componentToAddTo));
	}

	jassertfalse; // ctrlrComponent == 0
	return (nullptr);
}

CtrlrComponent *CtrlrPanelCanvas::addNewComponent (const Identifier &componentType, const Rectangle<int> componentBounds)
{
	CtrlrComponent *c = addNewComponent (componentType, componentBounds.getPosition());
	c->setBounds (componentBounds);
	return (c);
}

CtrlrComponent *CtrlrPanelCanvas::addNewComponent (const ValueTree &savedState, Component *componentToAddTo, const bool force)
{
	CtrlrModulator *ctrlrModulator = nullptr;
	Rectangle<int> ctrlrComponentPosition;

	if (savedState.getChildWithName (Ids::component).isValid())
	{
		ctrlrComponentPosition = VAR2RECT (savedState.getChildWithName (Ids::component).getProperty(Ids::componentRectangle, "0 0 32 32"));
	}
	else
	{
		_ERR("CtrlrPanelCanvas::addNewComponent a modulator without a component was attempted, not possible when adding from a ValueTree");
		return (nullptr);
	}

	ctrlrModulator = addModulator(savedState.getChildWithName (Ids::component).getProperty(Ids::uiType).toString());

	if (ctrlrModulator != nullptr)
	{
		ctrlrModulator->restoreState (savedState);

		CtrlrComponent *ctrlrComponent = ctrlrModulator->getComponent();

		if (ctrlrComponent != 0)
		{
			if (!ctrlrComponentPosition.isEmpty())
			{
				ctrlrComponent->setBounds (ctrlrComponentPosition);
			}
			return (attach (ctrlrComponent, componentToAddTo, force));
		}

		jassertfalse; // ctrlrComponent == 0
	}
	return (nullptr);
}

void CtrlrPanelCanvas::findLassoItemsInArea (Array <CtrlrComponent*>& itemsFound, const Rectangle<int>& area)
{
	const Rectangle<int> lasso (area);

	for (int i=0; i<getNumChildComponentsLayered(); i++)
	{
		CtrlrComponent *c = dynamic_cast<CtrlrComponent*>(getChildComponentLayered(i));
		if (c!=0)
		{
			if (c->getBounds().intersects (lasso))
	            itemsFound.add (c);
		}
    }
}

SelectedItemSet <CtrlrComponent*>& CtrlrPanelCanvas::getLassoSelection()
{
	return (*getOwner().getSelection());
}

CtrlrComponent *CtrlrPanelCanvas::findEventComponent (const MouseEvent &e)
{
	CtrlrComponent *c = 0;

	if (getOwner().getOwner().containsCtrlrComponent ((CtrlrComponent *)e.eventComponent))
	{
		c = (CtrlrComponent *)e.eventComponent;
	}
	else if (getOwner().getOwner().containsCtrlrComponent ((CtrlrComponent *)e.eventComponent->findParentComponentOfClass<CtrlrComponent>()))
	{
		c = (CtrlrComponent *)e.eventComponent->findParentComponentOfClass<CtrlrComponent>();
	}

	return (c);
}

int CtrlrPanelCanvas::snapPosition (int pos, int snapSize, const bool allowSnap)
{
	if (snapSize <= 0 || allowSnap == false)
		return pos;

	pos = ((pos + snapSize * 1024 + snapSize / 2) / snapSize - 1024) * snapSize;
    return pos;
}

void CtrlrPanelCanvas::moveSelectedComps (int dx, int dy, bool snap)
{
	if ((bool)owner.getProperty (Ids::uiPanelLock))
		return;

    startDraggingSelection();
    dragSelectedComps (dx, dy, snap);
    endDraggingSelection();
}

void CtrlrPanelCanvas::dragSelectedComps (int dx, int dy, const bool allowSnap)
{
    if (getOwner().getSelection() == nullptr)
        return;

	if ((bool)owner.getProperty (Ids::uiPanelLock))
		return;

	if (allowSnap && getOwner().getSelection()->getNumSelected() > 1)
    {
        dx = snapPosition (dx, (int)getOwner().getProperty(Ids::uiPanelSnapSize), allowSnap);
        dy = snapPosition (dy, (int)getOwner().getProperty(Ids::uiPanelSnapSize), allowSnap);
    }

    for (int i = 0; i < getOwner().getSelection()->getNumSelected(); ++i)
    {
        CtrlrComponent* const c = getOwner().getSelection()->getSelectedItem (i);

		if ((bool)c->getProperty(Ids::componentIsLocked) == true)
			continue;

        const int startX = c->getProperties() ["xDragStart"];
        const int startY = c->getProperties() ["yDragStart"];

        if (getOwner().getSelection()->getNumSelected() == 1)
        {
            c->setTopLeftPosition (snapPosition (startX + dx, (int)getOwner().getProperty(Ids::uiPanelSnapSize), allowSnap), snapPosition (startY + dy, (int)getOwner().getProperty(Ids::uiPanelSnapSize), allowSnap));
        }
        else
        {
            c->setTopLeftPosition (snapPosition (startX + dx, (int)getOwner().getProperty(Ids::uiPanelSnapSize), allowSnap), snapPosition (startY + dy, (int)getOwner().getProperty(Ids::uiPanelSnapSize), allowSnap));
        }
    }
}

void CtrlrPanelCanvas::endDraggingSelection()
{
    if (getOwner().getSelection() == nullptr)
        return;

	for (int i = 0; i < getOwner().getSelection()->getNumSelected(); ++i)
    {
        CtrlrComponent* const c = getOwner().getSelection()->getSelectedItem (i);

        const int newX = c->getX();
        const int newY = c->getY();

        const int startX = c->getProperties() ["xDragStart"];
        const int startY = c->getProperties() ["yDragStart"];

        c->setTopLeftPosition (startX, startY);
        c->setTopLeftPosition (newX, newY);
		c->toFront (false);
    }
}

void CtrlrPanelCanvas::startDraggingSelection()
{
    if (getOwner().getSelection() == nullptr)
        return;

	for (int i = 0; i < getOwner().getSelection()->getNumSelected(); ++i)
    {
		CtrlrComponent* const c = getOwner().getSelection()->getSelectedItem(i);
        c->getProperties().set ("xDragStart", c->getX());
        c->getProperties().set ("yDragStart", c->getY());
		c->toBack();
    }
	startDragging ("__ctrlr_component_selection", this, Image (Image::ARGB,1,1,true));

	if (getOwner().getSelection()->getNumSelected() > 1)
		getPanel().getUndoManager()->beginNewTransaction ("Move multiple");
	else if (getOwner().getSelection()->getNumSelected() == 1)
		getPanel().getUndoManager()->beginNewTransaction ("Move "+getOwner().getSelection()->getSelectedItem(0)->getVisibleName());
}

void CtrlrPanelCanvas::restoreState (const ValueTree &savedState)
{
	setBounds (VAR2RECT(getProperty(Ids::uiPanelCanvasRectangle)));

	/* first restore any layers used */
	if (savedState.getChildWithName (Ids::uiPanelEditor).isValid())
	{
		if (savedState.getChildWithName (Ids::uiPanelEditor).getChildWithName (Ids::uiPanelCanvasLayer).isValid())
		{
			/* canvas has it's own layers, delete the default one */
			removeAllLayers();
		}

		for (int i=0; i<savedState.getChildWithName (Ids::uiPanelEditor).getNumChildren(); i++)
		{
			ValueTree child = savedState.getChildWithName (Ids::uiPanelEditor).getChild(i);

			if (child.hasType(Ids::uiPanelCanvasLayer))
			{
				addLayer (child);
			}
		}

		layers.sort(*this);
		layersChanged();
	}

	/* now restore components */
	int dispatchCounter = 0;
	for (int i=0; i<savedState.getNumChildren(); i++)
	{
		ValueTree child = savedState.getChild(i);

		if (child.hasType(Ids::modulator))
		{
			CtrlrComponent *c = addNewComponent (child);
			if (c == nullptr)
			{
				_WRN("CtrlrPanelCanvas::restoreState failed to add component: " + child.getProperty(Ids::name).toString());
			}
			else
			{
				if ((bool)c->getProperty(Ids::componentSentBack) == true)
				{
					c->toBack();
				}
				c->setVisible ((bool)c->getProperty(Ids::componentVisibility));
			}
		}

#ifdef JUCE_WINDOWS
		if (MessageManager::getInstance() && ++dispatchCounter > 300)
		{
			MessageManager::getInstance()->runDispatchLoopUntil (25);
			dispatchCounter = 0;
		}
#endif
	}

	canvasStateRestored();

	getPanel().getUndoManager()->clearUndoHistory();
}

void CtrlrPanelCanvas::canvasStateRestored()
{
	Array <CtrlrModulator*> tabModulators	= owner.getOwner().getModulatorsByUIType(Ids::uiTabs);
	Array <CtrlrModulator*> geoupModulators = owner.getOwner().getModulatorsByUIType(Ids::uiGroup);

	for (int i=0; i<tabModulators.size(); i++)
	{
		CtrlrTabsComponent *tc = dynamic_cast<CtrlrTabsComponent*>(tabModulators.getReference(i)->getComponent());
		if (tc)
		{
			tc->canvasStateRestored();
		}
	}

	for (int i=0; i<geoupModulators.size(); i++)
	{
		CtrlrGroup *gc = dynamic_cast<CtrlrGroup*>(geoupModulators.getReference(i)->getComponent());
		if (gc)
		{
			gc->canvasStateRestored();
		}
	}

	editModeChanged((bool)getProperty(Ids::uiPanelEditMode));
}

void CtrlrPanelCanvas::editMenuPaste()
{
    if (getOwner().getSelection() == nullptr)
        return;

	owner.getSelection()->deselectAll();

	ValueTree clipboardTree = valueTreeFromXml (SystemClipboard::getTextFromClipboard());
	if (clipboardTree.hasType (Ids::uiPanelClipboardTree))
	{
		emptyGroupping (clipboardTree);

		for (int i=0; i<clipboardTree.getNumChildren(); i++)
		{
			CtrlrComponent *c = addNewComponent (clipboardTree.getChild(i), 0, true);
			c->setTopLeftPosition (c->getX()+(c->getWidth()/2), c->getY()+(c->getHeight()/2));
			c->panelEditModeChanged (owner.getProperty (Ids::uiPanelEditMode));
			c->getOwner().setProperty (Ids::vstIndex, owner.getOwner().getOwner().getVstManager().getFirstFree());
			owner.getSelection()->addToSelection (c);
		}
	}

	if (clipboardTree.hasType ("groupTree"))
	{
		pasteGroupComponent(clipboardTree);
	}
}

void CtrlrPanelCanvas::editMenuPaste(const MouseEvent &e)
{
	ValueTree clipboardTree = valueTreeFromXml (SystemClipboard::getTextFromClipboard());
	if (clipboardTree.hasType (Ids::uiPanelClipboardTree))
	{
		emptyGroupping (clipboardTree);
		/** author Anita aka buns of steel

		*/
		Rectangle <int> list = VAR2RECT (clipboardTree.getProperty("selectionRect"));
		const int deltaX = e.x - list.getX();
		const int deltaY = e.y - list.getY();

		for (int i=0; i<clipboardTree.getNumChildren(); i++)
		{
			CtrlrComponent *c = addNewComponent (clipboardTree.getChild(i), e.eventComponent, true);
			c->setTopLeftPosition (c->getX()+deltaX, c->getY()+deltaY);
		}
	}

	if (clipboardTree.hasType ("groupTree"))
	{
		pasteGroupComponent(clipboardTree,e);
	}
}

void CtrlrPanelCanvas::emptyGroupping(ValueTree &tree)
{
	if (!tree.getProperty (Ids::componentGroupName).toString().isEmpty())
	{
		tree.setProperty (Ids::componentGroupName, String::empty, 0);
	}

	if (!tree.getProperty (Ids::componentTabName).toString().isEmpty())
	{
		tree.setProperty (Ids::componentTabName, String::empty, 0);
	}
}

void CtrlrPanelCanvas::editMenuDelete()
{
    if (getOwner().getSelection() == nullptr)
        return;

	Array<CtrlrComponent*> car = getOwner().getSelection()->getItemArray();
	getOwner().getSelection()->deselectAll();

	for (int i=0; i<car.size(); i++)
	{
		CtrlrComponent *c = car[i];
		if (c != 0)
		{
			removeComponent (c, false);
		}
	}

	sendChangeMessage();
}

const PopupMenu CtrlrPanelCanvas::getRightClickComponentMenu(const MouseEvent &e)
{
	PopupMenu m;

	if (e.eventComponent && e.mods.isPopupMenu())
	{
		CtrlrComponent *component = dynamic_cast<CtrlrComponent*>(e.eventComponent);
		if (component != nullptr)
		{
			return (component->getComponentMenu(e));
		}
	}

	return (m);
}

void CtrlrPanelCanvas::handleComponentPopupMenu(const MouseEvent &e, const int itemId)
{
	if (e.eventComponent)
	{
		CtrlrComponent *component = dynamic_cast<CtrlrComponent*>(e.eventComponent);
		if (component != nullptr)
		{
			component->handlePopupMenu (itemId);
		}
	}
}

void CtrlrPanelCanvas::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiPanelImageResource)
	{
		if (treeWhosePropertyHasChanged.getProperty(Ids::uiPanelImageResource).toString() == COMBO_NONE_ITEM)
		{
			ctrlrPanelBackgroundImage = Image::null;
		}
		else
		{
			ctrlrPanelBackgroundImage = getOwner().getOwner().getResourceManager().getResourceAsImage(treeWhosePropertyHasChanged.getProperty(Ids::uiPanelImageResource));
		}
		repaint();
	}

	if (property == Ids::uiPanelImageAlpha)
	{
		repaint();
	}

	if (property == Ids::uiPanelImageLayout)
	{
		repaint();
	}

	if (property == Ids::uiPanelBackgroundColour)
	{
		repaint();
	}

	if (property == Ids::luaPanelPaintBackground)
	{
		if (getProperty(property) == String::empty)
			return;

		paintCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}

	if (property == Ids::luaPanelResized)
	{
		if (getProperty(property) == String::empty)
			return;

		resizedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}

	if (property == Ids::luaPanelFileDragDropHandler)
	{
		if (getProperty(property) == String::empty)
			return;

		luaPanelFileDragDropHandlerCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}

	if (property == Ids::luaPanelFileDragEnterHandler)
	{
		if (getProperty(property) == String::empty)
			return;

		luaPanelFileDragEnterHandlerCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}

	if (property == Ids::luaPanelFileDragExitHandler)
	{
		if (getProperty(property) == String::empty)
			return;

		luaPanelFileDragExitHandlerCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	if (property == Ids::uiPanelEditMode)
	{
		editModeChanged((bool)getProperty(property));
	}
}

CtrlrPanel &CtrlrPanelCanvas::getPanel()
{
	return (owner.getOwner());
}

void CtrlrPanelCanvas::setProperty (const Identifier& name, const var &newValue, const bool isUndoable)
{
	if (isUndoable)
	{
		owner.setProperty (name, newValue, isUndoable);
	}
	else
	{
		owner.setProperty (name, newValue, nullptr);
	}
}

const var &CtrlrPanelCanvas::getProperty (const Identifier& name) const
{
	return (owner.getProperty (name));
}

const var CtrlrPanelCanvas::getProperty (const Identifier& name, const var &defaultReturnValue) const
{
	return (owner.getProperty (name, defaultReturnValue));
}

ValueTree &CtrlrPanelCanvas::getCanvasTree()
{
	return (owner.getPanelEditorTree());
}

void CtrlrPanelCanvas::moveSelectionBy (const int deltaOffset, const Direction directionToMove)
{
    if (getOwner().getSelection() == nullptr)
        return;

	if (directionToMove == Right)
	{
		for (int i = 0; i < getOwner().getSelection()->getNumSelected(); ++i)
		{
			CtrlrComponent* const c = getOwner().getSelection()->getSelectedItem(i);
			if (c) c->setTopLeftPosition (c->getX()+1, c->getY());
		}
	}
	if (directionToMove == Left)
	{
		for (int i = 0; i < getOwner().getSelection()->getNumSelected(); ++i)
		{
			CtrlrComponent* const c = getOwner().getSelection()->getSelectedItem(i);
			if (c) c->setTopLeftPosition (c->getX()-1, c->getY());
		}
	}
	if (directionToMove == Down)
	{
		for (int i = 0; i < getOwner().getSelection()->getNumSelected(); ++i)
		{
			CtrlrComponent* const c = getOwner().getSelection()->getSelectedItem(i);
			if (c) c->setTopLeftPosition (c->getX(), c->getY()+1);
		}
	}
	if (directionToMove == Up)
	{
		for (int i = 0; i < getOwner().getSelection()->getNumSelected(); ++i)
		{
			CtrlrComponent* const c = getOwner().getSelection()->getSelectedItem(i);
			if (c) c->setTopLeftPosition (c->getX(), c->getY()-1);
		}
	}
}

const CtrlrPanelCanvas::Direction CtrlrPanelCanvas::keyPressToDirection(const KeyPress &k)
{
	if (k == KeyPress::leftKey)
	{
		return (Left);
	}

	if (k == KeyPress::rightKey)
	{
		return (Right);
	}

	if (k == KeyPress::upKey)
	{
		return (Up);
	}

	if (k == KeyPress::downKey)
	{
		return (Down);
	}

	return (None);
}

void CtrlrPanelCanvas::alignSelection(const EditMenuItems direction)
{
    if (getOwner().getSelection() == nullptr)
        return;

	if (getOwner().getSelection()->getNumSelected() > 0)
	{
		RectangleList<int> rlist;
		int y1, y2, x1, x2;
		for (int i=0; i<getSelection().getNumSelected(); i++)
		{
			rlist.add (getSelection().getSelectedItem(i)->getBounds());
		}

		switch (direction)
		{
			case AlignToTop:
				for (int i=0; i<getSelection().getNumSelected(); i++)
				{
					getSelection().getSelectedItem(i)->setBounds(getSelection().getSelectedItem(i)->getBounds().withY(rlist.getBounds().getY()));
				}
				break;

			case AlignToBottom:
				for (int i=0; i<getSelection().getNumSelected(); i++)
				{
					y1 = rlist.getBounds().getY() + rlist.getBounds().getHeight();	// y position of the lower edge
					y2 = y1 - getSelection().getSelectedItem(i)->getHeight();		// new y position of the element
					getSelection().getSelectedItem(i)->setBounds (getSelection().getSelectedItem(i)->getBounds().withY(y2));
				}
				break;

			case AlignToLeft:
				for (int i=0; i<getSelection().getNumSelected(); i++)
				{
					getSelection().getSelectedItem(i)->setBounds(getSelection().getSelectedItem(i)->getBounds().withX(rlist.getBounds().getX()));
				}
				break;

			case AlignToRight:
				for (int i=0; i<getSelection().getNumSelected(); i++)
				{
					x1 = rlist.getBounds().getX() + rlist.getBounds().getWidth();	// x position of the right edge
					x2 = x1 - getSelection().getSelectedItem(i)->getWidth();		// new x position of the element
					getSelection().getSelectedItem(i)->setBounds(getSelection().getSelectedItem(i)->getBounds().withX(x2));
				}
				break;
			case Copy:
			case Cut:
			case Paste:
			case Delete:
			case Undo:
			case Redo:
			case FitToRect:
			case GroupCreate:
			case GroupDestroy:
				break;
		}
	}
}

CtrlrComponentSelection &CtrlrPanelCanvas::getSelection()
{
	return (*getOwner().getSelection());
}

bool CtrlrPanelCanvas::isInterestedInFileDrag (const StringArray &files)
{
	return (true);
}

void CtrlrPanelCanvas::fileDragEnter (const StringArray &files, int x, int y)
{
	if (luaPanelFileDragEnterHandlerCbk && !luaPanelFileDragEnterHandlerCbk.wasObjectDeleted())
	{
		if (luaPanelFileDragEnterHandlerCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (luaPanelFileDragEnterHandlerCbk, files, x, y);

			return;
		}
	}
}

void CtrlrPanelCanvas::fileDragExit (const StringArray &files)
{
	if (luaPanelFileDragExitHandlerCbk && !luaPanelFileDragExitHandlerCbk.wasObjectDeleted())
	{
		if (luaPanelFileDragExitHandlerCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (luaPanelFileDragExitHandlerCbk, files);

			return;
		}
	}
}

void CtrlrPanelCanvas::filesDropped (const StringArray &files, int x, int y)
{
	for (int i=0; i<files.size(); i++)
	{
		const File f = files[i];

		if (f.hasFileExtension(".component"))
		{
			importComponent (f, x, y);
		}
		else if (CtrlrPanel::isPanelFile (f))
		{
			importPanel (f, x, y);
		}
		else
		{
			Image i = ImageFileFormat::loadFrom(f);
			if (i != Image::null)
			{
				importImage (f, x, y);
			}
		}
	}

	if (luaPanelFileDragDropHandlerCbk && !luaPanelFileDragDropHandlerCbk.wasObjectDeleted())
	{
		if (luaPanelFileDragDropHandlerCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (luaPanelFileDragDropHandlerCbk, files, x, y);

			return;
		}
	}
}

void CtrlrPanelCanvas::exportSelectedComponents()
{
    if (owner.getSelection() == nullptr)
        return;

	for (int i=0; i<owner.getSelection()->getNumSelected(); i++)
	{
		CtrlrComponent *c = owner.getSelection()->getSelectedItem(i);
		if (c != 0)
		{
			exportComponent(c);
		}
	}
}

void CtrlrPanelCanvas::exportComponent(CtrlrComponent *componentToExport)
{
	if (componentToExport != 0)
	{
		File f(owner.getProperty (Ids::lastBrowsedComponentDir));
		if (f == File::nonexistent)
		{
			owner.setProperty (Ids::lastBrowsedComponentDir, File::getSpecialLocation(File::userDocumentsDirectory).getFullPathName());
		}

		FileChooser fileChooser ("Ctrlr component file", File(owner.getProperty (Ids::lastBrowsedComponentDir)).getChildFile (componentToExport->getOwner().getName()+".component"), "*.component");
		if (fileChooser.browseForFileToSave(true))
		{
			File fileToSave = fileChooser.getResult().withFileExtension(".component");

			owner.setProperty (Ids::lastBrowsedComponentDir, fileToSave.getParentDirectory().getFullPathName());
			ScopedPointer <FileOutputStream> fileOutputStream(fileToSave.createOutputStream());
			if (fileOutputStream)
			{
				componentToExport->getOwner().getModulatorTree().writeToStream (*fileOutputStream);
			}
		}
	}
}

void CtrlrPanelCanvas::importComponent (const File &componentFile, int x, int y)
{
	ScopedPointer <FileInputStream> fileInputStream(componentFile.createInputStream());
	if (fileInputStream)
	{
		ValueTree componentTree = ValueTree::readFromStream(*fileInputStream);
		if (componentTree.isValid())
		{
			CtrlrComponent *c = addNewComponent (componentTree);
			if (c)
			{
				c->setTopLeftPosition (x,y);
			}
		}
	}
}

void CtrlrPanelCanvas::importPanel (const File &panelFile, int x, int y)
{
}

void CtrlrPanelCanvas::importImage (const File &imageFile, int x, int y)
{
	if (owner.getOwner().getResourceManager().addResource (imageFile))
	{
		AlertWindow::showMessageBox(AlertWindow::InfoIcon, "Image import", "Can't import the file as a image resource");
		return;
	}

	Image i = owner.getOwner().getResourceManager().getResourceAsImage(imageFile.getFileNameWithoutExtension());

	if (i == Image::null)
	{
		AlertWindow::showMessageBox(AlertWindow::InfoIcon, "Image import", "Image has been imported as a resource, but i can't fetch if from the resource manager");
		return;
	}

	CtrlrComponent *c = addNewComponent(Ids::uiImage, Point<int>(x,y));
	if (c)
	{
		c->setProperty(Ids::uiImageResource, imageFile.getFileNameWithoutExtension());
		c->setSize (i.getWidth(), i.getHeight());
	}
}

void CtrlrPanelCanvas::fitSelection()
{
}

const bool CtrlrPanelCanvas::isOnlyGroupSelected()
{
	if (getSelection().getNumSelected() > 1)
	{
		const String groupName = getSelection().getSelectedItem(0)->getProperty(Ids::componentGroupName);

		for (int i=0; i<getSelection().getNumSelected(); i++)
		{
			if (getSelection().getSelectedItem(i)->getProperty(Ids::componentGroupName) == groupName)
				continue;
			else
			{
				return (false);
			}
		}
	}

	return (true);
}

Path CtrlrPopupMenuLook::getTickShape (const float height)
{
    static const unsigned char tickShapeData[] =
    {
        109,0,224,168,68,0,0,119,67,108,0,224,172,68,0,128,146,67,113,0,192,148,68,0,0,219,67,0,96,110,68,0,224,56,68,113,0,64,51,68,0,32,130,68,0,64,20,68,0,224,
        162,68,108,0,128,3,68,0,128,168,68,113,0,128,221,67,0,192,175,68,0,0,207,67,0,32,179,68,113,0,0,201,67,0,224,173,68,0,0,181,67,0,224,161,68,108,0,128,168,67,
        0,128,154,68,113,0,128,141,67,0,192,138,68,0,128,108,67,0,64,131,68,113,0,0,62,67,0,128,119,68,0,0,5,67,0,128,114,68,113,0,0,102,67,0,192,88,68,0,128,155,
        67,0,192,88,68,113,0,0,190,67,0,192,88,68,0,128,232,67,0,224,131,68,108,0,128,246,67,0,192,139,68,113,0,64,33,68,0,128,87,68,0,0,93,68,0,224,26,68,113,0,
        96,140,68,0,128,188,67,0,224,168,68,0,0,119,67,99,101
    };

    Path p;
    p.loadPathFromData (tickShapeData, sizeof (tickShapeData));
    p.scaleToFit (0, 0, height * 2.0f, height, true);
    return p;
}

void CtrlrPopupMenuLook::drawPopupMenuItem (Graphics& g,
                                     int width, int height,
                                     const bool isSeparator,
                                     const bool isActive,
                                     const bool isHighlighted,
                                     const bool isTicked,
                                     const bool hasSubMenu,
                                     const String& text,
                                     const String& shortcutKeyText,
                                     Image* image,
                                     const Colour* const textColourToUse)
{
    const float halfH = height * 0.5f;

	bool hasSecondLine = false;
	if (text.indexOf("\n") > 0)
		hasSecondLine = true;
	const int secondLineStart = Font(14).getStringWidth(text.upToFirstOccurrenceOf("\n",false, true));
	const String secondLine  = text.fromLastOccurrenceOf("\n", false, true);
	const String ttext = text.upToFirstOccurrenceOf("\n", false, true);

    if (isSeparator)
    {
        const float separatorIndent = 5.5f;

        g.setColour (Colour (0x33000000));
        g.drawLine (separatorIndent, halfH, width - separatorIndent, halfH);

        g.setColour (Colour (0x66ffffff));
        g.drawLine (separatorIndent, halfH + 1.0f, width - separatorIndent, halfH + 1.0f);
    }
    else
    {
		Colour textColour (Colours::black);

        if (textColourToUse != nullptr)
            textColour = *textColourToUse;

        if (isHighlighted)
        {
			g.setColour (Colour(0x991111aa));
            g.fillRect (1, 1, width - 2, height - 2);

			g.setColour (Colours::white);
        }
        else
        {
            g.setColour (textColour);
        }

        if (! isActive)
            g.setOpacity (0.3f);

        Font font (14);

        if (font.getHeight() > height / 1.3f)
            font.setHeight (height / 1.3f);

        g.setFont (font);

        const int leftBorder = (height * 5) / 4;
        const int rightBorder = 4;

        if (image != nullptr)
        {
            g.drawImageWithin (*image,
                               2, 1, leftBorder - 4, height - 2,
                               RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, false);
        }
        else if (isTicked)
        {
            const Path tick (getTickShape (1.0f));
            const float th = font.getAscent();
            const float ty = halfH - th * 0.5f;

            g.fillPath (tick, tick.getTransformToScaleToFit (2.0f, ty, (float) (leftBorder - 4),
                                                             th, true));
        }

        g.drawFittedText (ttext,
                          leftBorder, 0,
                          width - (leftBorder + rightBorder), height,
                          Justification::centredLeft, 1);

        if (shortcutKeyText.isNotEmpty() || hasSecondLine)
        {
            Font f2 (font);
            f2.setHeight (f2.getHeight() * 0.65f);
            f2.setHorizontalScale (0.95f);
            g.setFont (f2);
			String textToDraw;
			if (hasSecondLine)
				textToDraw = secondLine;
			else
				textToDraw = shortcutKeyText;

			g.drawFittedText (textToDraw,
                        secondLineStart+8 + leftBorder,
                        0,
                        width - (leftBorder + rightBorder + 4) - secondLineStart - 8,
                        height,
                        Justification::centredRight,
						3);
        }

        if (hasSubMenu)
        {
            const float arrowH = 0.6f * font.getAscent();
            const float x = width - height * 0.6f;

            Path p;
            p.addTriangle (x, halfH - arrowH * 0.5f,
                           x, halfH + arrowH * 0.5f,
                           x + arrowH * 0.6f, halfH);

            g.fillPath (p);
        }
    }
}

void CtrlrPopupMenuLook::getIdealPopupMenuItemSize (const String &text, bool isSeparator, int standardMenuItemHeight, int &idealWidth, int &idealHeight)
{
	if (isSeparator)
    {
        idealWidth = 50;
        idealHeight = standardMenuItemHeight > 0 ? standardMenuItemHeight / 2 : 10;
    }
    else
    {
        Font font (Font(14));

        if (standardMenuItemHeight > 0 && font.getHeight() > standardMenuItemHeight / 1.3f)
            font.setHeight (standardMenuItemHeight / 1.3f);

        idealHeight = standardMenuItemHeight > 0 ? standardMenuItemHeight : roundToInt (font.getHeight() * 1.8f);
		idealWidth = (font.getStringWidth (text.upToFirstOccurrenceOf("\n", false, true))*2) + idealHeight * 2;
    }
}

int CtrlrPanelCanvas::getWidth()
{
	return (Component::getWidth());
}

int CtrlrPanelCanvas::getHeight()
{
	return (Component::getHeight());
}

void CtrlrPanelCanvas::repaint()
{
	Component::repaint();
}

uint8 CtrlrPanelCanvas::getType()
{
	return (0);
}

const String CtrlrPanelCanvas::getLayerName(const int indexInArray)
{
	if (layers[indexInArray])
	{
		return (layers[indexInArray]->getProperty(Ids::uiPanelCanvasLayerName).toString());
	}
	return (String::empty);
}

bool CtrlrPanelCanvas::isInterestedInDragSource (const SourceDetails &dragSourceDetails)
{
	if (dragSourceDetails.description == "__ctrlr_component_selection")
	{
		return (true);
	}
	return (false);
}

void CtrlrPanelCanvas::itemDropped (const SourceDetails &dragSourceDetails)
{
    if (getOwner().getSelection() == nullptr)
        return;

	for (int i = 0; i < getOwner().getSelection()->getNumSelected(); ++i)
	{
		CtrlrComponent* const c = getOwner().getSelection()->getSelectedItem (i);

		if (c != nullptr)
		{
			if ((bool)c->getProperty(Ids::componentIsLocked) == true)
				return;
		}
	}

	if (dragSourceDetails.description == "__ctrlr_component_selection")
	{
		AffineTransform trans = owner.getOwner().getEditor()->moveSelectionToPosition(dragSourceDetails.localPosition.getX(), dragSourceDetails.localPosition.getY());

		for (int i=0; i<owner.getSelection()->getNumSelected(); i++)
		{
			CtrlrComponent *child  = owner.getSelection()->getSelectedItem(i);

			if ( (bool)child->getProperty (Ids::componentGroupped) == true)
			{
				child->setProperty (Ids::componentGroupped, false, true);
				owner.getSelection()->getSelectedItem(i)->setBounds (owner.getSelection()->getSelectedItem(i)->getBounds().transformedBy(trans));
			}
		}
	}
}

void CtrlrPanelCanvas::itemDragExit (const SourceDetails &dragSourceDetails)
{
}

void CtrlrPanelCanvas::itemDragEnter (const SourceDetails &dragSourceDetails)
{
}
