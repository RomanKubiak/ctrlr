#ifndef LOOK_AND_FEEL_PARAM_WRAPPER
#define LOOK_AND_FEEL_PARAM_WRAPPER

#include "CtrlrMacros.h"

struct ParamWrapper
{
	ParamWrapper(Graphics &_g, int _x, int _y, int _width, int _height, float _sliderPosProportional, float _rotaryStartAngle, float _rotaryEndAngle, Slider &_slider)
		:   g(&_g),
            x(_x),
            y(_y),
            width(_width),
            height(_height),
            sliderPosProportional(_sliderPosProportional),
            rotaryStartAngle(_rotaryStartAngle),
            rotaryEndAngle(_rotaryEndAngle),
            slider(&_slider) {}

	ParamWrapper(const String &_text, bool _isSeparator, int _standardMenuItemHeight, int &_idealWidth, int &_idealHeight)
		:   text(_text),
            isSeparator(_isSeparator),
            standardMenuItemHeight(_standardMenuItemHeight),
            idealWidth(_idealWidth),
            idealHeight(_idealHeight) {}

    /* Common */
	Graphics *g;
	int x;
	int y;
	int width;
	int height;
	String text;
	int colourId;
	Colour colour;
	Font font;
	Component *component;
	/* Common */

	/* getIdealPopupMenuItemSize */
	bool isSeparator;
	int standardMenuItemHeight;
	int idealWidth;
	int idealHeight;
    /* getIdealPopupMenuItemSize */

    /* drawRotarySlider */
	float sliderPosProportional, rotaryStartAngle, rotaryEndAngle;
	Slider *slider;
	/* drawRotarySlider */

    static void wrapForLua (lua_State *L)
    {
        using namespace luabind;
        module(L)
        [
            class_<ParamWrapper>("ParamWrapper")
                .def_readwrite ("g", &ParamWrapper::g)
                .def_readonly ("x", &ParamWrapper::x)
                .def_readonly ("y", &ParamWrapper::y)
                .def_readonly ("width", &ParamWrapper::width)
                .def_readonly ("height", &ParamWrapper::height)
                .def_readonly ("isSeparator", &ParamWrapper::isSeparator)
                .def_readonly ("standardMenuItemHeight", &ParamWrapper::standardMenuItemHeight)
                .def_readonly ("sliderPosProportional", &ParamWrapper::sliderPosProportional)
                .def_readonly ("rotaryStartAngle", &ParamWrapper::rotaryStartAngle)
                .def_readonly ("rotaryEndAngle", &ParamWrapper::rotaryEndAngle)
                .def_readwrite ("slider", &ParamWrapper::slider)
                .def_readwrite ("idealWidth", &ParamWrapper::idealWidth)
                .def_readwrite ("idealHeight", &ParamWrapper::idealHeight)
        ];
    }
};

#endif
