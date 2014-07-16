#include "stdafx.h"
#include "CtrlrLookAndFeel.h"
#include "CtrlrUtilities.h"
#include "CtrlrInlineUtilitiesGUI.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrPanel/CtrlrPanelEditor.h"

CtrlrLookAndFeel::CtrlrLookAndFeel(CtrlrManager &_owner) : owner(_owner)
{
}

void CtrlrLookAndFeel::setActivePanelEditor(CtrlrPanelEditor *_editor)
{
	editor = _editor;
}

Typeface::Ptr CtrlrLookAndFeel::getTypefaceForFont(const Font &font)
{
    return Font::getDefaultTypefaceForFont (font);
}

const var CtrlrLookAndFeel::getPanelProperty(const Identifier &identifier, const var defaultValue)
{
	if (editor)
		return (editor->getProperty(identifier));
	else
		return (defaultValue);
}

void CtrlrLookAndFeel::drawBubble (Graphics &g, BubbleComponent&, const Point<float>& tip, const Rectangle<float>& body)
{
    Path p;
    p.addBubble (body, body.getUnion (Rectangle<float> (tip.x, tip.y, 1.0f, 1.0f)),
                 tip, getPanelProperty(Ids::uiPanelTooltipCornerRound, 5.0f), jmin (15.0f, body.getWidth() * 0.2f, body.getHeight() * 0.2f));

	g.setColour (VAR2COLOUR(getPanelProperty(Ids::uiPanelTooltipBackgroundColour, "0xffeeeebb")));
    g.fillPath (p);

    g.setColour (VAR2COLOUR(getPanelProperty(Ids::uiPanelTooltipOutlineColour, "0xff000000")));
    g.strokePath (p, PathStrokeType (1.33f));
}

Font CtrlrLookAndFeel::getSliderPopupFont(Slider &)
{
	return (owner.getFontManager().getFontFromString(getPanelProperty(Ids::uiPanelTooltipFont, Font(15.0f, Font::bold).toString())));
}

int CtrlrLookAndFeel::getSliderPopupPlacement(Slider &)
{
    return (getPanelProperty(Ids::uiPanelTooltipPlacement, 0));
}

void CtrlrLookAndFeel::drawStretchableLayoutResizerBar (Graphics &g, int w, int h, bool isVerticalBar, bool isMouseOver, bool isMouseDragging)
{
	if (isMouseOver)
		g.fillAll (Colours::black.withAlpha(0.2f));
	else
		g.fillAll (Colours::black.withAlpha(0.1f));

	g.setColour (Colours::black.withAlpha(0.3f));
	if (isVerticalBar)
		g.fillRoundedRectangle (0.0f, (float)(h/2) - w, w, w, w * 0.75f);
	else
		g.fillRoundedRectangle ((float)(w/2)-h, 0.0f, h, h, h * 0.75f);
}

void CtrlrLookAndFeel::setUsingNativeAlerts(const bool useNativeAlerts)
{
	setUsingNativeAlertWindows(useNativeAlerts);
}

void CtrlrLookAndFeel::drawMenuBarBackground (Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &menuBar)
{
	ColourGradient cg(Colour(0xfff7f7f7), 0.0f, 1.0f, Colour(0xffcccccc), 0.0f, (float)height-2.0f, false);
	g.setGradientFill (cg);
	g.fillRect (0.0f, 1.0f, (float)width, (float)height - 2.0f);

	g.setColour (Colour(0xff454545));
	g.drawLine (0.0f, (float)height, (float)width, (float)height, 1.0f);
}

CtrlrFontManager &CtrlrLookAndFeel::getFontManager()
{
	return (owner.getFontManager());
}

/**
 * Menu bar look and feel for panels to override
 *
 */

CtrlrMenuBarLookAndFeel::CtrlrMenuBarLookAndFeel(CtrlrEditor &_owner) : owner(_owner)
{
	owner.getMenuBar()->setLookAndFeel (this);
}

void CtrlrMenuBarLookAndFeel::setPanel(CtrlrPanel *_panel)
{
	panel = _panel;

	if (panel)
	{
		setColour (PopupMenu::headerTextColourId, VAR2COLOUR(panel->getProperty (Ids::ctrlrMenuItemHeaderColour)));
		owner.getMenuBar()->repaint();
	}
}

Colour CtrlrMenuBarLookAndFeel::getColour (const Identifier &property)
{
	if (panel)
	{
		return (VAR2COLOUR(panel->getProperty (property)));
	}
	else
	{
        if (property == Ids::ctrlrMenuItemBackgroundColour)
		{
			return (findColour (PopupMenu::backgroundColourId));
		}
		else if (property == Ids::ctrlrMenuItemTextColour || property == Ids::ctrlrMenuBarTextColour)
		{
			return (findColour (PopupMenu::textColourId));
		}
		else if (property == Ids::ctrlrMenuItemHighlightColour || property == Ids::ctrlrMenuBarHighlightColour)
		{
			return (Colour (HIGHLIGHT_COLOUR));
		}
		else if (property == Ids::ctrlrMenuItemHighlightedTextColour)
		{
			return (findColour (PopupMenu::highlightedTextColourId));
		}
		else if (property == Ids::ctrlrMenuBarBackgroundColour1)
		{
			return (Colour(0xfff7f7f7));
		}
		else if (property == Ids::ctrlrMenuBarBackgroundColour2)
		{
			return (Colour(0xffcccccc));
		}
		else if (property == Ids::ctrlrMenuItemSeparatorColour)
		{
			return (Colour(0x44000000));
		}
		else if (property == Ids::ctrlrMenuItemHeaderColour)
		{
			return (findColour (PopupMenu::headerTextColourId));
		}
		return (Colours::white);
	}
}

Font CtrlrMenuBarLookAndFeel::getFont(const Identifier &property)
{
	if (panel)
	{
		return (owner.getOwner().getFontManager().getFontFromString (panel->getProperty (property)));
	}
	return (Font(18.0f));
}

void CtrlrMenuBarLookAndFeel::drawPopupMenuBackground (Graphics &g, int width, int height)
{
	const Colour background (getColour (Ids::ctrlrMenuItemBackgroundColour));

    g.fillAll (background);
    g.setColour (background.overlaidWith (Colour (0x2badd8e6)));

    //for (int i = 0; i < height; i += 3)
 //       g.fillRect (0, i, width, 1);

#if ! JUCE_MAC
    g.setColour (findColour (PopupMenu::textColourId).withAlpha (0.6f));
    g.drawRect (0, 0, width, height);
#endif
}

void CtrlrMenuBarLookAndFeel::drawPopupMenuItem (Graphics &g, const Rectangle<int>& area, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const String& text, const String& shortcutKeyText, const Drawable* icon, const Colour* textColourToUse)
{
	const float halfH = area.getHeight() * 0.5f;

    if (isSeparator)
    {
        const float separatorIndent = 5.5f;

        g.setColour (getColour (Ids::ctrlrMenuItemSeparatorColour));
		g.fillRect (separatorIndent, halfH, area.getWidth() - (separatorIndent*2), 1.25f);
    }
    else
    {
        Colour textColour (getColour (Ids::ctrlrMenuItemTextColour));

        if (isHighlighted)
        {
			drawSelectionRectangle (g, area.getWidth(), area.getHeight(), getColour (Ids::ctrlrMenuItemHighlightColour));
            g.setColour (getColour (Ids::ctrlrMenuItemHighlightedTextColour));
        }
        else
        {
            g.setColour (getColour (Ids::ctrlrMenuItemTextColour));
        }

        if (! isActive)
            g.setOpacity (0.3f);

        Font font (getPopupMenuFont());

        if (font.getHeight() > area.getHeight() / 1.3f)
            font.setHeight (area.getHeight() / 1.3f);

        g.setFont (font);

        const int leftBorder = (area.getHeight() * 5) / 4;
        const int rightBorder = 4;

        if (icon != nullptr)
        {
			icon->drawWithin (g, Rectangle<float> (2.0f, 1.0f, leftBorder - 4.0f, area.getHeight() - 2.0f), RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, 1.0f);
        }
        else if (isTicked)
        {
            const Path tick (getTickShape (1.0f));
            const float th = font.getAscent();
            const float ty = halfH - th * 0.5f;

            g.fillPath (tick, tick.getTransformToScaleToFit (2.0f, ty, (float) (leftBorder - 4),
                                                             th, true));
        }

        g.drawFittedText (text,
							leftBorder, 0, area.getWidth() - (leftBorder + rightBorder), area.getHeight(),
                          Justification::centredLeft, 1);

        if (shortcutKeyText.isNotEmpty())
        {
            Font f2 (font);
            f2.setHeight (f2.getHeight() * 0.75f);
            f2.setHorizontalScale (0.95f);
            g.setFont (f2);

            g.drawText (shortcutKeyText,
                        leftBorder, 0, area.getWidth() - (leftBorder + rightBorder + 4), area.getHeight(),
                        Justification::centredRight,
                        true);
        }

        if (hasSubMenu)
        {
            const float arrowH = 0.6f * getPopupMenuFont().getAscent();
            const float x = area.getWidth() - area.getHeight() * 0.6f;

            Path p;
            p.addTriangle (x, halfH - arrowH * 0.5f,
                           x, halfH + arrowH * 0.5f,
                           x + arrowH * 0.6f, halfH);

            g.fillPath (p);
        }
    }
}

Font CtrlrMenuBarLookAndFeel::getPopupMenuFont ()
{
	return (getFont (Ids::ctrlrMenuItemFont));
}

Font CtrlrMenuBarLookAndFeel::getMenuBarFont (MenuBarComponent &menuBar, int itemIndex, const String &itemText)
{
	return (getFont(Ids::ctrlrMenuBarFont));
}

void CtrlrMenuBarLookAndFeel::drawPopupMenuUpDownArrow (Graphics &g, int width, int height, bool isScrollUpArrow)
{
	const Colour background (getColour (Ids::ctrlrMenuItemBackgroundColour));

    g.setGradientFill (ColourGradient (background, 0.0f, height * 0.5f,
                                       background.withAlpha (0.0f),
                                       0.0f, isScrollUpArrow ? ((float) height) : 0.0f,
                                       false));

    g.fillRect (1, 1, width - 2, height - 2);

    const float hw = width * 0.5f;
    const float arrowW = height * 0.3f;
    const float y1 = height * (isScrollUpArrow ? 0.6f : 0.3f);
    const float y2 = height * (isScrollUpArrow ? 0.3f : 0.6f);

    Path p;
    p.addTriangle (hw - arrowW, y1,
                   hw + arrowW, y1,
                   hw, y2);

    g.setColour (findColour (PopupMenu::textColourId).withAlpha (0.5f));
    g.fillPath (p);
}

void CtrlrMenuBarLookAndFeel::getIdealPopupMenuItemSize (const String &text, bool isSeparator, int standardMenuItemHeight, int &idealWidth, int &idealHeight)
{
	if (isSeparator)
    {
        idealWidth = 50;
        idealHeight = standardMenuItemHeight > 0 ? standardMenuItemHeight / 2 : 10;
    }
    else
    {
        Font font (getPopupMenuFont());

        if (standardMenuItemHeight > 0 && font.getHeight() > standardMenuItemHeight / 1.3f)
            font.setHeight (standardMenuItemHeight / 1.3f);

        idealHeight = standardMenuItemHeight > 0 ? standardMenuItemHeight : roundToInt (font.getHeight() * 1.3f);
        idealWidth = font.getStringWidth (text) + idealHeight * 2;
    }
}

int CtrlrMenuBarLookAndFeel::getMenuWindowFlags()
{
    return ComponentPeer::windowHasDropShadow;
}

void CtrlrMenuBarLookAndFeel::drawMenuBarBackground (Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &menuBar)
{
	drawCtrlrMenuBarBackground (g, width, height, isMouseOverBar, getColour(Ids::ctrlrMenuBarBackgroundColour1), getColour(Ids::ctrlrMenuBarBackgroundColour2));
}

int CtrlrMenuBarLookAndFeel::getMenuBarItemWidth (MenuBarComponent &menuBar, int itemIndex, const String &itemText)
{
	return getMenuBarFont (menuBar, itemIndex, itemText).getStringWidth (itemText) + menuBar.getHeight();
}

void CtrlrMenuBarLookAndFeel::drawMenuBarItem (Graphics &g, int width, int height, int itemIndex, const String &itemText, bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar, MenuBarComponent &menuBar)
{
	if (itemText.isEmpty())
		return;

	Colour textColour	= getColour (Ids::ctrlrMenuBarTextColour);
	Font textFont		= getMenuBarFont (menuBar, itemIndex, itemText);

	if (!menuBar.isEnabled())
	{
		textColour = textColour.withMultipliedAlpha (0.5f);
	}
	else if (isMouseOverItem && !isMenuOpen)
	{
		textColour = getColour (Ids::ctrlrMenuBarHighlightedTextColour);
		drawSelectionRectangle (g, width, height, getColour (Ids::ctrlrMenuBarHighlightColour).darker(0.3f));
	}
	else if (isMouseOverItem && isMenuOpen)
	{
		textColour = getColour (Ids::ctrlrMenuBarHighlightedTextColour);
		drawSelectionRectangle (g, width, height, getColour (Ids::ctrlrMenuBarHighlightColour));
	}
	else if (isMenuOpen)
	{
		textColour = getColour (Ids::ctrlrMenuBarHighlightedTextColour);
		drawSelectionRectangle (g, width, height, getColour (Ids::ctrlrMenuBarHighlightColour));
	}

	g.setColour (textColour);
	g.setFont (textFont);
	g.drawFittedText (itemText, 0, 0, width, height, Justification::centred, 1);
}
