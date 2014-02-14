#ifndef __JUCER_HEADER_CTRLRPANELCANVAS_CTRLRPANELCANVAS_13CAE15F__
#define __JUCER_HEADER_CTRLRPANELCANVAS_CTRLRPANELCANVAS_13CAE15F__

#include "CtrlrComponentSelection.h"
#include "CtrlrIDs.h"
#include "CtrlrPanelCanvasLayer.h"
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"


class CtrlrQuickXmlPreview : public Button::Listener, public Component
{
	public:
		CtrlrQuickXmlPreview(ValueTree &_treeToPreview) : h("Show XML", URL()), treeToPreview(_treeToPreview)
		{
			addAndMakeVisible (&h);
			h.addListener (this);
			setSize (64,16);
		}

		void resized()
		{
			h.setSize (getWidth(), getHeight());
		}

		void buttonClicked(Button *button)
		{
			CodeDocument doc;
			CodeEditorComponent ed(doc, 0);
			ScopedPointer <XmlElement> xml(treeToPreview.createXml());
			doc.replaceAllContent(xml->createDocument(""));
			ed.setSize (600,600);
			DialogWindow::showModalDialog ("XML Preview", &ed, this, Colours::white, true, true, true);
		}

		JUCE_LEAK_DETECTOR(CtrlrQuickXmlPreview)

	private:
		HyperlinkButton h;
		ValueTree &treeToPreview;
};

class CtrlrPopupMenuLook : public LookAndFeel_V2
{
	public:
		CtrlrPopupMenuLook(){}
		~CtrlrPopupMenuLook(){}
		Path getTickShape (float height);
		void drawPopupMenuItem (Graphics& g,
                                     int width, int height,
                                     bool isSeparator,
                                     bool isActive,
                                     bool isHighlighted,
                                     bool isTicked,
                                     bool hasSubMenu,
                                     const String& text,
                                     const String& shortcutKeyText,
                                     Image* image,
                                     const Colour *textColourToUse);
		void getIdealPopupMenuItemSize (const String &text, bool isSeparator, int standardMenuItemHeight, int &idealWidth, int &idealHeight);
};

class CtrlrPanelEditor;

//==============================================================================
/** @brief Class that represents a panel's canvas (layers are held by the canvas)

*/
class CtrlrPanelCanvas  : public CtrlrChildWindowContent,
                          public KeyListener,
                          public LassoSource<CtrlrComponent*>,
                          public ChangeBroadcaster,
                          public ChangeListener,
                          public ValueTree::Listener,
                          public FileDragAndDropTarget,
						  public DragAndDropContainer,
						  public DragAndDropTarget
{
public:
    CtrlrPanelCanvas (CtrlrPanelEditor &_owner);
    ~CtrlrPanelCanvas();

	enum EditMenuItems
	{
		Copy	=	2048,
		Paste	=	2049,
		Cut		=	2050,
		Delete	=	2051,
		Undo	=	2052,
		Redo	=	2053,
		AlignToTop		= 2054,
		AlignToLeft		= 2055,
		AlignToBottom	= 2056,
		AlignToRight	= 2057,
		FitToRect		= 2058,
		GroupCreate		= 2059,
		GroupDestroy	= 2060
	};

	enum Direction
	{
		Up,
		Down,
		Left,
		Right,
		None
	};

	CtrlrComponent *addNewComponent (const Identifier &componentType, const Point<int> insertAt, Component *componentToAddTo=0);
	CtrlrComponent *addNewComponent (const Identifier &componentType, const Rectangle<int> componentBounds);
	CtrlrComponent *addNewComponent (const ValueTree &savedState, Component *componentToAddTo=0, const bool force=false);
	CtrlrModulator *addModulator(const Identifier &componentType=Ids::uiNone);
	void removeModulator(CtrlrModulator *m, const bool sendNotificationForEachElement=true);
	void removeComponent(CtrlrComponent *c, const bool sendNotificationForEachElement=true);
	void removeComponentsInGroup(CtrlrComponent *c, const bool sendNotificationForEachElement=true);
    void findLassoItemsInArea (Array <CtrlrComponent*>& itemsFound, const Rectangle<int>& area);
	SelectedItemSet <CtrlrComponent*>& getLassoSelection();
	CtrlrComponent *findEventComponent (const MouseEvent &e);
	const PopupMenu getRightClickComponentMenu(const MouseEvent &e);
	void handleComponentPopupMenu(const MouseEvent &e, const int ret);
	const PopupMenu getGroupPopup(const int startIndex=4096);
	const PopupMenu getTabPopup(const int startIndex=8192);
	void handleGroupMenu (const int returnCode, CtrlrComponent *c, const bool altCoords=false);
	void handleTabMenu (PopupMenu &m, const int returnCode, CtrlrComponent *c, const bool altCoords=false);
	void handleLeftClickOnComponent(const MouseEvent &e);
	void handleRightClickOnCanvas(const MouseEvent &e);
	void handleRightClickOnTabs(const MouseEvent &e);
	void handleRightClickOnComponent(const MouseEvent &e);
	void handleRightClickOnMultiSelection(const MouseEvent &e);
	void pasteGroupComponent(const ValueTree &groupTree, const int destinationX=-1, const int destinationY=-1);
	void pasteGroupComponent(const ValueTree &groupTree, const MouseEvent &e);
	void copyWithChildren(CtrlrComponent *c);
	void deleteWithChildren(CtrlrComponent *c);
	int snapPosition (int pos, int snapSize, const bool allowSnap);
	void moveSelectedComps (int dx, int dy, bool snap);
	void dragSelectedComps (int dx, int dy, const bool allowSnap);
	void startDraggingSelection();
	void endDraggingSelection();
	void restoreState (const ValueTree &savedState);
	void canvasStateRestored();
	void changeListenerCallback (ChangeBroadcaster* source);
	void getEditMenu(PopupMenu &m);
	void handleEditMenu (const int returnCode, const MouseEvent &e);
	void editMenuCopy(const MouseEvent *e=nullptr);
	void editMenuPaste(const MouseEvent &e);
	void editMenuPaste();
	void editMenuDelete();
	void cut();
	void copy();
	void paste();
	void editModeChanged(const bool isEditMode);
	CtrlrPanelEditor &getOwner()																				{ return (owner); }
	CtrlrPanel &getPanel();
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
	void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
	void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
	void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
	void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
	void moveSelectionBy (const int deltaOffset, const Direction directionToMove);
	static const Direction keyPressToDirection(const KeyPress &k);
	void alignSelection(const EditMenuItems direction);
	CtrlrComponentSelection &getSelection();
	bool isInterestedInFileDrag (const StringArray &files);
	void filesDropped (const StringArray &files, int x, int y);
	void fileDragExit (const StringArray &files);
	void fileDragEnter (const StringArray &files, int x, int y);
	void exportSelectedComponents();
	void exportComponent (CtrlrComponent *componentToExport);
	void importComponent (const File &componentFile, int x=0, int y=0);
	void importPanel (const File &panelFile, int x=0, int y=0);
	void importImage (const File &imageFile, int x=0, int y=0);
	bool keyPressed (const KeyPress& key, Component* originatingComponent);
	void fitSelection();
	ResizableBorderComponent *getResizableBorder() { return (ctrlrPanelCanvasResizableBorder); }
	const bool isOnlyGroupSelected();
	int getWidth();
	int getHeight();
	void repaint();
	static void wrapForLua (lua_State *L);
	uint8 getType();
	UndoManager* getUndoManager() const;
	void setProperty (const Identifier& name, const var &newValue, const bool isUndoable=false);
	const var &getProperty (const Identifier& name) const;
	const var getProperty (const Identifier& name, const var &defaultReturnValue) const;
	ValueTree &getCanvasTree();
	CtrlrComponent *attach(CtrlrComponent *ctrlrComponent, Component *componentToAddTo, const bool force=false);
	void emptyGroupping(ValueTree &tree);
	void initLayers();
	void addLayer(const ValueTree &layerTree);
	void removeLayer(const int index);
	void removeLayer(CtrlrPanelCanvasLayer *layerToRemove);
	void removeAllLayers();
	int getNumLayers();
	void addAndMakeVisibleNg(CtrlrComponent *componentToAdd, Component *componentToAddTo=0, const bool force=false);
	CtrlrPanelCanvasLayer *getCurrentLayer();
	CtrlrPanelCanvasLayer *getLayer(const String &layerUid);
	CtrlrPanelCanvasLayer *getLayerByName(const String &layerName);
	CtrlrPanelCanvasLayer *getLayerFromArray(const int indexInArray);
	const String getLayerName(const int indexInArray);
	void layersResize();
	bool isLayer(Component *componentToCheck);
	Component *getChildComponentLayered(const int componentIndex);
	int getNumChildComponentsLayered();
	void layersChanged();
	void moveLayer(CtrlrPanelCanvasLayer *layerToMove, const bool moveUp=true);
	void assignToLayer(CtrlrComponent *c, CtrlrPanelCanvasLayer *l);
	int compareElements (CtrlrPanelCanvasLayer *first, CtrlrPanelCanvasLayer *second);
	void dumpLayers();
    void paint (Graphics& g);
    void resized();
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);
    void mouseUp (const MouseEvent& e);
	bool isInterestedInDragSource (const SourceDetails &dragSourceDetails);
	void itemDropped (const SourceDetails &dragSourceDetails);
	void itemDragExit (const SourceDetails &dragSourceDetails);
	void itemDragEnter (const SourceDetails &dragSourceDetails);
	void replaceComponent (CtrlrModulator &modulator, const String &targetComponentType);
    JUCE_LEAK_DETECTOR(CtrlrPanelCanvas)

private:
	CtrlrPanelEditor &owner;
	LassoComponent <CtrlrComponent*> lassoComponent;
	bool componentWasDragged;
	Image backgroundFill;
	Image ctrlrPanelBackgroundImage;
	CtrlrPopupMenuLook menuLook;
	WeakReference <CtrlrLuaMethod>
		paintCbk,
		resizedCbk,
		luaPanelFileDragDropHandlerCbk,
		luaPanelFileDragEnterHandlerCbk,
		luaPanelFileDragExitHandlerCbk;
	int64 lastRMBMouseEventTime, lastLMBMouseEventTime;
	OwnedArray <CtrlrPanelCanvasLayer> layers;
    ResizableBorderComponent* ctrlrPanelCanvasResizableBorder;
    CtrlrPanelCanvas (const CtrlrPanelCanvas&);
    const CtrlrPanelCanvas& operator= (const CtrlrPanelCanvas&);
};


#endif
