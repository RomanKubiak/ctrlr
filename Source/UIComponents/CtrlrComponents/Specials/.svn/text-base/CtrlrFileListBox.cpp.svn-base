#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  17 Jan 2012 2:37:05am

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
#include "CtrlrFileListBox.h"
#include "CtrlrIDs.h"
#include "CtrlrUtilities.h"
#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrLuaManager.h"
//[/Headers]



//[MiscUserDefs] You can add your own user definitions and misc code here...
CtrlrFileListBoxLF::CtrlrFileListBoxLF (CtrlrFileListBox &_owner) : owner(_owner)
{
}

void CtrlrFileListBoxLF::drawFileBrowserRow (Graphics &g, int width, int height, const String &filename, Image *icon, const String &fileSizeDescription, const String &fileTimeDescription, bool isDirectory, bool isItemSelected, int itemIndex, DirectoryContentsDisplayComponent &component)
{
	if (isItemSelected)
		g.fillAll (VAR2COLOUR(owner.getProperty(Ids::uiFileListHighlightBgColour)));

    const int x = 32;
    g.setColour (Colours::black);

    if (icon != nullptr && icon->isValid())
    {
        g.drawImageWithin (*icon, 2, 2, x - 4, height - 4,
                           RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize,
                           false);
    }
    else
    {
        const Drawable* d = isDirectory ? getDefaultFolderImage()
                                        : getDefaultDocumentFileImage();

        if (d != nullptr)
            d->drawWithin (g, Rectangle<float> (2.0f, 2.0f, x - 4.0f, height - 4.0f),
                           RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
    }

	if (isItemSelected)
	{
		g.setFont (owner.getOwner().getOwner().getOwner().getFontManager().getFontFromString (owner.getProperty(Ids::uiFileListBoxHighlightFont)));
		g.setColour (VAR2COLOUR(owner.getProperty(Ids::uiFileListHighlightTextColour)));
	}
	else
	{
		g.setFont (owner.getOwner().getOwner().getOwner().getFontManager().getFontFromString (owner.getProperty(Ids::uiFileListFont)));
		g.setColour (VAR2COLOUR(owner.getProperty(Ids::uiFileListTextColour)));
	}

	if (width > 450 && ! isDirectory)
	{
		const int sizeX = roundToInt (width * 0.7f);
		const int dateX = roundToInt (width * 0.8f);

		g.drawFittedText (filename, x, 0, sizeX - x, height, Justification::centredLeft, 1);

		g.setFont (owner.getOwner().getOwner().getOwner().getFontManager().getFontFromString (owner.getProperty(Ids::uiFileListFont)));
		g.setColour (VAR2COLOUR(owner.getProperty(Ids::uiFileListTextColour)));

		if (! isDirectory)
		{
			g.drawFittedText (fileSizeDescription, sizeX, 0, dateX - sizeX - 8, height, Justification::centredRight, 1);
			g.drawFittedText (fileTimeDescription, dateX, 0, width - 8 - dateX, height, Justification::centredRight, 1);
		}
	}
	else
	{
		g.drawFittedText (filename, x, 0, width - x, height, Justification::centredLeft, 1);
	}
}

CtrlrFileTreeComponent::CtrlrFileTreeComponent (CtrlrFileListBox &_owner, DirectoryContentsList &listToShow) : owner(_owner), FileTreeComponent( listToShow )
{
}

void CtrlrFileTreeComponent::paint (Graphics& g)
{
	int i = owner.getProperty(Ids::uiFileListBoxOutline);
	g.setColour (VAR2COLOUR(owner.getProperty(Ids::uiFileListBoxBgColour)));
	g.fillRect(i, i, (getWidth() - 2*i), (getHeight() - 2*i));

	g.setColour (VAR2COLOUR(owner.getProperty(Ids::uiFileListBoxOutlineColour)));
	g.drawRect (0, 0, getWidth(), getHeight(),  i);
}

//[/MiscUserDefs]

//==============================================================================
CtrlrFileListBox::CtrlrFileListBox (CtrlrModulator &owner)
    : CtrlrComponent(owner), timeSliceThread("CTRLR FILE LIST BOX THREAD"), fileListBoxLookAndFeel(*this)
{
    //[UserPreSize]
	File folder (File::getSpecialLocation (File::userHomeDirectory));
	while (folder.getParentDirectory() != folder)
		folder = folder.getParentDirectory();

	directoryContentsList = new DirectoryContentsList (0, timeSliceThread);
	directoryContentsList->setDirectory (folder, true, true);
	timeSliceThread.startThread (3);

	treeComponent = new CtrlrFileTreeComponent( *this, *directoryContentsList );
	treeComponent->addListener (this);
	addAndMakeVisible (treeComponent);

	setProperty (Ids::uiFileListBoxBgColour, "0xffffffff");
	setProperty (Ids::uiFileListLineColour, "0xff000000");
	setProperty (Ids::uiFileListIndentSize, 16);
	setProperty (Ids::uiFileListFont, FONT2STR (Font(14)));
	setProperty (Ids::uiFileListTextColour, "0xff000000");

	setProperty (Ids::uiFileListHighlightTextColour, "0xff000000");
	setProperty (Ids::uiFileListHighlightBgColour, "0xff0000ff");
	setProperty (Ids::uiFileListBoxHighlightFont, FONT2STR (Font(14)));
	setProperty (Ids::uiFileListBoxOutline, 0);
	setProperty (Ids::uiFileListBoxOutlineColour, "0xff000000");
	setProperty (Ids::uiFileListBoxVScrollBgColour, "0xffffffff");
	setProperty (Ids::uiFileListBoxVScrollThumbColour, "0xffababab");
	setProperty (Ids::uiFileListBoxVScrollTrackColour, "0xffff0000");
	setProperty (Ids::uiFileListBoxHScrollBgColour, "0xffffffff");
	setProperty (Ids::uiFileListBoxHScrollThumbColour, "0xffababab");
	setProperty (Ids::uiFileListBoxHScrollTrackColour, "0xffff0000");

	setProperty (Ids::uiFileListOpenButtonVisible, true);
	setProperty (Ids::uiFileListFileClicked, COMBO_NONE_ITEM);
	setProperty (Ids::uiFileListFileDoubleClicked, COMBO_NONE_ITEM);
//	setProperty (Ids::uiFileListItemDeleteKeyPressed, COMBO_NONE_ITEM);
//	setProperty (Ids::uiFileListItemReturnKeyPressed, COMBO_NONE_ITEM);
	setProperty (Ids::uiFileListCurrentRoot, folder.getFullPathName());

	treeComponent->setLookAndFeel (&fileListBoxLookAndFeel);
    //[/UserPreSize]

    setSize (128, 256);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrFileListBox::~CtrlrFileListBox()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	treeComponent->removeListener (this);
	delete treeComponent.release();
	delete directoryContentsList.release();
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrFileListBox::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrFileListBox::resized()
{
    //[UserResized] Add your own custom resize handling here..
	treeComponent->setBounds (getUsableRect());
	int i = getProperty(Ids::uiFileListBoxOutline);
	int w = getWidth(), h = getHeight();
	Viewport* v = treeComponent->getViewport();
	v->setBounds( i, i, w - i*2, h - i*2 );
//	v->getHorizontalScrollBar()->setBounds( i, i, w - i*2, h - i*2 );
//	v->getVerticalScrollBar()->setBounds( i, i, w - i*2, h - i*2 );
//	v->resized();
    //[/UserResized]
}


//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrFileListBox::setComponentValue (const double newValue, const bool sendChangeMessage)
{
	treeComponent->setSelectedFile (treeComponent->getSelectedFile(newValue));
}

const double CtrlrFileListBox::getComponentValue()
{
	return (1);
}

const int CtrlrFileListBox::getComponentMidiValue()
{
	return (1);
}

const double CtrlrFileListBox::getComponentMaxValue()
{
	return (directoryContentsList->getNumFiles());
}

const String CtrlrFileListBox::getComponentText()
{
	return (treeComponent->getSelectedFile().getFullPathName());
}

void CtrlrFileListBox::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::uiFileListBoxBgColour)
	{
		treeComponent->setColour (TreeView::backgroundColourId, VAR2COLOUR(getProperty(property)));
	}
	else if (property == Ids::uiFileListLineColour)
	{
		treeComponent->setColour (TreeView::linesColourId, VAR2COLOUR(getProperty(property)));
	}
	else if (property == Ids::uiFileListIndentSize)
	{
		treeComponent->setIndentSize (getProperty(property));
	}
	else if (property == Ids::uiFileListBoxOutline)
	{
		int i = getProperty(Ids::uiFileListBoxOutline);
		int w = getWidth(), h = getHeight();
		Viewport* v = treeComponent->getViewport();
		v->setBounds( i, i, w - i*2, h - i*2 );
//		v->getHorizontalScrollBar()->setBounds( i, i, w - i*2, h - i*2 );
//		v->getVerticalScrollBar()->setBounds( i, i, w - i*2, h - i*2 );
//		v->resized();
		treeComponent->repaint();
	}
	else if (property == Ids::uiFileListBoxOutlineColour)
	{
		treeComponent->setColour (ListBox::outlineColourId, VAR2COLOUR(getProperty (property)));
		treeComponent->repaint();
	}
	else if (property == Ids::uiFileListBoxHScrollBgColour
		|| property == Ids::uiFileListBoxHScrollThumbColour
		|| property == Ids::uiFileListBoxHScrollTrackColour
		|| property == Ids::uiFileListBoxVScrollBgColour
		|| property == Ids::uiFileListBoxVScrollThumbColour
		|| property == Ids::uiFileListBoxVScrollTrackColour
		)
	{
		Viewport* view = treeComponent->getViewport();
		if ( ScrollBar* h = view->getHorizontalScrollBar() )
		{
			h->setColour (ScrollBar::backgroundColourId, VAR2COLOUR(getProperty (Ids::uiFileListBoxHScrollBgColour)));
			h->setColour (ScrollBar::thumbColourId, VAR2COLOUR(getProperty (Ids::uiFileListBoxHScrollThumbColour)));
			h->setColour (ScrollBar::trackColourId, VAR2COLOUR(getProperty (Ids::uiFileListBoxHScrollTrackColour)));
		}
		if ( ScrollBar* v = view->getVerticalScrollBar() )
		{
			v->setColour (ScrollBar::backgroundColourId, VAR2COLOUR(getProperty (Ids::uiFileListBoxVScrollBgColour)));
			v->setColour (ScrollBar::thumbColourId, VAR2COLOUR(getProperty (Ids::uiFileListBoxVScrollThumbColour)));
			v->setColour (ScrollBar::trackColourId, VAR2COLOUR(getProperty (Ids::uiFileListBoxVScrollTrackColour)));
		}
	} 
	else if (property == Ids::uiFileListFont)
	{
		treeComponent->setLookAndFeel (0);
		treeComponent->setLookAndFeel (&fileListBoxLookAndFeel);
	}
	else if (property == Ids::uiFileListTextColour)
	{
		treeComponent->setColour (DirectoryContentsDisplayComponent::textColourId, VAR2COLOUR(getProperty(property)));
	}
	else if (property == Ids::uiFileListHighlightTextColour)
	{
		treeComponent->setColour (DirectoryContentsDisplayComponent::highlightColourId, VAR2COLOUR(getProperty(property)));
	}
	else if (property == Ids::uiFileListOpenButtonVisible)
	{
		treeComponent->setOpenCloseButtonsVisible (getProperty(property));
	}
	else if (property == Ids::uiFileListFileClicked)
	{
		if (getProperty(property) == String::empty)
			return;

		fileClickedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiFileListFileDoubleClicked)
	{
		if (getProperty(property) == String::empty)
			return;

		fileDoubleClickedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
/*	else if (property == Ids::uiFileListItemDeleteKeyPressed)
	{
		if (getProperty(property) == String::empty)
			return;

		itemDeleteKeyPressedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	}
	else if (property == Ids::uiFileListItemReturnKeyPressed)
	{
		if (getProperty(property) == String::empty)
			return;

		itemReturnKeyPressedCbk = owner.getOwner().getCtrlrLuaManager().getMethodManager().getMethod(getProperty(property));
	} */
	else if (property == Ids::uiFileListCurrentRoot)
	{
		directoryContentsList->setDirectory (File(getProperty(property)), true, true);
		treeComponent->refresh();
	}
	else
	{
		CtrlrComponent::valueTreePropertyChanged(treeWhosePropertyHasChanged, property);
	}

	if (restoreStateInProgress == false)
	{
		resized();
	}
}

void CtrlrFileListBox::fileClicked (const File &file, const MouseEvent &e)
{
	if (fileClickedCbk && !fileClickedCbk.wasObjectDeleted())
	{
		if (fileClickedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (fileClickedCbk, &owner, file);
		}
	}
}

void CtrlrFileListBox::fileDoubleClicked (const File &file)
{
	if (fileDoubleClickedCbk && !fileDoubleClickedCbk.wasObjectDeleted())
	{
		if (fileDoubleClickedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (fileDoubleClickedCbk, &owner, file);
		}
	}
}

/*
void CtrlrFileListBox::deleteKeyPressed (const int value)
{
	if (itemDeleteKeyPressedCbk && !itemDeleteKeyPressedCbk.wasObjectDeleted())
	{
		if (itemDeleteKeyPressedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (itemDeleteKeyPressedCbk, &owner, value);
		}
	}
}

void CtrlrFileListBox::returnKeyPressed (const int value)
{
	if (itemReturnKeyPressedCbk && !itemReturnKeyPressedCbk.wasObjectDeleted())
	{
		if (itemReturnKeyPressedCbk->isValid())
		{
			owner.getOwner().getCtrlrLuaManager().getMethodManager().call (itemReturnKeyPressedCbk, &owner, value);
		}
	}
}
*/

void CtrlrFileListBox::selectionChanged ()
{
}

void CtrlrFileListBox::browserRootChanged (const File &newRoot)
{
}

int CtrlrFileListBox::getNumSelectedFiles() const
{
	return (treeComponent->getNumSelectedFiles());
}

File CtrlrFileListBox::getSelectedFile(int index) const
{
	return (treeComponent->getSelectedFile(index));
}

void CtrlrFileListBox::deselectAllFiles()
{
	treeComponent->deselectAllFiles();
}

void CtrlrFileListBox::scrollToTop()
{
	treeComponent->scrollToTop();
}

void CtrlrFileListBox::setSelectedFile(const File &file)
{
	treeComponent->setSelectedFile(file);
}

void CtrlrFileListBox::refresh()
{
	treeComponent->refresh();
}

void CtrlrFileListBox::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrFileListBox,bases<CtrlrComponent,CtrlrLuaObject> >("CtrlrFileListBox")
			.def("getNumSelectedFiles", &CtrlrFileListBox::getNumSelectedFiles)
			.def("getSelectedFile", &CtrlrFileListBox::getSelectedFile)
			.def("deselectAllFiles", &CtrlrFileListBox::deselectAllFiles)
			.def("scrollToTop", &CtrlrFileListBox::scrollToTop)
			.def("setSelectedFile", &CtrlrFileListBox::setSelectedFile)
			.def("refresh", &CtrlrFileListBox::refresh)
	];
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrFileListBox" componentName=""
                 parentClasses="public CtrlrComponent" constructorParams="CtrlrModulator &amp;owner"
                 variableInitialisers="CtrlrComponent(owner), timeSliceThread(&quot;CTRLR FILE LIST BOX THREAD&quot;), fileListBoxLookAndFeel(*this)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="128" initialHeight="256">
  <BACKGROUND backgroundColour="ffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
