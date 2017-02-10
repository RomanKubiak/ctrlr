#ifndef __JUCER_HEADER_CTRLRCUSTOMBUTTONINTERNAL_CTRLRCUSTOMBUTTONINTERNAL_1CA0CFDB__
#define __JUCER_HEADER_CTRLRCUSTOMBUTTONINTERNAL_CTRLRCUSTOMBUTTONINTERNAL_1CA0CFDB__

#include "CtrlrMacros.h"
class CtrlrImageButton;

class CtrlrCustomButtonInternal  : public Button
{
public:
    //==============================================================================
    CtrlrCustomButtonInternal (CtrlrImageButton &_owner);
    ~CtrlrCustomButtonInternal();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void setImage (const Image imageToSet, const int _frameWidth, const int _frameHeight);
	void setPaintMode(const RectanglePlacement _paintMode);
	void setOrientation(const bool _isVertical)						{ isVertical = _isVertical; }

	Rectangle<int> getFrameCoordsFromStrip(const bool isMouseOver, const bool isMouseDown);
	const Rectangle<int> getFrameDestinationRect();
	void drawFrame(Graphics &g, const Rectangle<int> &destinationRect, const bool isMouseOver, const bool isMouseDown);
	void drawTextBoxText(Graphics &g, const Rectangle<int> &frameRect, const Rectangle<int> &totalAreaToDraw);
	const bool getMouseOverMode();
    //[/UserMethods]

    void resized();
    void paintButton (Graphics& g, bool isMouseOverButton, bool isButtonDown);

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CtrlrImageButton &owner;
	int frameHeight;
	int frameWidth;
	Image filmStripImage;
	Array <Rectangle<int> > possibleValues;
	RectanglePlacement paintMode;
	bool isVertical;
    //[/UserVariables]

    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrCustomButtonInternal (const CtrlrCustomButtonInternal&);
    const CtrlrCustomButtonInternal& operator= (const CtrlrCustomButtonInternal&);
};


#endif   // __JUCER_HEADER_CTRLRCUSTOMBUTTONINTERNAL_CTRLRCUSTOMBUTTONINTERNAL_1CA0CFDB__
