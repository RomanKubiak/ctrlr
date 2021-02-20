/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2020 - Raw Material Software Limited

   JUCE is an open source library subject to commercial or open-source
   licensing.

   By using JUCE, you agree to the terms of both the JUCE 6 End-User License
   Agreement and JUCE Privacy Policy (both effective as of the 16th June 2020).

   End User License Agreement: www.juce.com/juce-6-licence
   Privacy Policy: www.juce.com/juce-privacy-policy

   Or: You may also use this code under the terms of the GPL v3 (see
   www.gnu.org/licenses).

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

namespace juce
{


//==============================================================================
/**
    Represents a colour, also including a transparency value.

    The colour is stored internally as unsigned 8-bit red, green, blue and alpha values.

    @tags{Graphics}
*/
class JUCE_API  Colour
{
public:
    //==============================================================================
    /** Creates a transparent black colour. */
    Colour() = default;

    /** Creates a copy of another Colour object. */
    Colour (const Colour&) = default;

    /** Creates a colour from a 32-bit ARGB value.

        The format of this number is:
            ((alpha << 24) | (red << 16) | (green << 8) | blue).

        All components in the range 0x00 to 0xff.
        An alpha of 0x00 is completely transparent, alpha of 0xff is opaque.

        @see getPixelARGB
    */
    explicit constexpr Colour (uint32 col) noexcept;


    /** Creates an opaque colour using 8-bit red, green and blue values */
    constexpr Colour (uint8 red,
		      uint8 green,
		      uint8 blue) noexcept;

    /** Creates an opaque colour using 8-bit red, green and blue values */
    static constexpr  Colour fromRGB (uint8 red,
				      uint8 green,
				      uint8 blue) noexcept;

    /** Creates a colour using 8-bit red, green, blue and alpha values. */
    constexpr Colour (uint8 red,
		      uint8 green,
		      uint8 blue,
		      uint8 alpha) noexcept;

    /** Creates a colour using 8-bit red, green, blue and alpha values. */
    static constexpr Colour fromRGBA (uint8 red,
				      uint8 green,
				      uint8 blue,
				      uint8 alpha) noexcept;

    /** Creates a colour from 8-bit red, green, and blue values, and a floating-point alpha.

        Alpha of 0.0 is transparent, alpha of 1.0f is opaque.
        Values outside the valid range will be clipped.
    */
    constexpr Colour (uint8 red,
		      uint8 green,
		      uint8 blue,
		      float alpha) noexcept;

    /** Creates a colour using floating point red, green, blue and alpha values.
        Numbers outside the range 0..1 will be clipped.
    */
    static constexpr Colour fromFloatRGBA (float red,
					   float green,
					   float blue,
					   float alpha) noexcept;

    /** Creates a colour using floating point hue, saturation and brightness values, and an 8-bit alpha.

        The floating point values must be between 0.0 and 1.0.
        An alpha of 0x00 is completely transparent, alpha of 0xff is opaque.
        Values outside the valid range will be clipped.
    */
    constexpr Colour (float hue,
		      float saturation,
		      float brightness,
		      uint8 alpha) noexcept;

    /** Creates a colour using floating point hue, saturation, brightness and alpha values.

        All values must be between 0.0 and 1.0.
        Numbers outside the valid range will be clipped.
    */
    constexpr Colour (float hue,
		      float saturation,
		      float brightness,
		      float alpha) noexcept;

    /** Creates a colour using floating point hue, saturation, brightness and alpha values.

        All values must be between 0.0 and 1.0.
        Numbers outside the valid range will be clipped.
    */
    static constexpr  Colour fromHSV (float hue,
				      float saturation,
				      float brightness,
				      float alpha) noexcept;

    /** Creates a colour using floating point hue, saturation, lightness and alpha values.

        All values must be between 0.0 and 1.0.
        Numbers outside the valid range will be clipped.
    */
    static constexpr Colour fromHSL (float hue,
				     float saturation,
				     float lightness,
				     float alpha) noexcept;

    /** Creates a colour using a PixelARGB object. This function assumes that the argb pixel is
        not premultiplied.
     */
    constexpr Colour (PixelARGB argb) noexcept;

    /** Creates a colour using a PixelRGB object.
     */
    constexpr Colour (PixelRGB rgb) noexcept;

    /** Creates a colour using a PixelAlpha object.
     */
    constexpr Colour (PixelAlpha alpha) noexcept;

    /** Destructor. */
    ~Colour() = default;

    /** Copies another Colour object. */
    Colour& operator= (const Colour&) = default;

    /** Compares two colours. */
    bool operator== (const Colour& other) const noexcept;
    /** Compares two colours. */
    bool operator!= (const Colour& other) const noexcept;

    //==============================================================================
    /** Returns the red component of this colour.
        @returns a value between 0x00 and 0xff.
    */
    constexpr uint8 getRed() const noexcept                       { return argb.getRed(); }

    /** Returns the green component of this colour.
        @returns a value between 0x00 and 0xff.
    */
    constexpr uint8 getGreen() const noexcept                     { return argb.getGreen(); }

    /** Returns the blue component of this colour.
        @returns a value between 0x00 and 0xff.
    */
    constexpr uint8 getBlue() const noexcept                      { return argb.getBlue(); }

    /** Returns the red component of this colour as a floating point value.
        @returns a value between 0.0 and 1.0
    */
    constexpr float getFloatRed() const noexcept;

    /** Returns the green component of this colour as a floating point value.
        @returns a value between 0.0 and 1.0
    */
    constexpr float getFloatGreen() const noexcept;

    /** Returns the blue component of this colour as a floating point value.
        @returns a value between 0.0 and 1.0
    */
    constexpr float getFloatBlue() const noexcept;

    /** Returns a premultiplied ARGB pixel object that represents this colour.
    */
    constexpr const PixelARGB getPixelARGB() const noexcept;

    /** Returns a 32-bit integer that represents this colour.

        The format of this number is:
            ((alpha << 24) | (red << 16) | (green << 8) | blue).
    */
    constexpr uint32 getARGB() const noexcept;

    //==============================================================================
    /** Returns the colour's alpha (opacity).

        Alpha of 0x00 is completely transparent, 0xff is completely opaque.
    */
    constexpr uint8 getAlpha() const noexcept                     { return argb.getAlpha(); }

    /** Returns the colour's alpha (opacity) as a floating point value.

        Alpha of 0.0 is completely transparent, 1.0 is completely opaque.
    */
    constexpr float getFloatAlpha() const noexcept;

    /** Returns true if this colour is completely opaque.

        Equivalent to (getAlpha() == 0xff).
    */
    bool isOpaque() const noexcept;

    /** Returns true if this colour is completely transparent.

        Equivalent to (getAlpha() == 0x00).
    */
    bool isTransparent() const noexcept;

    /** Returns a colour that's the same colour as this one, but with a new alpha value. */
    Colour withAlpha (uint8 newAlpha) const noexcept;

    /** Returns a colour that's the same colour as this one, but with a new alpha value. */
    Colour withAlpha (float newAlpha) const noexcept;

    /** Returns a colour that's the same colour as this one, but with a modified alpha value.
        The new colour's alpha will be this object's alpha multiplied by the value passed-in.
    */
    Colour withMultipliedAlpha (float alphaMultiplier) const noexcept;

    //==============================================================================
    /** Returns a colour that is the result of alpha-compositing a new colour over this one.
        If the foreground colour is semi-transparent, it is blended onto this colour accordingly.
    */
    Colour overlaidWith (Colour foregroundColour) const noexcept;

    /** Returns a colour that lies somewhere between this one and another.
        If amountOfOther is zero, the result is 100% this colour, if amountOfOther
        is 1.0, the result is 100% of the other colour.
    */
    Colour interpolatedWith (Colour other, float proportionOfOther) const noexcept;

    //==============================================================================
    /** Returns the colour's hue component.
        The value returned is in the range 0.0 to 1.0
    */
    float getHue() const noexcept;

    /** Returns the colour's saturation component.
        The value returned is in the range 0.0 to 1.0
    */
    float getSaturation() const noexcept;

    /** Returns the colour's saturation component as represented in the HSL colour space.
        The value returned is in the range 0.0 to 1.0
    */
    float getSaturationHSL() const noexcept;

    /** Returns the colour's brightness component.
        The value returned is in the range 0.0 to 1.0
    */
    float getBrightness() const noexcept;

    /** Returns the colour's lightness component.
        The value returned is in the range 0.0 to 1.0
    */
    float getLightness() const noexcept;

    /** Returns a skewed brightness value, adjusted to better reflect the way the human
        eye responds to different colour channels. This makes it better than getBrightness()
        for comparing differences in brightness.
    */
    float getPerceivedBrightness() const noexcept;

    /** Returns the colour's hue, saturation and brightness components all at once.
        The values returned are in the range 0.0 to 1.0
    */
    void getHSB (float& hue,
                 float& saturation,
                 float& brightness) const noexcept;

    /** Returns the colour's hue, saturation and lightness components all at once.
        The values returned are in the range 0.0 to 1.0
    */
    void getHSL (float& hue,
                 float& saturation,
                 float& lightness) const noexcept;

    //==============================================================================
    /** Returns a copy of this colour with a different hue. */
    Colour withHue (float newHue) const noexcept;

    /** Returns a copy of this colour with a different saturation. */
    Colour withSaturation (float newSaturation) const noexcept;

    /** Returns a copy of this colour with a different saturation in the HSL colour space. */
    Colour withSaturationHSL (float newSaturation) const noexcept;

    /** Returns a copy of this colour with a different brightness.
        @see brighter, darker, withMultipliedBrightness
    */
    Colour withBrightness (float newBrightness) const noexcept;

    /** Returns a copy of this colour with a different lightness.
        @see lighter, darker, withMultipliedLightness
    */
    Colour withLightness (float newLightness) const noexcept;

    /** Returns a copy of this colour with its hue rotated.
        The new colour's hue is ((this->getHue() + amountToRotate) % 1.0)
        @see brighter, darker, withMultipliedBrightness
    */
    Colour withRotatedHue (float amountToRotate) const noexcept;

    /** Returns a copy of this colour with its saturation multiplied by the given value.
        The new colour's saturation is (this->getSaturation() * multiplier)
        (the result is clipped to legal limits).
    */
    Colour withMultipliedSaturation (float multiplier) const noexcept;

    /** Returns a copy of this colour with its saturation multiplied by the given value.
        The new colour's saturation is (this->getSaturation() * multiplier)
        (the result is clipped to legal limits).

        This will be in the HSL colour space.
    */
    Colour withMultipliedSaturationHSL (float multiplier) const noexcept;

    /** Returns a copy of this colour with its brightness multiplied by the given value.
        The new colour's brightness is (this->getBrightness() * multiplier)
        (the result is clipped to legal limits).
    */
    Colour withMultipliedBrightness (float amount) const noexcept;

    /** Returns a copy of this colour with its lightness multiplied by the given value.
        The new colour's lightness is (this->lightness() * multiplier)
        (the result is clipped to legal limits).
    */
    Colour withMultipliedLightness (float amount) const noexcept;

    //==============================================================================
    /** Returns a brighter version of this colour.
        @param amountBrighter   how much brighter to make it - a value from 0 to 1.0 where 0 is
                                unchanged, and higher values make it brighter
        @see withMultipliedBrightness
    */
    Colour brighter (float amountBrighter = 0.4f) const noexcept;

    /** Returns a darker version of this colour.
        @param amountDarker     how much darker to make it - a value from 0 to 1.0 where 0 is
                                unchanged, and higher values make it darker
        @see withMultipliedBrightness
    */
    Colour darker (float amountDarker = 0.4f) const noexcept;

    //==============================================================================
    /** Returns a colour that will be clearly visible against this colour.

        The amount parameter indicates how contrasting the new colour should
        be, so e.g. Colours::black.contrasting (0.1f) will return a colour
        that's just a little bit lighter; Colours::black.contrasting (1.0f) will
        return white; Colours::white.contrasting (1.0f) will return black, etc.
    */
    Colour contrasting (float amount = 1.0f) const noexcept;

    /** Returns a colour that is as close as possible to a target colour whilst
        still being in contrast to this one.

        The colour that is returned will be the targetColour, but with its luminosity
        nudged up or down so that it differs from the luminosity of this colour
        by at least the amount specified by minLuminosityDiff.
    */
    Colour contrasting (Colour targetColour, float minLuminosityDiff) const noexcept;

    /** Returns a colour that contrasts against two colours.
        Looks for a colour that contrasts with both of the colours passed-in.
        Handy for things like choosing a highlight colour in text editors, etc.
    */
    static Colour contrasting (Colour colour1,
                               Colour colour2) noexcept;

    //==============================================================================
    /** Returns an opaque shade of grey.
        @param brightness the level of grey to return - 0 is black, 1.0 is white
    */
    static Colour greyLevel (float brightness) noexcept;

    //==============================================================================
    /** Returns a stringified version of this colour.
        The string can be turned back into a colour using the fromString() method.
    */
    String toString() const;

    /** Reads the colour from a string that was created with toString(). */
    static Colour fromString (StringRef encodedColourString);

    /** Returns the colour as a hex string in the form RRGGBB or AARRGGBB. */
    String toDisplayString (bool includeAlphaValue) const;

private:
    //==============================================================================
    PixelARGB argb { 0, 0, 0, 0 };
};

namespace ColourHelpers
{
    constexpr inline  uint8 floatToUInt8 (float n) noexcept
    {
        return n <= 0.0f ? 0 : (n >= 1.0f ? 255 : (uint8) roundToInt (n * 255.0f));
    }

    constexpr inline float getHue (int r, int g, int b)
    {
        auto hi = jmax (r, g, b);
        auto lo = jmin (r, g, b);

        float hue = 0.0f;

        if (hi > 0)
        {
            auto invDiff = 1.0f / (float) (hi - lo);

            auto red   = (float) (hi - r) * invDiff;
            auto green = (float) (hi - g) * invDiff;
            auto blue  = (float) (hi - b) * invDiff;

            if      (r == hi)  hue = blue - green;
            else if (g == hi)  hue = 2.0f + red - blue;
            else               hue = 4.0f + green - red;

            hue *= 1.0f / 6.0f;

            if (hue < 0.0f)
                hue += 1.0f;
        }

        return hue;
    }
    constexpr inline float getHue (Colour col)
    {
	    return getHue( col.getRed(), col.getGreen(), col.getBlue() );
    }


	    //==============================================================================
    struct HSL
    {
        constexpr HSL (const int r, const int g, const int b) noexcept
        {
            auto hi = jmax (r, g, b);
            auto lo = jmin (r, g, b);

            if (hi > 0)
            {
                lightness = ((float) (hi + lo) / 2.0f) / 255.0f;

                if (lightness > 0.0f)
			hue = getHue (r,g,b);

                saturation = (float) (hi - lo) / (1.0f - std::abs ((2.0f * lightness) - 1.0f));
            }
        }

	constexpr HSL (const Colour col) noexcept
		: HSL ( col.getRed(),
			col.getGreen(),
			col.getBlue() ) {}


        constexpr Colour toColour (Colour original) const noexcept
        {
            return Colour::fromHSL (hue, saturation, lightness, original.getAlpha());
        }

        constexpr static PixelARGB toRGB (float h, float s, float l, uint8 alpha) noexcept
        {
            auto v = l < 0.5f ? l * (1.0f + s) : l + s - (l * s);

            if (approximatelyEqual (v, 0.0f))
                return PixelARGB (alpha, 0, 0, 0);

            auto min = (2.0f * l) - v;
            auto sv = (v - min) / v;

            h = ((h - std::floor (h)) * 360.0f) / 60.0f;
            auto f = h - std::floor (h);
            auto vsf = v * sv * f;
            auto mid1 = min + vsf;
            auto mid2 = v - vsf;

            if      (h < 1.0f)  return PixelARGB (alpha, floatToUInt8 (v),    floatToUInt8 (mid1), floatToUInt8 (min));
            else if (h < 2.0f)  return PixelARGB (alpha, floatToUInt8 (mid2), floatToUInt8 (v),    floatToUInt8 (min));
            else if (h < 3.0f)  return PixelARGB (alpha, floatToUInt8 (min),  floatToUInt8 (v),    floatToUInt8 (mid1));
            else if (h < 4.0f)  return PixelARGB (alpha, floatToUInt8 (min),  floatToUInt8 (mid2), floatToUInt8 (v));
            else if (h < 5.0f)  return PixelARGB (alpha, floatToUInt8 (mid1), floatToUInt8 (min),  floatToUInt8 (v));
            else if (h < 6.0f)  return PixelARGB (alpha, floatToUInt8 (v),    floatToUInt8 (min),  floatToUInt8 (mid2));

            return PixelARGB (alpha, 0, 0, 0);
        }

        float hue = 0.0f, saturation = 0.0f, lightness = 0.0f;
    };

    //==============================================================================


    struct HSB
    {
	constexpr HSB (Colour col) noexcept
        {
            auto r = (int) col.getRed();
            auto g = (int) col.getGreen();
            auto b = (int) col.getBlue();

            auto hi = jmax (r, g, b);
            auto lo = jmin (r, g, b);

            if (hi > 0)
            {
                saturation = (float) (hi - lo) / (float) hi;

                if (saturation > 0.0f)
                    hue = getHue (col);

                brightness = (float) hi / 255.0f;
            }
        }

        constexpr Colour toColour (Colour original) const noexcept
        {
            return Colour (hue, saturation, brightness, original.getAlpha());
        }

        constexpr static PixelARGB toRGB (float h, float s, float v, uint8 alpha) noexcept
        {
            v = jlimit (0.0f, 255.0f, v * 255.0f);
            auto intV = (uint8) roundToInt (v);

            if (s <= 0)
                return PixelARGB (alpha, intV, intV, intV);

            s = jmin (1.0f, s);
            h = ((h - std::floor (h)) * 360.0f) / 60.0f;
            auto f = h - std::floor (h);
            auto x = (uint8) roundToInt (v * (1.0f - s));

            if (h < 1.0f)   return PixelARGB (alpha, intV,    (uint8) roundToInt (v * (1.0f - (s * (1.0f - f)))), x);
            if (h < 2.0f)   return PixelARGB (alpha,          (uint8) roundToInt (v * (1.0f - s * f)), intV, x);
            if (h < 3.0f)   return PixelARGB (alpha, x, intV, (uint8) roundToInt (v * (1.0f - (s * (1.0f - f)))));
            if (h < 4.0f)   return PixelARGB (alpha, x,       (uint8) roundToInt (v * (1.0f - s * f)), intV);
            if (h < 5.0f)   return PixelARGB (alpha,          (uint8) roundToInt (v * (1.0f - (s * (1.0f - f)))), x, intV);
            return                 PixelARGB (alpha, intV, x, (uint8) roundToInt (v * (1.0f - s * f)));
        }

        float hue = 0.0f, saturation = 0.0f, brightness = 0.0f;
    };

    //==============================================================================
    struct YIQ
    {
        YIQ (Colour c) noexcept
        {
            auto r = c.getFloatRed();
            auto g = c.getFloatGreen();
            auto b = c.getFloatBlue();

            y = 0.2999f * r + 0.5870f * g + 0.1140f * b;
            i = 0.5957f * r - 0.2744f * g - 0.3212f * b;
            q = 0.2114f * r - 0.5225f * g - 0.3113f * b;
            alpha = c.getFloatAlpha();
        }

        Colour toColour() const noexcept
        {
            return Colour::fromFloatRGBA (y + 0.9563f * i + 0.6210f * q,
                                          y - 0.2721f * i - 0.6474f * q,
                                          y - 1.1070f * i + 1.7046f * q,
                                          alpha);
        }

        float y = 0.0f, i = 0.0f, q = 0.0f, alpha = 0.0f;
    };
}


constexpr Colour :: Colour  (uint32 col) noexcept
: argb (static_cast<uint8> ((col >> 24) & 0xff),
	static_cast<uint8> ((col >> 16) & 0xff),
	static_cast<uint8> ((col >> 8) & 0xff),
	static_cast<uint8> (col & 0xff))
{
}

constexpr Colour::Colour (uint8 red, uint8 green, uint8 blue) noexcept
{
    argb.setARGB (0xff, red, green, blue);
}

constexpr Colour Colour::fromRGB (uint8 red, uint8 green, uint8 blue) noexcept
{
    return Colour (red, green, blue);
}

constexpr Colour::Colour (uint8 red, uint8 green, uint8 blue, uint8 alpha) noexcept
{
    argb.setARGB (alpha, red, green, blue);
}

constexpr Colour Colour::fromRGBA (uint8 red, uint8 green, uint8 blue, uint8 alpha) noexcept
{
    return Colour (red, green, blue, alpha);
}

constexpr Colour::Colour (uint8 red, uint8 green, uint8 blue, float alpha) noexcept
{
    argb.setARGB (ColourHelpers::floatToUInt8 (alpha), red, green, blue);
}

constexpr Colour Colour::fromFloatRGBA (float red, float green, float blue, float alpha) noexcept
{
    return Colour (ColourHelpers::floatToUInt8 (red),
                   ColourHelpers::floatToUInt8 (green),
                   ColourHelpers::floatToUInt8 (blue), alpha);
}

constexpr Colour::Colour (float hue, float saturation, float brightness, float alpha) noexcept
    : argb (ColourHelpers::HSB::toRGB (hue, saturation, brightness, ColourHelpers::floatToUInt8 (alpha)))
{
}

constexpr Colour Colour::fromHSV (float hue, float saturation, float brightness, float alpha) noexcept
{
    return Colour (hue, saturation, brightness, alpha);
}

constexpr Colour Colour::fromHSL (float hue, float saturation, float lightness, float alpha) noexcept
{
    Colour hslColour;
    hslColour.argb = ColourHelpers::HSL::toRGB (hue, saturation, lightness, ColourHelpers::floatToUInt8 (alpha));

    return hslColour;
}

constexpr Colour::Colour (float hue, float saturation, float brightness, uint8 alpha) noexcept
    : argb (ColourHelpers::HSB::toRGB (hue, saturation, brightness, alpha))
{
}

constexpr Colour::Colour (PixelARGB argb_) noexcept
    : argb (argb_)
{
}

constexpr Colour::Colour (PixelRGB rgb) noexcept
    : argb (Colour (rgb.getInARGBMaskOrder()).argb)
{
}

constexpr Colour::Colour (PixelAlpha alpha) noexcept
    : argb (Colour (alpha.getInARGBMaskOrder()).argb)
{
}


inline constexpr float Colour::getFloatRed() const noexcept      { return getRed()   / 255.0f; }
inline constexpr float Colour::getFloatGreen() const noexcept    { return getGreen() / 255.0f; }
inline constexpr float Colour::getFloatBlue() const noexcept     { return getBlue()  / 255.0f; }
inline constexpr float Colour::getFloatAlpha() const noexcept    { return getAlpha() / 255.0f; }
inline constexpr uint32 Colour::getARGB() const noexcept
{
    return argb.getInARGBMaskOrder();
}
inline constexpr const PixelARGB Colour::getPixelARGB() const noexcept
{
    PixelARGB p (argb);
    p.premultiply();
    return p;
}

//==============================================================================



} // namespace juce
