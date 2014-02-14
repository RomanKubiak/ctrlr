#ifndef __CTRLR_COMPONENT__
#define __CTRLR_COMPONENT__

#include "../Core/CtrlrModulator/CtrlrModulator.h"
#include "CtrlrComponentBubble.h"
#include "Deprecated/CtrlrLuaRectangle.h"
#include "CtrlrLog.h"
#include "CtrlrFontManager.h"

class CtrlrPanelResource;
class CtrlrComponent;

class CtrlrGrouppingComponent
{
	public:
		virtual void setOwned (CtrlrComponent *componentToOwn, const int subIndexInGroup = 0, const bool shouldOwnThisComponent = true) = 0;
};

class CtrlrComponentResizableBorder : public ResizableBorderComponent, public LookAndFeel_V2
{
	public:
		CtrlrComponentResizableBorder(CtrlrComponent *_owner, ComponentBoundsConstrainer *constrainer);
		void paint (Graphics &g);
		void drawResizableFrame (Graphics& g, int w, int h, const BorderSize<int> &borderSize);

		JUCE_LEAK_DETECTOR(CtrlrComponentResizableBorder)

	private:
		CtrlrComponent *owner;
};

class CtrlrComponent :	public Component,
						public ChangeListener,
						public ComponentListener,
						public ValueTree::Listener,
						public CtrlrLuaObject
{
	public:
		CtrlrComponent(CtrlrModulator &_owner);
		virtual ~CtrlrComponent();
		void resized();
		void moved();

		virtual void setComponentValue (const double newValue, const bool sendChangeMessage=false)		= 0;
		virtual const double getComponentValue()														= 0;
		virtual const double getComponentMaxValue()														= 0;

		virtual void setComponentMidiValue (const int newValue, const bool sendChangeMessage=false);
		virtual const int getComponentMidiValue ();
		virtual const String getComponentText()														{ return (String::empty); }
		virtual void setComponentText (const String &componentText)									{}
		virtual const int getComponentRadioGroupId();
		virtual const bool getToggleState()															{ return (false); }
		virtual void setToggleState(const bool toggleState, const bool sendChangeMessage=false) 	{ }
		virtual const bool isToggleButton()															{ return (false); }
		virtual const String getTextForValue(const double value);
		virtual void panelChanged()																	{ }
		virtual void restoreState (const ValueTree &savedState);
		virtual void setText(const String &newText)													{ }
		virtual void modulatorNameChanged(const String &newName)									{ }
		virtual void changeListenerCallback (ChangeBroadcaster* source);
		virtual void click()																		{ }
		virtual Array <CtrlrComponent*> getOwnedChildren()											{ Array <CtrlrComponent*> ar; return (ar); }
		virtual void setOwned (CtrlrComponent *componentToOwn, const bool shouldOwnComponent=true)  { }
		virtual const PopupMenu getComponentMenu(const MouseEvent &e)										{ return (PopupMenu()); }
		virtual void handlePopupMenu (const int popupMenuItem)												{ }
		virtual CtrlrFontManager &getFontManager();
		virtual void allModulatorsInitialized()																{ }
		virtual void panelEditModeChanged(const bool isInEditMode=false);
		virtual void reloadResources(Array <CtrlrPanelResource*> resourcesThatChanged) {}
		void componentMovedOrResized (Component &component, bool wasMoved, bool wasResized);
		void addAndMakeVisible (Component *child, int zOrder=-1);
		CtrlrModulator &getOwner() const															{ return (owner); }
		void setProperty (const Identifier& name, const var &newValue, const bool isUndoable=false);
		void removeProperty (const Identifier &name);
		const var &getProperty (const Identifier& name) const												{ return componentTree.getProperty (name); }
		const var getProperty (const Identifier& name, const var &defaultReturnValue) const					{ return componentTree.getProperty (name, defaultReturnValue); }
		UndoManager* getUndoManager() const;
		ValueTree &getComponentTree()																		{ return (componentTree); }
		Rectangle<int> getUsableRect();
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		const String getVisibleName();
		const WeakReference<CtrlrComponent>::SharedRef& getWeakReference();
		const String getComponentGroup();

		void setGroupped (const bool addToGroup);
		const String getComponentTab();
		void setComponentTab (const String &newTab);
		void removeFromTab();
		void groupComponent () {}
		int snapPosition (int pos, int snapSize, const bool allowSnap);
		void visibilityChanged();
		ValueTree &getObjectTree()																			{ return (componentTree); }
		void setEffect();
		int snapDim(int dim);
		const bool getRestoreState();
		static void wrapForLua (lua_State *L);
		const double getMaximum();
		const double getMinimum();
		// Deprecated
		CtrlrLuaRectangle getLuaBounds();
		void setLuaBounds(CtrlrLuaRectangle newBounds);

		JUCE_LEAK_DETECTOR(CtrlrComponent)

	protected:
		bool restoreStateInProgress;
		bool isSelected;
		bool editMode;
		bool allowDimSnap;
		int snapDimSize;
		CtrlrComponentResizableBorder selectionBorder;
		ValueTree componentTree;
		CtrlrModulator &owner;
		Label componentNameLabel;
		WeakReference<CtrlrComponent>::Master masterReference;
		friend class WeakReference<CtrlrComponent>;
		CtrlrComponentBubble bubble;
		ScopedPointer <GlowEffect> glowEffect;
		ScopedPointer <DropShadowEffect> shadowEffect;
};
#endif
