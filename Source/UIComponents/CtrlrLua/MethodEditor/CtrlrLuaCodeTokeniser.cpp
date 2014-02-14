#include "stdafx.h"
#include "CtrlrLuaCodeTokeniser.h"
#include "CtrlrLuaCodeTokeniserFunctions.h"

CtrlrLuaCodeTokeniser::CtrlrLuaCodeTokeniser() {}
CtrlrLuaCodeTokeniser::~CtrlrLuaCodeTokeniser() {}

int CtrlrLuaCodeTokeniser::readNextToken (CodeDocument::Iterator& source)
{
    return CtrlrLuaCodeTokeniserFunctions::readNextToken (source);
}

CodeEditorComponent::ColourScheme CtrlrLuaCodeTokeniser::getDefaultColourScheme()
{
    struct Type
    {
        const char* name;
        uint32 colour;
    };

    const Type types[] =
    {
        { "Error",              0xffcc0000 },
        { "Comment",            0xff3c3c3c },
        { "Keyword",            0xff0000cc },
        { "Operator",           0xff225500 },
        { "Identifier",         0xff000000 },
        { "Integer",            0xff880000 },
        { "Float",              0xff885500 },
        { "String",             0xff990099 },
        { "Bracket",            0xff000055 },
        { "Punctuation",        0xff004400 }
    };

    CodeEditorComponent::ColourScheme cs;

    for (unsigned int i = 0; i < sizeof (types) / sizeof (types[0]); ++i)  // (NB: numElementsInArray doesn't work here in GCC4.2)
        cs.set (types[i].name, Colour (types[i].colour));

    return cs;
}

bool CtrlrLuaCodeTokeniser::isReservedKeyword (const String& token) noexcept
{
    return CtrlrLuaCodeTokeniserFunctions::isReservedKeyword (token.getCharPointer(), token.length());
}
