#ifndef __JUCER_HEADER_CTRLRCOMBO_CTRLRCOMBO_380F4A09__
#define __JUCER_HEADER_CTRLRCOMBO_CTRLRCOMBO_380F4A09__

#include "CtrlrComponents/CtrlrComponent.h"
class CtrlrValueMap;

class CtrlrCombo  : public CtrlrComponent,
                    public KeyListener,
					public ComboBox::Listener
{
public:
    //==============================================================================
    CtrlrCombo (CtrlrModulator &owner);
    ~CtrlrCombo();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	double getComponentValue();
	int getComponentMidiValue();
	double getComponentMaxValue();
	const String getComponentText();
	void setComponentText (const String &componentText);
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
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
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr);
	CtrlrValueMap &getValueMap() { return (*valueMap); }

	static void wrapForLua(lua_State *L);
    //[/UserMethods]
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
	ScopedPointer<CtrlrValueMap> valueMap;
    //[/UserVariables]

    //==============================================================================
    ComboBox* ctrlrCombo;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrCombo (const CtrlrCombo&);
    const CtrlrCombo& operator= (const CtrlrCombo&);
};


#endif   // __JUCER_HEADER_CTRLRCOMBO_CTRLRCOMBO_380F4A09__
