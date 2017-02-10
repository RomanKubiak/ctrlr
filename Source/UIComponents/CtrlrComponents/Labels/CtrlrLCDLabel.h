#ifndef __JUCER_HEADER_CTRLRLCDLABEL_CTRLRLCDLABEL_980087AF__
#define __JUCER_HEADER_CTRLRLCDLABEL_CTRLRLCDLABEL_980087AF__

#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrPanel/CtrlrPanel.h"

class CtrlrLCDLabel  : public CtrlrComponent,
                       public CtrlrPanel::Listener,
					   public Label::Listener
{
public:
    //==============================================================================
    CtrlrLCDLabel (CtrlrModulator &owner);
    ~CtrlrLCDLabel();

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
	void modulatorChanged (CtrlrModulator *modulatorThatChanged);
	void labelTextChanged (Label* labelThatHasChanged);
	static void wrapForLua(lua_State *L);
	CtrlrLCDLabel &setLabelText(const String &text);
	CtrlrLCDLabel &appendText(const String &text);
	const String getText();
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	WeakReference <CtrlrLuaMethod> labelChangedCbk;
    //[/UserVariables]

    //==============================================================================
    Label* ctrlrLabel;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrLCDLabel (const CtrlrLCDLabel&);
    const CtrlrLCDLabel& operator= (const CtrlrLCDLabel&);
};


#endif   // __JUCER_HEADER_CTRLRLCDLABEL_CTRLRLCDLABEL_980087AF__
