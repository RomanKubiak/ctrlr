/*
  ==============================================================================

    XmlTokeniser.h
    Created: 25 Nov 2013 1:25:01am
    Author:  Christoph Hart

  ==============================================================================
*/

#ifndef XMLTOKENISER_H_INCLUDED
#define XMLTOKENISER_H_INCLUDED

#include "JuceHeader.h"

//==============================================================================
/**
    A simple lexical analyser for syntax colouring of Xml code.

    @see CodeEditorComponent, CodeDocument
*/
class JUCE_API  XmlTokeniser    : public CodeTokeniser
{
public:
    //==============================================================================
    XmlTokeniser():
	  is_in_tag(false)
	  {};
    ~XmlTokeniser();

    //==============================================================================
    int readNextToken (CodeDocument::Iterator&);
    CodeEditorComponent::ColourScheme getDefaultColourScheme()
	{
		struct Type
		{
			const char* name;
			uint32 colour;
		};

		const Type types[] =
		{
			{ "Error",              0xffff0000 },
			{ "Tag",            0xff0000AA },
			{ "String",         0xff006600 },
			{ "Attribute", 0xff660000 },
			{ "Text", 0xff000000 }
		};

		CodeEditorComponent::ColourScheme cs;

		for (unsigned int i = 0; i < sizeof (types) / sizeof (types[0]); ++i)  // (NB: numElementsInArray doesn't work here in GCC4.2)
			cs.set (types[i].name, Colour (types[i].colour));

		return cs;
	};


    /** The token values returned by this tokeniser. */
    enum TokenType
    {
        tokenType_error = 0,
        tokenType_tag,
        tokenType_string,
        tokenType_attribute,
		tokenType_text
    };

private:

	bool is_in_tag;

    //==============================================================================
    JUCE_LEAK_DETECTOR (XmlTokeniser)
};

#endif  // XMLTOKENISER_H_INCLUDED
