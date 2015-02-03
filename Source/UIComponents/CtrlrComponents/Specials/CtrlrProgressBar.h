#include "JuceHeader.h"
#include "../CtrlrComponent.h"
#include "CtrlrPanel/CtrlrPanel.h"

class CtrlrProgressBar : public CtrlrComponent
{
    public:
        CtrlrProgressBar(CtrlrModulator &owner);
        ~CtrlrProgressBar();
        void setComponentValue (const double newValue, const bool sendChangeMessage=false);
        double getComponentValue();
        int getComponentMidiValue();
        double getComponentMaxValue();
        void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
        void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
        void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
        void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
        void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
        void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
        void resized();
        const String getComponentText();
        void setComponentText (const String &componentText);
        void customLookAndFeelChanged(LookAndFeelBase *customLookAndFeel = nullptr) {}
    private:
        ScopedPointer <ProgressBar> bar;
        String textToDisplay;
        double progress;
};
