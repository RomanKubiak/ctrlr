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

#ifndef __JUCER_HEADER_CTRLRFILELISTBOX_CTRLRFILELISTBOX_BC137D95__
#define __JUCER_HEADER_CTRLRFILELISTBOX_CTRLRFILELISTBOX_BC137D95__

//[Headers]     -- You can add your own extra header files here --
#include "../CtrlrComponent.h"
class CtrlrFileListBox;

class CtrlrFileListBoxLF : public LookAndFeel_V2
{
	public:
		CtrlrFileListBoxLF (CtrlrFileListBox &_owner);
		void drawFileBrowserRow (Graphics &g, int width, int height, const String &filename, Image *icon, const String &fileSizeDescription, const String &fileTimeDescription, bool isDirectory, bool isItemSelected, int itemIndex, DirectoryContentsDisplayComponent &component);

	private:
		CtrlrFileListBox &owner;
};

class CtrlrFileTreeComponent : public FileTreeComponent
{
public:
	CtrlrFileTreeComponent ( CtrlrFileListBox &_owner, DirectoryContentsList &listToShow );
	void paint( Graphics& g );
private:
	CtrlrFileListBox &owner;
};
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrFileListBox  : public CtrlrComponent, public FileBrowserListener
{
public:
    //==============================================================================
    CtrlrFileListBox (CtrlrModulator &owner);
    ~CtrlrFileListBox();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	const double getComponentValue();
	const int getComponentMidiValue();
	const double getComponentMaxValue();
	const String getComponentText();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
	void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
	void selectionChanged ();
	void fileClicked (const File &file, const MouseEvent &e);
	void fileDoubleClicked (const File &file);
//	void deleteKeyPressed (const int value);
//	void returnKeyPressed (const int value);
	void browserRootChanged (const File &newRoot);
	static void wrapForLua(lua_State *L);
	int getNumSelectedFiles() const;
	File getSelectedFile(int index=0) const;
	void deselectAllFiles();
	void scrollToTop();
	void setSelectedFile(const File &file);
	void refresh();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ScopedPointer <DirectoryContentsList> directoryContentsList;
	TimeSliceThread timeSliceThread;
//	ScopedPointer <FileTreeComponent> treeComponent;
	ScopedPointer <CtrlrFileTreeComponent> treeComponent;
//	ScopedPointer <FileListComponent> fileListComponent;
	CtrlrFileListBoxLF fileListBoxLookAndFeel;
	WeakReference <CtrlrLuaMethod> fileClickedCbk,fileDoubleClickedCbk; //,itemDeleteKeyPressedCbk,itemReturnKeyPressedCbk;
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrFileListBox (const CtrlrFileListBox&);
    const CtrlrFileListBox& operator= (const CtrlrFileListBox&);
};


#endif   // __JUCER_HEADER_CTRLRFILELISTBOX_CTRLRFILELISTBOX_BC137D95__
