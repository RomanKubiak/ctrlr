#ifndef __CTRLR_PANEL_MODULATOR_LIST_TREE__
#define __CTRLR_PANEL_MODULATOR_LIST_TREE__

#include "CtrlrModulator/CtrlrModulator.h"
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"

class CtrlrModulatorTreeViewItem;
class CtrlrPanelModulatorListTree;
class CtrlrPanelModulatorListTree;

class CtrlrTreeViewItemListener
{
	public:
		virtual void itemChanged (ValueTree &itemTreeThatChanged)=0;
		virtual Image getIconForType (const ValueTree &item)=0;
		virtual const String getDisplayTextForItem (const ValueTree &item) { return (String::empty); }
		virtual void itemClicked (const MouseEvent &e, const ValueTree &item) { }
		virtual void itemDoubleClicked (const MouseEvent &e, const ValueTree &item) { }
		virtual bool itemRenamed (ValueTree &itemRenamed, const String &newName) { return (false); }
};

class CtrlrModulatorTreeXmlEditor : public Component, public Button::Listener
{
	public:
		CtrlrModulatorTreeXmlEditor();
		~CtrlrModulatorTreeXmlEditor();
		void setSelectedTree(ValueTree &_selectedTree);
		void resized();
		void buttonClicked (Button *btn);

		JUCE_LEAK_DETECTOR(CtrlrModulatorTreeXmlEditor)

	private:
		ValueTree selectedTree;
		CodeEditorComponent *xmlEditor;
		CodeDocument xmlDocument;
		TextButton saveButton;
};

class CtrlrModulatorTreePropertyPanel : public Component
{
	public:
		CtrlrModulatorTreePropertyPanel(CtrlrPanelModulatorListTree &_owner);
		~CtrlrModulatorTreePropertyPanel();
		void resized();
		void setSelectedTree(ValueTree &selectedTree);

		JUCE_LEAK_DETECTOR(CtrlrModulatorTreePropertyPanel)

	private:
		PropertyPanel properties;
		CtrlrModulatorTreeXmlEditor xmlEditor;
		StretchableLayoutResizerBar* spacerComponent;
		StretchableLayoutManager layoutManager;
		CtrlrPanelModulatorListTree &owner;
};


class CtrlrModulatorTreeLabel : public Component, public KeyListener, public DragAndDropContainer
{
	public:
		CtrlrModulatorTreeLabel(CtrlrModulatorTreeViewItem &_owner, const ValueTree &_itemToAttach);
		~CtrlrModulatorTreeLabel() { masterReference.clear(); }
		void setSelected (const bool isSelected);
		void mouseEnter (const MouseEvent &e);
		void mouseExit (const MouseEvent &e);
		void resized();
		void paint(Graphics &g);
		bool keyPressed (const KeyPress &key, Component *originatingComponent);
		Image getIconForOurType();
		const String getLabelText();
		void addLabelListener (Label::Listener *listenerToAdd);
		void removeLabelListener (Label::Listener *listenerToRemove);
		JUCE_LEAK_DETECTOR(CtrlrModulatorTreeLabel)

	private:
		friend class WeakReference<CtrlrModulatorTreeLabel>;
		WeakReference<CtrlrModulatorTreeLabel>::Master masterReference;
		Label label;
		Image icon;
		CtrlrModulatorTreeViewItem &owner;
		ValueTree itemToAttach;
};

class CtrlrModulatorTreeViewItem : public TreeViewItem, 
									public MouseListener, 
									public ValueTree::Listener, 
									public Label::Listener 
{
	public:
		CtrlrModulatorTreeViewItem(CtrlrTreeViewItemListener *_defaultListener, const ValueTree &_itemToAttach);
		~CtrlrModulatorTreeViewItem();
		void itemClicked (const MouseEvent &e);
		bool mightContainSubItems ();
		String getUniqueName () const;
		int	getItemWidth () const;
		int	getItemHeight () const;
		void itemSelectionChanged (bool isNowSelected);
		bool canBeSelected () const;
		void mouseDown (const MouseEvent &e);
		void mouseDoubleClick (const MouseEvent &e);
		void labelTextChanged (Label *labelThatHasChanged);
		Component *createItemComponent ();
		void itemOpennessChanged (bool isNowOpen);
		CtrlrModulatorTreeLabel *createItemLabel(const ValueTree &itemToAttach);

		bool isInterestedInDragSource (const DragAndDropTarget::SourceDetails &dragSourceDetails);
		var getDragSourceDescription ();

		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged);
		void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged);
		void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded);
		void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved);
		void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved);
		void itemChanged();
		

		void addListener (CtrlrTreeViewItemListener *listener)						{ listeners.add(listener); }
		void removeListener (CtrlrTreeViewItemListener *listener)					{ listeners.remove(listener); }
		Image getIconForType(const ValueTree &item);

		JUCE_LEAK_DETECTOR(CtrlrModulatorTreeViewItem)

	private:
		ListenerList <CtrlrTreeViewItemListener> listeners;
		WeakReference<CtrlrModulatorTreeLabel> itemLabel;
		ValueTree itemToAttach;
		Font labelFont;
		Font labelMouseOverFont;
		CtrlrTreeViewItemListener *defaultListener;
};

class CtrlrPanelModulatorListTree : public Component, public CtrlrTreeViewItemListener
{
	public:
		CtrlrPanelModulatorListTree(CtrlrPanel &_owner);
		~CtrlrPanelModulatorListTree();
		void resized();
		void itemChanged (ValueTree &itemTreeThatChanged);
		Image getIconForType (const ValueTree &item);
		JUCE_LEAK_DETECTOR(CtrlrPanelModulatorListTree)

	private:
		CtrlrModulatorTreePropertyPanel propertyPanel;
		TreeView treeView;
		StretchableLayoutResizerBar* spacerComponent;
		StretchableLayoutManager layoutManager;
		CtrlrPanel &owner;
};

#endif