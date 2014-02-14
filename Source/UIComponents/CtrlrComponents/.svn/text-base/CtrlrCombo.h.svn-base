/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  13 Oct 2011 10:49:23pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_CTRLRCOMBO_CTRLRCOMBO_380F4A09__
#define __JUCER_HEADER_CTRLRCOMBO_CTRLRCOMBO_380F4A09__

//[Headers]     -- You can add your own extra header files here --
#include "CtrlrComponent.h"
#include "CtrlrValueMap.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CtrlrCombo  : public CtrlrComponent,
                    public KeyListener,
                    public ComboBoxListener
{
public:
    //==============================================================================
    CtrlrCombo (CtrlrModulator &owner);
    ~CtrlrCombo();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	const double getComponentValue();
	const int getComponentMidiValue();
	const double getComponentMaxValue();
	const String getComponentText();
	void setComponentText (const String &componentText);
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
	void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
	void comboContentChanged();
	bool keyPressed (const KeyPress& key, Component* originatingComponent);

	class CtrlrComboLF : public LookAndFeel_V2
	{
		public:
			CtrlrComboLF (CtrlrCombo &_owner) : owner(_owner) {}
			Font getComboBoxFont (ComboBox &box);
			Font getPopupMenuFont ();
			void drawPopupMenuBackground (Graphics &g, int width, int height);
			//void drawPopupMenuItem (Graphics &g, int width, int height, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const String &text, const String &shortcutKeyText, Image *image, const Colour *textColourToUse);
			void drawPopupMenuItem (Graphics &g, const Rectangle<int>& area,
                            bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
                            const String& text, const String& shortcutKeyText,
                            const Drawable* icon, const Colour* textColourToUse);
			void drawComboBox (Graphics& g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& box);
			const Colour createBaseColour (const Colour& buttonColour, const bool hasKeyboardFocus, const bool isMouseOverButton, const bool isButtonDown);
			void positionComboBoxText (ComboBox& box, Label& label);
		private:
			CtrlrCombo &owner;
	};

	void fillContent(const int contentType);
	void panelEditModeChanged(const bool isInEditMode);

	int getSelectedId();
	int getSelectedItemIndex();
	void setSelectedId(const int id, const bool dontNotify);
	void setSelectedItemIndex(const int index, const bool dontNotify);
	const String getText();
	void setText(const String &text, const bool dontNotify);
	ComboBox *getOwnedComboBox() { return (ctrlrCombo); }
	static void wrapForLua(lua_State *L);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void mouseDown (const MouseEvent& e);
    bool keyPressed (const KeyPress& key);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	Array <var> values;
	CtrlrComboLF lf;
	CtrlrValueMap valueMap;
    //[/UserVariables]

    //==============================================================================
    ComboBox* ctrlrCombo;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrCombo (const CtrlrCombo&);
    const CtrlrCombo& operator= (const CtrlrCombo&);
};


#endif   // __JUCER_HEADER_CTRLRCOMBO_CTRLRCOMBO_380F4A09__
