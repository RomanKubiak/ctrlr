#ifndef __JUCER_HEADER_CTRLRBUTTON_CTRLRBUTTON_4EC1070F__
#define __JUCER_HEADER_CTRLRBUTTON_CTRLRBUTTON_4EC1070F__

#include "CtrlrComponents/CtrlrComponent.h"
class CtrlrValueMap;

class CtrlrButton  : public CtrlrComponent,
                     public ButtonListener,
					 public Timer
{
public:
    //==============================================================================
    CtrlrButton (CtrlrModulator &owner);
    ~CtrlrButton();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	double getComponentValue();
	int getComponentMidiValue();
	double getComponentMaxValue();
	const String getComponentText();
	bool getToggleState();
	void setComponentText (const String &componentText);
	void buttonContentChanged();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
	void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
	void click();
	bool isToggleButton();
	void setToggleState(const bool toggleState, const bool sendChangeMessage=false);
	void timerCallback();
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}
	CtrlrValueMap &getValueMap() { return (*valueMap); }

	static void wrapForLua(lua_State *L);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void mouseDown (const MouseEvent& e);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	ScopedPointer <CtrlrValueMap> valueMap;
    //[/UserVariables]

    //==============================================================================
    TextButton* ctrlrButton;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrButton (const CtrlrButton&);
    const CtrlrButton& operator= (const CtrlrButton&);
};


#endif   // __JUCER_HEADER_CTRLRBUTTON_CTRLRBUTTON_4EC1070F__
