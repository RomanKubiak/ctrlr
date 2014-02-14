#include "stdafx.h"
#include "LURL.h"

void LURL::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<URL>("URL")
			.def(constructor<const String &>())
			.def("toString", &URL::toString)
			.def("isWellFormed", &URL::isWellFormed)
			.def("getDomain", &URL::getDomain)
			.def("getSubPath", &URL::getSubPath)
			.def("getScheme", &URL::getScheme)
			.def("withNewSubPath", &URL::withNewSubPath)
			.def("withParameter", &URL::withParameter)
			.def("withFileToUpload", &URL::withFileToUpload)
			.def("withPOSTData", &URL::withPOSTData)
			.def("getPostData", &URL::getPostData)
			.def("launchInDefaultBrowser", &URL::launchInDefaultBrowser)
			.def("isProbablyAWebsiteURL", &URL::isProbablyAWebsiteURL)
			.def("isProbablyAnEmailAddress", &URL::isProbablyAnEmailAddress)
			.def("readEntireTextStream", &URL::readEntireTextStream)
			.def("readEntireXmlStream", &URL::readEntireXmlStream)
			.def("readEntireBinaryStream", &URL::readEntireBinaryStream)
			.def("addEscapeChars", &URL::addEscapeChars)
			.def("removeEscapeChars", &URL::removeEscapeChars)
	];
}