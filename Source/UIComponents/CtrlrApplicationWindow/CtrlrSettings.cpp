#include "stdafx.h"
#include "CtrlrSettings.h"

CtrlrSettings::CtrlrSettings (CtrlrManager &_owner) : Component ("Global Properties"), owner(_owner), propertyPanel (0)
{
    addAndMakeVisible (propertyPanel = new PropertyPanel());
    propertyPanel->setName ("propertyPanel");
	Array <PropertyComponent*> globalProperties;
	Array <PropertyComponent*> instanceProperties;
	for (int i=0; i<owner.getManagerTree().getNumProperties(); i++)
	{
		globalProperties.add
		(
			owner.getIDManager().createComponentForProperty (owner.getManagerTree().getPropertyName(i), owner.getManagerTree(), nullptr)
		);
	}
	propertyPanel->addSection ("Ctrlr", globalProperties);
    setSize (700, 600);
}

CtrlrSettings::~CtrlrSettings()
{
    deleteAndZero (propertyPanel);
}

void CtrlrSettings::paint (Graphics& g)
{
}

void CtrlrSettings::resized()
{
    propertyPanel->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
}
