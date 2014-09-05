#ifndef L_LOOK_AND_FEEL
#define L_LOOK_AND_FEEL

#include "CtrlrLuaManager.h"
#include "CtrlrLog.h"

class LLookAndFeel_V3 : public LookAndFeel_V3, public luabind::wrap_base
{
	public:
	    LLookAndFeel_V3() : LookAndFeel_V3() {}
		static void wrapForLua (lua_State *L);

        virtual Colour findColour (int colourId) override
        { return (call<Colour>("findColour", colourId)); }
        static Colour def_findColour (LookAndFeel_V3 *ptr, int colourId)
        { return (ptr->LookAndFeel_V3::findColour (colourId)); }

        virtual void setColour (int colourId, Colour colour) override
        { call<void>("setColour", colourId, colour); }
        static void def_setColour (LookAndFeel_V3 *ptr, int colourId, Colour colour)
        { return (ptr->LookAndFeel_V3::setColour (colourId, colour)); }

        virtual bool isColourSpecified (int colourId) override
        { return (call<bool>("isColourSpecified", colourId)); }
        static bool def_isColourSpecified (LookAndFeel_V3 *ptr, int colourId)
        { return (ptr->LookAndFeel_V3::isColourSpecified (colourId)); }

        virtual Typeface::Ptr getTypefaceForFont (const Font &font) override
        { return (call<Typeface::Ptr>("getTypefaceForFont", font)); }
        static Typeface::Ptr def_getTypefaceForFont (LookAndFeel_V3 *ptr, const Font &font)
        { return (ptr->LookAndFeel_V3::getTypefaceForFont (font)); }

        virtual MouseCursor getMouseCursorFor (Component &component) override
        { /* This is causing crashes !!! */
            try
            {
                MouseCursor mc (call<MouseCursor>("getMouseCursorFor", boost::ref(component)));

                return (mc);
            }
            catch (...)
            {
                return (component.getMouseCursor());
            }
        }

        static MouseCursor def_getMouseCursorFor (LookAndFeel_V3 *ptr, Component &component)
        { return (ptr->LookAndFeel_V3::getMouseCursorFor (component)); }

		virtual void drawButtonBackground (Graphics &g, Button &b, const Colour &c, bool over, bool down) override
        { call<void>("drawButtonBackground", boost::ref (g), boost::ref(b), c, over, down); }
        static void def_drawButtonBackground (LookAndFeel_V3 *ptr, Graphics &g, Button &b, const Colour &c, bool over, bool down)
        { return (ptr->LookAndFeel_V3::drawButtonBackground (g,b,c,over,down)); }

        virtual void drawButtonText (Graphics &g, TextButton &button, bool isMouseOverButton, bool isButtonDown) override
        { call<void>("drawButtonText", boost::ref(g), boost::ref(button), isMouseOverButton, isButtonDown); }
        static void def_drawButtonText (LookAndFeel_V3 *ptr, Graphics &g, TextButton &button, bool isMouseOverButton, bool isButtonDown)
        { return (ptr->LookAndFeel_V3::drawButtonText (g, button, isMouseOverButton, isButtonDown)); }

        virtual void drawToggleButton (Graphics &g, ToggleButton &button, bool isMouseOverButton, bool isButtonDown) override
        { call<void>("drawToggleButton", boost::ref(g), boost::ref(button), isMouseOverButton, isButtonDown); }
        static void def_drawToggleButton (LookAndFeel_V3 *ptr, Graphics &g, ToggleButton &button, bool isMouseOverButton, bool isButtonDown)
        { return (ptr->LookAndFeel_V3::drawToggleButton (g, button, isMouseOverButton, isButtonDown)); }

        virtual void changeToggleButtonWidthToFitText (ToggleButton &button) override
        { call<void>("changeToggleButtonWidthToFitText", boost::ref(button)); }
        static void def_changeToggleButtonWidthToFitText (LookAndFeel_V3 *ptr, ToggleButton &button)
        { return (ptr->LookAndFeel_V3::changeToggleButtonWidthToFitText (button)); }

        virtual void drawTickBox (Graphics &g, Component &component, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown) override
        { call<void>("drawTickBox", boost::ref(g), boost::ref(component), x, y, w, h, ticked, isEnabled, isMouseOverButton, isButtonDown); }
        static void def_drawTickBox (LookAndFeel_V3 *ptr, Graphics &g, Component &component, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown)
        { return (ptr->LookAndFeel_V3::drawTickBox (g, component, x, y, w, h, ticked, isEnabled, isMouseOverButton, isButtonDown)); }

        virtual AlertWindow *createAlertWindow (const String &title, const String &message, const String &button1, const String &button2, const String &button3, AlertWindow::AlertIconType iconType, int numButtons, Component *associatedComponent) override
        { return (call<AlertWindow *>("createAlertWindow", title, message, button1, button2, button3, iconType, numButtons, associatedComponent)); }
        static AlertWindow * def_createAlertWindow (LookAndFeel_V3 *ptr, const String &title, const String &message, const String &button1, const String &button2, const String &button3, AlertWindow::AlertIconType iconType, int numButtons, Component *associatedComponent)
        { return (ptr->LookAndFeel_V3::createAlertWindow (title, message, button1, button2, button3, iconType, numButtons, associatedComponent)); }

        virtual void drawAlertBox (Graphics &g, AlertWindow &window, const Rectangle<int> &textArea, TextLayout &layout) override
        { call<void>("drawAlertBox", boost::ref(g), boost::ref(window), textArea, layout); }
        static void def_drawAlertBox (LookAndFeel_V3 *ptr, Graphics &g, AlertWindow &window, const Rectangle<int> &textArea, TextLayout &layout)
        { return (ptr->LookAndFeel_V3::drawAlertBox (g, window, textArea, layout)); }

        virtual int getAlertBoxWindowFlags () override
        { return (call<int>("getAlertBoxWindowFlags")); }
        static int def_getAlertBoxWindowFlags (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::getAlertBoxWindowFlags ()); }

        virtual int getAlertWindowButtonHeight () override
        { return (call<int>("getAlertWindowButtonHeight")); }
        static int def_getAlertWindowButtonHeight (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::getAlertWindowButtonHeight ()); }

        virtual Font getAlertWindowMessageFont () override
        { return (call<Font>("getAlertWindowMessageFont")); }
        static Font def_getAlertWindowMessageFont (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::getAlertWindowMessageFont ()); }

        virtual Font getAlertWindowFont () override
        { return (call<Font>("getAlertWindowFont")); }
        static Font def_getAlertWindowFont (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::getAlertWindowFont ()); }

        virtual void drawProgressBar (Graphics &g, ProgressBar &bar, int width, int height, double progress, const String &textToShow) override
        { call<void>("drawProgressBar", boost::ref(g), boost::ref(bar), width, height, progress, textToShow); }
        static void def_drawProgressBar (LookAndFeel_V3 *ptr, Graphics &g, ProgressBar &bar, int width, int height, double progress, const String &textToShow)
        { return (ptr->LookAndFeel_V3::drawProgressBar (g, bar, width, height, progress, textToShow)); }

        virtual void drawSpinningWaitAnimation (Graphics &g, const Colour &colour, int x, int y, int w, int h) override
        { call<void>("drawSpinningWaitAnimation", boost::ref(g), colour, x, y, w, h); }
        static void def_drawSpinningWaitAnimation (LookAndFeel_V3 *ptr, Graphics &g, const Colour &colour, int x, int y, int w, int h)
        { return (ptr->LookAndFeel_V3::drawSpinningWaitAnimation (g, colour, x, y, w, h)); }

        virtual bool areScrollbarButtonsVisible () override
        { call<bool>("areScrollbarButtonsVisible"); }
        static bool def_areScrollbarButtonsVisible (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::areScrollbarButtonsVisible ()); }

        virtual ImageEffectFilter *getScrollbarEffect () override
        { call<ImageEffectFilter*>("getScrollbarEffect"); }
        static ImageEffectFilter *def_getScrollbarEffect (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::getScrollbarEffect ()); }

        virtual int getMinimumScrollbarThumbSize (ScrollBar &bar) override
        { call<int>("getMinimumScrollbarThumbSize", boost::ref(bar)); }
        static int def_getMinimumScrollbarThumbSize (LookAndFeel_V3 *ptr, ScrollBar &bar)
        { return (ptr->LookAndFeel_V3::getMinimumScrollbarThumbSize (bar)); }

        virtual int getDefaultScrollbarWidth () override
        { call<int>("getDefaultScrollbarWidth"); }
        static int def_getDefaultScrollbarWidth (LookAndFeel_V3 *ptr)
        { return (ptr->LookAndFeel_V3::getDefaultScrollbarWidth ()); }

        virtual int getScrollbarButtonSize (ScrollBar &bar) override
        { call<int>("getScrollbarButtonSize", boost::ref(bar)); }
        static int def_getScrollbarButtonSize (LookAndFeel_V3 *ptr, ScrollBar &bar)
        { return (ptr->LookAndFeel_V3::getScrollbarButtonSize (bar)); }

        virtual Path getTickShape (float height) override
        { call<Path>("getTickShape", height); }
        static Path def_getTickShape (LookAndFeel_V3 *ptr, float height)
        { return (ptr->LookAndFeel_V3::getTickShape (height)); }

        virtual Path getCrossShape (float height) override
        { call<Path>("getCrossShape", height); }
        static Path def_getCrossShape (LookAndFeel_V3 *ptr, float height)
        { return (ptr->LookAndFeel_V3::getCrossShape (height)); }

        virtual void drawTreeviewPlusMinusBox (Graphics &g, const Rectangle<float> &area, Colour backgroundColour, bool isOpen, bool isMouseOver) override
        { call<void>("drawTreeviewPlusMinusBox", boost::ref(g), area, backgroundColour, isOpen, isMouseOver); }
        static void def_drawTreeviewPlusMinusBox (LookAndFeel_V3 *ptr, Graphics &g, const Rectangle<float> &area, Colour backgroundColour, bool isOpen, bool isMouseOver)
        { return (ptr->LookAndFeel_V3::drawTreeviewPlusMinusBox (g, area, backgroundColour, isOpen, isMouseOver)); }

        virtual void fillTextEditorBackground (Graphics &g, int width, int height, TextEditor &editor) override
        { call<void>("fillTextEditorBackground", boost::ref(g), width, height, boost::ref(editor)); }
        static void def_fillTextEditorBackground (LookAndFeel_V3 *ptr, Graphics &g, int width, int height, TextEditor &editor)
        { return (ptr->LookAndFeel_V3::fillTextEditorBackground (g, width, height, editor)); }

        virtual void drawTextEditorOutline (Graphics &g, int width, int height, TextEditor &editor) override
        { call<void>("drawTextEditorOutline", boost::ref(g), width, height, boost::ref(editor)); }
        static void def_drawTextEditorOutline (LookAndFeel_V3 *ptr, Graphics &g, int width, int height, TextEditor &editor)
        { return (ptr->LookAndFeel_V3::drawTextEditorOutline (g, width, height, editor)); }
};

#endif
