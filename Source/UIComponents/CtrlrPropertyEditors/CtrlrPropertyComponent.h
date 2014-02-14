#ifndef __CTRLR_PROPERTY_COMPONENT__
#define __CTRLR_PROPERTY_COMPONENT__

#include "CtrlrIDManager.h"
class CtrlrPanel;

class CtrlrPropertyChild
{
	public:
		virtual ~CtrlrPropertyChild() {}
		virtual void refresh()=0;
};

class CtrlrPropertyComponent  : public PropertyComponent
{
	public:
		CtrlrPropertyComponent (const Identifier &_propertyName, 
								const ValueTree &_propertyElement, 
								const ValueTree &_identifierDefinition,
								CtrlrPanel *_panel=nullptr, 
								StringArray *_possibleChoices=nullptr, 
								Array<var>  *_possibleValues=nullptr);

		virtual ~CtrlrPropertyComponent();
		int getPreferredHeight() const noexcept                 { return preferredHeight; }
		void setPreferredHeight (int newHeight) noexcept        { preferredHeight = newHeight; }
		Component *getPropertyComponent();
		void resized();
		void paint (Graphics &g);
		void refresh();
		void mouseEnter (const MouseEvent &e);
		void mouseExit (const MouseEvent &e);
		void mouseDown (const MouseEvent &e);
		void mouseMove (const MouseEvent &e);
		const String getElementSubType();
		const String getElementType();

	private:
	    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrPropertyComponent);
		String visibleText;
		ValueTree propertyElement;
		Identifier propertyName;
		ValueTree identifierDefinition;
		Font currentFont;
		CtrlrIDManager::PropertyType propertyType;
		CtrlrPanel *panel;
		StringArray *possibleChoices;
		Array<var>  *possibleValues;
};


#endif
