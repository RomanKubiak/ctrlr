#include "stdafx.h"
#include "CtrlrFontManager.h"
#include "CtrlrLog.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanel/CtrlrPanelResourceManager.h"
#include "CtrlrPanel/CtrlrPanelResource.h"

#define FONT_FROM_DATA(x)		getFont (BinaryData::x, BinaryData::x ## Size)

CtrlrFontManager::CtrlrFontManager(CtrlrManager &_owner) : owner(_owner)
{
	reloadFonts();
}

CtrlrFontManager::~CtrlrFontManager()
{
}

void CtrlrFontManager::reloadFonts()
{
	reloadOSFonts();
	reloadBuiltInFonts();
	reloadImportedFonts();
	reloadJuceFonts();
}

void CtrlrFontManager::reloadOSFonts()
{
	osFonts.clear();
	osTypefaceNames.clear();
	osTypefaceStyles.clear();

	osTypefaceNames = Font::findAllTypefaceNames();
	Font::findFonts (osFonts);
}

void CtrlrFontManager::reloadJuceFonts()
{
	juceFonts.clear();

	juceFonts.add (Font (Font::getDefaultMonospacedFontName(), 14.0f, Font::plain));
	juceFonts.add (Font (Font::getDefaultSansSerifFontName(), 14.0f, Font::plain));
	juceFonts.add (Font (Font::getDefaultSerifFontName(), 14.0f, Font::plain));
}

const int CtrlrFontManager::getNumBuiltInFonts()
{
	return (10);
}

void CtrlrFontManager::reloadBuiltInFonts()
{
	builtInFonts.clear();

	for (int i=0; i<getNumBuiltInFonts(); i++)
	{
		builtInFonts.add (CtrlrFontManager::getBuiltInFont (i));
	}
}

void CtrlrFontManager::reloadImportedFonts(CtrlrPanel *panelToLoadFrom)
{
	importedFonts.clear();
	CtrlrPanel *panel = nullptr;

    if (panelToLoadFrom)
    {
        panel = panelToLoadFrom;
    }
    else
    {
        panel = owner.getActivePanel();
    }

	if (panel)
    {
        CtrlrPanelResourceManager &manager = panel->getResourceManager();

        for (int i=0; i<manager.getNumResources(); i++)
        {
            if (manager.getResource(i)->getType() == CtrlrPanelResourceManager::FontRes)
            {
                importedFonts.add (manager.getResource(i)->asFont());
            }
        }
    }
}

const Array<Font> &CtrlrFontManager::getOsFontArray()
{
	return (osFonts);
}

void CtrlrFontManager::fillCombo (ComboBox &comboToFill, const bool showOsFonts, const bool showBuiltInFonts, const bool showImportedFonts, const bool showJuceFonts)
{
	comboToFill.clear();
	int i = 0;

	if (showJuceFonts)
	{
		comboToFill.addSectionHeading ("OS Default fonts");
		for (i=0; i<juceFonts.size(); i++)
		{
			comboToFill.addItem (juceFonts[i].getTypefaceName(), allFontCount + i + 1);
		}

		allFontCount += i;
	}

	if (showBuiltInFonts)
	{
		comboToFill.addSectionHeading ("Ctrlr Built-In fonts");
		for (i=0; i<builtInFonts.size(); i++)
		{
			comboToFill.addItem (builtInFonts[i].getTypefaceName(), allFontCount + i + 1);
		}

		allFontCount += i;
	}

	if (showImportedFonts)
	{
	    reloadImportedFonts();

		comboToFill.addSectionHeading ("Imported fonts (from resources)");
		for (i=0; i<importedFonts.size(); i++)
		{
			comboToFill.addItem (importedFonts[i].getTypefaceName(), allFontCount + i + 1);
		}

		allFontCount += i;
	}

	if (showOsFonts)
	{
		comboToFill.addSectionHeading ("OS Fonts");
		for (i=0; i<osFonts.size(); i++)
		{
			comboToFill.addItem (osFonts[i].getTypefaceName(), allFontCount + i + 1);
		}

		allFontCount += i;
	}
}

Font CtrlrFontManager::getFont(const int fontIndex)
{
	if (fontIndex >= 0 && fontIndex < juceFonts.size())
	{
		return (juceFonts[fontIndex]);
	}
	if (fontIndex >= juceFonts.size() && fontIndex < (builtInFonts.size() + juceFonts.size()))
	{
		return (builtInFonts [fontIndex - juceFonts.size()]);
	}
	else if (fontIndex >= builtInFonts.size() && fontIndex < (importedFonts.size() + builtInFonts.size() + juceFonts.size()))
	{
		return (importedFonts [fontIndex - juceFonts.size() - builtInFonts.size()]);
	}
	else if (fontIndex >= (importedFonts.size()+builtInFonts.size()) && fontIndex < (importedFonts.size() + juceFonts.size() + builtInFonts.size() + osFonts.size()))
	{
		return (osFonts [fontIndex - juceFonts.size() - builtInFonts.size() - importedFonts.size()]);
	}

	return (builtInFonts[0]);
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
	_DBG("CtrlrFontManager::getFontFromString \""+string+"\"");

	if (!string.contains (";"))
	{
	    if (string == String::empty)
        {
            return (Font (18.0f));
        }
		return (Font::fromString(string));
	}

	StringArray fontProps;
	fontProps.addTokens (string, ";", "\"\'");
	Font font;

	if (fontProps[fontTypefaceName] != String::empty)
	{
		if (fontProps[fontSet] != String::empty && fontProps[fontSet].getIntValue() >= 0)
		{
			/* We need to fetch the typeface for the font from the correct font set */
			
			Array<Font> &fontSetToUse = getFontSet((const FontSet)fontProps[fontSet].getIntValue());
            
			for (int i=0; i<fontSetToUse.size(); i++)
			{
				if (fontSetToUse[i].getTypefaceName() == fontProps[fontTypefaceName])
				{
					font = fontSetToUse[i];
				}
			}
		}
		else
		{
			/* The font set is not specified, fall back to JUCE to find the typeface name
				this will actualy be the OS set */
			font.setTypefaceName (fontProps[fontTypefaceName]);
		}

		font.setHeight (fontProps[fontHeight].getFloatValue());

		font.setBold (false);
        font.setUnderline (false);
        font.setItalic (false);

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
	fontProps.add (font.getTypefaceName());
	fontProps.add (String(font.getHeight()));
	fontProps.add (String(font.isBold()));
	fontProps.add (String(font.isItalic()));
	fontProps.add (String(font.isUnderlined()));
	fontProps.add (String(font.getExtraKerningFactor()));
	fontProps.add (String(font.getHorizontalScale()));
	fontProps.add (String((uint8)getFontSetEnum (font)));

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

const Font CtrlrFontManager::getBuiltInFont(const int fontIndex)
{
	Font f;

	switch (fontIndex)
	{
		case 0:
			f = FONT_FROM_DATA (FONT_LCD_bin);
			break;
		case 1:
			f = FONT_FROM_DATA (FONT_Digital7_bin);
			break;
		case 2:
			f = FONT_FROM_DATA (FONT_DottyShadow_bin);
			break;
		case 3:
			f = FONT_FROM_DATA (FONT_ZX81_bin);
			break;
		case 4:
			f = FONT_FROM_DATA (FONT_Invasion2000_bin);
			break;
		case 5:
			f = FONT_FROM_DATA (FONT_Digit_bin);
			break;
		case 6:
			f = FONT_FROM_DATA (FONT_Computerfont_bin);
			break;
		case 7:
			f = FONT_FROM_DATA (FONT_Electronic_Highway_Sign_bin);
			break;
		case 8:
			f = FONT_FROM_DATA (FONT_Karmatic_Arcade_bin);
			break;
		case 9:
			f = FONT_FROM_DATA (FONT_60sekuntia_bin);
			break;
		default:
			break;
	}

	return (f);
}

const CtrlrFontManager::FontSet CtrlrFontManager::getFontSetEnum (const Font &font)
{
	for (int i=0; i<osFonts.size(); i++)
	{
		if (osFonts[i].getTypefaceName() == font.getTypefaceName())
			return (osFontSet);
	}

	for (int i=0; i<builtInFonts.size(); i++)
	{
		if (builtInFonts[i].getTypefaceName() == font.getTypefaceName())
			return (builtInFontSet);
	}

	for (int i=0; i<importedFonts.size(); i++)
	{
		if (importedFonts[i].getTypefaceName() == font.getTypefaceName())
			return (importedFontSet);
	}

	for (int i=0; i<juceFonts.size(); i++)
	{
		if (juceFonts[i].getTypefaceName() == font.getTypefaceName())
			return (juceFontSet);
	}

	return (unknownFontSet);
}

Array<Font> &CtrlrFontManager::getFontSet (const FontSet fontSetToFetch)
{
	switch (fontSetToFetch)
	{
		case osFontSet:
			return (osFonts);
		case builtInFontSet:
			return (builtInFonts);
		case importedFontSet:
			return (importedFonts);
		case juceFontSet:
		case unknownFontSet:
		default:
			return (juceFonts);
			break;
	}
}
