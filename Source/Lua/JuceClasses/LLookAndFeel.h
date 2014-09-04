#ifndef L_LOOK_AND_FEEL
#define L_LOOK_AND_FEEL

#include "CtrlrLuaManager.h"
#include "CtrlrLog.h"

class LLookAndFeel : public LookAndFeel_V3, public luabind::wrap_base
{
	public:
	    LLookAndFeel();
		static void wrapForLua (lua_State *L);
        virtual int method (int param1, int param2)
        {
            _DBG("method");
            call<int> ("method", param1, param2);
        }

        static int def_method (LLookAndFeel *ptr, int param1, int param2)
        {
            _DBG("def_method");
            return (ptr->LLookAndFeel::method (param1, param2));
        }
		/*virtual Colour findColour (int colourId) override
			{ return (call<Colour>("findColour", colourId)); }
		static Colour def_findColour (LookAndFeel_V3 *ptr, int colourId)
			{ return (ptr->LookAndFeel_V3::findColour (colourId)); }

		virtual void setColour (int colourId, Colour colour) override
			{ call<void>("setColour", colourId, colour); }
		static void def_setColour (LookAndFeel_V3 *ptr, int colourId, Colour colour)
			{ return (ptr->LookAndFeel_V3::setColour (colourId, colour)); }

		virtual bool isColourSpecified (Graphics &g, int colourId) override
			{ return (call<bool>("isColourSpecified", colourId)); }
		static bool def_isColourSpecified (LookAndFeel_V3 *ptr, int colourId)
			{ return (ptr->LookAndFeel_V3::isColourSpecified (colourId)); }

		virtual Typeface::Ptr getTypefaceForFont (const Font &font) override
			{ return (call<Typeface::Ptr>("getTypefaceForFont", font)); }
		static Typeface::Ptr def_getTypefaceForFont (LookAndFeel_V3 *ptr, const Font &font)
			{ return (ptr->LookAndFeel_V3::getTypefaceForFont (font)); }

		virtual void setDefaultSansSerifTypefaceName (const String &newName) override
			{ call<void>("setDefaultSansSerifTypefaceName", newName); }
		static void def_setDefaultSansSerifTypefaceName (LookAndFeel_V3 *ptr, const String &newName)
			{ return (ptr->LookAndFeel_V3::setDefaultSansSerifTypefaceName (newName)); }

		virtual MouseCursor getMouseCursorFor (Component &component) override
			{ return (call<MouseCursor>("getMouseCursorFor", boost::ref(component))); }
		static MouseCursor def_getMouseCursorFor (LookAndFeel_V3 *ptr, Component &component)
			{ return (ptr->LookAndFeel_V3::getMouseCursorFor (component)); }

		virtual void drawButtonBackground (Graphics &g, Button &b, const Colour &c, bool over, bool down) override
			{ call<void>("drawButtonBackground", boost::ref (g), boost::ref(b), c, over, down); }
		static void def_drawButtonBackground (LookAndFeel_V3 *ptr, Graphics &g, Button &b, const Colour &c, bool over, bool down)
			{ return (ptr->LookAndFeel_V3::drawButtonBackground (g,b,c,over,down)); }
        */

    private:
        luabind::object self;
};

#endif
