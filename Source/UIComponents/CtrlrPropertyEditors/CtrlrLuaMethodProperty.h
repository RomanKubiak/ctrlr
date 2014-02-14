#ifndef __CTRLR_LUA_METHOD_PROPERTY__
#define __CTRLR_LUA_METHOD_PROPERTY__

#include "CtrlrMacros.h"
#include "CtrlrPropertyEditors/CtrlrPropertyComponent.h"

class CtrlrLuaMethodProperty  : public Component,
                                public ComboBoxListener,
                                public ButtonListener,
								public CtrlrPropertyChild
{
	public:
		CtrlrLuaMethodProperty (const Value &_valeToControl, const Identifier &_id, CtrlrPanel *_owner);
		~CtrlrLuaMethodProperty();
		void refresh();
		void resized();
		void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
		void buttonClicked (Button* buttonThatWasClicked);

	private:
		Value valeToControl;
		Identifier id;
		String propertyName;
		CtrlrPanel *owner;
		ComboBox* methodSelectorCombo;
		ImageButton* editMethodButton;
		ImageButton* newMethodButton;
		ImageButton* deleteMethodButton;
};


#endif
