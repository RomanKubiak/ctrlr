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
    Contains a set of predefined named colours (mostly standard HTML colours)

    @see Colour

    @tags{Graphics}
*/
namespace Colours
{

    constexpr const  Colour transparentBlack     { 0 };
    constexpr const  Colour transparentWhite     { 0x00ffffff };

    constexpr const  Colour aliceblue            { 0xfff0f8ff };
    constexpr const  Colour antiquewhite         { 0xfffaebd7 };
    constexpr const  Colour aqua                 { 0xff00ffff };
    constexpr const  Colour aquamarine           { 0xff7fffd4 };
    constexpr const  Colour azure                { 0xfff0ffff };
    constexpr const  Colour beige                { 0xfff5f5dc };
    constexpr const  Colour bisque               { 0xffffe4c4 };
    constexpr const  Colour black                { 0xff000000 };
    constexpr const  Colour blanchedalmond       { 0xffffebcd };
    constexpr const  Colour blue                 { 0xff0000ff };
    constexpr const  Colour blueviolet           { 0xff8a2be2 };
    constexpr const  Colour brown                { 0xffa52a2a };
    constexpr const  Colour burlywood            { 0xffdeb887 };
    constexpr const  Colour cadetblue            { 0xff5f9ea0 };
    constexpr const  Colour chartreuse           { 0xff7fff00 };
    constexpr const  Colour chocolate            { 0xffd2691e };
    constexpr const  Colour coral                { 0xffff7f50 };
    constexpr const  Colour cornflowerblue       { 0xff6495ed };
    constexpr const  Colour cornsilk             { 0xfffff8dc };
    constexpr const  Colour crimson              { 0xffdc143c };
    constexpr const  Colour cyan                 { 0xff00ffff };
    constexpr const  Colour darkblue             { 0xff00008b };
    constexpr const  Colour darkcyan             { 0xff008b8b };
    constexpr const  Colour darkgoldenrod        { 0xffb8860b };
    constexpr const  Colour darkgrey             { 0xff555555 };
    constexpr const  Colour darkgreen            { 0xff006400 };
    constexpr const  Colour darkkhaki            { 0xffbdb76b };
    constexpr const  Colour darkmagenta          { 0xff8b008b };
    constexpr const  Colour darkolivegreen       { 0xff556b2f };
    constexpr const  Colour darkorange           { 0xffff8c00 };
    constexpr const  Colour darkorchid           { 0xff9932cc };
    constexpr const  Colour darkred              { 0xff8b0000 };
    constexpr const  Colour darksalmon           { 0xffe9967a };
    constexpr const  Colour darkseagreen         { 0xff8fbc8f };
    constexpr const  Colour darkslateblue        { 0xff483d8b };
    constexpr const  Colour darkslategrey        { 0xff2f4f4f };
    constexpr const  Colour darkturquoise        { 0xff00ced1 };
    constexpr const  Colour darkviolet           { 0xff9400d3 };
    constexpr const  Colour deeppink             { 0xffff1493 };
    constexpr const  Colour deepskyblue          { 0xff00bfff };
    constexpr const  Colour dimgrey              { 0xff696969 };
    constexpr const  Colour dodgerblue           { 0xff1e90ff };
    constexpr const  Colour firebrick            { 0xffb22222 };
    constexpr const  Colour floralwhite          { 0xfffffaf0 };
    constexpr const  Colour forestgreen          { 0xff228b22 };
    constexpr const  Colour fuchsia              { 0xffff00ff };
    constexpr const  Colour gainsboro            { 0xffdcdcdc };
    constexpr const  Colour ghostwhite           { 0xfff8f8ff };
    constexpr const  Colour gold                 { 0xffffd700 };
    constexpr const  Colour goldenrod            { 0xffdaa520 };
    constexpr const  Colour grey                 { 0xff808080 };
    constexpr const  Colour green                { 0xff008000 };
    constexpr const  Colour greenyellow          { 0xffadff2f };
    constexpr const  Colour honeydew             { 0xfff0fff0 };
    constexpr const  Colour hotpink              { 0xffff69b4 };
    constexpr const  Colour indianred            { 0xffcd5c5c };
    constexpr const  Colour indigo               { 0xff4b0082 };
    constexpr const  Colour ivory                { 0xfffffff0 };
    constexpr const  Colour khaki                { 0xfff0e68c };
    constexpr const  Colour lavender             { 0xffe6e6fa };
    constexpr const  Colour lavenderblush        { 0xfffff0f5 };
    constexpr const  Colour lawngreen            { 0xff7cfc00 };
    constexpr const  Colour lemonchiffon         { 0xfffffacd };
    constexpr const  Colour lightblue            { 0xffadd8e6 };
    constexpr const  Colour lightcoral           { 0xfff08080 };
    constexpr const  Colour lightcyan            { 0xffe0ffff };
    constexpr const  Colour lightgoldenrodyellow { 0xfffafad2 };
    constexpr const  Colour lightgreen           { 0xff90ee90 };
    constexpr const  Colour lightgrey            { 0xffd3d3d3 };
    constexpr const  Colour lightpink            { 0xffffb6c1 };
    constexpr const  Colour lightsalmon          { 0xffffa07a };
    constexpr const  Colour lightseagreen        { 0xff20b2aa };
    constexpr const  Colour lightskyblue         { 0xff87cefa };
    constexpr const  Colour lightslategrey       { 0xff778899 };
    constexpr const  Colour lightsteelblue       { 0xffb0c4de };
    constexpr const  Colour lightyellow          { 0xffffffe0 };
    constexpr const  Colour lime                 { 0xff00ff00 };
    constexpr const  Colour limegreen            { 0xff32cd32 };
    constexpr const  Colour linen                { 0xfffaf0e6 };
    constexpr const  Colour magenta              { 0xffff00ff };
    constexpr const  Colour maroon               { 0xff800000 };
    constexpr const  Colour mediumaquamarine     { 0xff66cdaa };
    constexpr const  Colour mediumblue           { 0xff0000cd };
    constexpr const  Colour mediumorchid         { 0xffba55d3 };
    constexpr const  Colour mediumpurple         { 0xff9370db };
    constexpr const  Colour mediumseagreen       { 0xff3cb371 };
    constexpr const  Colour mediumslateblue      { 0xff7b68ee };
    constexpr const  Colour mediumspringgreen    { 0xff00fa9a };
    constexpr const  Colour mediumturquoise      { 0xff48d1cc };
    constexpr const  Colour mediumvioletred      { 0xffc71585 };
    constexpr const  Colour midnightblue         { 0xff191970 };
    constexpr const  Colour mintcream            { 0xfff5fffa };
    constexpr const  Colour mistyrose            { 0xffffe4e1 };
    constexpr const  Colour moccasin             { 0xffffe4b5 };
    constexpr const  Colour navajowhite          { 0xffffdead };
    constexpr const  Colour navy                 { 0xff000080 };
    constexpr const  Colour oldlace              { 0xfffdf5e6 };
    constexpr const  Colour olive                { 0xff808000 };
    constexpr const  Colour olivedrab            { 0xff6b8e23 };
    constexpr const  Colour orange               { 0xffffa500 };
    constexpr const  Colour orangered            { 0xffff4500 };
    constexpr const  Colour orchid               { 0xffda70d6 };
    constexpr const  Colour palegoldenrod        { 0xffeee8aa };
    constexpr const  Colour palegreen            { 0xff98fb98 };
    constexpr const  Colour paleturquoise        { 0xffafeeee };
    constexpr const  Colour palevioletred        { 0xffdb7093 };
    constexpr const  Colour papayawhip           { 0xffffefd5 };
    constexpr const  Colour peachpuff            { 0xffffdab9 };
    constexpr const  Colour peru                 { 0xffcd853f };
    constexpr const  Colour pink                 { 0xffffc0cb };
    constexpr const  Colour plum                 { 0xffdda0dd };
    constexpr const  Colour powderblue           { 0xffb0e0e6 };
    constexpr const  Colour purple               { 0xff800080 };
    constexpr const  Colour rebeccapurple        { 0xff663399 };
    constexpr const  Colour red                  { 0xffff0000 };
    constexpr const  Colour rosybrown            { 0xffbc8f8f };
    constexpr const  Colour royalblue            { 0xff4169e1 };
    constexpr const  Colour saddlebrown          { 0xff8b4513 };
    constexpr const  Colour salmon               { 0xfffa8072 };
    constexpr const  Colour sandybrown           { 0xfff4a460 };
    constexpr const  Colour seagreen             { 0xff2e8b57 };
    constexpr const  Colour seashell             { 0xfffff5ee };
    constexpr const  Colour sienna               { 0xffa0522d };
    constexpr const  Colour silver               { 0xffc0c0c0 };
    constexpr const  Colour skyblue              { 0xff87ceeb };
    constexpr const  Colour slateblue            { 0xff6a5acd };
    constexpr const  Colour slategrey            { 0xff708090 };
    constexpr const  Colour snow                 { 0xfffffafa };
    constexpr const  Colour springgreen          { 0xff00ff7f };
    constexpr const  Colour steelblue            { 0xff4682b4 };
    constexpr const  Colour tan                  { 0xffd2b48c };
    constexpr const  Colour teal                 { 0xff008080 };
    constexpr const  Colour thistle              { 0xffd8bfd8 };
    constexpr const  Colour tomato               { 0xffff6347 };
    constexpr const  Colour turquoise            { 0xff40e0d0 };
    constexpr const  Colour violet               { 0xffee82ee };
    constexpr const  Colour wheat                { 0xfff5deb3 };
    constexpr const  Colour white                { 0xffffffff };
    constexpr const  Colour whitesmoke           { 0xfff5f5f5 };
    constexpr const  Colour yellow               { 0xffffff00 };
    constexpr const  Colour yellowgreen          { 0xff9acd32 };

    /** Attempts to look up a string in the list of known colour names, and return
        the appropriate colour.

        A non-case-sensitive search is made of the list of predefined colours, and
        if a match is found, that colour is returned. If no match is found, the
        colour passed in as the defaultColour parameter is returned.
    */
    JUCE_API Colour findColourForName (const String& colourName,
                                       Colour defaultColour);
} // namespace Colours

} // namespace juce
