#ifndef CTRLR_VIEWPORT_H
#define CTRLR_VIEWPORT_H

#include "JuceHeader.h"

class CtrlrViewport  : public Component,
                            private ComponentListener,
                            private ScrollBar::Listener
{
    public:
        explicit CtrlrViewport (const String& componentName = String::empty);
        ~CtrlrViewport();
        void setViewedComponent (Component* newViewedComponent, bool deleteComponentWhenNoLongerNeeded = true);
        Component* getViewedComponent() const noexcept                  { return contentComp; }
        void setViewPosition (int xPixelsOffset, int yPixelsOffset);
        void setViewPosition (const Point<int>& newPosition);
        void setViewPositionProportionately (double proportionX, double proportionY);
        bool autoScroll (int mouseX, int mouseY, int distanceFromEdge, int maximumSpeed);
        const Point<int> getViewPosition() const noexcept       { return lastVisibleArea.getPosition(); }
        int getViewPositionX() const noexcept                   { return lastVisibleArea.getX(); }
        int getViewPositionY() const noexcept                   { return lastVisibleArea.getY(); }
        int getViewWidth() const noexcept                       { return lastVisibleArea.getWidth(); }
        int getViewHeight() const noexcept                      { return lastVisibleArea.getHeight(); }
        int getMaximumVisibleWidth() const;
        int getMaximumVisibleHeight() const;
        virtual void visibleAreaChanged (const Rectangle<int>& newVisibleArea);
        void setScrollBarsShown (bool showVerticalScrollbarIfNeeded, bool showHorizontalScrollbarIfNeeded);
        bool isVerticalScrollBarShown() const noexcept              { return showVScrollbar; }
        bool isHorizontalScrollBarShown() const noexcept            { return showHScrollbar; }
        void setScrollBarThickness (int thickness);
        int getScrollBarThickness() const;
        void setSingleStepSizes (int stepX, int stepY);
        void setScrollBarButtonVisibility (bool buttonsVisible);
        ScrollBar* getVerticalScrollBar() noexcept                  { return &verticalScrollBar; }
        ScrollBar* getHorizontalScrollBar() noexcept                { return &horizontalScrollBar; }
        void resized();
        void scrollBarMoved (ScrollBar* scrollBarThatHasMoved, double newRangeStart);
        void mouseWheelMove (const MouseEvent& e, const MouseWheelDetails &wheel);
        bool keyPressed (const KeyPress& key);
        void componentMovedOrResized (Component& component, bool wasMoved, bool wasResized);
        bool useMouseWheelMoveIfNeeded (const MouseEvent& e, float wheelIncrementX, float wheelIncrementY);

    private:
        WeakReference<Component> contentComp;
        Rectangle<int> lastVisibleArea;
        int scrollBarThickness;
        int singleStepX, singleStepY;
        bool showHScrollbar, showVScrollbar, deleteContent;
        Component contentHolder;
        ScrollBar verticalScrollBar;
        ScrollBar horizontalScrollBar;

        void updateVisibleArea();
        void deleteContentComp();

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrViewport);
};


#endif   // __JUCE_VIEWPORT_JUCEHEADER__
