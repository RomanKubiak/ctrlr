#include "stdafx.h"
#include "CtrlrPanelViewport.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanelEditor.h"
#include "CtrlrManager/CtrlrManager.h"

/**
 */

CtrlrPanelViewport::CtrlrPanelViewport (CtrlrPanelEditor &_owner)
	: owner(_owner), isSpaceDown(false)
{
	currentZoom = 1.0;

	canvasList.add (new CtrlrPanelCanvas (owner));

	magnifier = new CtrlrMagnifierComponent (canvasList[0]);
	addAndMakeVisible (viewport = new CtrlrViewport(this));
	viewport->setViewedComponent (magnifier);

    setSize (512, 512);
}

CtrlrPanelViewport::~CtrlrPanelViewport()
{
	canvasList.clear (false);
	deleteAndZero (viewport);
}


void CtrlrPanelViewport::paint (Graphics& g)
{
	g.fillAll (Colours::transparentBlack);
}

void CtrlrPanelViewport::resized()
{
	viewport->setBounds	(0, 0, getWidth(), getHeight());
}

bool CtrlrPanelViewport::keyStateChanged (const bool isKeyDown)
{
	if (KeyPress::isKeyCurrentlyDown(KeyPress::spaceKey))
	{
		dragKeyHeldDown (true);
	}
	else
	{
		dragKeyHeldDown (false);
	}
    return false;
}

void CtrlrPanelViewport::setZoom (const double zoom, int anchorX, int anchorY)
{
	if (zoom < 0.5)
		return;

	currentZoom = zoom;

	Point<int> anchor (getCurrentCanvas()->getLocalPoint (viewport, Point<int> (anchorX, anchorY)));

	resized();
	anchor = viewport->getLocalPoint (getCurrentCanvas(), anchor);

	viewport->setViewPosition (jlimit (0, jmax (0, viewport->getViewedComponent()->getWidth() - viewport->getViewWidth()),
                                       viewport->getViewPositionX() + anchor.getX() - anchorX),
                               jlimit (0, jmax (0, viewport->getViewedComponent()->getHeight() - viewport->getViewHeight()),
                                       viewport->getViewPositionY() + anchor.getY() - anchorY));
	magnifier->setScaleFactor (currentZoom);
}

const double CtrlrPanelViewport::getZoom ()
{
	return (currentZoom);
}

void CtrlrPanelViewport::dragKeyHeldDown (const bool isKeyDown)
{
	if (isSpaceDown != isKeyDown)
	{
		isSpaceDown = isKeyDown;

		if (isSpaceDown)
		{
			CtrlrDraggerOverlayComp* const dc = new CtrlrDraggerOverlayComp(viewport);
			addAndMakeVisible (dc);
			dc->setBounds (0, 0, getWidth(), getHeight());
		}
		else
		{
			for (int i = getNumChildComponents(); --i >= 0;)
			{
				if (dynamic_cast <CtrlrDraggerOverlayComp*> (getChildComponent (i)) != 0)
				{
					delete getChildComponent (i);
				}
			}
		}
	}
}

CtrlrViewport::CtrlrViewport(CtrlrPanelViewport *_panelViewport) : panelViewport(_panelViewport)
{
}

CtrlrViewport::~CtrlrViewport()
{
}

void CtrlrViewport::mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel)
{
    if (e.mods.isCtrlDown() || e.mods.isAltDown())
	{
	    const double factor = (wheel.deltaY > 0) ? 2.0 : 0.5;

		panelViewport->setZoom (panelViewport->getZoom() * factor, e.x, e.y);
    }
    else
    {
		ViewportExt::mouseWheelMove (e, wheel);
	}
}

bool CtrlrViewport::keyPressed (const KeyPress &key, Component *originatingComponent)
{
	return (false);
}

bool CtrlrViewport::keyStateChanged (bool isKeyDown, Component *originatingComponent)
{
	return (false);
}

void CtrlrPanelViewport::setCurrentEditedCanvas(const int canvasIndex)
{
}

void CtrlrPanelViewport::addCanvas(const String &canvasName)
{
	CtrlrPanelCanvas *c = new CtrlrPanelCanvas (owner);
	c->setProperty (Ids::uiPanelCanvasLayerName, canvasName);
	c->setProperty (Ids::uiPanelCanvasLayerIndex, canvasList.size());

	canvasList.add (c);
}

void CtrlrPanelViewport::removeCanvas(const int canvasIndex)
{
}

const int CtrlrPanelViewport::getNumCanvases()
{
	return (canvasList.size());
}

void CtrlrPanelViewport::moveCanvasUp(const int canvasIndex)
{
}

void CtrlrPanelViewport::moveCanvasDown(const int canvasIndex)
{
}

CtrlrPanelCanvas *CtrlrPanelViewport::getCurrentCanvas()
{
	return (canvasList[0]);
}

void CtrlrPanelViewport::lookAndFeelChanged()
{
	resized();
}
