#ifndef CTRLR_FONT_MANAGER
#define CTRLR_FONT_MANAGER

#include "CtrlrMacros.h"

class CtrlrPanel;

class CtrlrFontManager
{
	public:
		enum FontSet
		{
			osFontSet,
			importedFontSet,
			builtInFontSet,
			juceFontSet,
			unknownFontSet
		};

		CtrlrFontManager();
		~CtrlrFontManager();
		void reloadOSFonts();
		void reloadBuiltInFonts();
		void reloadImportedFonts();
		void reloadJuceFonts();
		void reloadFonts();
		const Array<Font> &getOsFontArray();
		void fillCombo (ComboBox &comboToFill, const bool showOsFonts=true, const bool showBuiltInFonts=true, const bool showImportedFonts=true, const bool showJuceFonts=true);
		Font getFont(const int fontIndex);
		Font getFont(const File &fontFile);
		Font getBuiltInFont(const char *fontData, const int fontDataSize);
		Font getBuiltInFont(const String &fontResourceName);
		const String getDefaultMonoFontName();
		static const String fontToBase64 (const Font &font);
		static const Font getFont (const char *fontData, const int fontDataSize);
		const Font getFontFromString (const String &string);
		static const Font getBuiltInFont(const int fontIndex);
		const String getStringFromFont (const Font &font);
		const int getNumBuiltInFonts();
		const FontSet getFontSetEnum (const Font &font);
		Array<Font> &getFontSet (const FontSet fontSetToFetch);
		static const bool isFontFile(const File &fontFile) { return (fontFile.hasFileExtension("jfont")); }
		JUCE_LEAK_DETECTOR(CtrlrFontManager);

	private:
		Array<Font> osFonts;
		Array<Font> builtInFonts;
		Array<Font> juceFonts;
		Array<Font> importedFonts;
		StringArray osTypefaceNames;
		StringArray osTypefaceStyles;
		int64 allFontCount;
};

#endif