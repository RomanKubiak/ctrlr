#ifndef __CTRLR_VALUE_TREE_EDITOR__
#define __CTRLR_VALUE_TREE_EDITOR__

#include "CtrlrIDs.h"
#include "CtrlrMacros.h"
#include "CtrlrUtilities.h"

class CtrlrValueTreeEditorLookProvider : public AsyncUpdater
{
	public:
		virtual const String			getUniqueName(const ValueTree &item)	const { return (item.getType().toString()); }
		virtual const AttributedString	getDisplayString(const ValueTree &item)	const { return (AttributedString(getUniqueName(item))); }
		virtual const Font				getItemFont(const ValueTree &item)		const { return (Font(12)); }
		virtual const int				getItemHeight(const ValueTree &item)	const { return (24); }
		virtual bool					canBeSelected(const ValueTree &item)	const { return (true); }
		virtual Image					getIconForItem(const ValueTree &item)	const { return (Image::null); }
		virtual void					itemClicked(const MouseEvent &e, ValueTree &item)	{ }
		virtual void					itemDoubleClicked(const MouseEvent &e, ValueTree &item)	{ }
		virtual const bool				renameItem(const ValueTree &item, const String &newName) const	{ return (false); }
		virtual const bool				canBeRenamed(const ValueTree &item) const						{ return (false); }
		virtual void					handleAsyncUpdate()=0;
		virtual const bool				isInterestedInDragSource(const ValueTree &item, const DragAndDropTarget::SourceDetails &dragSourceDetails) const { return (false); }
		virtual void					itemDropped (ValueTree &targetItem, const DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex) {}
		virtual void					itemOpennessChanged(const bool isNowOpen)						{ }
		virtual var						getDragSourceDescription(Array <ValueTree> &selectedTreeItems)	{ return (String::empty); }
};

class CtrlrValueTreeEditorTree : public TreeView
{
	public:
		CtrlrValueTreeEditorTree(const String &name) : TreeView(name) {}
		bool keyPressed (const KeyPress &key);
};

class CtrlrValueTreeEditorItem : public TreeViewItem, public ValueTree::Listener
{
	public:
		CtrlrValueTreeEditorItem(CtrlrValueTreeEditorLookProvider &_provider, ValueTree _treeToEdit, const Identifier &_nameIdentifier=Ids::name);
		~CtrlrValueTreeEditorItem();
		bool mightContainSubItems();
		String getUniqueName () const;
		void itemSelectionChanged (bool isNowSelected);
		int	getItemWidth () const;
		int	getItemHeight () const;
		bool canBeSelected () const;
		void itemOpennessChanged (bool isNowOpen);
		bool isInterestedInDragSource (const DragAndDropTarget::SourceDetails &dragSourceDetails);
		void itemDropped (const DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex);
		var getDragSourceDescription ();
		void paintItem (Graphics &g, int width, int height);
		void itemClicked (const MouseEvent &e);
		void itemDoubleClicked (const MouseEvent &e);
		void keyPressed (const KeyPress &key);
		const bool canHandleDragAndDrop();
		ValueTree &getTree() { return (treeToEdit); }
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
		void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
		void valueTreeChildAdded (ValueTree& parentTree, ValueTree& child){}
		void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& child){}
		void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
		JUCE_LEAK_DETECTOR(CtrlrValueTreeEditorItem)

	private:
		ValueTree treeToEdit;
		CtrlrValueTreeEditorLookProvider &provider;
		Identifier nameIdentifier;
};

#endif
