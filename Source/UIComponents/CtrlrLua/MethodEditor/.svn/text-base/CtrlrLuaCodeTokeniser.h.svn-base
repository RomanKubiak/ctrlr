#ifndef __CTRLR_LUA_CODE_TOKENISER__
#define __CTRLR_LUA_CODE_TOKENISER__

#include "CtrlrMacros.h"

class CtrlrLuaCodeTokeniser : public CodeTokeniser
{
	public:
		CtrlrLuaCodeTokeniser();
		~CtrlrLuaCodeTokeniser();
		int readNextToken (CodeDocument::Iterator& source);
		CodeEditorComponent::ColourScheme getDefaultColourScheme();
		static bool isReservedKeyword (const String& token) noexcept;

		enum TokenType
		{
	        tokenType_error = 0,
			tokenType_comment,
			tokenType_keyword,
			tokenType_operator,
			tokenType_identifier,
			tokenType_integer,
			tokenType_float,
			tokenType_string,
			tokenType_bracket,
			tokenType_punctuation
		};

		JUCE_LEAK_DETECTOR (CtrlrLuaCodeTokeniser);
};

#endif