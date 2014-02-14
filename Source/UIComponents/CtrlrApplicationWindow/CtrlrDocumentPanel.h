#ifndef __CTRLR_DOCUMENT_PANEL__
#define __CTRLR_DOCUMENT_PANEL__

#include "CtrlrMacros.h"

class CtrlrEditor;
class CtrlrManager;

class CtrlrDocumentPanel  : public MultiDocumentPanel
{
	public:
		CtrlrDocumentPanel (CtrlrManager &_owner);
		~CtrlrDocumentPanel();
		bool tryToCloseDocument (Component* component);
		void activeDocumentChanged();
		void setEditor (CtrlrEditor *_editorToSet);
		void paint (Graphics& g);
		void resized();
		JUCE_LEAK_DETECTOR(CtrlrDocumentPanel)

	private:
		CtrlrEditor *ctrlrEditor;
		CtrlrManager &owner;
};


#endif
