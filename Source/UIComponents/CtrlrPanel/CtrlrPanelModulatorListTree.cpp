#include "stdafx.h"
#include "CtrlrPanelModulatorListTree.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"
#include "CtrlrPanel/CtrlrPanelCanvas.h"



/* ********************************************************************************** */
CtrlrModulatorTreeLabel::CtrlrModulatorTreeLabel(CtrlrModulatorTreeViewItem &_owner, const ValueTree &_itemToAttach)
	:	owner(_owner),
		itemToAttach(_itemToAttach)
{
	icon				= getIconForOurType();
	label.setText (owner.getUniqueName(),dontSendNotification);
	label.addMouseListener (this, false);
	addAndMakeVisible (&label);
	addKeyListener (this);
	setWantsKeyboardFocus (true);
}

void CtrlrModulatorTreeLabel::addLabelListener (Label::Listener *listenerToAdd)
{
	label.addListener (listenerToAdd);
}

void CtrlrModulatorTreeLabel::removeLabelListener (Label::Listener *listenerToRemove)
{
	label.removeListener (listenerToRemove);
}

void CtrlrModulatorTreeLabel::resized()
{
	label.setBounds (24, 0, getWidth()-24, 24);
}

void CtrlrModulatorTreeLabel::paint(Graphics &g)
{
	g.drawImageWithin (icon, 2, 2, 20, 20, RectanglePlacement::centred);
}

void CtrlrModulatorTreeLabel::setSelected (const bool isSelected)
{
	if (isSelected)
	{
		label.setColour (Label::backgroundColourId, Colour(0xff048cf5));
	}
	else
	{
		label.setColour (Label::backgroundColourId, Colours::transparentBlack);
	}
}

Image CtrlrModulatorTreeLabel::getIconForOurType()
{
	return (owner.getIconForType(itemToAttach));
}

void CtrlrModulatorTreeLabel::mouseEnter (const MouseEvent &e)
{
	if (e.eventComponent == &label)
	{
		label.setMouseCursor (MouseCursor::PointingHandCursor);
	}
}

void CtrlrModulatorTreeLabel::mouseExit (const MouseEvent &e)
{
	if (e.eventComponent == &label)
	{
		label.setMouseCursor (MouseCursor::NormalCursor);
	}
}

bool CtrlrModulatorTreeLabel::keyPressed (const KeyPress &key, Component *originatingComponent)
{
	if (owner.isSelected() && key.getKeyCode() == KeyPress::F2Key)
	{
		label.setColour (Label::backgroundColourId, Colours::transparentBlack);
		label.showEditor();
	}
	return (false);
}

/* ********************************************************************************** */
CtrlrModulatorTreeViewItem::CtrlrModulatorTreeViewItem(CtrlrTreeViewItemListener *_defaultListener, const ValueTree &_itemToAttach)
	: itemToAttach(_itemToAttach), itemLabel(nullptr), defaultListener(_defaultListener)
{
	addListener (defaultListener);
	itemToAttach.addListener (this);
}

CtrlrModulatorTreeViewItem::~CtrlrModulatorTreeViewItem()
{
	itemToAttach.removeListener (this);
}

void CtrlrModulatorTreeViewItem::itemClicked (const MouseEvent &e)
{
}

String CtrlrModulatorTreeViewItem::getUniqueName () const
{
	if (defaultListener)
	{
		if (defaultListener->getDisplayTextForItem (itemToAttach) != String::empty)
		{
			return (defaultListener->getDisplayTextForItem(itemToAttach));
		}
	}
	if (itemToAttach.hasProperty(Ids::name))
	{
		return (itemToAttach.getType().toString() + "/"+ itemToAttach.getProperty(Ids::name).toString());
	}
	else
	{
		return (itemToAttach.getType().toString());
	}
}

void CtrlrModulatorTreeViewItem::itemSelectionChanged (bool isNowSelected)
{
	itemLabel->setSelected (isNowSelected);
}

bool CtrlrModulatorTreeViewItem::mightContainSubItems ()
{
	return (itemToAttach.getNumChildren() ? true : false);
}

int	CtrlrModulatorTreeViewItem::getItemWidth () const
{
	return (labelFont.getStringWidth (getUniqueName()) + 48);
}

int	CtrlrModulatorTreeViewItem::getItemHeight () const
{
	return (24);
}

bool CtrlrModulatorTreeViewItem::canBeSelected () const
{
	return (true);
}

Component *CtrlrModulatorTreeViewItem::createItemComponent ()
{
	CtrlrModulatorTreeLabel *l = new CtrlrModulatorTreeLabel(*this, itemToAttach);
	l->addMouseListener (this, true);
	l->addLabelListener (this);

	itemLabel = l;

	return (l);
}

void CtrlrModulatorTreeViewItem::itemOpennessChanged (bool isNowOpen)
{
	if (isNowOpen)
	{
		if (getNumSubItems() == 0)
		{
			for (int i=0; i<itemToAttach.getNumChildren(); i++)
			{
				addSubItem (new CtrlrModulatorTreeViewItem (defaultListener, itemToAttach.getChild(i)));
			}
		}
	}
	else
	{
		clearSubItems();
	}
}

void CtrlrModulatorTreeViewItem::mouseDown (const MouseEvent &e)
{
	if (!e.mods.isPopupMenu())
	{
		setSelected (!isSelected(), true);
		listeners.call (&CtrlrTreeViewItemListener::itemChanged, itemToAttach);
	}
	else
	{
		setSelected (true, true);
	}

	listeners.call (&CtrlrTreeViewItemListener::itemClicked, e, itemToAttach);
}

void CtrlrModulatorTreeViewItem::mouseDoubleClick (const MouseEvent &e)
{
	if (e.mods.isPopupMenu())
		return;

	setSelected (true, true);
	listeners.call (&CtrlrTreeViewItemListener::itemDoubleClicked, e, itemToAttach);
}

CtrlrModulatorTreeLabel *CtrlrModulatorTreeViewItem::createItemLabel(const ValueTree &itemToAttach)
{
	return (itemLabel);
}

Image CtrlrModulatorTreeViewItem::getIconForType(const ValueTree &item)
{
	if (defaultListener)
	{
		return (defaultListener->getIconForType(item));
	}

	return (Image::null);
}

void CtrlrModulatorTreeViewItem::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	treeHasChanged();
}

void CtrlrModulatorTreeViewItem::valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged)
{
	itemChanged();
}

void CtrlrModulatorTreeViewItem::valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged)
{
	itemChanged();
}

void CtrlrModulatorTreeViewItem::valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded)
{
	itemChanged();
}

void CtrlrModulatorTreeViewItem::valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved)
{
	itemChanged();
}

void CtrlrModulatorTreeViewItem::valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved)
{
	itemChanged();
}

void CtrlrModulatorTreeViewItem::itemChanged()
{
	treeHasChanged();
}

void CtrlrModulatorTreeViewItem::labelTextChanged (Label *labelThatHasChanged)
{
	if (defaultListener)
	{
		if (defaultListener->itemRenamed(itemToAttach, labelThatHasChanged->getText()))
		{
			itemToAttach.setProperty (Ids::name, labelThatHasChanged->getText(), nullptr);
			treeHasChanged();
		}
	}

	if (isSelected())
	{
		labelThatHasChanged->setColour (Label::backgroundColourId, Colour(0xff048cf5));
	}
}

var CtrlrModulatorTreeViewItem::getDragSourceDescription ()
{
	return (itemToAttach.getProperty(Ids::uuid));
}

bool CtrlrModulatorTreeViewItem::isInterestedInDragSource (const DragAndDropTarget::SourceDetails &dragSourceDetails)
{
	return (true);
}

/* ********************************************************************************** */
CtrlrModulatorTreeXmlEditor::CtrlrModulatorTreeXmlEditor()
	:	xmlEditor(nullptr),
		saveButton("Save", "Click to save XML and apply properties")
{
	xmlEditor = new CodeEditorComponent (xmlDocument, nullptr);
	addAndMakeVisible (xmlEditor);
	saveButton.setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight );
	addAndMakeVisible (&saveButton);
	saveButton.addListener (this);
}

CtrlrModulatorTreeXmlEditor::~CtrlrModulatorTreeXmlEditor()
{
	deleteAndZero (xmlEditor);
}

void CtrlrModulatorTreeXmlEditor::resized()
{
	saveButton.setBounds (0, getHeight() - 24, 64, 24);
	xmlEditor->setBounds (0, 0, getWidth(), getHeight() - 24);
}

void CtrlrModulatorTreeXmlEditor::setSelectedTree(ValueTree &_selectedTree)
{
	ScopedPointer <XmlElement> xml(_selectedTree.createXml());
	if (xml)
	{
		xmlDocument.replaceAllContent (xml->createDocument(""));
	}

	selectedTree = _selectedTree;
}

void CtrlrModulatorTreeXmlEditor::buttonClicked (Button *btn)
{
	ScopedPointer <XmlElement> changedXml (XmlDocument::parse (xmlDocument.getAllContent()));

	if (changedXml)
	{
		ValueTree tree = ValueTree::fromXml (*changedXml);

		if (tree.isValid())
		{
			if (selectedTree.isValid())
			{
				for (int i=0; i<selectedTree.getNumProperties(); i++)
				{
					if (!tree.hasProperty (selectedTree.getPropertyName(i)))
					{
						selectedTree.removeProperty (selectedTree.getPropertyName(i), 0);
					}
				}

				for (int i=0; i<tree.getNumProperties(); i++)
				{
					selectedTree.setProperty (tree.getPropertyName(i), tree.getProperty (tree.getPropertyName(i)), 0);
				}
			}
		}
		else
		{
			_WRN("XML was valid, but can't make a ValueTree out of it");
		}
	}
	else
	{
		_WRN("XML is invalid, can't use it");
	}
}

/* ********************************************************************************** */
CtrlrModulatorTreePropertyPanel::CtrlrModulatorTreePropertyPanel(CtrlrPanelModulatorListTree &_owner) : owner(_owner)
{
	addAndMakeVisible (&properties);
	addAndMakeVisible (&xmlEditor);
	addAndMakeVisible (spacerComponent = new StretchableLayoutResizerBar (&layoutManager, 1, false));
	layoutManager.setItemLayout (0, -0.001, -1.0, -0.5);
 	layoutManager.setItemLayout (1, 8, 8, 8);
 	layoutManager.setItemLayout (2, -0.001, -1.0, -0.5);
}

CtrlrModulatorTreePropertyPanel::~CtrlrModulatorTreePropertyPanel()
{
	deleteAndZero (spacerComponent);
}

void CtrlrModulatorTreePropertyPanel::resized()
{
	Component* comps[] = { &properties, spacerComponent, &xmlEditor };
 	layoutManager.layOutComponents (comps, 3, 0, 0, getWidth(), getHeight(), true, true);
}

void CtrlrModulatorTreePropertyPanel::setSelectedTree(ValueTree &selectedTree)
{
	xmlEditor.setSelectedTree (selectedTree);

	properties.clear();
	Array <PropertyComponent*> propertyEditors;
	for (int i=0; i<selectedTree.getNumProperties(); i++)
	{
		propertyEditors.add (new TextPropertyComponent (selectedTree.getPropertyAsValue (selectedTree.getPropertyName (i),0), selectedTree.getPropertyName (i).toString(), 4096, false));
	}
	properties.addProperties (propertyEditors);
}

/* ********************************************************************************** */
CtrlrPanelModulatorListTree::CtrlrPanelModulatorListTree(CtrlrPanel &_owner) : owner(_owner), propertyPanel(*this)
{
	addAndMakeVisible (&propertyPanel);
	addAndMakeVisible (&treeView);
	addAndMakeVisible (spacerComponent = new StretchableLayoutResizerBar (&layoutManager, 1, true));
	layoutManager.setItemLayout (0, -0.001, -1.0, -0.5);
 	layoutManager.setItemLayout (1, 8, 8, 8);
 	layoutManager.setItemLayout (2, -0.001, -1.0, -0.5);
	treeView.setRootItem (new CtrlrModulatorTreeViewItem(this, owner.getObjectTree()));
}

CtrlrPanelModulatorListTree::~CtrlrPanelModulatorListTree()
{
	treeView.deleteRootItem();
	deleteAndZero (spacerComponent);
}

void CtrlrPanelModulatorListTree::resized()
{
	Component* comps[] = { &treeView, spacerComponent, &propertyPanel };
 	layoutManager.layOutComponents (comps, 3, 0, 0, getWidth(), getHeight(), false, true);
}

void CtrlrPanelModulatorListTree::itemChanged (ValueTree &itemTreeThatChanged)
{
	propertyPanel.setSelectedTree (itemTreeThatChanged);
}

Image CtrlrPanelModulatorListTree::getIconForType (const ValueTree &item)
{
	if (item.getType() == Ids::panel)
	{
		return (IMAGE(ico_box_png));
	}
	else if (item.getType() == Ids::component)
	{
		return (IMAGE(ico_gui_png));
	}
	else if (item.getType() == Ids::modulator)
	{
		return (IMAGE(ico_unit_png));
	}
	else if (item.getType() == Ids::midi)
	{
		return (IMAGE(ico_midi_png));
	}
	else
	{
		return (IMAGE(ico_unknown_png));
	}
}
