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

namespace ColourHelpers
{


}

//==============================================================================
bool Colour::operator== (const Colour& other) const noexcept    { return argb.getNativeARGB() == other.argb.getNativeARGB(); }
bool Colour::operator!= (const Colour& other) const noexcept    { return argb.getNativeARGB() != other.argb.getNativeARGB(); }

//==============================================================================
bool Colour::isTransparent() const noexcept
{
    return getAlpha() == 0;
}

bool Colour::isOpaque() const noexcept
{
    return getAlpha() == 0xff;
}

Colour Colour::withAlpha (uint8 newAlpha) const noexcept
{
    PixelARGB newCol (argb);
    newCol.setAlpha (newAlpha);
    return Colour (newCol);
}

Colour Colour::withAlpha (float newAlpha) const noexcept
{
    jassert (newAlpha >= 0 && newAlpha <= 1.0f);

    PixelARGB newCol (argb);
    newCol.setAlpha (ColourHelpers::floatToUInt8 (newAlpha));
    return Colour (newCol);
}

Colour Colour::withMultipliedAlpha (float alphaMultiplier) const noexcept
{
    jassert (alphaMultiplier >= 0);

    PixelARGB newCol (argb);
    newCol.setAlpha ((uint8) jmin (0xff, roundToInt (alphaMultiplier * newCol.getAlpha())));
    return Colour (newCol);
}

//==============================================================================
Colour Colour::overlaidWith (Colour src) const noexcept
{
    auto destAlpha = getAlpha();

    if (destAlpha <= 0)
        return src;

    auto invA = 0xff - (int) src.getAlpha();
    auto resA = 0xff - (((0xff - destAlpha) * invA) >> 8);

    if (resA <= 0)
        return *this;

    auto da = (invA * destAlpha) / resA;

    return Colour ((uint8) (src.getRed()   + ((((int) getRed()   - src.getRed())   * da) >> 8)),
                   (uint8) (src.getGreen() + ((((int) getGreen() - src.getGreen()) * da) >> 8)),
                   (uint8) (src.getBlue()  + ((((int) getBlue()  - src.getBlue())  * da) >> 8)),
                   (uint8) resA);
}

Colour Colour::interpolatedWith (Colour other, float proportionOfOther) const noexcept
{
    if (proportionOfOther <= 0)
        return *this;

    if (proportionOfOther >= 1.0f)
        return other;

    PixelARGB c1 (getPixelARGB());
    PixelARGB c2 (other.getPixelARGB());
    c1.tween (c2, (uint32) roundToInt (proportionOfOther * 255.0f));
    c1.unpremultiply();

    return Colour (c1);
}

//==============================================================================
void Colour::getHSB (float& h, float& s, float& v) const noexcept
{
    ColourHelpers::HSB hsb (*this);
    h = hsb.hue;
    s = hsb.saturation;
    v = hsb.brightness;
}

void Colour::getHSL (float& h, float& s, float& l) const noexcept
{
    ColourHelpers::HSL hsl (*this);
    h = hsl.hue;
    s = hsl.saturation;
    l = hsl.lightness;
}

float Colour::getHue() const noexcept           { return ColourHelpers::HSB (*this).hue; }
float Colour::getSaturation() const noexcept    { return ColourHelpers::HSB (*this).saturation; }
float Colour::getBrightness() const noexcept    { return ColourHelpers::HSB (*this).brightness; }

float Colour::getSaturationHSL() const noexcept { return ColourHelpers::HSL (*this).saturation; }
float Colour::getLightness() const noexcept     { return ColourHelpers::HSL (*this).lightness; }

Colour Colour::withHue (float h) const noexcept          { ColourHelpers::HSB hsb (*this); hsb.hue = h;        return hsb.toColour (*this); }
Colour Colour::withSaturation (float s) const noexcept   { ColourHelpers::HSB hsb (*this); hsb.saturation = s; return hsb.toColour (*this); }
Colour Colour::withBrightness (float v) const noexcept   { ColourHelpers::HSB hsb (*this); hsb.brightness = v; return hsb.toColour (*this); }

Colour Colour::withSaturationHSL (float s) const noexcept { ColourHelpers::HSL hsl (*this); hsl.saturation = s; return hsl.toColour (*this); }
Colour Colour::withLightness (float l) const noexcept     { ColourHelpers::HSL hsl (*this); hsl.lightness = l;  return hsl.toColour (*this); }

float Colour::getPerceivedBrightness() const noexcept
{
    return std::sqrt (0.241f * square (getFloatRed())
                    + 0.691f * square (getFloatGreen())
                    + 0.068f * square (getFloatBlue()));
}

//==============================================================================
Colour Colour::withRotatedHue (float amountToRotate) const noexcept
{
    ColourHelpers::HSB hsb (*this);
    hsb.hue += amountToRotate;
    return hsb.toColour (*this);
}

Colour Colour::withMultipliedSaturation (float amount) const noexcept
{
    ColourHelpers::HSB hsb (*this);
    hsb.saturation = jmin (1.0f, hsb.saturation * amount);
    return hsb.toColour (*this);
}

Colour Colour::withMultipliedSaturationHSL (float amount) const noexcept
{
    ColourHelpers::HSL hsl (*this);
    hsl.saturation = jmin (1.0f, hsl.saturation * amount);
    return hsl.toColour (*this);
}

Colour Colour::withMultipliedBrightness (float amount) const noexcept
{
    ColourHelpers::HSB hsb (*this);
    hsb.brightness = jmin (1.0f, hsb.brightness * amount);
    return hsb.toColour (*this);
}

Colour Colour::withMultipliedLightness (float amount) const noexcept
{
    ColourHelpers::HSL hsl (*this);
    hsl.lightness = jmin (1.0f, hsl.lightness * amount);
    return hsl.toColour (*this);
}

//==============================================================================
Colour Colour::brighter (float amount) const noexcept
{
    amount = 1.0f / (1.0f + amount);

    return Colour ((uint8) (255 - (amount * (255 - getRed()))),
                   (uint8) (255 - (amount * (255 - getGreen()))),
                   (uint8) (255 - (amount * (255 - getBlue()))),
                   getAlpha());
}

Colour Colour::darker (float amount) const noexcept
{
    amount = 1.0f / (1.0f + amount);

    return Colour ((uint8) (amount * getRed()),
                   (uint8) (amount * getGreen()),
                   (uint8) (amount * getBlue()),
                   getAlpha());
}

//==============================================================================
Colour Colour::greyLevel (float brightness) noexcept
{
    auto level = ColourHelpers::floatToUInt8 (brightness);
    return Colour (level, level, level);
}

//==============================================================================
Colour Colour::contrasting (float amount) const noexcept
{
   return overlaidWith ((getPerceivedBrightness() >= 0.5f
                           ? Colours::black
                           : Colours::white).withAlpha (amount));
}

Colour Colour::contrasting (Colour target, float minContrast) const noexcept
{
    ColourHelpers::YIQ bg (*this);
    ColourHelpers::YIQ fg (target);

    if (std::abs (bg.y - fg.y) >= minContrast)
        return target;

    auto y1 = jmax (0.0f, bg.y - minContrast);
    auto y2 = jmin (1.0f, bg.y + minContrast);
    fg.y = (std::abs (y1 - bg.y) > std::abs (y2 - bg.y)) ? y1 : y2;

    return fg.toColour();
}

Colour Colour::contrasting (Colour colour1,
                            Colour colour2) noexcept
{
    auto b1 = colour1.getPerceivedBrightness();
    auto b2 = colour2.getPerceivedBrightness();
    float best = 0.0f, bestDist = 0.0f;

    for (float i = 0.0f; i < 1.0f; i += 0.02f)
    {
        auto d1 = std::abs (i - b1);
        auto d2 = std::abs (i - b2);
        auto dist = jmin (d1, d2, 1.0f - d1, 1.0f - d2);

        if (dist > bestDist)
        {
            best = i;
            bestDist = dist;
        }
    }

    return colour1.overlaidWith (colour2.withMultipliedAlpha (0.5f))
                  .withBrightness (best);
}

//==============================================================================
String Colour::toString() const
{
    return String::toHexString ((int) argb.getInARGBMaskOrder());
}

Colour Colour::fromString (StringRef encodedColourString)
{
    return Colour ((uint32) CharacterFunctions::HexParser<int>::parse (encodedColourString.text));
}

String Colour::toDisplayString (const bool includeAlphaValue) const
{
    return String::toHexString ((int) (argb.getInARGBMaskOrder() & (includeAlphaValue ? 0xffffffff : 0xffffff)))
                  .paddedLeft ('0', includeAlphaValue ? 8 : 6)
                  .toUpperCase();
}


//==============================================================================
//==============================================================================
#if JUCE_UNIT_TESTS

class ColourTests  : public UnitTest
{
public:
    ColourTests()
        : UnitTest ("Colour", UnitTestCategories::graphics)
    {}

    void runTest() override
    {
        auto testColour = [this] (Colour colour,
                                  uint8 expectedRed, uint8 expectedGreen, uint8 expectedBlue,
                                  uint8 expectedAlpha = 255, float expectedFloatAlpha = 1.0f)
        {
            expectEquals (colour.getRed(),        expectedRed);
            expectEquals (colour.getGreen(),      expectedGreen);
            expectEquals (colour.getBlue(),       expectedBlue);
            expectEquals (colour.getAlpha(),      expectedAlpha);
            expectEquals (colour.getFloatAlpha(), expectedFloatAlpha);
        };

        beginTest ("Constructors");
        {
            Colour c1;
            testColour (c1, (uint8) 0, (uint8) 0, (uint8) 0, (uint8) 0, 0.0f);

            Colour c2 ((uint32) 0);
            testColour (c2, (uint8) 0, (uint8) 0, (uint8) 0, (uint8) 0, 0.0f);

            Colour c3 ((uint32) 0xffffffff);
            testColour (c3, (uint8) 255, (uint8) 255, (uint8) 255, (uint8) 255, 1.0f);

            Colour c4 (0, 0, 0);
            testColour (c4, (uint8) 0, (uint8) 0, (uint8) 0, (uint8) 255, 1.0f);

            Colour c5 (255, 255, 255);
            testColour (c5, (uint8) 255, (uint8) 255, (uint8) 255, (uint8) 255, 1.0f);

            Colour c6 ((uint8) 0, (uint8) 0, (uint8) 0, (uint8) 0);
            testColour (c6, (uint8) 0, (uint8) 0, (uint8) 0, (uint8) 0, 0.0f);

            Colour c7 ((uint8) 255, (uint8) 255, (uint8) 255, (uint8) 255);
            testColour (c7, (uint8) 255, (uint8) 255, (uint8) 255, (uint8) 255, 1.0f);

            Colour c8 ((uint8) 0, (uint8) 0, (uint8) 0, 0.0f);
            testColour (c8, (uint8) 0, (uint8) 0, (uint8) 0, (uint8) 0, 0.0f);

            Colour c9 ((uint8) 255, (uint8) 255, (uint8) 255, 1.0f);
            testColour (c9, (uint8) 255, (uint8) 255, (uint8) 255, (uint8) 255, 1.0f);
        }

        beginTest ("HSV");
        {
            // black
            testColour (Colour::fromHSV (0.0f, 0.0f, 0.0f, 1.0f), 0, 0, 0);
            // white
            testColour (Colour::fromHSV (0.0f, 0.0f, 1.0f, 1.0f), 255, 255, 255);
            // red
            testColour (Colour::fromHSV (0.0f, 1.0f, 1.0f, 1.0f), 255, 0, 0);
            testColour (Colour::fromHSV (1.0f, 1.0f, 1.0f, 1.0f), 255, 0, 0);
            // lime
            testColour (Colour::fromHSV (120 / 360.0f, 1.0f, 1.0f, 1.0f), 0, 255, 0);
            // blue
            testColour (Colour::fromHSV (240 / 360.0f, 1.0f, 1.0f, 1.0f), 0, 0, 255);
            // yellow
            testColour (Colour::fromHSV (60 / 360.0f, 1.0f, 1.0f, 1.0f), 255, 255, 0);
            // cyan
            testColour (Colour::fromHSV (180 / 360.0f, 1.0f, 1.0f, 1.0f), 0, 255, 255);
            // magenta
            testColour (Colour::fromHSV (300 / 360.0f, 1.0f, 1.0f, 1.0f), 255, 0, 255);
            // silver
            testColour (Colour::fromHSV (0.0f, 0.0f, 0.75f, 1.0f), 191, 191, 191);
            // grey
            testColour (Colour::fromHSV (0.0f, 0.0f, 0.5f, 1.0f), 128, 128, 128);
            // maroon
            testColour (Colour::fromHSV (0.0f, 1.0f, 0.5f, 1.0f), 128, 0, 0);
            // olive
            testColour (Colour::fromHSV (60 / 360.0f, 1.0f, 0.5f, 1.0f), 128, 128, 0);
            // green
            testColour (Colour::fromHSV (120 / 360.0f, 1.0f, 0.5f, 1.0f), 0, 128, 0);
            // purple
            testColour (Colour::fromHSV (300 / 360.0f, 1.0f, 0.5f, 1.0f), 128, 0, 128);
            // teal
            testColour (Colour::fromHSV (180 / 360.0f, 1.0f, 0.5f, 1.0f), 0, 128, 128);
            // navy
            testColour (Colour::fromHSV (240 / 360.0f, 1.0f, 0.5f, 1.0f), 0, 0, 128);
        }

        beginTest ("HSL");
        {
            // black
            testColour (Colour::fromHSL (0.0f, 0.0f, 0.0f, 1.0f), 0, 0, 0);
            // white
            testColour (Colour::fromHSL (0.0f, 0.0f, 1.0f, 1.0f), 255, 255, 255);
            // red
            testColour (Colour::fromHSL (0.0f, 1.0f, 0.5f, 1.0f), 255, 0, 0);
            testColour (Colour::fromHSL (1.0f, 1.0f, 0.5f, 1.0f), 255, 0, 0);
            // lime
            testColour (Colour::fromHSL (120 / 360.0f, 1.0f, 0.5f, 1.0f), 0, 255, 0);
            // blue
            testColour (Colour::fromHSL (240 / 360.0f, 1.0f, 0.5f, 1.0f), 0, 0, 255);
            // yellow
            testColour (Colour::fromHSL (60 / 360.0f, 1.0f, 0.5f, 1.0f), 255, 255, 0);
            // cyan
            testColour (Colour::fromHSL (180 / 360.0f, 1.0f, 0.5f, 1.0f), 0, 255, 255);
            // magenta
            testColour (Colour::fromHSL (300 / 360.0f, 1.0f, 0.5f, 1.0f), 255, 0, 255);
            // silver
            testColour (Colour::fromHSL (0.0f, 0.0f, 0.75f, 1.0f), 191, 191, 191);
            // grey
            testColour (Colour::fromHSL (0.0f, 0.0f, 0.5f, 1.0f), 128, 128, 128);
            // maroon
            testColour (Colour::fromHSL (0.0f, 1.0f, 0.25f, 1.0f), 128, 0, 0);
            // olive
            testColour (Colour::fromHSL (60 / 360.0f, 1.0f, 0.25f, 1.0f), 128, 128, 0);
            // green
            testColour (Colour::fromHSL (120 / 360.0f, 1.0f, 0.25f, 1.0f), 0, 128, 0);
            // purple
            testColour (Colour::fromHSL (300 / 360.0f, 1.0f, 0.25f, 1.0f), 128, 0, 128);
            // teal
            testColour (Colour::fromHSL (180 / 360.0f, 1.0f, 0.25f, 1.0f), 0, 128, 128);
            // navy
            testColour (Colour::fromHSL (240 / 360.0f, 1.0f, 0.25f, 1.0f), 0, 0, 128);
        }

        beginTest ("Modifiers");
        {
            Colour red (255, 0, 0);
            testColour (red, 255, 0, 0);

            testColour (red.withHue (120.0f / 360.0f), 0, 255, 0);
            testColour (red.withSaturation (0.5f), 255, 128, 128);
            testColour (red.withSaturationHSL (0.5f), 191, 64, 64);
            testColour (red.withBrightness (0.5f), 128, 0, 0);
            testColour (red.withLightness (1.0f), 255, 255, 255);
            testColour (red.withRotatedHue (120.0f / 360.0f), 0, 255, 0);
            testColour (red.withRotatedHue (480.0f / 360.0f), 0, 255, 0);
            testColour (red.withRotatedHue (-240.0f / 360.0f), 0, 255, 0);
            testColour (red.withRotatedHue (-600.0f / 360.0f), 0, 255, 0);
            testColour (red.withMultipliedSaturation (0.0f), 255, 255, 255);
            testColour (red.withMultipliedSaturationHSL (0.0f), 128, 128, 128);
            testColour (red.withMultipliedBrightness (0.5f), 128, 0, 0);
            testColour (red.withMultipliedLightness (2.0f), 255, 255, 255);
        }
    }
};

static ColourTests colourTests;

#endif

} // namespace juce
