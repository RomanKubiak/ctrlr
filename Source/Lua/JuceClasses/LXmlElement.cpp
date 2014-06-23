#include "stdafx.h"
#include "LXmlElement.h"

void LXmlElement::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<XmlElement>("XmlElement")
			.def(constructor<const String &>())
			.def(constructor<const XmlElement &>())
			.def(constructor<const char *>())
			.def("isEquivalentTo", &XmlElement::isEquivalentTo)
			.def("createDocument", &XmlElement::createDocument)
			.def("writeToStream", &XmlElement::writeToStream)
			.def("writeToFile", &XmlElement::writeToFile)
			.def("getTagName", &XmlElement::getTagName)
			.def("getNamespace", &XmlElement::getNamespace)
			.def("getTagNameWithoutNamespace", &XmlElement::getTagNameWithoutNamespace)
			.def("hasTagName", &XmlElement::hasTagName)
			.def("hasTagNameIgnoringNamespace", &XmlElement::hasTagNameIgnoringNamespace)
			.def("getNumAttributes", &XmlElement::getNumAttributes)
			.def("getAttributeName", &XmlElement::getAttributeName)
			.def("getAttributeValue", &XmlElement::getAttributeValue)
			.def("hasAttribute", &XmlElement::hasAttribute)
			.def("getStringAttribute", (const String &(XmlElement::*)(StringRef) const) &XmlElement::getStringAttribute)
			.def("getStringAttribute", (String (XmlElement::*)(StringRef, const String &) const) &XmlElement::getStringAttribute)
			.def("compareAttribute", &XmlElement::compareAttribute)
			.def("getIntAttribute", &XmlElement::getIntAttribute)
			.def("getDoubleAttribute", &XmlElement::getDoubleAttribute)
			.def("getBoolAttribute", &XmlElement::getBoolAttribute)
			.def("setAttribute", (void (XmlElement::*)(const Identifier &, const String &)) &XmlElement::setAttribute)
			.def("setAttribute", (void (XmlElement::*)(const Identifier &, int)) &XmlElement::setAttribute)
			.def("setAttribute", (void (XmlElement::*)(const Identifier &, double)) &XmlElement::setAttribute)
			.def("removeAttribute", &XmlElement::removeAttribute)
			.def("removeAllAttributes", &XmlElement::removeAllAttributes)
			.def("getFirstChildElement", &XmlElement::getFirstChildElement)
			.def("getNextElement", &XmlElement::getNextElement)
			.def("getNextElementWithTagName", &XmlElement::getNextElementWithTagName)
			.def("getNumChildElements", &XmlElement::getNumChildElements)
			.def("getChildElement", &XmlElement::getChildElement)
			.def("getChildByName", &XmlElement::getChildByName)
			.def("getChildByAttribute", &XmlElement::getChildByAttribute)
			.def("addChildElement", &XmlElement::addChildElement)
			.def("insertChildElement", &XmlElement::insertChildElement)
			.def("prependChildElement", &XmlElement::prependChildElement)
			.def("createNewChildElement", &XmlElement::createNewChildElement)
			.def("replaceChildElement", &XmlElement::replaceChildElement)
			.def("removeChildElement", &XmlElement::removeChildElement)
			.def("deleteAllChildElements", &XmlElement::deleteAllChildElements)
			.def("deleteAllChildElementsWithTagName", &XmlElement::deleteAllChildElementsWithTagName)
			.def("containsChildElement", &XmlElement::containsChildElement)
			.def("findParentElementOf", &XmlElement::findParentElementOf)
            .def("isTextElement", &XmlElement::isTextElement)
            .def("getText", &XmlElement::getText)
            .def("setText", &XmlElement::setText)
            .def("getAllSubText", &XmlElement::getAllSubText)
            .def("getChildElementAllSubText", &XmlElement::getChildElementAllSubText)
            .def("addTextElement", &XmlElement::addTextElement)
            .def("deleteAllTextElements", &XmlElement::deleteAllTextElements)
            .def("getChildElementAllSubText", &XmlElement::getChildElementAllSubText)
            .scope[
                def("createTextElement", &XmlElement::createTextElement)
            ]
        ,
        class_<XmlDocument>("XmlDocument")
            .def(constructor<const String &>())
            .def(constructor<const File &>())
            .def("getDocumentElement", &XmlDocument::getDocumentElement)
            .def("getLastParseError", &XmlDocument::getLastParseError)
            .def("setInputSource", &XmlDocument::setInputSource)
            .def("setEmptyTextElementsIgnored", &XmlDocument::setEmptyTextElementsIgnored)
            .scope[
                def("parse", (XmlElement *(*)(const File &))&XmlDocument::parse),
                def("parse", (XmlElement *(*)(const String &))&XmlDocument::parse)
            ]
    ];
}
