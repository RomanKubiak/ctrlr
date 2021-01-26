#include "stdafx.h"
#include "CtrlrViewport.h"


//==============================================================================
CtrlrViewport::CtrlrViewport (const String& componentName)
  : Component (componentName),
    scrollBarThickness (0),
    singleStepX (16),
    singleStepY (16),
    showHScrollbar (true),
    showVScrollbar (true),
    deleteContent (true),
    verticalScrollBar (true),
    horizontalScrollBar (false)
{
    // content holder is used to clip the contents so they don't overlap the scrollbars
    addAndMakeVisible (&contentHolder);
    contentHolder.setInterceptsMouseClicks (false, true);

    addChildComponent (&verticalScrollBar);
    addChildComponent (&horizontalScrollBar);

    verticalScrollBar.addListener (this);
    horizontalScrollBar.addListener (this);

    setInterceptsMouseClicks (false, true);
    setWantsKeyboardFocus (true);
}

CtrlrViewport::~CtrlrViewport()
{
    deleteContentComp();
}

//==============================================================================
void CtrlrViewport::visibleAreaChanged (const Rectangle<int>&)
{
}

//==============================================================================
void CtrlrViewport::deleteContentComp()
{
    if (deleteContent)
    {
        // This sets the content comp to a null pointer before deleting the old one, in case
        // anything tries to use the old one while it's in mid-deletion..
        ScopedPointer<Component> oldCompDeleter (contentComp);
        contentComp = nullptr;
    }
    else
    {
        contentComp = nullptr;
    }
}

void CtrlrViewport::setViewedComponent (Component* const newViewedComponent, const bool deleteComponentWhenNoLongerNeeded)
{
    if (contentComp.get() != newViewedComponent)
    {
        deleteContentComp();
        contentComp = newViewedComponent;
        deleteContent = deleteComponentWhenNoLongerNeeded;

        if (contentComp != nullptr)
        {
            contentHolder.addAndMakeVisible (contentComp);
            setViewPosition (0, 0);
            contentComp->addComponentListener (this);
        }

        updateVisibleArea();
    }
}

int CtrlrViewport::getMaximumVisibleWidth() const    { return contentHolder.getWidth(); }
int CtrlrViewport::getMaximumVisibleHeight() const   { return contentHolder.getHeight(); }

void CtrlrViewport::setViewPosition (const int xPixelsOffset, const int yPixelsOffset)
{
    if (contentComp != nullptr)
        contentComp->setTopLeftPosition (jmax (jmin (0, contentHolder.getWidth() - contentComp->getWidth()), jmin (0, -xPixelsOffset)),
                                         jmax (jmin (0, contentHolder.getHeight() - contentComp->getHeight()), jmin (0, -yPixelsOffset)));
}

void CtrlrViewport::setViewPosition (const Point<int>& newPosition)
{
    setViewPosition (newPosition.getX(), newPosition.getY());
}

void CtrlrViewport::setViewPositionProportionately (const double x, const double y)
{
    if (contentComp != nullptr)
        setViewPosition (jmax (0, roundToInt (x * (contentComp->getWidth() - getWidth()))),
                         jmax (0, roundToInt (y * (contentComp->getHeight() - getHeight()))));
}

bool CtrlrViewport::autoScroll (const int mouseX, const int mouseY, const int activeBorderThickness, const int maximumSpeed)
{
    if (contentComp != nullptr)
    {
        int dx = 0, dy = 0;

        if (horizontalScrollBar.isVisible() || contentComp->getX() < 0 || contentComp->getRight() > getWidth())
        {
            if (mouseX < activeBorderThickness)
                dx = activeBorderThickness - mouseX;
            else if (mouseX >= contentHolder.getWidth() - activeBorderThickness)
                dx = (contentHolder.getWidth() - activeBorderThickness) - mouseX;

            if (dx < 0)
                dx = jmax (dx, -maximumSpeed, contentHolder.getWidth() - contentComp->getRight());
            else
                dx = jmin (dx, maximumSpeed, -contentComp->getX());
        }

        if (verticalScrollBar.isVisible() || contentComp->getY() < 0 || contentComp->getBottom() > getHeight())
        {
            if (mouseY < activeBorderThickness)
                dy = activeBorderThickness - mouseY;
            else if (mouseY >= contentHolder.getHeight() - activeBorderThickness)
                dy = (contentHolder.getHeight() - activeBorderThickness) - mouseY;

            if (dy < 0)
                dy = jmax (dy, -maximumSpeed, contentHolder.getHeight() - contentComp->getBottom());
            else
                dy = jmin (dy, maximumSpeed, -contentComp->getY());
        }

        if (dx != 0 || dy != 0)
        {
            contentComp->setTopLeftPosition (contentComp->getX() + dx,
                                             contentComp->getY() + dy);

            return true;
        }
    }

    return false;
}

void CtrlrViewport::componentMovedOrResized (Component&, bool, bool)
{
    updateVisibleArea();
}

void CtrlrViewport::resized()
{
    updateVisibleArea();
}

//==============================================================================
void CtrlrViewport::updateVisibleArea()
{
    const int scrollbarWidth = getScrollBarThickness();
    const bool canShowAnyBars = getWidth() > scrollbarWidth && getHeight() > scrollbarWidth;
    const bool canShowHBar = showHScrollbar && canShowAnyBars;
    const bool canShowVBar = showVScrollbar && canShowAnyBars;

    bool hBarVisible = canShowHBar && ! horizontalScrollBar.autoHides();
    bool vBarVisible = canShowVBar && ! verticalScrollBar.autoHides();

    Rectangle<int> contentArea (getLocalBounds());

    if (contentComp != nullptr && ! contentArea.contains (contentComp->getBounds()))
    {
        hBarVisible = canShowHBar && (hBarVisible || contentComp->getX() < 0 || contentComp->getRight() > contentArea.getWidth());
        vBarVisible = canShowVBar && (vBarVisible || contentComp->getY() < 0 || contentComp->getBottom() > contentArea.getHeight());

        if (vBarVisible)
            contentArea.setWidth (getWidth() - scrollbarWidth);

        if (hBarVisible)
            contentArea.setHeight (getHeight() - scrollbarWidth);

        if (! contentArea.contains (contentComp->getBounds()))
        {
            hBarVisible = canShowHBar && (hBarVisible || contentComp->getRight() > contentArea.getWidth());
            vBarVisible = canShowVBar && (vBarVisible || contentComp->getBottom() > contentArea.getHeight());
        }
    }

    if (vBarVisible)
        contentArea.setWidth (getWidth() - scrollbarWidth);

    if (hBarVisible)
        contentArea.setHeight (getHeight() - scrollbarWidth);

    contentHolder.setBounds (contentArea);

    Rectangle<int> contentBounds;
    if (contentComp != nullptr)
        contentBounds = contentHolder.getLocalArea (contentComp, contentComp->getLocalBounds());

    Point<int> visibleOrigin (-contentBounds.getPosition());

    if (hBarVisible)
    {
        horizontalScrollBar.setBounds (0, contentArea.getHeight(), contentArea.getWidth(), scrollbarWidth);
        horizontalScrollBar.setRangeLimits (0.0, contentBounds.getWidth());
        horizontalScrollBar.setCurrentRange (visibleOrigin.getX(), contentArea.getWidth());
        horizontalScrollBar.setSingleStepSize (singleStepX);
        // horizontalScrollBar.cancelPendingUpdate();
    }
    else if (canShowHBar)
    {
        visibleOrigin.setX (0);
    }

    if (vBarVisible)
    {
        verticalScrollBar.setBounds (contentArea.getWidth(), 0, scrollbarWidth, contentArea.getHeight());
        verticalScrollBar.setRangeLimits (0.0, contentBounds.getHeight());
        verticalScrollBar.setCurrentRange (visibleOrigin.getY(), contentArea.getHeight());
        verticalScrollBar.setSingleStepSize (singleStepY);
        // verticalScrollBar.cancelPendingUpdate();
    }
    else if (canShowVBar)
    {
        visibleOrigin.setY (0);
    }

    // Force the visibility *after* setting the ranges to avoid flicker caused by edge conditions in the numbers.
    horizontalScrollBar.setVisible (hBarVisible);
    verticalScrollBar.setVisible (vBarVisible);

    setViewPosition (visibleOrigin);

    const Rectangle<int> visibleArea (visibleOrigin.getX(), visibleOrigin.getY(),
                                      jmin (contentBounds.getWidth() - visibleOrigin.getX(),  contentArea.getWidth()),
                                      jmin (contentBounds.getHeight() - visibleOrigin.getY(), contentArea.getHeight()));

    if (lastVisibleArea != visibleArea)
    {
        lastVisibleArea = visibleArea;
        visibleAreaChanged (visibleArea);
    }

    // horizontalScrollBar.handleUpdateNowIfNeeded();
    // verticalScrollBar.handleUpdateNowIfNeeded();
}

//==============================================================================
void CtrlrViewport::setSingleStepSizes (const int stepX, const int stepY)
{
    if (singleStepX != stepX || singleStepY != stepY)
    {
        singleStepX = stepX;
        singleStepY = stepY;
        updateVisibleArea();
    }
}

void CtrlrViewport::setScrollBarsShown (const bool showVerticalScrollbarIfNeeded,
                                   const bool showHorizontalScrollbarIfNeeded)
{
    if (showVScrollbar != showVerticalScrollbarIfNeeded
         || showHScrollbar != showHorizontalScrollbarIfNeeded)
    {
        showVScrollbar = showVerticalScrollbarIfNeeded;
        showHScrollbar = showHorizontalScrollbarIfNeeded;
        updateVisibleArea();
    }
}

void CtrlrViewport::setScrollBarThickness (const int thickness)
{
    if (scrollBarThickness != thickness)
    {
        scrollBarThickness = thickness;
        updateVisibleArea();
    }
}

int CtrlrViewport::getScrollBarThickness() const
{
    return scrollBarThickness > 0 ? scrollBarThickness
                                  : getLookAndFeel().getDefaultScrollbarWidth();
}

void CtrlrViewport::setScrollBarButtonVisibility (const bool /* buttonsVisible */)
{
    // verticalScrollBar.setButtonVisibility (buttonsVisible);
    // horizontalScrollBar.setButtonVisibility (buttonsVisible);
}

void CtrlrViewport::scrollBarMoved (ScrollBar* scrollBarThatHasMoved, double newRangeStart)
{
    const int newRangeStartInt = roundToInt (newRangeStart);

    if (scrollBarThatHasMoved == &horizontalScrollBar)
    {
        setViewPosition (newRangeStartInt, getViewPositionY());
    }
    else if (scrollBarThatHasMoved == &verticalScrollBar)
    {
        setViewPosition (getViewPositionX(), newRangeStartInt);
    }
}

void CtrlrViewport::mouseWheelMove (const MouseEvent& e, const MouseWheelDetails &wheel)
{
	if (! useMouseWheelMoveIfNeeded (e, wheel.deltaX, wheel.deltaY))
        Component::mouseWheelMove (e, wheel);
}

bool CtrlrViewport::useMouseWheelMoveIfNeeded (const MouseEvent& e, float wheelIncrementX, float wheelIncrementY)
{
    if (! (e.mods.isAltDown() || e.mods.isCtrlDown()))
    {
        const bool hasVertBar = verticalScrollBar.isVisible();
        const bool hasHorzBar = horizontalScrollBar.isVisible();

        if (hasHorzBar || hasVertBar)
        {
            if (wheelIncrementX != 0)
            {
                wheelIncrementX *= 14.0f * singleStepX;
                wheelIncrementX = (wheelIncrementX < 0) ? jmin (wheelIncrementX, -1.0f)
                                                        : jmax (wheelIncrementX, 1.0f);
            }

            if (wheelIncrementY != 0)
            {
                wheelIncrementY *= 14.0f * singleStepY;
                wheelIncrementY = (wheelIncrementY < 0) ? jmin (wheelIncrementY, -1.0f)
                                                        : jmax (wheelIncrementY, 1.0f);
            }

            Point<int> pos (getViewPosition());

            if (wheelIncrementX != 0 && wheelIncrementY != 0 && hasHorzBar && hasVertBar)
            {
                pos.setX (pos.getX() - roundToInt (wheelIncrementX));
                pos.setY (pos.getY() - roundToInt (wheelIncrementY));
            }
            else if (hasHorzBar && (wheelIncrementX != 0 || e.mods.isShiftDown() || ! hasVertBar))
            {
                if (wheelIncrementX == 0 && ! hasVertBar)
                    wheelIncrementX = wheelIncrementY;

                pos.setX (pos.getX() - roundToInt (wheelIncrementX));
            }
            else if (hasVertBar && wheelIncrementY != 0)
            {
                pos.setY (pos.getY() - roundToInt (wheelIncrementY));
            }

            if (pos != getViewPosition())
            {
                setViewPosition (pos);
                return true;
            }
        }
    }

    return false;
}

bool CtrlrViewport::keyPressed (const KeyPress&)
{
	return false;
	/*
    const bool isUpDownKey = key.isKeyCode (KeyPress::upKey)
                                || key.isKeyCode (KeyPress::downKey)
                                || key.isKeyCode (KeyPress::pageUpKey)
                                || key.isKeyCode (KeyPress::pageDownKey)
                                || key.isKeyCode (KeyPress::homeKey)
                                || key.isKeyCode (KeyPress::endKey);

    if (verticalScrollBar.isVisible() && isUpDownKey)
        return verticalScrollBar.keyPressed (key);

    const bool isLeftRightKey = key.isKeyCode (KeyPress::leftKey)
                                 || key.isKeyCode (KeyPress::rightKey);

    if (horizontalScrollBar.isVisible() && (isUpDownKey || isLeftRightKey))
        return horizontalScrollBar.keyPressed (key);

    return false;
	*/
}
