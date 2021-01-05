#include "stdafx.h"
#include "CtrlrPanelComponentProperties.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrPanel/CtrlrPanelResource.h"
#include "CtrlrPropertyEditors/CtrlrPropertyComponent.h"

CtrlrPanelComponentProperties::CtrlrPanelComponentProperties (CtrlrPanelEditor &_owner)
    : owner(_owner), panelPropertyOpennessState("invalid"), modulatorPropertyOpennessState("invalid")
{
    addAndMakeVisible (propertyPanel = new PropertyPanel());
    propertyPanel->getViewport().setScrollBarThickness(owner.getOwner().getOwner().getProperty(Ids::ctrlrScrollbarThickness));

    //[UserPreSize]
	selectedItems=-1;
	owner.getOwner().getCtrlrManagerOwner().addListener (this);
	selectionTree.addListener (this);
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

CtrlrIDManager &CtrlrPanelComponentProperties::getIDManager()
{
	return owner.getOwner().getCtrlrManagerOwner().getIDManager();
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
		Array <PropertyComponent*> panelOSCProperties;

		for (int i=0; i<treeToEdit.getNumProperties(); i++)
		{
			if (treeToEdit.getPropertyName(i) == Ids::uiPanelImageResource)
			{
				panelProperties.add
				(
						getIDManager().createComponentForProperty
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
						getIDManager().createComponentForProperty
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
						getIDManager().createComponentForProperty
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
						getIDManager().createComponentForProperty
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
						getIDManager().createComponentForProperty
					(
						treeToEdit.getPropertyName(i),
						treeToEdit,
						&owner.getOwner()
					)
				);
			}
			else if (treeToEdit.getPropertyName(i).toString().startsWith("panelOSC"))
			{
				panelOSCProperties.add
				(
						getIDManager().createComponentForProperty
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
						getIDManager().createComponentForProperty
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
							getIDManager().createComponentForProperty
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
							getIDManager().createComponentForProperty
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
			propertyPanel->addSection ("Panel", filterProperties(panelProperties));

		if (panelMidiProperties.size() != 0)
			propertyPanel->addSection ("MIDI", filterProperties(panelMidiProperties));

		if (panelOSCProperties.size() != 0)
			propertyPanel->addSection ("OSC", filterProperties(panelOSCProperties));

		if (panelMidiProperties.size() != 0)
			propertyPanel->addSection ("Editor", filterProperties(panelEditorProperties));

		(propertyPanel);
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
						getIDManager().createComponentForProperty
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
						getIDManager().createComponentForProperty
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
						getIDManager().createComponentForProperty
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
						getIDManager().createComponentForProperty
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
								getIDManager().createComponentForProperty
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
								getIDManager().createComponentForProperty
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
										getIDManager().createComponentForProperty
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
										getIDManager().createComponentForProperty
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
										getIDManager().createComponentForProperty
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
								getIDManager().createComponentForProperty
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
								getIDManager().createComponentForProperty
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
								getIDManager().createComponentForProperty
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
			propertyPanel->addSection ("Modulator", filterProperties(modulatorProperties));

		if (midiProperties.size() != 0)
			propertyPanel->addSection ("MIDI", filterProperties(midiProperties));

		if (componentProperties.size() != 0)
			propertyPanel->addSection ("Component generic", filterProperties(componentProperties));

		if (componentUIProperties.size() != 0)
			propertyPanel->addSection ("Component", filterProperties(componentUIProperties));
	}
}

void CtrlrPanelComponentProperties::changeListenerCallback (ChangeBroadcaster* source)
{
    if (owner.getSelection() == nullptr)
        return;

	if (selectedItems != owner.getSelection()->getNumSelected() && owner.getSelection()->getNumSelected() > 1)
	{
		selectedItems = owner.getSelection()->getNumSelected();
		selectionTree = ValueTree(Ids::modulator);
		selectionTree.removeListener (this);

		for (int i=0; i<owner.getSelection()->getNumSelected(); i++)
		{
			ValueTree modTree = owner.getSelection()->getSelectedItem(i)->getOwner().getModulatorTree();

			copyProperties (modTree, selectionTree);

			for (int j=0; j<modTree.getNumChildren(); j++)
			{
				if (!selectionTree.getChildWithName(modTree.getChild(j).getType()).isValid())
					selectionTree.addChild (modTree.getChild(i).createCopy(), j, 0);
			}
		}

		if (selectionTree.getChildWithName(Ids::component).isValid())
		{
			selectionTree.getChildWithName(Ids::component).setProperty (Ids::uiType, "uiMultipleSelection", 0);
		}

		selectionTree.addListener (this);
		setTree (selectionTree);
	}

	if (owner.getSelection()->getNumSelected() == 0)
	{
		setTree (owner.getOwner().getPanelTree());
		propertyPanel->restoreOpennessState(panelPropertyOpennessState);
	}

	if (owner.getSelection()->getNumSelected() == 1)
	{
	    refreshTargetModulationPropertyList(owner.getSelection()->getSelectedItem(0)->getOwner().getModulatorTree());
		refreshDynamicData();
		setTree (owner.getSelection()->getSelectedItem(0)->getOwner().getModulatorTree());
		propertyPanel->restoreOpennessState(modulatorPropertyOpennessState);
	}
}

void CtrlrPanelComponentProperties::refreshDynamicData()
{
	midiOutputDevices.clear();
	midiOutputDevices = owner.getOwner().getCtrlrManagerOwner().getCtrlrMidiDeviceManager().getManagedDevices(outputDevice);
	midiOutputDevices.add (COMBO_NONE_ITEM);

	midiInputDevices.clear();
	midiInputDevices = owner.getOwner().getCtrlrManagerOwner().getCtrlrMidiDeviceManager().getManagedDevices(inputDevice);
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

    // This can't be done everytime, once is enough
    // we should use the FontManager to provide this
    // and update when needed

	//Font::findFonts (fonts);

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

		if ((int)sourceModulationTree.getProperty (Ids::modulatorLinkedToComponent) == 1)
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
		if ((int)sourceModulationTree.getProperty (Ids::modulatorLinkedToComponent) == 0)
		{
			for (int i=0; i<target->getModulatorTree().getNumProperties(); i++)
			{
				modulatorPropertyList.add (target->getModulatorTree().getPropertyName(i).toString());
			}
		}
		if ((int)sourceModulationTree.getProperty (Ids::modulatorLinkedToComponent) == 2)
        {
            if (target->getMidiMessagePtr())
            {
                for (int i=0; i<target->getMidiMessage().getMidiTree().getNumProperties(); i++)
                {
                    modulatorPropertyList.add (target->getMidiMessage().getMidiTree().getPropertyName(i).toString());
                }
            }
        }
	}
}

void CtrlrPanelComponentProperties::visibilityChanged()
{
	propertyPanel->clear();
	refreshAll();
}

const String CtrlrPanelComponentProperties::setFilter(const String &filter)
{
	if (filter == "" )
	{
		currentFilter = filter;
		visibilityChanged();
		return "";
	}

	String tempFilter;

	if (!filter.startsWith("*"))
		tempFilter = _STR("*") + filter;

	if (!filter.endsWith("*"))
		tempFilter << "*";

	currentFilter = tempFilter;

	visibilityChanged();

	return currentFilter;
}

Array<PropertyComponent*> CtrlrPanelComponentProperties::filterProperties(Array<PropertyComponent*> &propsToFilter)
{
	if (currentFilter == "")
	{
		return propsToFilter;
	}

	Array<PropertyComponent *> leftovers;
	for (auto v : propsToFilter)
	{
		CtrlrPropertyComponent *p = dynamic_cast<CtrlrPropertyComponent *> (v);
		if (p != nullptr)
		{
			// _TXT("%s || %s match filter %s", p->getPropertyName().toRawUTF8(), p->getVisibleText().toRawUTF8(), currentFilter.toRawUTF8());

			if (p->getPropertyName().matchesWildcard(currentFilter, true) ||
				p->getVisibleText().matchesWildcard(currentFilter, true))
			{
				leftovers.add(v);
			}
			else
			{
				delete v;
			}
		}
	}

	return leftovers;
}
