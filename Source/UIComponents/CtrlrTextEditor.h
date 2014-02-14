#ifndef __CTRLR_TEXT_EDITOR__
#define __CTRLR_TEXT_EDITOR__

#include "CtrlrMacros.h"

class CtrlrTextEditor : public TextEditor
{
	public:
		CtrlrTextEditor(const String &componentName=String::empty, juce_wchar passwordCharacter=0);
		~CtrlrTextEditor();

		void setAttributedText (const AttributedString &text);
		void insertAttributedText (const AttributedString &text);
		const String getLineAtPosition(const int index);
		void setXmlSource (const String &xmlSource);
		void insertText (const String &text, const Font &font, const Colour &colour);
		void updateContent();

		static CtrlrTextEditor *readOnlyMultiline(const String &xmlSource, const Colour backgroundColour=Colours::transparentBlack, const Colour outlineColour=Colours::transparentBlack, const Colour shadowColour=Colours::transparentBlack);
		JUCE_LEAK_DETECTOR(CtrlrTextEditor)
};

#endif