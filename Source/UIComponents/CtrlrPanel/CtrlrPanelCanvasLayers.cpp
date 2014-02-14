#include "stdafx.h"
#include "CtrlrPanelCanvas.h"
#include "CtrlrLog.h"

void CtrlrPanelCanvas::initLayers()
{
	layers.add (new CtrlrPanelCanvasLayer(*this));
	addAndMakeVisible (layers[0]);
	layers[0]->addMouseListener (this, true);
	layers[0]->addKeyListener (this);
}

void CtrlrPanelCanvas::addAndMakeVisibleNg(CtrlrComponent *componentToAdd, Component *componentToAddTo, const bool force)
{
	if (componentToAdd == nullptr)
		return;

	CtrlrPanelCanvasLayer *layer	= dynamic_cast<CtrlrPanelCanvasLayer*>(componentToAddTo);
	String componentsCurrentLayer		= String::empty;

	if (componentToAdd->getObjectTree().hasProperty (Ids::componentLayerUid))
	{
		componentsCurrentLayer = componentToAdd->getProperty(Ids::componentLayerUid).toString();
	}

	if (componentsCurrentLayer != String::empty)
	{
		/* component has a layer assigned */
		if (layer == 0)
		{
			/* there is no destination component 
				if it's forced, move the component to the top-most visible layer*/
			if (force && getCurrentLayer())
			{
				assignToLayer (componentToAdd, getCurrentLayer());
			}
			if (force == false && getLayer(componentsCurrentLayer))
			{
				assignToLayer (componentToAdd, getLayer(componentsCurrentLayer));
			}
		}
		else
		{
			/* there is a destination component and a source component.
				If the add is forced do that, otherwise leave it */
			if (force)
			{
				assignToLayer (componentToAdd, layer);
			}
			else
			{
				_WRN("CtrlrPanelCanvas::addAndMakeVisibleNg won't add component="+componentToAdd->getName()+" to layer="+layer->getProperty(Ids::uiPanelCanvasLayerName).toString()+" the add is not forced");
			}
		}
	}
	else
	{
		/* component has no layer assigned yet */
		if (layer)
		{
			/* the destination layer is provided, add the component to it */
			assignToLayer (componentToAdd, layer);
		}
		else
		{
			/* the destination layer is not provided, add it to the top-most visible layer 
				or if there isn't one that's visible, the one indexed 0*/
			if (getCurrentLayer())
			{
				assignToLayer (componentToAdd, getCurrentLayer());
			}
			else
			{
				assignToLayer (componentToAdd, layers[0]);
			}
		}
	}
}

void CtrlrPanelCanvas::assignToLayer(CtrlrComponent *c, CtrlrPanelCanvasLayer *l)
{
	c->setProperty (Ids::componentLayerUid, l->getProperty(Ids::uiPanelCanvasLayerUid));
	l->addAndMakeVisible (c);
}

bool CtrlrPanelCanvas::isLayer(Component *componentToCheck)
{
	return (layers.contains((CtrlrPanelCanvasLayer*)componentToCheck));
}

/** @brief Gets a layer by it's name, if the layer is not found 0 is returned

*/
CtrlrPanelCanvasLayer *CtrlrPanelCanvas::getLayerByName(const String &layerName)
{
	for (int i=0; i<layers.size(); i++)
	{
		if (layers[i]->getProperty (Ids::uiPanelCanvasLayerName) == String(layerName))
		{
			return (layers[i]);
		}
	}

	return (0);
}

/** @brief Gets a layer by it's unique identifier, if the layer is not found 0 is returned

*/
CtrlrPanelCanvasLayer *CtrlrPanelCanvas::getLayer(const String &layerUid)
{
	for (int i=0; i<layers.size(); i++)
	{
		if (layers[i]->getProperty (Ids::uiPanelCanvasLayerUid) == layerUid)
		{
			return (layers[i]);
		}
	}

	return (0);
}

/** @brief Gets the top most visible layer (current)

*/
CtrlrPanelCanvasLayer *CtrlrPanelCanvas::getCurrentLayer()
{
	for (int i = layers.size(); --i >= 0;)
	{
		if ((bool)layers[i]->getProperty(Ids::uiPanelCanvasLayerVisibility) == true)
		{
			return (layers[i]);
		}
	}
	return (layers[0]);
}

/** @brief Get a layer from the internal array (this indexing does not need to correspond to the layers own indexes, be sure to double check)

*/
CtrlrPanelCanvasLayer *CtrlrPanelCanvas::getLayerFromArray(const int indexInArray)
{
	return (layers[indexInArray]);
}

void CtrlrPanelCanvas::layersResize()
{
	for (int i=0; i<layers.size(); i++)
	{
		layers[i]->setBounds (getBounds());
	}
}

Component *CtrlrPanelCanvas::getChildComponentLayered(const int componentIndex)
{
	return (getCurrentLayer()->getChildComponent(componentIndex));
}

int CtrlrPanelCanvas::getNumChildComponentsLayered()
{
	return (getCurrentLayer()->getNumChildComponents());
}

/** @brief Get the number of layers

*/
int CtrlrPanelCanvas::getNumLayers()
{
	return (layers.size());
}

void CtrlrPanelCanvas::removeLayer(const int index)
{
	if (layers[index] != 0)
	{
		getCanvasTree().removeChild (layers[index]->getObjectTree(), 0);
		layers.remove (index, true);
	}

	layersChanged();
}

void CtrlrPanelCanvas::removeLayer(CtrlrPanelCanvasLayer *layerToRemove)
{
	if (layers.indexOf (layerToRemove) >= 0)
	{
		getCanvasTree().removeChild (layerToRemove->getObjectTree(), 0);
		layers.removeObject (layerToRemove);
	}

	layersChanged();
}

void CtrlrPanelCanvas::removeAllLayers()
{
	for (int i=0; i<layers.size(); i++)
	{
		removeLayer(i);
	}
}

void CtrlrPanelCanvas::addLayer(const ValueTree &layerTree)
{
	CtrlrPanelCanvasLayer *l = new CtrlrPanelCanvasLayer(*this);
	l->addMouseListener (this, true);
	l->addKeyListener (this);
	l->setWantsKeyboardFocus (true);
	l->setBounds (getBounds());
	layers.add (l);
	addAndMakeVisible (l);

	if (layerTree.isValid())
	{
		l->restoreState (layerTree);
	}
	else
	{
		l->setProperty (Ids::uiPanelCanvasLayerIndex, layers.indexOf(l));
	}
}

void CtrlrPanelCanvas::moveLayer(CtrlrPanelCanvasLayer *layerToMove, const bool moveUp)
{
	if (layerToMove == 0)
		return;

	const int currentLayerIndex = layers.indexOf(layerToMove);
	int newLayerIndex			= currentLayerIndex;

	if (layerToMove == layers.getLast())
	{
		if (moveUp)
		{
			newLayerIndex = currentLayerIndex - 1;
		}
	}
	else if (layerToMove == layers.getFirst())
	{
		if (moveUp == false)
		{
			newLayerIndex = currentLayerIndex + 1;
		}
	}
	else
	{
		if (moveUp)
		{
			newLayerIndex = currentLayerIndex - 1;
		}
		else
		{
			newLayerIndex = currentLayerIndex + 1;
		}
	}

	layers[currentLayerIndex]->setProperty (Ids::uiPanelCanvasLayerIndex, newLayerIndex);
	if (layers[newLayerIndex])
		layers[newLayerIndex]->setProperty (Ids::uiPanelCanvasLayerIndex, currentLayerIndex);

	layers.move (currentLayerIndex, newLayerIndex);
	layersChanged();
}

void CtrlrPanelCanvas::layersChanged()
{
	for (int i=0; i<layers.size(); i++)
	{
		removeChildComponent (layers[i]);
	}

	for (int i=0; i<layers.size(); i++)
	{	
		if ((bool)layers[i]->getProperty (Ids::uiPanelCanvasLayerVisibility) == true)
		{
			addAndMakeVisible (layers[i]);
		}
			else
		{
			addChildComponent (layers[i]);
		}
	}
}

int CtrlrPanelCanvas::compareElements (CtrlrPanelCanvasLayer *first, CtrlrPanelCanvasLayer *second)
{
	if ((int)first->getProperty(Ids::uiPanelCanvasLayerIndex) < (int)second->getProperty (Ids::uiPanelCanvasLayerIndex))
		return (-1);
	else if ((int)first->getProperty(Ids::uiPanelCanvasLayerIndex) > (int)second->getProperty (Ids::uiPanelCanvasLayerIndex))
		return (1);
	else
		return (0);
}

void CtrlrPanelCanvas::dumpLayers()
{
}

void CtrlrPanelCanvas::editModeChanged(const bool isEditMode)
{
	if (isEditMode)
	{
		for (int i=0; i<layers.size(); i++)
		{
			layers[i]->setInterceptsMouseClicks (true, true);
		}
	}
	else
	{
		for (int i=0; i<layers.size(); i++)
		{
			layers[i]->setInterceptsMouseClicks (false, true);
		}
	}
}