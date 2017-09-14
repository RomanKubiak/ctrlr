#ifndef CTRLR_FONT_MANAGER
#define CTRLR_FONT_MANAGER

#include "CtrlrMacros.h"

class CtrlrPanel;
class CtrlrManager;

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

		CtrlrFontManager(CtrlrManager &_owner);
		~CtrlrFontManager();
		void reloadOSFonts();
		void reloadBuiltInFonts();
		void reloadImportedFonts(CtrlrPanel *panelToLoadFrom=nullptr);
		void reloadJuceFonts();
		void reloadFonts();
		const Array<Font> &getOsFontArray();
		void fillCombo (ComboBox &comboToFill, const bool showOsFonts=true, const bool showBuiltInFonts=true, const bool showImportedFonts=true, const bool showJuceFonts=true);
		Font getFont(const int fontIndex);
		Font getFont(const File &fontFile);
		const String getDefaultMonoFontName();
		const Font getFontFromString (const String &string);
		const String getStringFromFont (const Font &font);
		int getNumBuiltInFonts();
		FontSet getFontSetEnum (const Font &font);
		Array<Font> &getFontSet (const FontSet fontSetToFetch);

		Font getDefaultLargeFont();
		Font getDefaultSmallFont();
		Font getDefaultNormalFont();

		static Font getBuiltInFont(const char *fontData, const int fontDataSize);
		static Font getBuiltInFont(const String &fontResourceName);
		static const Font getFont (const char *fontData, const int fontDataSize);
		static const Font getBuiltInFont(const int fontIndex);
		static bool isFontFile(const File &fontFile) { return (fontFile.hasFileExtension("jfont")); }

		JUCE_LEAK_DETECTOR(CtrlrFontManager);

	private:
	    CtrlrManager &owner;
		Array<Font> osFonts;
		Array<Font> builtInFonts;
		Array<Font> juceFonts;
		Array<Font> importedFonts;
		StringArray osTypefaceNames;
		StringArray osTypefaceStyles;
		int64 allFontCount;
};

#endif
