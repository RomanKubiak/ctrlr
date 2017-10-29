#include "stdafx.h"
#include "CtrlrPanelUtilities.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrComponents/CtrlrComponent.h"

CtrlrPanelUtilities::CtrlrPanelUtilities (CtrlrPanelEditor &_owner)
    : owner(_owner),
      xmlPreview (0)
{
    addAndMakeVisible (xmlPreview = new CodeEditorComponent (codeDocument, &xmlTokeniser));
    xmlPreview->setName (L"xmlPreview");


    //[UserPreSize]
	xmlPreview->setColour (CodeEditorComponent::backgroundColourId, Colours::white);
	xmlPreview->setColour (CodeEditorComponent::highlightColourId, Colours::lightgrey);
	xmlPreview->setColour(CodeEditorComponent::lineNumberBackgroundId, Colours::lightgrey);

    if (owner.getSelection())
        owner.getSelection()->addChangeListener(this);
    //[/UserPreSize]

    setSize (216, 340);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrPanelUtilities::~CtrlrPanelUtilities()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (xmlPreview);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrPanelUtilities::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrPanelUtilities::resized()
{
    xmlPreview->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CtrlrPanelUtilities::changeListenerCallback (ChangeBroadcaster* source)
{
    if (owner.getSelection() == nullptr || !isVisible())
        return;

	if (owner.getSelection()->getNumSelected() == 0)
		return;

    reloadContent();
}

void CtrlrPanelUtilities::reloadContent()
{
    if ((owner.isVisible() && owner.getSelection()->getNumSelected() == 0) || owner.getSelection()->getNumSelected() > 1)
	{
		ScopedPointer <XmlElement> xml (owner.getOwner().getPanelTree().createXml());
		if (xml)
		{
			codeDocument.replaceAllContent (xml->createDocument(String::empty));
		}
	}
	else if (owner.isVisible() && owner.getSelection()->getNumSelected() == 1)
	{
		CtrlrComponent *c =  owner.getSelection()->getSelectedItem(0);
		if (c)
		{
			ScopedPointer <XmlElement> xml (c->getOwner().getModulatorTree().createXml());
			String doc = xml->createDocument(String::empty);
			if (doc.length() <= 8192)
			{
				codeDocument.replaceAllContent (doc);
			}
		}
	}
}

void CtrlrPanelUtilities::visibilityChanged()
{
    if (isVisible())
    {
        reloadContent();
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrPanelUtilities" componentName=""
                 parentClasses="public Component, public ChangeListener" constructorParams="CtrlrPanelEditor &amp;_owner"
                 variableInitialisers="owner(_owner)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330000013" fixedSize="1" initialWidth="216"
                 initialHeight="340">
  <BACKGROUND backgroundColour="ffffff"/>
  <GENERICCOMPONENT name="xmlPreview" id="5def743fbb85c9be" memberName="xmlPreview"
                    virtualName="" explicitFocusOrder="0" pos="0 0 0M 0M" class="CodeEditorComponent"
                    params="codeDocument, 0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
