/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "stdafx.h"
#include "CtrlrPanelComponentProperties.h"
#include "CtrlrLog.h"
#include "CtrlrPanel/CtrlrPanelResource.h"
//[/Headers]

#include "CtrlrPanelComponentProperties.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "CtrlrProcessor.h"
//[/MiscUserDefs]

//==============================================================================
CtrlrPanelComponentProperties::CtrlrPanelComponentProperties (CtrlrPanelEditor &_owner)
    : owner(_owner), panelPropertyOpennessState("invalid"), modulatorPropertyOpennessState("invalid")
{
    addAndMakeVisible (propertyPanel = new PropertyPanel());


    //[UserPreSize]
	selectedItems=-1;
	owner.getOwner().getOwner().addListener (this);
	msTree.addListener (this);
	refreshDynamicData();
    if (owner.getSelection())
	{
        owner.getSelection()->addChangeListener (this);
	}
    //[/UserPreSize]

    setSize (216, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CtrlrPanelComponentProperties::~CtrlrPanelComponentProperties()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    if (owner.getSelection())
        owner.getSelection()->removeChangeListener (this);
    //[/Destructor_pre]

    propertyPanel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrPanelComponentProperties::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrPanelComponentProperties::resized()
{
    propertyPanel->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
PropertyComponent *CtrlrPanelComponentProperties::getPropertyEditor (const Value &valueToEdit, const Identifier &valueIdentifier)
{
	return (new TextPropertyComponent (valueToEdit, valueIdentifier.toString(), 1024, false));
}

void CtrlrPanelComponentProperties::setTree (const ValueTree &_treeToEdit, const bool force)
{
	if (_treeToEdit == treeToEdit && force == false)
	{
		return;
	}

	ScopedPointer <XmlElement> xml(propertyPanel->getOpennessState());
	if (treeToEdit.hasType(Ids::panel))
	{
		panelPropertyOpennessState		= *xml;
	}
	else if (treeToEdit.hasType(Ids::modulator))
	{
		modulatorPropertyOpennessState	= *xml;
	}

	treeToEdit = _treeToEdit;

	/** Panel properties **/
	if (treeToEdit.hasType (Ids::panel))
	{
		Array <PropertyComponent*> panelProperties;
		Array <PropertyComponent*> panelEditorProperties;
		Array <PropertyComponent*> panelMidiProperties;

		for (int i=0; i<treeToEdit.getNumProperties(); i++)
		{
			if (treeToEdit.getPropertyName(i) == Ids::uiPanelImageResource)
			{
				panelProperties.add
				(
					owner.getOwner().getOwner().getIDManager().createComponentForProperty
					(	treeToEdit.getPropertyName(i),
						treeToEdit,
						&owner.getOwner(),
						&resourceList,
						&resourceList
					)
				);
			}
			else if (treeToEdit.getPropertyName(i) == Ids::panelMidiInputDevice)
			{
				panelMidiProperties.add
				(
					owner.getOwner().getOwner().getIDManager().createComponentForProperty
					(
						treeToEdit.getPropertyName(i),
						treeToEdit,
						&owner.getOwner(),
						&midiInputDevices,
						&midiInputDevices
					)
				);
			}
			else if (treeToEdit.getPropertyName(i) == Ids::panelMidiOutputDevice)
			{
				panelMidiProperties.add
				(
					owner.getOwner().getOwner().getIDManager().createComponentForProperty
					(
						treeToEdit.getPropertyName(i),
						treeToEdit,
						&owner.getOwner(),
						&midiOutputDevices,
						&midiOutputDevices
					)
				);
			}
			else if (treeToEdit.getPropertyName(i) == Ids::panelMidiControllerDevice)
			{
				panelMidiProperties.add
				(
					owner.getOwner().getOwner().getIDManager().createComponentForProperty
					(
						treeToEdit.getPropertyName(i),
						treeToEdit,
						&owner.getOwner(),
						&midiInputDevices,
						&midiInputDevices
					)
				);
			}
			else if (treeToEdit.getPropertyName(i).toString().startsWith("panelMidi"))
			{
				panelMidiProperties.add
				(
					owner.getOwner().getOwner().getIDManager().createComponentForProperty
					(
						treeToEdit.getPropertyName(i),
						treeToEdit,
						&owner.getOwner()
					)
				);
			}
			else
			{
				panelProperties.add
				(
					owner.getOwner().getOwner().getIDManager().createComponentForProperty
					(
						treeToEdit.getPropertyName(i),
						treeToEdit,
						&owner.getOwner()
					)
				);
			}
		}

		/** Panel editor properties **/
		if (treeToEdit.getChildWithName (Ids::uiPanelEditor).isValid())
		{
			for (int i=0; i<treeToEdit.getChildWithName (Ids::uiPanelEditor).getNumProperties(); i++)
			{
				if (treeToEdit.getChildWithName (Ids::uiPanelEditor).getPropertyName(i) == Ids::uiPanelImageResource)
				{
					panelEditorProperties.add
					(
						owner.getOwner().getOwner().getIDManager().createComponentForProperty
						(
							treeToEdit.getChildWithName (Ids::uiPanelEditor).getPropertyName(i),
							treeToEdit.getChildWithName(Ids::uiPanelEditor),
							&owner.getOwner(),
							&resourceList,
							&resourceList
						)
					);
				}
				else
				{
					panelEditorProperties.add
					(
						owner.getOwner().getOwner().getIDManager().createComponentForProperty
						(
							treeToEdit.getChildWithName (Ids::uiPanelEditor).getPropertyName(i),
							treeToEdit.getChildWithName(Ids::uiPanelEditor),
							&owner.getOwner()
						)
					);
				}
			}
		}

		propertyPanel->clear();

		if (panelProperties.size() != 0)
			propertyPanel->addSection ("Panel", panelProperties);

		if (panelMidiProperties.size() != 0)
			propertyPanel->addSection ("MIDI", panelMidiProperties);

		if (panelMidiProperties.size() != 0)
			propertyPanel->addSection ("Editor", panelEditorProperties);
	}

	/** Modulator properties **/

	if (treeToEdit.hasType (Ids::modulator))
	{
		propertyPanel->clear();

		refreshTargetModulationPropertyList (treeToEdit);

		Array <PropertyComponent*> modulatorProperties;
		Array <PropertyComponent*> componentProperties;
		Array <PropertyComponent*> midiProperties;
		Array <PropertyComponent*> componentUIProperties;

		for (int i=0; i<treeToEdit.getNumProperties(); i++)
		{
			if (treeToEdit.getPropertyName(i) == Ids::modulatorLinkedToModulator)
			{
				modulatorProperties.add
				(
					owner.getOwner().getOwner().getIDManager().createComponentForProperty
					(
						treeToEdit.getPropertyName(i),
						treeToEdit,
						&owner.getOwner(),
						&modulatorList,
						&modulatorList
					)
				);
			}
			else if (treeToEdit.getPropertyName(i) == Ids::modulatorLinkedToModulatorProperty)
			{
				modulatorProperties.add
				(
					owner.getOwner().getOwner().getIDManager().createComponentForProperty
					(
						treeToEdit.getPropertyName(i),
						treeToEdit,
						&owner.getOwner(),
						&modulatorPropertyList,
						&modulatorPropertyList
					)
				);
			}
			else if (treeToEdit.getPropertyName(i) == Ids::modulatorLinkedToPanelProperty)
			{
				modulatorProperties.add
				(
					owner.getOwner().getOwner().getIDManager().createComponentForProperty
					(
						treeToEdit.getPropertyName(i),
						treeToEdit,
						&owner.getOwner(),
						&panelPropertyList,
						&panelPropertyList
					)
				);
			}
			else
			{
				modulatorProperties.add
				(
					owner.getOwner().getOwner().getIDManager().createComponentForProperty
					(
						treeToEdit.getPropertyName(i),
						treeToEdit,
						&owner.getOwner(),
						&emptyValueSet,
						&emptyValueSet
					)
				);
			}
		}

		for (int i=0; i<treeToEdit.getNumChildren(); i++)
		{
			/** MIDI properties **/
			if (treeToEdit.getChild(i).hasType(Ids::midi))
			{
				for (int j=0; j<treeToEdit.getChild(i).getNumProperties(); j++)
				{
					const Identifier n = treeToEdit.getChild(i).getPropertyName(j);

					if (treeToEdit.getChild(i).getPropertyName(j) == Ids::midiMessageType)
					{
						midiProperties.add
						(
							owner.getOwner().getOwner().getIDManager().createComponentForProperty
							(
								treeToEdit.getChild(i).getPropertyName(j),
								treeToEdit.getChild(i),
								&owner.getOwner(),
								&midiTemplateNames,
								&emptyValueSet)
							);
					}
					else
					{
						midiProperties.add
						(
							owner.getOwner().getOwner().getIDManager().createComponentForProperty
							(
								treeToEdit.getChild(i).getPropertyName(j),
								treeToEdit.getChild(i),
								&owner.getOwner()
							)
						);
					}
				}
			}

			/** Component properties **/
			if (treeToEdit.getChild(i).hasType(Ids::component))
			{
				if (treeToEdit.getChild(i).getNumChildren() >= 0)
				{
					for (int j=0; j<treeToEdit.getChild(i).getNumChildren(); j++)
					{
						ValueTree child = treeToEdit.getChild(i).getChild(j);

						for (int k=0; k<child.getNumProperties(); k++)
						{
							if (child.getPropertyName(k) == Ids::uiTabsTabBackgroundImage)
							{
								componentProperties.add
								(
									owner.getOwner().getOwner().getIDManager().createComponentForProperty
									(
										child.getPropertyName(k),
										child,
										&owner.getOwner(),
										&resourceList,
										&resourceList
									)
								);
							}
							else if (child.getPropertyName(k) == Ids::uiEnvelopePointLinkX || child.getPropertyName(k) == Ids::uiEnvelopePointLinkY)
							{
								componentProperties.add
								(
									owner.getOwner().getOwner().getIDManager().createComponentForProperty
									(
										child.getPropertyName(k),
										child,
										&owner.getOwner(),
										&modulatorList,
										&modulatorList
									)
								);
							}
							else
							{
								componentProperties.add
								(
									owner.getOwner().getOwner().getIDManager().createComponentForProperty
									(
										child.getPropertyName(k),
										child,
										&owner.getOwner()
									)
								);
							}
						}
					}
				}

				for (int j=0; j<treeToEdit.getChild(i).getNumProperties(); j++)
				{
					const Identifier n = treeToEdit.getChild(i).getPropertyName(j);

					if (n == Ids::uiImageResource
						|| n == Ids::uiImageSliderResource
						|| n == Ids::uiImageButtonResource
						|| n == Ids::uiGroupBackgroundImage
						|| n == Ids::uiTabsTabBackgroundImage
						|| n == Ids::uiXYSurfaceBgImageResource)
					{
						componentProperties.add
						(
							owner.getOwner().getOwner().getIDManager().createComponentForProperty
							(
								treeToEdit.getChild(i).getPropertyName(j),
								treeToEdit.getChild(i),
								&owner.getOwner(),
								&resourceList,
								&resourceList
							)
						);
					}
					else if (n.toString().startsWith("ui"))
					{
						componentUIProperties.add
						(
							owner.getOwner().getOwner().getIDManager().createComponentForProperty
							(
								treeToEdit.getChild(i).getPropertyName(j),
								treeToEdit.getChild(i),
								&owner.getOwner()
							)
						);
					}
					else
					{
						componentProperties.add
						(
							owner.getOwner().getOwner().getIDManager().createComponentForProperty
							(
								treeToEdit.getChild(i).getPropertyName(j),
								treeToEdit.getChild(i),
								&owner.getOwner()
							)
						);
					}
				}
			}
		}

		if (modulatorProperties.size() != 0)
			propertyPanel->addSection ("Modulator", modulatorProperties);

		if (midiProperties.size() != 0)
			propertyPanel->addSection ("MIDI", midiProperties);

		if (componentProperties.size() != 0)
			propertyPanel->addSection ("Component generic", componentProperties);

		if (componentUIProperties.size() != 0)
			propertyPanel->addSection ("Component", componentUIProperties);
	}
}

void CtrlrPanelComponentProperties::changeListenerCallback (ChangeBroadcaster* source)
{
    if (owner.getSelection() == nullptr)
        return;

	if (selectedItems != owner.getSelection()->getNumSelected() && owner.getSelection()->getNumSelected() > 1)
	{
		selectedItems = owner.getSelection()->getNumSelected();
		msTree = ValueTree(Ids::modulator);
		msTree.removeListener (this);

		for (int i=0; i<owner.getSelection()->getNumSelected(); i++)
		{
			ValueTree modTree = owner.getSelection()->getSelectedItem(i)->getOwner().getModulatorTree();

			copyProperties (modTree, msTree);

			for (int i=0; i<modTree.getNumChildren(); i++)
			{
				if (!msTree.getChildWithName(modTree.getChild(i).getType()).isValid())
					msTree.addChild (modTree.getChild(i).createCopy(), i, 0);
			}
		}

		if (msTree.getChildWithName(Ids::component).isValid())
		{
			msTree.getChildWithName(Ids::component).setProperty (Ids::uiType, "uiMultipleSelection", 0);
		}

		msTree.addListener (this);
		setTree (msTree);
	}

	if (owner.getSelection()->getNumSelected() == 0)
	{
		setTree (owner.getOwner().getPanelTree());
		propertyPanel->restoreOpennessState(panelPropertyOpennessState);
	}

	if (owner.getSelection()->getNumSelected() == 1)
	{
		setTree (owner.getSelection()->getSelectedItem(0)->getOwner().getModulatorTree());
		propertyPanel->restoreOpennessState(modulatorPropertyOpennessState);
	}
}

void CtrlrPanelComponentProperties::refreshDynamicData()
{
	midiOutputDevices.clear();
	midiOutputDevices = owner.getOwner().getCtrlrManager().getCtrlrMidiDeviceManager().getManagedDevices(CtrlrMidiDeviceManager::outputDevice);
	midiOutputDevices.add (COMBO_NONE_ITEM);

	midiInputDevices.clear();
	midiInputDevices = owner.getOwner().getCtrlrManager().getCtrlrMidiDeviceManager().getManagedDevices(CtrlrMidiDeviceManager::inputDevice);
	midiInputDevices.add (COMBO_NONE_ITEM);

	midiTemplateNames = owner.getOwner().getSysExProcessor().templatesPrepare();

	possibleMidiReferences.clear();
	resourceList.clear();

	Array <CtrlrModulator*> ar = owner.getOwner().getModulatorsByMidiType(SysEx);

	possibleMidiReferences.add (COMBO_NONE_ITEM);
	for (int i=0; i<ar.size(); i++)
	{
		possibleMidiReferences.add (ar[i]->getProperty(Ids::name));
	}

	resourceList.add (COMBO_NONE_ITEM);
	for (int i=0; i<owner.getOwner().getResourceManager().getNumResources(); i++)
	{
		resourceList.add (owner.getOwner().getResourceManager().getResource(i)->getName());
	}

	modulatorList.clear();
	modulatorList.add (COMBO_NONE_ITEM);

	for (int i=0; i<owner.getOwner().getModulators().size(); i++)
	{
		modulatorList.add (owner.getOwner().getModulators() [i]->getProperty(Ids::name));
	}

	panelPropertyList.clear();
	panelPropertyList.add (COMBO_NONE_ITEM);
	for (int i=0; i<owner.getOwner().getPanelTree().getNumProperties(); i++)
	{
		panelPropertyList.add (owner.getOwner().getPanelTree().getPropertyName(i).toString());
	}

	Font::findFonts (fonts);

	componentGroupList.clear();
	Array <CtrlrModulator*> groupModulators = owner.getOwner().getModulatorsByUIType(Ids::uiGroup);
	for (int i=0; i<groupModulators.size(); i++)
	{
		componentGroupList.add (groupModulators[i]->getProperty(Ids::uiGroupText));
	}

	luaMethodList.clear();
}

void CtrlrPanelComponentProperties::refreshAll()
{
	refreshDynamicData();
	propertyPanel->refreshAll();
	setTree(treeToEdit, true);
}

void CtrlrPanelComponentProperties::copyProperties(ValueTree &sourceTree, ValueTree &destinationTree)
{
	for (int i=0; i<sourceTree.getNumProperties(); i++)
	{
		if (!destinationTree.hasProperty (sourceTree.getPropertyName(i)))
		{
			if (sourceTree.getPropertyName(i) != Ids::vstIndex)
				destinationTree.setProperty (sourceTree.getPropertyName(i), sourceTree.getPropertyAsValue(sourceTree.getPropertyName(i), 0), 0);
		}
	}
}

void CtrlrPanelComponentProperties::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
    if (owner.getSelection() == nullptr)
        return;

	for (int i=0; i<owner.getSelection()->getNumSelected(); i++)
	{
		if (treeWhosePropertyHasChanged.hasType (Ids::modulator))
		{
			owner.getSelection()->getSelectedItem(i)->getOwner().setProperty (property, treeWhosePropertyHasChanged.getPropertyAsValue(property, 0));
		}
		if (treeWhosePropertyHasChanged.hasType (Ids::component))
		{
			owner.getSelection()->getSelectedItem(i)->setProperty (property, treeWhosePropertyHasChanged.getPropertyAsValue(property, 0));
		}
		if (treeWhosePropertyHasChanged.hasType (Ids::midi))
		{
			if (owner.getSelection()->getSelectedItem(i)->getOwner().getMidiMessagePtr())
			{
				owner.getSelection()->getSelectedItem(i)->getOwner().getMidiMessage().setProperty (property, treeWhosePropertyHasChanged.getPropertyAsValue(property, 0));
			}
		}
	}
}

void CtrlrPanelComponentProperties::managerStateChanged (const CtrlrManager::CtrlrManagerState newState)
{
	if (newState == CtrlrManager::PanelsLoaded)
	{
		refreshAll();
	}
}

void CtrlrPanelComponentProperties::refreshTargetModulationPropertyList (const ValueTree &sourceModulationTree)
{
	CtrlrModulator *target = owner.getOwner().getModulator (sourceModulationTree.getProperty (Ids::modulatorLinkedToModulator));

	if (target)
	{
		modulatorPropertyList.clear();
		modulatorPropertyList.add (COMBO_NONE_ITEM);

		if ((bool)sourceModulationTree.getProperty (Ids::modulatorLinkedToComponent) == true)
		{
			CtrlrComponent *c = target->getComponent();
			if (c)
			{
				for (int i=0; i<c->getComponentTree().getNumProperties(); i++)
				{
					modulatorPropertyList.add (c->getComponentTree().getPropertyName(i).toString());
				}
			}
		}
		else
		{
			for (int i=0; i<target->getModulatorTree().getNumProperties(); i++)
			{
				modulatorPropertyList.add (target->getModulatorTree().getPropertyName(i).toString());
			}
		}
	}
}

void CtrlrPanelComponentProperties::visibilityChanged()
{
	propertyPanel->clear();
	refreshAll();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrPanelComponentProperties"
                 componentName="" parentClasses="public Component, public ChangeListener, public ValueTree::Listener, public CtrlrManager::Listener, public LookAndFeel"
                 constructorParams="CtrlrPanelEditor &amp;_owner" variableInitialisers="owner(_owner), panelPropertyOpennessState(&quot;invalid&quot;), modulatorPropertyOpennessState(&quot;invalid&quot;)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="216" initialHeight="400">
  <BACKGROUND backgroundColour="ffffff"/>
  <GENERICCOMPONENT name="" id="5bd21e18c5d102" memberName="propertyPanel" virtualName=""
                    explicitFocusOrder="0" pos="0 0 0M 0M" class="PropertyPanel"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
