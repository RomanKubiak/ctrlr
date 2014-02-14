#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  7 Oct 2011 4:24:16pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "CtrlrManager/CtrlrManager.h"
#include "../CtrlrComponentTypeManager.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanelResource.h"
//[/Headers]

#include "CtrlrXYSurface.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CtrlrXYSurface::CtrlrXYSurface (CtrlrModulator &owner)
    : CtrlrComponent(owner),
      surfaceModulator (0)
{
    addAndMakeVisible (surfaceModulator = new CtrlrXYModulator (*this));

    //[UserPreSize]
	initialized=false;
	surfaceModulator->setAlwaysOnTop(true);
	surfaceModulator->addMouseListener(this,true);

	setProperty (Ids::uiXYSurfaceBgGradientType, "Radial");
	setProperty (Ids::uiXYSurfaceBackgroundColour1, "0xff222222");
	setProperty (Ids::uiXYSurfaceBackgroundColour2, "0xff000000");
	setProperty (Ids::uiXYSurfaceOutlineGradientType, "0xff909090");
	setProperty (Ids::uiXYSurfaceOutlineColour1, "0xff909090");
	setProperty (Ids::uiXYSurfaceOutlineColour2, "0xff909090");
	setProperty (Ids::uiXYSurfaceOutlineThickness, 1);
	setProperty (Ids::uiXYSurfaceCornerSize, 10);
	setProperty (Ids::uiXYSurfaceBgImageResource, COMBO_NONE_ITEM);
	setProperty (Ids::uiXYSurfaceBgImageLayout, 0);
	setProperty (Ids::uiXYSurfaceBgImageAlpha, 255);

	setProperty (Ids::uiXYSurfaceXTrackEnabled, true);
	setProperty (Ids::uiXYSurfaceXTrackColour, "0xffffffff");
	setProperty (Ids::uiXYSurfaceXTrackThickness, 2);
	setProperty (Ids::uiXYSurfaceYTrackColour, "0xffffffff");
	setProperty (Ids::uiXYSurfaceYTrackThickness, 2);
	setProperty (Ids::uiXYSurfaceModSectionLocation, true);
	setProperty (Ids::uiXYSurfaceModSectionHeight, 16);
	setProperty (Ids::uiXYSurfaceInfoLabelVisible, true);
	setProperty (Ids::uiXYSurfaceInfoLabelLocation, "bottomRight");
	setProperty (Ids::uiXYSurfaceInfoLabelColour, "0xffffffff");
	setProperty (Ids::uiXYSurfaceInfoLabelFont, FONT2STR (Font(12)));
	setProperty (Ids::uiXYSurfaceMaxX, 127);
	setProperty (Ids::uiXYSurfaceDestinationX, COMBO_NONE_ITEM);
	setProperty (Ids::uiXYSurfaceMaxY, 127);
	setProperty (Ids::uiXYSurfaceDestinationY, COMBO_NONE_ITEM);
	setProperty (Ids::uiXYSurfaceGradientColour, "0x10ffffff");
	setProperty (Ids::uiXYSurfaceGradientGrain, 8);

	setProperty (Ids::uiXYSurfaceModulatorBgGradientType, "None");
	setProperty (Ids::uiXYSurfaceModulatorBgColour1, "0xffff0000");
	setProperty (Ids::uiXYSurfaceModulatorBgColour2, "0xff900000");
	setProperty (Ids::uiXYSurfaceModulatorOutlineGradientType, "None");
	setProperty (Ids::uiXYSurfaceModulatorOutlineColour1, "0xffff0000");
	setProperty (Ids::uiXYSurfaceModulatorOutlineColour2, "0xffff0000");
	setProperty (Ids::uiXYSurfaceModulatorOutlineThickness, 1);
	setProperty (Ids::uiXYSurfaceModulatorWidth, 16);
	setProperty (Ids::uiXYSurfaceModulatorHeight, 16);
	setProperty (Ids::uiXYSuraceXFlip, false);
	setProperty (Ids::uiXYSuraceYFlip, false);
	setProperty (Ids::uiXYSuraceShowRightClickMenu, true);
	setProperty (Ids::uiXYSurfaceDestinationXGroupFilter, String::empty);
	setProperty (Ids::uiXYSurfaceDestinationYGroupFilter, String::empty);
    //[/UserPreSize]

    setSize (256, 256);


    //[Constructor] You can add your own custom stuff here..
	surfaceModulator->setBounds (128,128,16,16);
    //[/Constructor]
}

CtrlrXYSurface::~CtrlrXYSurface()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (surfaceModulator);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrXYSurface::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
	gradientFromProperty (g, usableRectangle.getSmallestIntegerContainer(), getObjectTree(), Ids::uiXYSurfaceBgGradientType, Ids::uiXYSurfaceBackgroundColour1, Ids::uiXYSurfaceBackgroundColour2);
	g.fillRoundedRectangle ((float)usableRectangle.getTopLeft().getX(), (float)usableRectangle.getTopLeft().getY(), (float)usableRectangle.getWidth(), (float)usableRectangle.getHeight(), getProperty(Ids::uiXYSurfaceCornerSize));

	gradientFromProperty (g, usableRectangle.getSmallestIntegerContainer(), getObjectTree(), Ids::uiXYSurfaceOutlineGradientType, Ids::uiXYSurfaceOutlineColour1, Ids::uiXYSurfaceOutlineColour2);
    g.drawRoundedRectangle ((float)usableRectangle.getX(), (float)usableRectangle.getY(), (float)usableRectangle.getWidth(), (float)usableRectangle.getHeight(), getProperty(Ids::uiXYSurfaceCornerSize), getProperty(Ids::uiXYSurfaceOutlineThickness));
	
	const int snapSize	= (int)getProperty (Ids::uiXYSurfaceGradientGrain, 8);
	Colour colour		= VAR2COLOUR(getProperty(Ids::uiXYSurfaceGradientColour));
	
	if (snapSize > 0)
	{
		Image backgroundFill(Image::ARGB, snapSize, snapSize, true);
		Graphics g1(backgroundFill);

		if (snapSize > 2)
		{
			g1.setColour (colour);
			g1.drawRect (0, 0, snapSize + 1, snapSize + 1);
		}

		g.setTiledImageFill (backgroundFill, 0, 0, 1.0f);
		g.fillRoundedRectangle ((float)usableRectangle.getX(), (float)usableRectangle.getY(), (float)usableRectangle.getWidth(), (float)usableRectangle.getHeight(), getProperty(Ids::uiXYSurfaceCornerSize));
	}
	
	if (backgroundImage.isValid())
	{
		if ((int)getProperty (Ids::uiXYSurfaceBgImageLayout) == 8192)
		{
			g.setTiledImageFill (backgroundImage, 0, 0, (float)getProperty (Ids::uiXYSurfaceBgImageAlpha)/255.0f);
			g.fillRect ((float)usableRectangle.getX(), (float)usableRectangle.getY(), (float)usableRectangle.getWidth(), (float)usableRectangle.getHeight());
		}
		else
		{
			g.setColour (Colours::black.withAlpha ((float)getProperty (Ids::uiXYSurfaceBgImageAlpha)/255.0f));
			g.drawImageWithin (backgroundImage,
								usableRectangle.getX(),
								usableRectangle.getX(),
								usableRectangle.getWidth(),
								usableRectangle.getHeight(),
								RectanglePlacement(getProperty (Ids::uiXYSurfaceBgImageLayout)));
		}
	}
	
	if (getProperty (Ids::uiXYSurfaceXTrackEnabled))
	{
		const Point<int> c = surfaceModulator->getBounds().getCentre();

		g.setColour (VAR2COLOUR(getProperty(Ids::uiXYSurfaceYTrackColour)));
		g.drawLine ((float)c.getX(), (float)usableRectangle.getY(), (float)c.getX(), (float)usableRectangle.getBottom(), getProperty(Ids::uiXYSurfaceYTrackThickness));

		g.setColour (VAR2COLOUR(getProperty(Ids::uiXYSurfaceXTrackColour)));
		g.drawLine ((float)usableRectangle.getX(), (float)c.getY(), (float)usableRectangle.getWidth(), (float)c.getY(), getProperty(Ids::uiXYSurfaceXTrackThickness));
	}
	
	if ((bool)getProperty(Ids::uiXYSurfaceInfoLabelVisible))
	{
		const int xScale = (int)getProperty(Ids::uiXYSurfaceMaxX);
		const int yScale = (int)getProperty(Ids::uiXYSurfaceMaxY);

		const Point<int> c = surfaceModulator->getBounds().getCentre();
		g.setColour (VAR2COLOUR(getProperty (Ids::uiXYSurfaceInfoLabelColour)));
		g.setFont (STR2FONT(getProperty(Ids::uiXYSurfaceInfoLabelFont)));
		g.drawText ("X="+String(getValueForPosition(c.getX(), true))+" Y="+String(getValueForPosition(c.getY(), false)), 
					usableRectangle.getX() + 8, 
					usableRectangle.getY() + 8, 
					usableRectangle.getWidth()-16, 
					usableRectangle.getHeight()-16, 
					justificationFromProperty(getProperty (Ids::uiXYSurfaceInfoLabelLocation)), 
					true);
	}
	
    //[/UserPaint]
}

void CtrlrXYSurface::resized()
{
    //[UserResized] Add your own custom resize handling here..
	surfaceModulator->setSize (getProperty(Ids::uiXYSurfaceModulatorWidth), getProperty(Ids::uiXYSurfaceModulatorHeight));
	CtrlrComponent::resized();
	usableRectangle = getUsableRect();
    //[/UserResized]
}

void CtrlrXYSurface::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
	if (e.mods.isPopupMenu())
	{
		showPopupMenu();
	}
	else if (e.eventComponent == this)
	{
		surfaceModulator->setCentrePosition (e.x, e.y);
		surfaceModulator->mouseDown (e);
		repaint();
	}
    //[/UserCode_mouseDown]
}

void CtrlrXYSurface::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
	if (e.mods.isPopupMenu())
	{
	}
	else if (e.eventComponent == this)
	{
		surfaceModulator->mouseDrag (e);
	}
    //[/UserCode_mouseDrag]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrXYSurface::setComponentValue (const double newValue, const bool sendChangeMessage)
{
}

const double CtrlrXYSurface::getComponentValue()
{
	return (1);
}

const int CtrlrXYSurface::getComponentMidiValue()
{
	return (1);
}

const double CtrlrXYSurface::getComponentMaxValue()
{
	return (1);
}

void CtrlrXYSurface::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiXYSurfaceBgImageResource)
	{
		setResource();
	}
	else if (property == Ids::uiXYSurfaceDestinationX || property == Ids::uiXYSurfaceDestinationY)
	{
		if (initialized)
		{
			syncDestination();
		}
	}
	else
	{
		CtrlrComponent::valueTreePropertyChanged (treeWhosePropertyHasChanged, property);
	}

	if (restoreStateInProgress == false)
	{
		resized();
	}
}

void CtrlrXYSurface::modulatorMoved()
{
	const Point<int> c	= surfaceModulator->getBounds().getCentre();

	if (destinationX)
	{	
		destinationX->getProcessor().setValueFromGUI (getValueForPosition(c.getX(), true));
	}

	if (destinationY)
	{
		destinationY->getProcessor().setValueFromGUI (getValueForPosition(c.getY(), false));
	}

	repaint();
}

void CtrlrXYSurface::syncDestination()
{
	int x			= surfaceModulator->getX();
	int y			= surfaceModulator->getY();

	destinationX = owner.getOwner().getModulator (getProperty (Ids::uiXYSurfaceDestinationX).toString());
	destinationY = owner.getOwner().getModulator (getProperty (Ids::uiXYSurfaceDestinationY).toString());

	if (destinationX)
	{
		x = getPositionForValue (destinationX->getValueNonMapped(), true);
	}
	if (destinationY)
	{
		y = getPositionForValue (destinationY->getValueNonMapped(), false);
	}

	surfaceModulator->setCentrePosition (x,y);
}

void CtrlrXYSurface::allModulatorsInitialized()
{
	initialized = true;
	syncDestination();

	resized();
}

void CtrlrXYSurface::showPopupMenu()
{
	if (!(bool)getProperty(Ids::uiXYSuraceShowRightClickMenu))
		return;

	rebuildModulatorList();

	PopupMenu m;
	PopupMenu modsX = getModulatorListAsMenu(3, getProperty(Ids::uiXYSurfaceDestinationX));
	PopupMenu modsY = getModulatorListAsMenu(3+modsX.getNumItems(), getProperty(Ids::uiXYSurfaceDestinationY));
	m.addItem (1, "Flip min/max for X axis",true, (bool)getProperty(Ids::uiXYSuraceXFlip));
	m.addItem (2, "Flip min/max for Y axis",true, (bool)getProperty(Ids::uiXYSuraceYFlip));

	m.addSectionHeader ("Assign modulators");
	m.addSubMenu ("X Axis", modsX);
	m.addSubMenu ("Y Axis", modsY);

	const int ret = m.show();

	if (ret == 1)
	{
		setProperty (Ids::uiXYSuraceXFlip, !getProperty(Ids::uiXYSuraceXFlip));
		return;
	}
	
	if (ret == 2)
	{
		setProperty (Ids::uiXYSuraceYFlip, !getProperty(Ids::uiXYSuraceYFlip));
		return;
	}
	
	if (ret > 2 && ret <= 3+modulatorList.size())
	{
		const int modulatorIndexOnList = ret - 3 - 1;
		setProperty (Ids::uiXYSurfaceDestinationX, modulatorList[modulatorIndexOnList]);
		return;
	}
	
	if (ret > 3+modulatorList.size())
	{
		const int modulatorIndexOnList = ret - 4 - 1 - modulatorList.size();
		setProperty (Ids::uiXYSurfaceDestinationY, modulatorList[modulatorIndexOnList]);
		return;
	}
	
}

const PopupMenu CtrlrXYSurface::getModulatorListAsMenu(const int startIndex, const String &itemToSelect)
{
	PopupMenu m;
	m.addItem (startIndex, COMBO_ITEM_NONE);

	const int offset = startIndex + 1;

	for (int i=0; i<modulatorList.size(); i++)
	{
		m.addItem (offset + i, modulatorList[i], true, (itemToSelect == modulatorList[i]));
	}

	return (m);
}

void CtrlrXYSurface::rebuildModulatorList()
{
	modulatorList.clear();

	for (int i=0; i<owner.getOwner().getModulators().size(); i++)
	{
		if (owner.getOwner().getModulatorByIndex(i) == &owner)
			continue;

		if (owner.getOwner().getModulatorByIndex(i)->isStatic())
			continue;

		modulatorList.add (owner.getOwner().getModulatorByIndex(i)->getName());
	}
}

const int CtrlrXYSurface::getValueForPosition(const int position, const bool forX)
{
	const bool flip		= forX ? (bool)getProperty(Ids::uiXYSuraceXFlip) : (bool)getProperty(Ids::uiXYSuraceYFlip);
	const float scale	= forX ? (float)getProperty(Ids::uiXYSurfaceMaxX) : (float)getProperty(Ids::uiXYSurfaceMaxY);
	const float dim		= forX ? (float)usableRectangle.getWidth() : (float)usableRectangle.getHeight();

	return (flip ? (scale - roundFloatToInt (scale / dim * position)) : roundFloatToInt (scale / dim * position));
}

const int CtrlrXYSurface::getPositionForValue(const int value, const bool forX)
{
	const bool flip		= forX ? (bool)getProperty(Ids::uiXYSuraceXFlip) : (bool)getProperty(Ids::uiXYSuraceYFlip);
	const float scale	= forX ? (float)getProperty(Ids::uiXYSurfaceMaxX) : (float)getProperty(Ids::uiXYSurfaceMaxY);
	const float dim		= forX ? (float)usableRectangle.getWidth() : (float)usableRectangle.getHeight();

	return (dim / scale * value);
}

void CtrlrXYSurface::setResource()
{
	backgroundImage = owner.getOwner().getResourceManager().getResourceAsImage (getProperty(Ids::uiXYSurfaceBgImageResource));
	repaint();
	resized();
}

void CtrlrXYSurface::reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged)
{
	for (int i=0; i<resourcesThatChanged.size(); i++)
	{
		if (resourcesThatChanged[i]->getName() == getProperty(Ids::uiXYSurfaceBgImageResource).toString())
		{
			setResource();
		}
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrXYSurface" componentName=""
                 parentClasses="public CtrlrComponent" constructorParams="CtrlrModulator &amp;owner"
                 variableInitialisers="CtrlrComponent(owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="256"
                 initialHeight="256">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffff"/>
  <JUCERCOMP name="" id="492f31ef5b9a710a" memberName="surfaceModulator" virtualName=""
             explicitFocusOrder="0" pos="0C 0C 16 16" sourceFile="CtrlrXYModulator.cpp"
             constructorParams="*this"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
