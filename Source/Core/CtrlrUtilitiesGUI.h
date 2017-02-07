#ifndef CTRLR_UTILITIES_GUI
#define CTRLR_UTILITIES_GUI

#include "stdafx.h"

/** Get a Drawable from an Image **/
DrawableImage *drawableFromImage (const Image &i);
const String imageToBase64 (const Image &image);

/** Convert string to usable properties **/
void gradientFromProperty (Graphics &g, Rectangle<int> gradientBounds, const ValueTree &propertyHolder, const Identifier &gradientType, const Identifier &colour1, const Identifier &colour2);
const Justification justificationFromProperty(const var &justificationProperty);
const RectanglePlacement relativePostionFromProperty (const var &positionProperty);
MouseCursor::StandardCursorType mouseCursorFromproperty (const var &cursorProperty);
const Point<int> pointFromString(const String &pointState);
#endif
