#include "stdafx.h"
#include "LValueTree.h"

void LValueTree::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Identifier>("Identifier")
				.def(constructor<const char *>())
				.def(constructor<const String &>())
				.def("toString", &Identifier::toString)
				.scope
				[
					def("isValidIdentifier", &Identifier::isValidIdentifier)
				]
		,
			class_<var>("var")
				.def(constructor<const var &>())
				.def(constructor<int>())
				.def(constructor<int64>())
				.def(constructor<bool>())
				.def(constructor<double>())
				.def(constructor<const char *>())
				.def(constructor<const wchar_t *>())
				.def(constructor<const String &>())
		,
			class_<ValueTree>("ValueTree")
				.def(constructor<>())
				.def(constructor<const ValueTree &>())
				.def(constructor<const Identifier &>())
				.def("isEquivalentTo", &ValueTree::isEquivalentTo)
				.def("isValid", &ValueTree::isValid)
				.def("createCopy", &ValueTree::createCopy)
				.def("getType", &ValueTree::getType)
				.def("hasType", &ValueTree::hasType)
				.def("getProperty", (var (ValueTree::*)(const Identifier, const var &) const) &ValueTree::getProperty)
				.def("getProperty", (const var &(ValueTree::*)(const Identifier) const) &ValueTree::getProperty)
				.def("setProperty", &ValueTree::setProperty)
				.def("hasProperty", &ValueTree::hasProperty)
				.def("removeProperty", &ValueTree::removeProperty)
				.def("removeAllProperties", &ValueTree::removeAllProperties)
				.def("getNumProperties", &ValueTree::getNumProperties)
				.def("getPropertyName", &ValueTree::getPropertyName)
				.def("getNumChildren", &ValueTree::getNumChildren)
				.def("getChild", &ValueTree::getChild)
				.def("getChildWithName", &ValueTree::getChildWithName)
				.def("getOrCreateChildWithName", &ValueTree::getOrCreateChildWithName)
				.def("getChildWithProperty", &ValueTree::getChildWithProperty)
				.def("addChild", &ValueTree::addChild)
				.def("removeChild", (void(ValueTree::*)(const ValueTree &, UndoManager *))&ValueTree::removeChild)
				.def("removeChild", (void(ValueTree::*)(const int, UndoManager *))&ValueTree::removeChild)
				.def("removeAllChildren", &ValueTree::removeAllChildren)
				.def("moveChild", &ValueTree::moveChild)
				.def("isAChildOf", &ValueTree::isAChildOf)
				.def("indexOf", &ValueTree::indexOf)
				.def("getParent", &ValueTree::getParent)
				.def("getSibling", &ValueTree::getSibling)
				.def("createXml", &ValueTree::createXml)
				.def("toXmlString", &ValueTree::toXmlString)
				.def("writeToStream", &ValueTree::writeToStream)
				.def("addListener", &ValueTree::addListener)
				.def("removeListener", &ValueTree::removeListener)
				.def("sendPropertyChangeMessage", &ValueTree::sendPropertyChangeMessage)
	];
}