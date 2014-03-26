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

void CtrlrLookAndFeel::drawPopupMenuBackground (Graphics &g, int width, int height)
{
	const Colour background (findColour (PopupMenu::backgroundColourId));

    g.fillAll (background);
    g.setColour (background.overlaidWith (Colour (0x2badd8e6)));

    for (int i = 0; i < height; i += 3)
        g.fillRect (0, i, width, 1);

#if ! JUCE_MAC
    g.setColour (findColour (PopupMenu::textColourId).withAlpha (0.6f));
    g.drawRect (0, 0, width, height);
#endif
}

void CtrlrLookAndFeel::drawMenuBarBackground (Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &menuBar)
{
	ColourGradient cg(Colour(0xfff7f7f7), 0.0f, 1.0f, Colour(0xffcccccc), 0.0f, (float)height-2.0f, false);
	g.setGradientFill (cg);
	g.fillRect (0.0f, 1.0f, (float)width, (float)height - 2.0f);

	g.setColour (Colour(0xff0c0f15));
	g.drawLine (0.0f, (float)height, (float)width, (float)height, 1.0f);

	g.setColour (Colour(0xfffafafa));
	g.drawLine (0.0f, 0.0f, (float)width, 0.0f, 1.0f);
}

Font CtrlrLookAndFeel::getPopupMenuFont()
{
	return (Font(13.5f, Font::plain));
}

Font CtrlrLookAndFeel::getMenuBarFont (MenuBarComponent &menuBar, int itemIndex, const String &itemText)
{
	return (getPopupMenuFont());
}

void CtrlrLookAndFeel::drawMenuBarItem (Graphics &g, int width, int height, int itemIndex, const String &itemText, bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar, MenuBarComponent &menuBar)
{
	Colour textColour	= menuBar.findColour (PopupMenu::textColourId);
	Font textFont		= getMenuBarFont (menuBar, itemIndex, itemText);

	if (!menuBar.isEnabled())
	{
		textColour = textColour.withMultipliedAlpha (0.5f);
	}
	else if (isMouseOverItem && !isMenuOpen)
	{
		textColour = textColour.contrasting(1.0f);
		drawSelectionRectangle (g, width, height, Colour(0xff4364ff).brighter(0.2f));
	}
	else if (isMouseOverItem && isMenuOpen)
	{
		textColour = textColour.contrasting(1.0f);
		drawSelectionRectangle (g, width, height, Colour(0xff4364ff).darker(0.1f));
	}

	g.setColour (textColour);
	g.setFont (textFont);
	g.drawFittedText (itemText, 0, 0, width, height, Justification::centred, 1);
}

void CtrlrLookAndFeel::drawPopupMenuItem (Graphics& g,
                                    int width, int height,
                                    bool isSeparator,
                                    bool isActive,
                                    bool isHighlighted,
                                    bool isTicked,
                                    bool hasSubMenu,
                                    const String& text,
                                    const String& shortcutKeyText,
                                    Image* image,
                                    const Colour* const textColourToUse)
{
    const float halfH = height * 0.5f;

    if (isSeparator)
    {
        const float separatorIndent = 5.5f;

        g.setColour (Colour (0x33000000));
        g.drawLine (separatorIndent, halfH, width - separatorIndent, halfH);

        g.setColour (Colour (0x66ffffff));
        g.drawLine (separatorIndent, halfH + 1.0f, width - separatorIndent, halfH + 1.0f);
    }
    else
    {
        Colour textColour (findColour (PopupMenu::textColourId));

        if (textColourToUse != nullptr)
            textColour = *textColourToUse;

        if (isHighlighted)
        {
			drawSelectionRectangle (g, width, height);
            g.setColour (findColour (PopupMenu::highlightedTextColourId));
        }
        else
        {
            g.setColour (textColour);
        }

        if (! isActive)
            g.setOpacity (0.3f);

        Font font (getPopupMenuFont());

        if (font.getHeight() > height / 1.3f)
            font.setHeight (height / 1.3f);

        g.setFont (font);

        const int leftBorder = (height * 5) / 4;
        const int rightBorder = 4;

        if (image != nullptr)
        {
            g.drawImageWithin (*image,
                               2, 1, leftBorder - 4, height - 2,
                               RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, false);
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
                          leftBorder, 0, width - (leftBorder + rightBorder), height,
                          Justification::centredLeft, 1);

        if (shortcutKeyText.isNotEmpty())
        {
            Font f2 (font);
            f2.setHeight (f2.getHeight() * 0.75f);
            f2.setHorizontalScale (0.95f);
            g.setFont (f2);

            g.drawText (shortcutKeyText,
                        leftBorder, 0, width - (leftBorder + rightBorder + 4), height,
                        Justification::centredRight,
                        true);
        }

        if (hasSubMenu)
        {
            const float arrowH = 0.6f * getPopupMenuFont().getAscent();
            const float x = width - height * 0.6f;

            Path p;
            p.addTriangle (x, halfH - arrowH * 0.5f,
                           x, halfH + arrowH * 0.5f,
                           x + arrowH * 0.6f, halfH);

            g.fillPath (p);
        }
    }
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
		return (owner.getOwner().getFontManager().getFontFromString (panel->getProperty(property)));
	}
	else
	{
		return (Font(13.5f));
	}
}

void CtrlrMenuBarLookAndFeel::drawPopupMenuBackground (Graphics &g, int width, int height)
{
	const Colour background (getColour (Ids::ctrlrMenuItemBackgroundColour));

    g.fillAll (background);
    g.setColour (background.overlaidWith (Colour (0x2badd8e6)));

    for (int i = 0; i < height; i += 3)
        g.fillRect (0, i, width, 1);

#if ! JUCE_MAC
    g.setColour (findColour (PopupMenu::textColourId).withAlpha (0.6f));
    g.drawRect (0, 0, width, height);
#endif
}

void CtrlrMenuBarLookAndFeel::drawPopupMenuItem (Graphics &g, int width, int height, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const String &text, const String &shortcutKeyText, Image *image,
													const Colour *const textColourToUse)
{
	const float halfH = height * 0.5f;

    if (isSeparator)
    {
        const float separatorIndent = 5.5f;

        g.setColour (getColour (Ids::ctrlrMenuItemSeparatorColour));
        g.fillRect (separatorIndent, halfH, width - (separatorIndent*2), 1.25f);
        //g.drawLine (separatorIndent, halfH, width - separatorIndent, halfH, 0.3f);
    }
    else
    {
        Colour textColour (getColour (Ids::ctrlrMenuItemTextColour));

        if (isHighlighted)
        {
			drawSelectionRectangle (g, width, height, getColour (Ids::ctrlrMenuItemHighlightColour));
            g.setColour (getColour (Ids::ctrlrMenuItemHighlightedTextColour));
        }
        else
        {
            g.setColour (getColour (Ids::ctrlrMenuItemTextColour));
        }

        if (! isActive)
            g.setOpacity (0.3f);

        Font font (getPopupMenuFont());

        if (font.getHeight() > height / 1.3f)
            font.setHeight (height / 1.3f);

        g.setFont (font);

        const int leftBorder = (height * 5) / 4;
        const int rightBorder = 4;

        if (image != nullptr)
        {
            g.drawImageWithin (*image,
                               2, 1, leftBorder - 4, height - 2,
                               RectanglePlacement::centred | RectanglePlacement::onlyReduceInSize, false);
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
                          leftBorder, 0, width - (leftBorder + rightBorder), height,
                          Justification::centredLeft, 1);

        if (shortcutKeyText.isNotEmpty())
        {
            Font f2 (font);
            f2.setHeight (f2.getHeight() * 0.75f);
            f2.setHorizontalScale (0.95f);
            g.setFont (f2);

            g.drawText (shortcutKeyText,
                        leftBorder, 0, width - (leftBorder + rightBorder + 4), height,
                        Justification::centredRight,
                        true);
        }

        if (hasSubMenu)
        {
            const float arrowH = 0.6f * getPopupMenuFont().getAscent();
            const float x = width - height * 0.6f;

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
	return (getFont(Ids::ctrlrMenuItemFont));
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

Font CtrlrMenuBarLookAndFeel::getMenuBarFont (MenuBarComponent &menuBar, int itemIndex, const String &itemText)
{
	return (getFont(Ids::ctrlrMenuBarFont));
}

void CtrlrMenuBarLookAndFeel::drawMenuBarItem (Graphics &g, int width, int height, int itemIndex, const String &itemText, bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar, MenuBarComponent &menuBar)
{
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

void CtrlrLookAndFeel::setActivePanelEditor(CtrlrPanelEditor *_editor)
{
	editor = _editor;
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

/*void CtrlrLookAndFeel::drawScrollbar (Graphics& g, ScrollBar& scrollbar, int x, int y, int width, int height, bool isScrollbarVertical, int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown)
{
    g.fillAll (scrollbar.findColour (ScrollBar::backgroundColourId));

    Path slotPath, thumbPath;

    const float slotIndent = jmin (width, height) > 15 ? 1.0f : 0.0f;
    const float slotIndentx2 = slotIndent * 2.0f;
    const float thumbIndent = slotIndent + 1.0f;
    const float thumbIndentx2 = thumbIndent * 2.0f;

    float gx1 = 0.0f, gy1 = 0.0f, gx2 = 0.0f, gy2 = 0.0f;

    if (isScrollbarVertical)
    {
        slotPath.addRoundedRectangle (x + slotIndent,
                                      y + slotIndent,
                                      width - slotIndentx2,
                                      height - slotIndentx2,
                                      (width - slotIndentx2) * 0.5f);

        if (thumbSize > 0)
            thumbPath.addRoundedRectangle (x + thumbIndent,
                                           thumbStartPosition + thumbIndent,
                                           width - thumbIndentx2,
                                           thumbSize - thumbIndentx2,
                                           (width - thumbIndentx2) * 0.5f);
        gx1 = (float) x;
        gx2 = x + width * 0.7f;
    }
    else
    {
        slotPath.addRoundedRectangle (x + slotIndent,
                                      y + slotIndent,
                                      width - slotIndentx2,
                                      height - slotIndentx2,
                                      (height - slotIndentx2) * 0.5f);

        if (thumbSize > 0)
            thumbPath.addRoundedRectangle (thumbStartPosition + thumbIndent,
                                           y + thumbIndent,
                                           thumbSize - thumbIndentx2,
                                           height - thumbIndentx2,
                                           (height - thumbIndentx2) * 0.5f);
        gy1 = (float) y;
        gy2 = y + height * 0.7f;
    }

    const Colour thumbColour (scrollbar.findColour (ScrollBar::thumbColourId));
    Colour trackColour1, trackColour2;

    if (scrollbar.isColourSpecified (ScrollBar::trackColourId)
         || isColourSpecified (ScrollBar::trackColourId))
    {
        trackColour1 = trackColour2 = scrollbar.findColour (ScrollBar::trackColourId);
    }
    else
    {
        trackColour1 = thumbColour.overlaidWith (Colour (0x44000000));
        trackColour2 = thumbColour.overlaidWith (Colour (0x19000000));
    }

    g.setGradientFill (ColourGradient (trackColour1, gx1, gy1,
                                       trackColour2, gx2, gy2, false));
    g.fillPath (slotPath);

    if (isScrollbarVertical)
    {
        gx1 = x + width * 0.6f;
        gx2 = (float) x + width;
    }
    else
    {
        gy1 = y + height * 0.6f;
        gy2 = (float) y + height;
    }

    g.setGradientFill (ColourGradient (Colours::transparentBlack,gx1, gy1,
                       Colour (0x19000000), gx2, gy2, false));
    g.fillPath (slotPath);

    g.setColour (thumbColour);
    g.fillPath (thumbPath);

    g.setGradientFill (ColourGradient (Colour (0x10000000), gx1, gy1,
                       Colours::transparentBlack, gx2, gy2, false));

    g.saveState();

    if (isScrollbarVertical)
        g.reduceClipRegion (x + width / 2, y, width, height);
    else
        g.reduceClipRegion (x, y + height / 2, width, height);

    g.fillPath (thumbPath);
    g.restoreState();

    g.setColour (Colour (0x4c000000));
    g.strokePath (thumbPath, PathStrokeType (0.4f));
}
*/