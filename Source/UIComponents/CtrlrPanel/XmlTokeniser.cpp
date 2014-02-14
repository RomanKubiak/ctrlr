/*
  ==============================================================================

    XmlTokeniser.cpp
    Created: 25 Nov 2013 1:25:01am
    Author:  Christoph Hart

  ==============================================================================
*/
#include "stdafx.h"
#include "XmlTokeniser.h"

//==============================================================================

XmlTokeniser::~XmlTokeniser() {}


void skipQuotedString(CodeDocument::Iterator& source)
{
	const juce_wchar quote = source.nextChar();

	for (;;)
	{
		const juce_wchar c = source.nextChar();

		if (c == quote || c == 0)
			break;

		if (c == '\\')
			source.skip();
	}
}

int XmlTokeniser::readNextToken (CodeDocument::Iterator& source)
{
    int result = tokenType_text;

	if(source.getPosition() == 0) is_in_tag = false;

	source.skipWhitespace();

	const juce_wchar firstChar = source.peekNextChar();

	switch (firstChar)
        {
        case 0:
            source.skip();
            break;

		case '"':
        case '\'':
            skipQuotedString (source);
            result = XmlTokeniser::tokenType_string;
            break;

		case '<':
			result = XmlTokeniser::tokenType_tag;
				while( source.peekNextChar() != ' ' && source.peekNextChar() != '>' && ! source.isEOF())
			{
				source.skip();

			};
			is_in_tag = true;
			break;

		case '/':
			result = XmlTokeniser::tokenType_tag;
			source.skip();
			break;

		case '>':
			result = XmlTokeniser::tokenType_tag;

			source.skip();
			is_in_tag = false;
			break;
		case '=':
			result = XmlTokeniser::tokenType_text;
			source.skip();
			break;
		default:

			result = is_in_tag ? XmlTokeniser::tokenType_attribute : XmlTokeniser::tokenType_text;

			source.skip();
	}

	return result;
}
