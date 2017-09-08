#ifndef __JUCER_HEADER_CTRLRHYPERLINK_CTRLRHYPERLINK_843BD87D__
#define __JUCER_HEADER_CTRLRHYPERLINK_CTRLRHYPERLINK_843BD87D__


#include "CtrlrComponents/CtrlrComponent.h"

class CtrlrHyperlink  : public CtrlrComponent,
                        public ButtonListener
{
public:
    //==============================================================================
    CtrlrHyperlink (CtrlrModulator &owner);
    ~CtrlrHyperlink();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setComponentValue (const double newValue, const bool sendChangeMessage=false);
	double getComponentValue();
	int getComponentMidiValue();
	double getComponentMaxValue();
	const String getComponentText();
	void setComponentText(const String &componentText);
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int, int){}
	void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}
	void buttonContentChanged();
	bool hyperlinkOpensUrl();
	//[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);


    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    CtrlrValueMap valueMap;
    //[/UserVariables]

    //==============================================================================
    HyperlinkButton* hyperlinkButton;

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrHyperlink (const CtrlrHyperlink&);
    const CtrlrHyperlink& operator= (const CtrlrHyperlink&);
};


#endif   // __JUCER_HEADER_CTRLRHYPERLINK_CTRLRHYPERLINK_843BD87D__
