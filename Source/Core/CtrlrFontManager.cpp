#include "stdafx.h"
#include "CtrlrFontManager.h"
#include "CtrlrLog.h"

CtrlrFontManager::CtrlrFontManager()
{
	reloadFonts();
}

CtrlrFontManager::~CtrlrFontManager()
{
}

void CtrlrFontManager::reloadOSFonts()
{
	osFonts.clear();
	osTypefaceNames.clear();
	osTypefaceStyles.clear();

	osTypefaceNames = Font::findAllTypefaceNames();
	Font::findFonts (osFonts);
}

void CtrlrFontManager::reloadBuiltInFonts()
{
}

void CtrlrFontManager::reloadImportedFonts()
{
}

void CtrlrFontManager::reloadFonts()
{
	reloadOSFonts();
	reloadBuiltInFonts();
	reloadImportedFonts();
}

const Array<Font> &CtrlrFontManager::getFontArray()
{
	return (osFonts);
}

void CtrlrFontManager::fillCombo (ComboBox &comboToFill)
{
	comboToFill.clear();
	for (int i=0; i<osFonts.size(); i++)
	{
		comboToFill.addItem (osFonts[i].getTypefaceName(), i+1);
	}
}

Font CtrlrFontManager::getFont(const int fontIndex)
{
	return (osFonts[fontIndex]);
}

Font CtrlrFontManager::getBuiltInFont(const String &fontResourceName)
{
	int dataSize;
	const char *dataPointer = BinaryData::getNamedResource(fontResourceName.toUTF8(), dataSize);
	if (dataSize <= 0)
		return (Font());

	MemoryBlock data(dataPointer, dataSize);
	MemoryInputStream mi (data, true);

	CustomTypeface *importedTypeFace = new CustomTypeface(mi);
	return (Font (importedTypeFace));
}

const Font CtrlrFontManager::getFont (const char *fontData, const int fontDataSize)
{
	MemoryBlock data(fontData, fontDataSize);
	MemoryInputStream mi (data, true);

	CustomTypeface *importedTypeFace = new CustomTypeface(mi);
	return (Font (importedTypeFace));
}

Font CtrlrFontManager::getFont(const File &fontFile)
{
	MemoryBlock data;
	fontFile.loadFileAsData (data);
	MemoryInputStream mi (data, true);

	CustomTypeface *importedTypeFace = new CustomTypeface(mi);
	return (Font (importedTypeFace));
}

const Font CtrlrFontManager::getFontFromString (const String &string)
{
	string.replace ("<Monospaced>", getDefaultMonoFontName(), false);

	if (!string.contains (";"))
	{
		return (Font::fromString(string));
	}

	StringArray fontProps;
	fontProps.addTokens (string, ";", "\"\'");
	Font font;

	if (fontProps[fontTypefaceName] != String::empty)
	{
		font.setTypefaceName (fontProps[fontTypefaceName]);
		font.setHeight (fontProps[fontHeight].getFloatValue());

		if (fontProps[fontBold] != String::empty)
			font.setBold (fontProps[fontBold].getIntValue() ? true : false);
		
		if (fontProps[fontItalic] != String::empty)
			font.setItalic (fontProps[fontItalic].getIntValue() ? true : false);
		
		if (fontProps[fontUnderline] != String::empty)
			font.setUnderline (fontProps[fontUnderline].getIntValue() ? true : false);

		if (fontProps[fontKerning] != String::empty)
			font.setExtraKerningFactor (fontProps[fontKerning].getFloatValue());

		if (fontProps[fontHorizontalScale] != String::empty)
			font.setHorizontalScale (fontProps[fontHorizontalScale].getFloatValue());
	}

	return (font);
}

const String CtrlrFontManager::getStringFromFont (const Font &_font)
{
	Font font(_font);
	StringArray fontProps;

	if (font.getTypefaceName() == "<Monospaced>")
	{
		font.setTypefaceName (getDefaultMonoFontName());
	}

	fontProps.add (font.getTypefaceName());
	fontProps.add (String(font.getHeight()));
	fontProps.add (String(font.isBold()));
	fontProps.add (String(font.isItalic()));
	fontProps.add (String(font.isUnderlined()));
	fontProps.add (String(font.getExtraKerningFactor()));
	fontProps.add (String(font.getHorizontalScale()));

	return (fontProps.joinIntoString(";"));
}

const String CtrlrFontManager::getDefaultMonoFontName()
{
	if (osTypefaceNames.contains("Courier New"))
	{
		return ("Courier New");
	}
	else
	{
		return (Font::getDefaultMonospacedFontName());
	}
}

const String CtrlrFontManager::fontToBase64 (const Font &font)
{
	/** taken from Zamrate's [http://www.rawmaterialsoftware.com/memberlist.php?mode=viewprofile&u=558] font serializer utility

		to restore a saved font:

		MemoryInputStream is(str.getData(), str.getDataSize(), false);
		CustomTypeface *newTypeface = new CustomTypeface(is);
		Font myFont(newTypeface);
		myFont.setHeight(16.0f);
		label3->setFont(myFont);
	*/

	// copy the font-properties to a CustomTypeface
    CustomTypeface customTypeface;
	customTypeface.setCharacteristics(font.getTypefaceName(), font.getAscent(), font.isBold(), font.isItalic(), ' ');
    // Here's the important part: copy all glyphs to a new instance of CustomTypeface
	customTypeface.addGlyphsFromOtherTypeface( *font.getTypeface(), 0, 256);
	MemoryBlock fontData;
	MemoryOutputStream str (fontData, true);
	customTypeface.writeToStream(str);

	return (fontData.toBase64Encoding());
}