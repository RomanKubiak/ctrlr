#ifndef __CTRLR_LUA_CODE_TOKENISER_FUNCTIONS__
#define __CTRLR_LUA_CODE_TOKENISER_FUNCTIONS__

struct CtrlrLuaCodeTokeniserFunctions
{
    static bool isIdentifierStart (const juce_wchar c) noexcept
    {
        return CharacterFunctions::isLetter (c)
                || c == '_' || c == '@';
    }

    static bool isIdentifierBody (const juce_wchar c) noexcept
    {
        return CharacterFunctions::isLetterOrDigit (c)
                || c == '_' || c == '@';
    }

	/*
	 if or in do
	 and end for nil not
	 then true else
     false local until while break
     repeat return elseif
	 function
	 */
    static bool isReservedKeyword (String::CharPointerType token, const int tokenLength) noexcept
    {
        static const char* const keywords2Char[] =
            { "if", "or", "in", "do", 0 };

        static const char* const keywords3Char[] =
            { "and", "end", "for", "nil", "not", 0 };

        static const char* const keywords4Char[] =
            { "then", "true", "else", 0 };

        static const char* const keywords5Char[] =
            {  "false", "local", "until", "while", "break", 0 };

        static const char* const keywords6Char[] =
            { "repeat", "return", "elseif", 0};

        static const char* const keywords7Char[] =
            { 0 };

        static const char* const keywordsOther[] =
            { "function", "@interface", "@end", "@synthesize", "@dynamic", "@public",
              "@private", "@property", "@protected", "@class", 0 };

        const char* const* k;

        switch (tokenLength)
        {
            case 2:     k = keywords2Char; break;
            case 3:     k = keywords3Char; break;
            case 4:     k = keywords4Char; break;
            case 5:     k = keywords5Char; break;
            case 6:     k = keywords6Char; break;
            case 7:     k = keywords7Char; break;

            default:
                if (tokenLength < 2 || tokenLength > 16)
                    return false;

                k = keywordsOther;
                break;
        }

        for (int i = 0; k[i] != 0; ++i)
            if (token.compare (CharPointer_ASCII (k[i])) == 0)
                return true;

        return false;
    }

    template<class Iterator>
    static int parseIdentifier (Iterator& source) noexcept
    {
        int tokenLength = 0;
        String::CharPointerType::CharType possibleIdentifier [100];
        String::CharPointerType possible (possibleIdentifier);

        while (isIdentifierBody (source.peekNextChar()))
        {
            const juce_wchar c = source.nextChar();

            if (tokenLength < 20)
                possible.write (c);

            ++tokenLength;
        }

        if (tokenLength > 1 && tokenLength <= 16)
        {
            possible.writeNull();

            if (isReservedKeyword (String::CharPointerType (possibleIdentifier), tokenLength))
                return CtrlrLuaCodeTokeniser::tokenType_keyword;
        }

        return CtrlrLuaCodeTokeniser::tokenType_identifier;
    }

    template<class Iterator>
    static bool skipNumberSuffix (Iterator& source)
    {
        const juce_wchar c = source.peekNextChar();
        if (c == 'l' || c == 'L' || c == 'u' || c == 'U')
            source.skip();

        if (CharacterFunctions::isLetterOrDigit (source.peekNextChar()))
            return false;

        return true;
    }

    static bool isHexDigit (const juce_wchar c) noexcept
    {
        return (c >= '0' && c <= '9')
                || (c >= 'a' && c <= 'f')
                || (c >= 'A' && c <= 'F');
    }

    template<class Iterator>
    static bool parseHexLiteral (Iterator& source) noexcept
    {
        if (source.peekNextChar() == '-')
            source.skip();

        if (source.nextChar() != '0')
            return false;

        juce_wchar c = source.nextChar();
        if (c != 'x' && c != 'X')
            return false;

        int numDigits = 0;
        while (isHexDigit (source.peekNextChar()))
        {
            ++numDigits;
            source.skip();
        }

        if (numDigits == 0)
            return false;

        return skipNumberSuffix (source);
    }

    static bool isOctalDigit (const juce_wchar c) noexcept
    {
        return c >= '0' && c <= '7';
    }

    template<class Iterator>
    static bool parseOctalLiteral (Iterator& source) noexcept
    {
        if (source.peekNextChar() == '-')
            source.skip();

        if (source.nextChar() != '0')
            return false;

        if (! isOctalDigit (source.nextChar()))
            return false;

        while (isOctalDigit (source.peekNextChar()))
            source.skip();

        return skipNumberSuffix (source);
    }

    static bool isDecimalDigit (const juce_wchar c) noexcept
    {
        return c >= '0' && c <= '9';
    }

    template<class Iterator>
    static bool parseDecimalLiteral (Iterator& source) noexcept
    {
        if (source.peekNextChar() == '-')
            source.skip();

        int numChars = 0;
        while (isDecimalDigit (source.peekNextChar()))
        {
            ++numChars;
            source.skip();
        }

        if (numChars == 0)
            return false;

        return skipNumberSuffix (source);
    }

    template<class Iterator>
    static bool parseFloatLiteral (Iterator& source) noexcept
    {
        if (source.peekNextChar() == '-')
            source.skip();

        int numDigits = 0;

        while (isDecimalDigit (source.peekNextChar()))
        {
            source.skip();
            ++numDigits;
        }

        const bool hasPoint = (source.peekNextChar() == '.');

        if (hasPoint)
        {
            source.skip();

            while (isDecimalDigit (source.peekNextChar()))
            {
                source.skip();
                ++numDigits;
            }
        }

        if (numDigits == 0)
            return false;

        juce_wchar c = source.peekNextChar();
        const bool hasExponent = (c == 'e' || c == 'E');

        if (hasExponent)
        {
            source.skip();

            c = source.peekNextChar();
            if (c == '+' || c == '-')
                source.skip();

            int numExpDigits = 0;
            while (isDecimalDigit (source.peekNextChar()))
            {
                source.skip();
                ++numExpDigits;
            }

            if (numExpDigits == 0)
                return false;
        }

        c = source.peekNextChar();
        if (c == 'f' || c == 'F')
            source.skip();
        else if (! (hasExponent || hasPoint))
            return false;

        return true;
    }

    template<class Iterator>
    static int parseNumber (Iterator& source)
    {
        const Iterator original (source);

        if (parseFloatLiteral (source))    return CtrlrLuaCodeTokeniser::tokenType_float;
        source = original;

        if (parseHexLiteral (source))      return CtrlrLuaCodeTokeniser::tokenType_integer;
        source = original;

        if (parseOctalLiteral (source))    return CtrlrLuaCodeTokeniser::tokenType_integer;
        source = original;

        if (parseDecimalLiteral (source))  return CtrlrLuaCodeTokeniser::tokenType_integer;
        source = original;

        return CtrlrLuaCodeTokeniser::tokenType_error;
    }

    template<class Iterator>
    static void skipQuotedString (Iterator& source) noexcept
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

    template<class Iterator>
    static void skipComment (Iterator& source) noexcept
    {
        bool lastWasStar = false;

        for (;;)
        {
            const juce_wchar c = source.nextChar();

            if (c == 0 || (c == '-' && lastWasStar))
                break;

            lastWasStar = (c == '-');
        }
    }

    template<class Iterator>
    static void skipPreprocessorLine (Iterator& source) noexcept
    {
        bool lastWasBackslash = false;

        for (;;)
        {
            const juce_wchar c = source.peekNextChar();

            if (c == '"')
            {
                skipQuotedString (source);
                continue;
            }

            if (c == '/')
            {
                Iterator next (source);
                next.skip();
                const juce_wchar c2 = next.peekNextChar();

                if (c2 == '/' || c2 == '*')
                    return;
            }

            if (c == 0)
                break;

            if (c == '\n' || c == '\r')
            {
                source.skipToEndOfLine();

                if (lastWasBackslash)
                    skipPreprocessorLine (source);

                break;
            }

            lastWasBackslash = (c == '\\');
            source.skip();
        }
    }

    template<class Iterator>
    static void skipIfNextCharMatches (Iterator& source, const juce_wchar c) noexcept
    {
        if (source.peekNextChar() == c)
            source.skip();
    }

    template<class Iterator>
    static void skipIfNextCharMatches (Iterator& source, const juce_wchar c1, const juce_wchar c2) noexcept
    {
        const juce_wchar c = source.peekNextChar();

        if (c == c1 || c == c2)
            source.skip();
    }

    template<class Iterator>
    static int readNextToken (Iterator& source)
    {
        int result = CtrlrLuaCodeTokeniser::tokenType_error;
        source.skipWhitespace();

        const juce_wchar firstChar = source.peekNextChar();

        switch (firstChar)
        {
        case 0:
            source.skip();
            break;

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
            result = parseNumber (source);

            if (result == CtrlrLuaCodeTokeniser::tokenType_error)
            {
                source.skip();

                if (firstChar == '.')
                    result = CtrlrLuaCodeTokeniser::tokenType_punctuation;
            }

            break;

        case ',':
        case ';':
        case ':':
            source.skip();
            result = CtrlrLuaCodeTokeniser::tokenType_punctuation;
            break;

        case '(':
        case ')':
        case '{':
        case '}':
        case '[':
        case ']':
            source.skip();
            result = CtrlrLuaCodeTokeniser::tokenType_bracket;
            break;

        case '"':
        case '\'':
            skipQuotedString (source);
            result = CtrlrLuaCodeTokeniser::tokenType_string;
            break;

        case '+':
            result = CtrlrLuaCodeTokeniser::tokenType_operator;
            source.skip();
            skipIfNextCharMatches (source, '+', '=');
            break;

        case '-':
            source.skip();
            result = parseNumber (source);

			if (source.peekNextChar() == '-')
			{
				result = CtrlrLuaCodeTokeniser::tokenType_comment;
                source.skipToEndOfLine();
			}
            else if (result == CtrlrLuaCodeTokeniser::tokenType_error)
            {
                result = CtrlrLuaCodeTokeniser::tokenType_operator;
                skipIfNextCharMatches (source, '-', '=');
            }
            break;

        case '*':
        case '%':
        case '=':
        case '!':
            result = CtrlrLuaCodeTokeniser::tokenType_operator;
            source.skip();
            skipIfNextCharMatches (source, '=');
            break;

        case '?':
        case '~':
            source.skip();
            result = CtrlrLuaCodeTokeniser::tokenType_operator;
            break;

        case '<':
        case '>':
        case '|':
        case '&':
        case '^':
            source.skip();
            result = CtrlrLuaCodeTokeniser::tokenType_operator;
            skipIfNextCharMatches (source, firstChar);
            skipIfNextCharMatches (source, '=');
            break;

        default:
            if (isIdentifierStart (firstChar))
                result = parseIdentifier (source);
            else
                source.skip();

            break;
        }

        return result;
    }

    /** A class that can be passed to the CppTokeniserFunctions functions in order to
        parse a String.
    */
    struct StringIterator
    {
        StringIterator (const String& s) noexcept                  : t (s.getCharPointer()), numChars (0) {}
        StringIterator (const String::CharPointerType& s) noexcept : t (s), numChars (0) {}

        juce_wchar nextChar() noexcept      { if (isEOF()) return 0; ++numChars; return t.getAndAdvance(); }
        juce_wchar peekNextChar()noexcept   { return *t; }
        void skip() noexcept                { if (! isEOF()) { ++t; ++numChars; } }
        void skipWhitespace() noexcept      { while (t.isWhitespace()) skip(); }
        void skipToEndOfLine() noexcept     { while (*t != '\r' && *t != '\n' && *t != 0) skip(); }
        bool isEOF() const noexcept         { return t.isEmpty(); }

        String::CharPointerType t;
        int numChars;
    };
};

#endif