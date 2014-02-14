#include "stdafx.h"
#include "CtrlrIDManager.h"
#include "CtrlrLog.h"
#include "CtrlrPropertyEditors/CtrlrPropertyComponent.h"

CtrlrIDManager::CtrlrIDManager() : ctrlrIdTree(Ids::ctrlr)
{
	XmlDocument contstantsDoc (String (BinaryData::CtrlrIDs_xml, BinaryData::CtrlrIDs_xmlSize));
	XmlDocument vendorsDoc (String (BinaryData::CtrlrMIDIVendors_xml, BinaryData::CtrlrMIDIVendors_xmlSize));

	{
		ScopedPointer <XmlElement> xml (contstantsDoc.getDocumentElement());
		if (xml)
		{
			ctrlrIdTree = ValueTree::fromXml (*xml);

			if (ctrlrIdTree.isValid())
				constantsTree = ctrlrIdTree.getChildWithName ("constants");
		}
	}

	{
		ScopedPointer <XmlElement> xml (vendorsDoc.getDocumentElement());
		if (xml)
		{
			vendorTree = ValueTree::fromXml (*xml);

			if (vendorTree.isValid())
			{
				/* let's sort it alphabeticaly */
				VendorComparator c;
				vendorTree.sort (c, nullptr, false);
			}
		}
	}
}

CtrlrIDManager::~CtrlrIDManager()
{
}

Array <var> CtrlrIDManager::toValueList (const StringArray &in)
{
	Array <var> ret;

	for (int i=0; i<in.size(); i++)
	{
		ret.add (in[i]);
	}

	return (ret);
}

StringArray CtrlrIDManager::getChoicesArray(const ValueTree &cid)
{
	StringArray r;
	StringArray toks;

	if (cid.getProperty("defaults").toString().startsWith("@"))
	{
		toks.addTokens (constantsTree.getChildWithProperty ( "name", cid.getProperty("defaults").toString().fromFirstOccurrenceOf("@", false,true) ).getProperty("value").toString(), ",", "\'\"");
	}
	else
	{
		toks.addTokens (cid.getProperty("defaults").toString(), ",", "\'\"");
	}

	for (int i=0; i<toks.size(); i++)
	{
		StringArray pairs;
		pairs.addTokens (toks[i], "=", "\'\"");

		if (pairs.size() == 2)
		{
			r.add (pairs[0]);
		}
		else
		{
			r.add (toks[i]);
		}
	}

	return (r);
}

StringArray CtrlrIDManager::getValuesArray(const ValueTree &cid)
{
	StringArray r;
	StringArray toks;

	if (cid.getProperty("defaults").toString().startsWith("@"))
	{
		toks.addTokens (constantsTree.getChildWithProperty ( "name", cid.getProperty("defaults").toString().fromFirstOccurrenceOf("@", false,true) ).getProperty("value").toString(), ",", "\'\"");
	}
	else
	{
		toks.addTokens (cid.getProperty("defaults").toString(),",","\'\"");
	}

	for (int i=0; i<toks.size(); i++)
	{
		StringArray pairs;
		pairs.addTokens (toks[i], "=", "\'\"");

		if (pairs.size() == 2)
		{
			r.add (pairs[1]);
		}
		else
		{
			r.add (toks[i]);
		}
	}

	return (r);
}


PropertyComponent *CtrlrIDManager::createComponentForProperty (const Identifier &propertyName, const ValueTree &propertyElement, CtrlrPanel *panel, StringArray *possibleChoices,  StringArray *possibleValues)
{
	ValueTree identifierDefinition = ctrlrIdTree.getChildWithProperty (Ids::name, propertyName.toString());

	StringArray choices;
	Array <var> values;

	if (possibleChoices != nullptr)
		choices = *possibleChoices;
	else
		choices = getChoicesArray(identifierDefinition);

	if (possibleValues != nullptr)
		values = toValueList(*possibleValues);
	else
		values = toValueList(getValuesArray(identifierDefinition));

	return (new CtrlrPropertyComponent (propertyName, propertyElement, identifierDefinition, panel, &choices, &values));
}

const String CtrlrIDManager::typeToString (const PropertyType t)
{
	switch (t)
	{
		case Numeric:
			return ("Numeric");
		case Text:
			return ("Text");
		case MultiLine:
			return ("MultiLine");
		case MultiLineSmall:
			return ("MultiLineSmall");
		case Bool:
			return ("Bool");
		case VarNumeric:
			return ("VarNumeric");
		case VarText:
			return ("VarText");
		case Colour:
			return ("Colour");
		case Font:
			return ("Font");
		case MultiMidi:
			return ("MultiMidi");
		case SysEx:
			return ("SysEx");
		case LuaMethod:
			return ("LuaMethod");
		case ActionButton:
			return ("ActionButton");
		case Expression:
			return ("Expression");
		case UnknownProperty:
			return ("UnknownProperty");
		case FileProperty:
			return ("FileProperty");
		case ReadOnly:
			return ("ReadOnly");
		case Timestamp:
			return ("Timestamp");
		case ModulatorList:
			return ("ModulatorList");
	}
	return ("");
}

const CtrlrIDManager::PropertyType CtrlrIDManager::stringToType (const String t)
{
	if (t == "Numeric")
	{
		return (Numeric);
	}
	else if (t == "Text")
	{
		return (Text);
	}
	else if (t == "MultiLine")
	{
		return (MultiLine);
	}
	else if (t == "MultiLineSmall")
	{
		return (MultiLineSmall);
	}
	else if (t == "Bool")
	{
		return (Bool);
	}
	else if (t == "VarNumeric")
	{
		return (VarNumeric);
	}
	else if (t == "VarText")
	{
		return (VarText);
	}
	else if (t == "Colour")
	{
		return (Colour);
	}
	else if (t == "Font")
	{
		return (Font);
	}
	else if (t == "MultiMidi")
	{
		return (MultiMidi);
	}
	else if (t == "SysEx")
	{
		return (SysEx);
	}
	else if (t == "LuaMethod")
	{
		return (LuaMethod);
	}
	else if (t == "ActionButton")
	{
		return (ActionButton);
	}
	else if (t == "Expression")
	{
		return (Expression);
	}
	else if (t == "UnknownProperty")
	{
		return (UnknownProperty);
	}
	else if (t == "FileProperty")
	{
		return (FileProperty);
	}
	else if (t == "ReadOnly")
	{
		return (ReadOnly);
	}
	else if (t == "Timestamp")
	{
		return (Timestamp);
	}
	else if (t == "ModulatorList")
	{
		return (ModulatorList);
	}

	return (Text);
}

const String CtrlrIDManager::getVendorForId (const MemoryBlock &vendorId)
{
	String idToMatch;

	if (vendorId.getSize() == 1)
		idToMatch = String::formatted ("%x%x%x", vendorId[0]);
	if (vendorId.getSize() == 3)
		idToMatch = String::formatted ("%x%x%x", vendorId[0], vendorId[1], vendorId[2]);

	return (vendorTree.getChildWithProperty ("id", idToMatch).getProperty(Ids::name));
}

const String CtrlrIDManager::getVendorForId (const String &vendorId)
{
	return (vendorTree.getChildWithProperty ("id", vendorId).getProperty(Ids::name));
}

ValueTree CtrlrIDManager::getVendorTree()
{
	return (vendorTree);
}
