#include "stdafx.h"
#include "CtrlrLuaMethodEditorTabs.h"

CtrlrLuaMethodEditorTabsLF::CtrlrLuaMethodEditorTabsLF()
{
}

CtrlrLuaMethodEditorTabsLF::~CtrlrLuaMethodEditorTabsLF()
{
}

int	CtrlrLuaMethodEditorTabsLF::getTabButtonBestWidth (TabBarButton &button, int tabDepth)
{
	Font f(14.0f);
	return (f.getStringWidth (button.getButtonText()) + 24);
}

void CtrlrLuaMethodEditorTabsLF::createTabTextLayout (const TabBarButton& button, float length, float depth, Colour colour, TextLayout& textLayout)
{
    Font font (12.0f);
    font.setUnderline (button.hasKeyboardFocus (false));

    AttributedString s;
    s.setJustification (Justification::centred);
    s.append (button.getButtonText().trim(), font, colour);

    textLayout.createLayout (s, length);
}

void CtrlrLuaMethodEditorTabsLF::drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown)
{
	const Rectangle<int> activeArea (button.getActiveArea());

    const TabbedButtonBar::Orientation o = button.getTabbedButtonBar().getOrientation();

    const Colour bkg (button.getTabBackgroundColour());

    if (button.getToggleState())
    {
        g.setColour (bkg);
    }
    else
    {
        Point<int> p1, p2;

        switch (o)
        {
            case TabbedButtonBar::TabsAtBottom:   p1 = activeArea.getBottomLeft(); p2 = activeArea.getTopLeft();    break;
            case TabbedButtonBar::TabsAtTop:      p1 = activeArea.getTopLeft();    p2 = activeArea.getBottomLeft(); break;
            case TabbedButtonBar::TabsAtRight:    p1 = activeArea.getTopRight();   p2 = activeArea.getTopLeft();    break;
            case TabbedButtonBar::TabsAtLeft:     p1 = activeArea.getTopLeft();    p2 = activeArea.getTopRight();   break;
            default:                              jassertfalse; break;
        }

        g.setGradientFill (ColourGradient (bkg.brighter (0.2f), (float) p1.x, (float) p1.y,
                                           bkg.darker (0.1f),   (float) p2.x, (float) p2.y, false));
    }

    g.fillRect (activeArea);

    g.setColour (button.findColour (TabbedButtonBar::tabOutlineColourId));

    Rectangle<int> r (activeArea);

    if (o != TabbedButtonBar::TabsAtBottom)   g.fillRect (r.removeFromTop (1));
    if (o != TabbedButtonBar::TabsAtTop)      g.fillRect (r.removeFromBottom (1));
    if (o != TabbedButtonBar::TabsAtRight)    g.fillRect (r.removeFromLeft (1));
    if (o != TabbedButtonBar::TabsAtLeft)     g.fillRect (r.removeFromRight (1));

    const float alpha = button.isEnabled() ? ((isMouseOver || isMouseDown) ? 1.0f : 0.8f) : 0.3f;

    Colour col (bkg.contrasting().withMultipliedAlpha (alpha));

    if (TabbedButtonBar* bar = button.findParentComponentOfClass<TabbedButtonBar>())
    {
        TabbedButtonBar::ColourIds colID = button.isFrontTab() ? TabbedButtonBar::frontTextColourId
                                                               : TabbedButtonBar::tabTextColourId;

        if (bar->isColourSpecified (colID))
            col = bar->findColour (colID);
        else if (isColourSpecified (colID))
            col = findColour (colID);
    }

    const Rectangle<float> area (button.getTextArea().toFloat());

    float length = area.getWidth();
    float depth  = area.getHeight();

    if (button.getTabbedButtonBar().isVertical())
        std::swap (length, depth);

    TextLayout textLayout;
    createTabTextLayout (button, length, depth, col, textLayout);

    AffineTransform t;

    switch (o)
    {
        case TabbedButtonBar::TabsAtLeft:   t = t.rotated (float_Pi * -0.5f).translated (area.getX(), area.getBottom()); break;
        case TabbedButtonBar::TabsAtRight:  t = t.rotated (float_Pi *  0.5f).translated (area.getRight(), area.getY()); break;
        case TabbedButtonBar::TabsAtTop:
        case TabbedButtonBar::TabsAtBottom: t = t.translated (area.getX(), area.getY()); break;
        default:                            jassertfalse; break;
    }

    g.addTransform (t);
    textLayout.draw (g, Rectangle<float> (length, depth));
}

Rectangle <int> CtrlrLuaMethodEditorTabsLF::getTabButtonExtraComponentBounds (const TabBarButton &button, Rectangle <int> &textArea, Component &extraComp)
{
	return (Rectangle<int> (button.getWidth() - 20, 2, 20, 22));
}

// Tabbed component
CtrlrLuaMethodEditorTabs::CtrlrLuaMethodEditorTabs(CtrlrLuaMethodEditor &_owner) 
	:	owner(_owner),
		TabbedComponent(TabbedButtonBar::TabsAtTop)
{
	lf = new CtrlrLuaMethodEditorTabsLF();
	setLookAndFeel (lf);
}

CtrlrLuaMethodEditorTabs::~CtrlrLuaMethodEditorTabs()
{
	setLookAndFeel (nullptr);
	deleteAndZero (lf);
}

TabBarButton *CtrlrLuaMethodEditorTabs::createTabButton (const String &tabName, int tabIndex)
{
	TabBarButton *btn = new TabBarButton (tabName, getTabbedButtonBar());
	CtrlrMethodEditorTabCloseButton *close = new CtrlrMethodEditorTabCloseButton(owner, tabIndex);
	close->setSize (20,20);
	btn->setExtraComponent (close, TabBarButton::afterText);
	return (btn);
}

