#ifndef __CTRLR_EXPRESSION_PROPERTY__
#define __CTRLR_EXPRESSION_PROPERTY__

#include "CtrlrPropertyEditors/CtrlrPropertyComponent.h"
#include "CtrlrWindowManagers/CtrlrManagerWindowManager.h"

class CtrlrExpressionProperty  : public Component,
                                 public TextEditor::Listener,
                                 public ButtonListener,
								 public CtrlrPropertyChild
{
	public:
		CtrlrExpressionProperty (const Value &_valeToControl);
		~CtrlrExpressionProperty();
		void refresh();
		void textEditorTextChanged (TextEditor &editor);
		void textEditorReturnKeyPressed (TextEditor &editor);
		void textEditorFocusLost (TextEditor &editor);
		const bool compile(const bool setPropertyIfValid);
		void resized();
		void buttonClicked (Button* buttonThatWasClicked);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrExpressionProperty);

	private:
		CtrlrFloatingWindow *externalEditorWindow;
		Value valeToControl;
		TextEditor* text;
		ImageButton* apply;
};


#endif
