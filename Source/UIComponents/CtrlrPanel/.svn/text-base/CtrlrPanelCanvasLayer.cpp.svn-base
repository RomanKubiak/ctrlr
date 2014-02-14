#include "stdafx.h"
#include "CtrlrPanelCanvas.h"
#include "CtrlrPanelCanvasLayer.h"
#include "CtrlrUtilities.h"
#include "CtrlrLog.h"

CtrlrPanelCanvasLayer::CtrlrPanelCanvasLayer(CtrlrPanelCanvas &_owner)
	: layerTree(Ids::uiPanelCanvasLayer), owner(_owner), mousePass(false)
{
	layerTree.addListener (this);
	int64 data = Time::getCurrentTime().getHighResolutionTicks();
	setProperty (Ids::uiPanelCanvasLayerName, "New layer");
	setProperty (Ids::uiPanelCanvasLayerUid, Uuid ((const uint8 *)&data).toString());
	setProperty (Ids::uiPanelCanvasLayerColour, "0x000000");
	setProperty (Ids::uiPanelCanvasLayerVisibility, true);
	setProperty (Ids::uiPanelCanvasLayerIndex, 0);
	owner.getCanvasTree().addChild (layerTree, -1, 0);
}

CtrlrPanelCanvasLayer::~CtrlrPanelCanvasLayer()
{
	layerTree.removeListener (this);
}

void CtrlrPanelCanvasLayer::resized()
{
}

void CtrlrPanelCanvasLayer::restoreState (const ValueTree &savedState)
{
	restoreProperties (savedState, layerTree, 0);
}

ValueTree &CtrlrPanelCanvasLayer::getObjectTree()
{
	return (layerTree);
}

void CtrlrPanelCanvasLayer::setProperty (const Identifier& name, const var &newValue, const bool isUndoable)
{
	layerTree.setProperty (name, newValue, 0);
}

const var &CtrlrPanelCanvasLayer::getProperty (const Identifier& name) const
{
	return (layerTree.getProperty (name));
}

const var CtrlrPanelCanvasLayer::getProperty (const Identifier& name, const var &defaultReturnValue) const
{
	return (layerTree.getProperty (name, defaultReturnValue));
}

void CtrlrPanelCanvasLayer::paint (Graphics &g)
{
	g.fillAll(VAR2COLOUR(getProperty (Ids::uiPanelCanvasLayerColour)));
}

void CtrlrPanelCanvasLayer::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiPanelCanvasLayerColour)
	{
		repaint();
	}

	if (property == Ids::uiPanelCanvasLayerVisibility)
	{
		setVisible (getProperty (property));
	}

	if (property == Ids::uiPanelCanvasLayerMouseHandle)
	{
		mousePass = (bool)getProperty(property);
	}
}
