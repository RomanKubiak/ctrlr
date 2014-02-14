#ifndef __CTRLR_FONT_MANAGER__
#define __CTRLR_FONT_MANAGER__

#include "CtrlrMacros.h"

class CtrlrPanel;

class CtrlrFontManager
{
	public:
		CtrlrFontManager();
		~CtrlrFontManager();
		void reloadOSFonts();
		void reloadBuiltInFonts();
		void reloadImportedFonts();
		void reloadFonts();
		const Array<Font> &getFontArray();
		void fillCombo (ComboBox &comboToFill);
		Font getFont(const int fontIndex);
		Font getFont(const File &fontFile);
		Font getBuiltInFont(const char *fontData, const int fontDataSize);
		Font getBuiltInFont(const String &fontResourceName);
		const String getDefaultMonoFontName();
		static const String fontToBase64 (const Font &font);
		static const Font getFont (const char *fontData, const int fontDataSize);
		const Font getFontFromString (const String &string);
		const String getStringFromFont (const Font &font);
		static const bool isFontFile(const File &fontFile) { return (fontFile.hasFileExtension("jfont")); }
		JUCE_LEAK_DETECTOR(CtrlrFontManager);

	private:
		Array<Font> osFonts;
		StringArray osTypefaceNames;
		StringArray osTypefaceStyles;
};

#endif