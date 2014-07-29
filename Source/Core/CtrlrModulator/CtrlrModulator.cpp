#include "stdafx.h"
#include "CtrlrLuaManager.h"
#include "CtrlrModulator.h"
#include "CtrlrProcessor.h"
#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrUtilities.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrComponents/CtrlrComponentTypeManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrLog.h"

CtrlrModulator::CtrlrModulator(CtrlrPanel &_owner)
	:	ctrlrComponent(0),
		owner(_owner),
		ctrlrModulatorReference(0),
		modulatorTree(Ids::modulator),
		restoreStateStatus(false),
		delayedProperties(Ids::modulator),
		processor(*this),
		vstExported(false)
{
    modulatorTree.addListener (this);
	setProperty (Ids::modulatorCustomIndex, 0);
	setProperty (Ids::modulatorCustomIndexGroup, 0);
	setProperty(Ids::modulatorIsStatic, true);
}

CtrlrModulator::CtrlrModulator(CtrlrPanel &_owner, const int suggestedVstIndex)
	:	ctrlrComponent(0),
		owner(_owner),
		ctrlrModulatorReference(0),
		modulatorTree(Ids::modulator),
		restoreStateStatus(false),
		delayedProperties(Ids::modulator),
		processor(*this),
		vstExported(true)
{
	modulatorTree.addChild (processor.getMidiMessage().getMidiTree(), -1, 0);
	modulatorTree.addListener (this);
	setProperty (Ids::modulatorVstExported, true, false);
	setProperty (Ids::modulatorMax, MAX_CONTROLLER_VALUE);
	setProperty (Ids::vstIndex, suggestedVstIndex);
	setProperty (Ids::modulatorIsStatic, false);
	setProperty (Ids::modulatorGlobalVariable, -1);
	setProperty (Ids::modulatorMuteOnStart, false);
	setProperty (Ids::modulatorExcludeFromSnapshot, false);
	setProperty (Ids::modulatorValueExpression, EXP_MODULATOR_FORWARD);
	setProperty (Ids::modulatorValueExpressionReverse, EXP_MODULATOR_REVERSE);
	setProperty (Ids::luaModulatorGetValueForMIDI, COMBO_NONE_ITEM);
	setProperty (Ids::luaModulatorGetValueFromMIDI, COMBO_NONE_ITEM);
	setProperty (Ids::modulatorLinkedToPanelProperty, COMBO_NONE_ITEM);
	setProperty (Ids::modulatorLinkedToModulatorProperty, COMBO_NONE_ITEM);
	setProperty (Ids::modulatorLinkedToModulator, COMBO_NONE_ITEM);
	setProperty (Ids::modulatorLinkedToModulatorSource, true);
	setProperty (Ids::modulatorLinkedToComponent, false);
	setProperty (Ids::modulatorBaseValue, 0);

	setProperty (Ids::modulatorCustomIndex, 0);
	setProperty (Ids::modulatorCustomName, String::empty);
	setProperty (Ids::modulatorCustomIndexGroup, 0);
	setProperty (Ids::modulatorCustomNameGroup, String::empty);

	setProperty (Ids::modulatorVstNameFormat, "%n");
	setProperty (Ids::luaModulatorValueChange, COMBO_NONE_ITEM);
}

CtrlrModulator::~CtrlrModulator()
{
	modulatorTree.removeListener (this);
	owner.getPanelTree().removeChild (modulatorTree,0);
	masterReference.clear();

	if (ctrlrComponent)
		deleteAndZero (ctrlrComponent);
}

void CtrlrModulator::restoreState (const ValueTree &savedState)
{
	setRestoreState (true);
	modulatorTree.removeAllChildren (0);

	for (int i=0; i<savedState.getNumChildren(); i++)
	{
		if (savedState.getChild(i).hasType(Ids::component))
		{
			setComponentType (savedState.getChild(i));
		}

		if (savedState.getChild(i).hasType(Ids::midi))
		{
			if (getMidiMessagePtr())
			{
				setMidiType (savedState.getChild(i));
				modulatorTree.addChild (processor.getMidiMessage().getMidiTree(), -1, 0);
			}
		}
	}

	for (int i=0; i<savedState.getNumProperties(); i++)
	{
		if (savedState.getPropertyName(i) == Ids::name)
		{
			modulatorTree.setProperty (Ids::name, owner.getUniqueModulatorName(savedState.getProperty(Ids::name)), 0);
		}
		else if (isDelayedProperty(savedState.getPropertyName(i)))
		{
			setDelayedProperty(savedState.getPropertyName(i), savedState.getProperty(savedState.getPropertyName(i)));
			continue;
		}
		else if (savedState.getPropertyName(i) == Ids::modulatorValue
				&& owner.getOwner().getInstanceMode() == InstanceMulti)
		{
			/*
			 set the modulator value
			 First see if it has a component attached to check out radio groups
			if (savedState.getChildWithName(Ids::component).isValid())
			{
				ValueTree c = savedState.getChildWithName(Ids::component);

				 If the component belongs to a radio group, only set the value
					to the group member that has the TRUE value all others will be FALSE
				if (((int)c.getProperty(Ids::componentRadioGroupId) > 0))
				{
					if ((int)savedState.getProperty(Ids::modulatorValue) == 1)
					{
						processor.setValueFromGUI (savedState.getProperty(Ids::modulatorValue), true);

						 This is something that should not be here, this should be called from the HOST
							as setParameter() call but it doesn't get called with the value set to 1.

							Fuck if I know why, for now it stays here, i don't know if it's a good idea
							i don't even know if it's an OK idea. But it seems to do the trick


						processor.triggerAsyncUpdate();
					}
				}
				else
				{
					No radio group just set the value
					processor.setValueFromGUI (savedState.getProperty(Ids::modulatorValue), true);
				}

				setProperty (Ids::modulatorValue, savedState.getProperty(Ids::modulatorValue));
				continue;
			}
			*/
			continue;
		}
		else if (savedState.getPropertyName(i) == Ids::modulatorMax || savedState.getPropertyName(i) == Ids::modulatorMin)
		{
			continue;
		}
		else
		{
			modulatorTree.setProperty (savedState.getPropertyName(i), savedState.getProperty(savedState.getPropertyName(i),0), 0);
		}
	}

	owner.setInitialProgramValue(getName(), savedState.getProperty(Ids::modulatorValue, (double)0));

	setRestoreState(false);

	processor.handleUpdateNowIfNeeded(); // TK: synchronous update requrired
}

void CtrlrModulator::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	if (property == Ids::name)
	{
		if (getComponent())
		{
			getComponent()->modulatorNameChanged(getProperty(property));
		}

		owner.modulatorNameChanged (this, getProperty(property));
	}
	else if (property == Ids::modulatorGlobalVariable)
	{
		if ((int)getProperty(property) >= 0)
		{
			processor.setLinkedToGlobal (true, getProperty(property));
		}
		else
		{
			processor.setLinkedToGlobal (false);
		}
	}
	else if (property == Ids::modulatorMax)
	{
		processor.setModulatorMaxValue (getProperty(property));
	}
	else if (property == Ids::modulatorMin)
	{
		processor.setModulatorMinValue (getProperty(property));
	}
	else if (property == Ids::modulatorValueExpression)
	{
		processor.setForwardExpression (getProperty(property));
	}
	else if (property == Ids::modulatorValueExpressionReverse)
	{
		processor.setReverseExpression (getProperty(property));
	}
	else if (property == Ids::modulatorLinkedToModulator)
	{
		setReference (getProperty(property));
	}
	else if (property == Ids::modulatorLinkedToPanelProperty)
	{
		if (getProperty(property).toString() != COMBO_NONE_ITEM)
		{
			setPanelReference (&owner);
		}
	}
	else if (property == Ids::modulatorValue)
	{
		if (!modulatorTree.hasProperty(property))
			return;

		modifyReference(getProperty(property));

		if (getRestoreState())
			return;

		owner.modulatorValueChanged(this);

		modulatorListeners.call (&ModulatorListener::modulatorChanged, this, getProperty(property));
	}
	else if (property == Ids::luaModulatorValueChange)
	{
		processor.setValueChangedCallback (getProperty(property));
	}
	else if (property == Ids::luaModulatorGetValueForMIDI)
	{
		processor.setGetValueForMidiCallback (getProperty(property));
	}
	else if (property == Ids::luaModulatorGetValueFromMIDI)
	{
		processor.setGetValueFromMidiCallback (getProperty(property));
	}
	else if (property == Ids::modulatorVstExported)
	{
		if ((bool)getProperty (property) == false && !getRestoreState())
		{
			owner.getOwner().getVstManager().remove (this);
		}

		vstExported = (bool)getProperty(property);
	}
	else if (property == Ids::vstIndex)
	{
		owner.getOwner().getVstManager().set (this, getProperty(property));
	}
}

const String CtrlrModulator::getName()
{
	return (hasProperty(Ids::name) ? getProperty(Ids::name) : "<unnamed>");
}

const bool CtrlrModulator::hasName()
{
	return (hasProperty(Ids::name));
}

const int CtrlrModulator::getVstIndex() const
{
	return ((int)getProperty(Ids::vstIndex));
}

const float CtrlrModulator::getVstValue(const int intValueToUse) const
{
	if (intValueToUse >= 0)
	{
		return ((float)intValueToUse/(float)getMaxModulatorValue());
	}
	else
	{
		return ((float)getModulatorValue()/(float)getMaxModulatorValue());
	}
}

const int CtrlrModulator::getMaxModulatorValue() const
{
	return (processor.getMax());
}

const int CtrlrModulator::getMinModulatorValue() const
{
	return (processor.getMin());
}

const int CtrlrModulator::getModulatorValue() const
{
	return (processor.getValue());
}

const bool CtrlrModulator::removeComponent()
{
	if (ctrlrComponent)
	{
		modulatorTree.removeChild (ctrlrComponent->getComponentTree(), 0);
		deleteAndZero (ctrlrComponent);

		return (true);
	}

	return (false);
}

void CtrlrModulator::setComponentType (const ValueTree &savedState)
{
	Rectangle<int> oldBounds;
	bool componentWasDeleted = false;

	if (ctrlrComponent)
	{
		oldBounds			= ctrlrComponent->getBounds();
		componentWasDeleted = removeComponent();
	}

	ctrlrComponent		= CtrlrComponentTypeManager::createComponent (savedState, *this);

	if (!oldBounds.isEmpty())
	{
		ctrlrComponent->setTopLeftPosition (oldBounds.getX(), oldBounds.getY());
	}
}

void CtrlrModulator::setComponentType (const Identifier &componentType, const bool forceIfAlreadyThisType)
{
	if (componentType == getComponentType() && !forceIfAlreadyThisType)
		return;

	ValueTree temp(Ids::component);
	temp.setProperty (Ids::uiType, componentType.toString(),0);
	setComponentType (temp);
}

const Identifier CtrlrModulator::getComponentType()
{
	if (modulatorTree.getChildWithName(Ids::component).isValid())
	{
		if (modulatorTree.getChildWithName(Ids::component).getProperty(Ids::uiType) == String::empty)
		{
			jassertfalse; // an empty type for a component, that can't happen
			return (Ids::uiNone);
		}
		else
		{
			return (modulatorTree.getChildWithName(Ids::component).getProperty(Ids::uiType).toString());
		}
	}
	else
	{
		return (Ids::uiNone);
	}
}

CtrlrComponent *CtrlrModulator::getComponent()
{
	return (ctrlrComponent);
}

CtrlrManager &CtrlrModulator::getCtrlrManager()
{
	return (owner.getCtrlrManager());
}

void CtrlrModulator::setMidiType (const ValueTree &savedState)
{
	if (getMidiMessagePtr())
	{
		getMidiMessage().restoreState (savedState);
	}
}

void CtrlrModulator::setProperty (const Identifier& name, const var &newValue, const bool isUndoable)
{
	if (isUndoable)
	{
		modulatorTree.setProperty (name, newValue, owner.getUndoManager());
	}
	else
	{
		modulatorTree.setProperty (name, newValue, 0);
	}
}

void CtrlrModulator::allModulatorsInitialized()
{
	for (int i=0; i<delayedProperties.getNumProperties(); i++)
	{
		setProperty (delayedProperties.getPropertyName(i), delayedProperties.getProperty(delayedProperties.getPropertyName(i)));
	}

	if (getComponent())
	{
		getComponent()->allModulatorsInitialized();
	}

	if (owner.getOwner().getInstanceMode() == InstanceSingle || owner.getOwner().getInstanceMode() == InstanceSingleRestriced)
	{
		processor.setValueFromGUI (getProperty(Ids::modulatorValue),true);
	}
}

CtrlrModulator *CtrlrModulator::getReference()
{
	return (ctrlrModulatorReference);
}

void CtrlrModulator::setPanelReference(CtrlrPanel *referencedPanel)
{
	ctrlrPanelReference = referencedPanel;
}

void CtrlrModulator::setReference (const String &modulatorToReference)
{
	if (modulatorToReference == COMBO_NONE_ITEM)
	{
		ctrlrModulatorReference = 0;
	}
	else if (modulatorToReference != getName())
	{
		CtrlrModulator *m = owner.getModulator (modulatorToReference);
		if (m == nullptr)
		{
			_WRN("CtrlrModulator::setReference ["+getName()+"] can't find modulator with name \""+modulatorToReference+"\" link won't work");
		}
		ctrlrModulatorReference = m;
	}
	else
	{
		AlertWindow::showMessageBox (AlertWindow::WarningIcon, "Modulator link", "Can't link to myself");
		setProperty (Ids::modulatorLinkedToModulator, COMBO_NONE_ITEM);
	}
}

void CtrlrModulator::modifyReference(const int newValue)
{
	if (ctrlrModulatorReference)
	{
		if (getProperty(Ids::modulatorLinkedToModulatorProperty).toString() == COMBO_ITEM_NONE)
		{
			return;
		}
		else if (!Identifier::isValidIdentifier(getProperty(Ids::modulatorLinkedToModulatorProperty)))
		{
			_WRN("Modulator link is invalid, the referenced property \""+getProperty(Ids::modulatorLinkedToModulatorProperty).toString()+"\" is invalid");
			return;
		}

		const String targetProperty = getProperty(Ids::modulatorLinkedToModulatorProperty);

		if (targetProperty == Ids::modulatorValue.toString()) /* if the target property is the value */
		{
			if ((bool)getProperty(Ids::modulatorLinkedToModulatorSource) == true) /* true means we are using Numeric values */
			{
				ctrlrModulatorReference->getProcessor().setValueFromGUI (processor.getValueForMidiMessage(newValue));
			}
		}
		else /* the target property is not the value, treat it as string */
		{
			if ((bool)getProperty (Ids::modulatorLinkedToComponent)) /* modify the component not the modulator */
			{
				if (ctrlrModulatorReference->getComponent()) /* make sure the target modulator has a component */
				{
					if ((bool)getProperty(Ids::modulatorLinkedToModulatorSource) == true) /* true means we are using Numeric values */
					{
						ctrlrModulatorReference->getComponent()->setProperty (targetProperty, processor.getValueForMidiMessage(newValue));
					}
					else if (getComponent())/* otherwise fetch our components text and set it as the value of the target property */
					{
						ctrlrModulatorReference->getComponent()->setProperty (targetProperty, getComponent()->getComponentText());
					}
				}
			}
			else /* modify the target modulator */
			{
				if ((bool)getProperty(Ids::modulatorLinkedToModulatorSource) == true) /* true means we are using Numeric values */
				{
					ctrlrModulatorReference->setProperty (targetProperty, newValue);
				}
				else if (getComponent())/* otherwise fetch our components text and set it as the value of the target property */
				{
					ctrlrModulatorReference->setProperty (targetProperty, getComponent()->getComponentText());
				}
			}
		}
	}

	if (ctrlrPanelReference)
	{
		if (ctrlrPanelReference == &owner)
		{
			const String targetProperty = getProperty(Ids::modulatorLinkedToPanelProperty).toString();
			if (!Identifier::isValidIdentifier(targetProperty))
			{
				_WRN("Modulator link (to panel) is invalid, the referenced property \""+targetProperty+"\" is invalid");
				return;

			}
			else
			{
				owner.setProperty (targetProperty, newValue);
			}
		}
	}
}

const bool CtrlrModulator::isDelayedProperty(const Identifier &name)
{
	if (name == Ids::modulatorLinkedToModulator)
		return (true);

	if (name == Ids::modulatorLinkedToModulatorProperty)
		return (true);

	if (name == Ids::modulatorLinkedToPanelProperty)
		return (true);

	if (name == Ids::modulatorVstExported)
		return (true);

	if (name == Ids::modulatorValue && (owner.getOwner().getInstanceMode() == InstanceSingle || owner.getOwner().getInstanceMode() == InstanceSingleRestriced))
		return (true);

	return (false);
}

void CtrlrModulator::setDelayedProperty(const Identifier &name, const var value)
{
	delayedProperties.setProperty (name, value, 0);
}

const String CtrlrModulator::getModulatorText()
{
	if (ctrlrComponent)
	{
		return (ctrlrComponent->getComponentText());
	}
	else
	{
		return (getProperty(Ids::modulatorValue));
	}
}

CtrlrMidiMessage &CtrlrModulator::getMidiMessage()
{
	return (processor.getMidiMessage());
}

CtrlrOwnedMidiMessage &CtrlrModulator::getOwnedMidiMessage()
{
	return (processor.getOwnedMidiMessage());
}

CtrlrMidiMessage *CtrlrModulator::getMidiMessagePtr()
{
	if ((bool)getProperty(Ids::modulatorIsStatic))
	{
		return (nullptr);
	}
	else
	{
		return (processor.getMidiMessagePtr());
	}
}

void CtrlrModulator::setRestoreState(const bool _restoreStateStatus)
{
	const ScopedWriteLock lock (modulatorLock);
	restoreStateStatus = _restoreStateStatus;
}

const bool CtrlrModulator::getRestoreState()
{
	const ScopedReadLock lock (modulatorLock);
	return (restoreStateStatus);
}

const bool CtrlrModulator::isStatic()
{
	return (getProperty(Ids::modulatorIsStatic));
}

const String CtrlrModulator::getNameForHost()
{
	return (labelFromProperty (this, getProperty(Ids::modulatorVstNameFormat)));
}

const String CtrlrModulator::getTextForHost()
{
	return (STR(getModulatorValue()));
}

const String CtrlrModulator::getGroupName()
{
	return (getProperty(Ids::modulatorCustomNameGroup));
}
