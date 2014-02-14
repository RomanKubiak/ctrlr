#ifndef __JUCER_HEADER_CTRLRPANELVIEWPORT_CTRLRPANELVIEWPORT_E4D6072C__
#define __JUCER_HEADER_CTRLRPANELVIEWPORT_CTRLRPANELVIEWPORT_E4D6072C__

#include "CtrlrPanelCanvas.h"
#include "ViewportExt.h"

class CtrlrPanelEditor;
class CtrlrPanelViewport;
class CtrlrChildWindowStatusbar;

class CtrlrMagnifierComponent  : public Component
{
	public:
		CtrlrMagnifierComponent (Component* content_) : scaleFactor (1.0), content (content_)
		{
			addAndMakeVisible (content);
			childBoundsChanged (content);
		}

		void childBoundsChanged (Component* child)
		{
			const Rectangle<int> childArea (getLocalArea (child, child->getLocalBounds()));
			setSize (childArea.getWidth(), childArea.getHeight());
		}

		double getScaleFactor() const   { return scaleFactor; }

		void setScaleFactor (double newScale)
		{
			scaleFactor = newScale;
			transform();
		}

		void setViewedComponent (Component* content_)
		{
			removeAllChildren();
			addAndMakeVisible (content);
			childBoundsChanged (content);
		}

		void transform()
		{
			const Rectangle<int> childArea (getLocalArea (content, content->getLocalBounds()));
			content->setTransform (AffineTransform::scale ((float) scaleFactor, (float) scaleFactor));
		}

		JUCE_LEAK_DETECTOR(CtrlrMagnifierComponent)

	private:
		double scaleFactor;
		ScopedPointer<Component> content;
};

class CtrlrViewport : public ViewportExt, public KeyListener
{
	public:
		CtrlrViewport(CtrlrPanelViewport *_panelViewport);
		~CtrlrViewport();
		bool keyPressed (const KeyPress &key, Component *originatingComponent);
		bool keyStateChanged (bool isKeyDown, Component *originatingComponent);
		void mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel);

		JUCE_LEAK_DETECTOR(CtrlrViewport)

	private:
		CtrlrPanelViewport *panelViewport;
};

class CtrlrDraggerOverlayComp    : public Component
{
	public:
		CtrlrDraggerOverlayComp(CtrlrViewport *_viewport) : viewport(_viewport)
		{
			setMouseCursor (MouseCursor::DraggingHandCursor);
			setAlwaysOnTop (true);
		}

		~CtrlrDraggerOverlayComp()
		{
		}

		void mouseDown (const MouseEvent& e)
		{
			if (viewport != 0)
			{
				startX = viewport->getViewPositionX();
				startY = viewport->getViewPositionY();
			}
		}

		void mouseDrag (const MouseEvent& e)
		{
			if (viewport != 0)
			{
				viewport->setViewPosition (jlimit (0, jmax (0, viewport->getViewedComponent()->getWidth() - viewport->getViewWidth()),
												startX - e.getDistanceFromDragStartX()),
											jlimit (0, jmax (0, viewport->getViewedComponent()->getHeight() - viewport->getViewHeight()),
												startY - e.getDistanceFromDragStartY()));
			}
		}

		JUCE_LEAK_DETECTOR(CtrlrDraggerOverlayComp)

		private:
			int startX, startY;
			CtrlrViewport *viewport;
};

class CtrlrPanelViewport  : public Component
{
public:
		CtrlrPanelViewport (CtrlrPanelEditor &_owner);
		~CtrlrPanelViewport();
		CtrlrPanelCanvas *getCanvas(const int canvasIndex=0)		{ return (canvasList[canvasIndex]); }
		CtrlrPanelEditor &getOwner()								{ return (owner); }
		CtrlrMagnifierComponent *getMagnifier()						{ return (magnifier); }
		void setZoom (const double zoom, int anchorX, int anchorY);
		const double getZoom ();
		void dragKeyHeldDown (const bool isKeyDown);
		void setCurrentEditedCanvas(const int canvasIndex);
		void addCanvas(const String &canvasName="New Layer");
		void removeCanvas(const int canvasIndex);
		const int getNumCanvases();
		void moveCanvasUp(const int canvasIndex);
		void moveCanvasDown(const int canvasIndex);
		CtrlrPanelCanvas *getCurrentCanvas();
		void paint (Graphics& g);
		void resized();
		bool keyStateChanged (bool isKeyDown);
		void lookAndFeelChanged();
		
		JUCE_LEAK_DETECTOR(CtrlrPanelViewport)

	private:
		CtrlrPanelEditor &owner;
		CtrlrViewport *viewport;
		OwnedArray <CtrlrPanelCanvas> canvasList;
		CtrlrMagnifierComponent *magnifier;
		bool isSpaceDown;
		double currentZoom;
};


#endif
