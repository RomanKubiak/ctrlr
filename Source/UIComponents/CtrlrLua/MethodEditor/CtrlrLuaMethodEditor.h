#ifndef __CTRLR_LUA_METHOD_EDITOR__
#define __CTRLR_LUA_METHOD_EDITOR__

#include "CtrlrPanel/CtrlrPanelModulatorListTree.h"
#include "CtrlrWindowManagers/CtrlrPanelWindowManager.h"
#include "CtrlrLuaMethodFind.h"
#include "CtrlrLuaMethodEditArea.h"
#include "CtrlrValueTreeEditor.h"


class CtrlrManager;
class CtrlrLookAndFeel;
class CtrlrLuaMethodManager;
class CtrlrLuaMethodCodeEditor;

#define METHOD_NEW				"Add new method"
#define METHOD_DEL				"Delete method"
#define METHOD_FROM_TEMPLATE	"Replace with template"
#define METHOD_SAVE				"Save method"
#define FIND_AND_REPLACE		"Find and replace"
#define GROUP_NEW				"Add new group"

class ChildSorter
{
	public:
		ChildSorter (const bool _sortByName);
		int compareElements (ValueTree first, ValueTree second);

	private:
		bool sortByName;
};

class CtrlrLuaMethodEditor  : public CtrlrChildWindowContent,
							  public CtrlrValueTreeEditorLookProvider,
							  public KeyListener,
							  public DragAndDropContainer,
							  public ValueTree::Listener
{
	public:
	    CtrlrLuaMethodEditor (CtrlrPanel &_owner);
	    ~CtrlrLuaMethodEditor();
		enum ToolbarItems
		{
			_none,
			saveMethod,
			saveAndCompileMethod,
			findInMethod
		};

		CtrlrLuaMethod *setEditedMethod (const Uuid &methodUuid);
		CtrlrLuaMethod *setEditedMethod (const String &methodName);
		void createNewTab (CtrlrLuaMethod *method);
		CtrlrLuaMethodCodeEditor *getCurrentEditor();
		CtrlrLuaMethodEditArea *getMethodEditArea();
		void restoreState(const ValueTree &savedState);
		void setPositionLabelText (const String &text);

		void addNewMethod(ValueTree parentGroup=ValueTree());
		void addMethodFromFile(ValueTree parentGroup=ValueTree());

		void addNewGroup(ValueTree parentGroup=ValueTree());
		void removeGroup(ValueTree parentGroup=ValueTree());
		void renameGroup(ValueTree parentGroup=ValueTree());

		const String getUniqueName(const ValueTree &item) const;
		Image getIconForItem(const ValueTree &item)	const;
		void itemClicked (const MouseEvent &e, ValueTree &item);
		void itemDoubleClicked (const MouseEvent &e, ValueTree &item);
		const bool renameItem(const ValueTree &item, const String &newName) const;
		const bool canBeRenamed(const ValueTree &item) const;
		const AttributedString	getDisplayString(const ValueTree &item)	const;
		const Font getItemFont(const ValueTree &item) const;
		const bool isInterestedInDragSource(const ValueTree &item, const DragAndDropTarget::SourceDetails &dragSourceDetails) const;
		void itemDropped (ValueTree &item, const DragAndDropTarget::SourceDetails &dragSourceDetails, int insertIndex);
		void handleAsyncUpdate();
		CtrlrLuaMethodManager &getMethodManager();
		String getContentName()					{ return ("LUA Editor"); }
		uint8 getType()							{ return (CtrlrPanelWindowManager::LuaMethodEditor); }
		CtrlrPanel &getOwner();
		void paint (Graphics& g);
		void resized();
		bool keyPressed (const KeyPress& key, Component* originatingComponent);
		void closeTab(const int tabIndex);
		void tabChanged(CtrlrLuaMethodCodeEditor *codeEditor, const bool save=false, const bool recompile=false);
		void updateTabs();
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
		void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
		void valueTreeChildAdded (ValueTree& parentTree, ValueTree& child){}
		void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& child){}
		void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
		TabbedComponent *getTabs();
		void updateRootItem();
		void itemChanged (ValueTree &itemTreeThatChanged);
		var getDragSourceDescription(Array <ValueTree> &selectedTreeItems);
		void setCurrentTab (CtrlrLuaMethod *methodToSetAsCurrent);
		void saveSettings();
		ValueTree &getComponentTree();
		StringArray getMenuBarNames();
		PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName);
		void menuItemSelected(int menuItemID, int topLevelMenuIndex);
		void searchResultClicked (const String &methodName, const int lineNumber, const int resultPositionStart, const int resultPositionEnd);

		JUCE_LEAK_DETECTOR(CtrlrLuaMethodEditor)

	private:
		WeakReference<CtrlrLuaMethodEditor>::Master masterReference;
		friend class WeakReference<CtrlrLuaMethodEditor>;
		File lastBrowsedSourceDir;
		CtrlrValueTreeEditorTree *methodTree;
		StretchableLayoutManager layoutManager;
		StretchableLayoutResizerBar *resizer;
		CtrlrPanel &owner;
		CtrlrLuaMethodEditArea *methodEditArea;
};


#endif
