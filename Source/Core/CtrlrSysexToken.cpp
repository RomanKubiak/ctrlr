#include "stdafx.h"
#include "CtrlrSysexToken.h"

CtrlrSysexToken::CtrlrSysexToken(const int _tokenPosition, const char _tokenIdentifier, const CtrlrSysExFormulaToken _tokenType, const int _tokenAdditionalData)
	:	tokenIdentifier(_tokenIdentifier),
		tokenType(_tokenType),
		tokenPosition(_tokenPosition),
		tokenAdditionalData(_tokenAdditionalData)
{
}

CtrlrSysexToken::~CtrlrSysexToken()
{
}

const int CtrlrSysexToken::getAdditionalData() const
{
	return (tokenAdditionalData);
}

void CtrlrSysexToken::setAdditionalData(const int _tokenAdditionalData)
{
	if (tokenType == GlobalVariable)
	{
		switch (tokenIdentifier)
		{
			case 'o':
				tokenAdditionalData = 16 + _tokenAdditionalData;
				break;
			case 'p':
				tokenAdditionalData = 32 + _tokenAdditionalData;
				break;
			case 'n':
				tokenAdditionalData = 48 + _tokenAdditionalData;
				break;
			case 'k':
				tokenAdditionalData = _tokenAdditionalData;
			default:
				break;
		}
	}
	else
	{
		tokenAdditionalData = _tokenAdditionalData;
	}
}

const CtrlrSysExFormulaToken CtrlrSysexToken::getType() const
{
	return (tokenType);
}

void CtrlrSysexToken::setType (const CtrlrSysExFormulaToken _tokenType)
{
	tokenType = _tokenType;
}

const int CtrlrSysexToken::getPosition() const
{
	return (tokenPosition);
}

void CtrlrSysexToken::setPosition(const int _tokenPosition)
{
	tokenPosition = _tokenPosition;
}

const bool CtrlrSysexToken::isHoldingValue()
{
	if (		tokenType == ByteValue
			||	tokenType == LSB7bitValue
			||	tokenType == MSB7bitValue
			||	tokenType == LSB4bitValue
			||	tokenType == MSB4bitValue
			)
	{
		return (true);
	}

	return (false);
}
