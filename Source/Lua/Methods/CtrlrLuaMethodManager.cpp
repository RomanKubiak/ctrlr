#include "stdafx.h"
#include "CtrlrLuaMethodManager.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrLua/MethodEditor/CtrlrLuaMethodEditor.h"
#include "CtrlrLuaManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
#include "CtrlrComponents/CtrlrCustomComponent.h"
#include "CtrlrLog.h"
#include "CtrlrLuaObjectWrapper.h"
#include "CtrlrWindowManagers/CtrlrManagerWindowManager.h"

CtrlrLuaMethodManager::CtrlrLuaMethodManager(CtrlrLuaManager &_owner)
	: managerTree(Ids::luaManagerMethods),
		owner(_owner),
		methodTemplates("methods"),
		debug(false),
		emptyMethod(*this),
		currentMethodEditor(nullptr),
		utilityMethods(nullptr)
{
	XmlDocument methodsDocument(String(BinaryData::CtrlrLuaMethodTemplates_xml, BinaryData::CtrlrLuaMethodTemplates_xmlSize));

	ScopedPointer <XmlElement> methodsXml (methodsDocument.getDocumentElement().release());

	if (methodsXml)
	{
		methodTemplates = XmlElement(*methodsXml);
		utilityMethods  = methodTemplates.getChildByName("utilityMethods");
	}

	managerTree.addListener(this);
}

CtrlrLuaMethodManager::~CtrlrLuaMethodManager()
{
	currentMethodEditor = nullptr;
	managerTree.removeListener (this);
}

CtrlrLuaManager &CtrlrLuaMethodManager::getOwner()
{
	return (owner);
}

int CtrlrLuaMethodManager::getNumUtilities()
{
	if (utilityMethods)
	{
		return (utilityMethods->getNumChildElements());
	}

	return (0);
}

String CtrlrLuaMethodManager::getUtilityCode(const int index)
{
	XmlElement *utilityXml = utilityMethods->getChildElement (index);

	if (utilityXml)
	{
		if (utilityXml->hasTagName("utility"))
        {
            if (utilityXml->hasAttribute("resource"))
            {
                int resourceSize;
                const char *resourceData = BinaryData::getNamedResource (utilityXml->getStringAttribute("resource").toUTF8(), resourceSize);
                return (String (CharPointer_UTF8(resourceData)));
            }
            else
            {
                return (utilityXml->getAllSubText());
            }
        }
	}

	return  ("-- No code for utility index "+String(index));
}

String CtrlrLuaMethodManager::getUtilityName(const int index)
{
	XmlElement *utilityXml = utilityMethods->getChildElement (index);

	if (utilityXml)
	{
		if (utilityXml->hasTagName ("utility"))
			return (utilityXml->getStringAttribute ("name", ""));
	}

	return ("UNKNOWN");
}

bool CtrlrLuaMethodManager::getUtilityAlwaysUpdate(const int index)
{
	XmlElement *utilityXml = utilityMethods->getChildElement (index);

	if (utilityXml)
	{
		if (utilityXml->hasTagName ("utility"))
			return (utilityXml->getBoolAttribute ("alwaysUpdate", false));
	}

	return (false);
}

String CtrlrLuaMethodManager::getUtilityDescription(const int index)
{
	XmlElement *utilityXml = utilityMethods->getChildElement (index);

	if (utilityXml)
	{
		if (utilityXml->hasTagName ("utility"))
			return (utilityXml->getStringAttribute ("description", ""));
	}

	return ("");
}

String CtrlrLuaMethodManager::getUtilityUuid(const int index)
{
	XmlElement *utilityXml = utilityMethods->getChildElement (index);

	if (utilityXml)
	{
		if (utilityXml->hasTagName ("utility"))
			return (utilityXml->getStringAttribute ("uuid", ""));
	}

	return ("");
}

bool CtrlrLuaMethodManager::isLuaDisabled()
{
	return ((bool)owner.getOwner().getCtrlrManagerOwner().getProperty (Ids::ctrlrLuaDisabled));
}

void CtrlrLuaMethodManager::restoreState (const ValueTree &savedState)
{
	for (int i=0; i<savedState.getNumChildren(); i++)
	{
		if (savedState.getChild(i).hasType (Ids::luaMethodGroup))
		{
			restoreGroup (savedState.getChild(i));
		}
	}

	for (int i=0; i<savedState.getNumChildren(); i++)
	{
		if (savedState.getChild(i).hasType (Ids::luaMethod))
		{
			restoreMethod (savedState.getChild(i));
		}

		if (savedState.getChild(i).hasType (Ids::luaMethodGroup))
		{
			restoreMethodsRecursivly (savedState.getChild(i));
		}
	}
}

void CtrlrLuaMethodManager::restoreGroup (const ValueTree &savedState, const Uuid parentUuid)
{
	addGroup (savedState.getProperty (Ids::name), parentUuid, Uuid(savedState.getProperty(Ids::uuid).toString()));

	/* let's be recursive */
	for (int i=0; i<savedState.getNumChildren(); i++)
	{
		if (savedState.getChild(i).hasType (Ids::luaMethodGroup))
		{
			restoreGroup (savedState.getChild(i), Uuid(savedState.getProperty(Ids::uuid).toString()));
		}

		if (savedState.getChild(i).hasType (Ids::luaMethod))
		{
			continue; //restoreMethod (savedState.getChild(i), parentUuid);
		}
	}
}

void CtrlrLuaMethodManager::removeGroup(ValueTree groupToRemove)
{
	ValueTree parent = groupToRemove.getParent();

	for (int i=0; i<groupToRemove.getNumChildren(); i++)
	{
		ValueTree child = groupToRemove.getChild(i);
		if (child.isValid() && child.hasType(Ids::luaMethod))
		{
			removeMethod (child.getProperty(Ids::uuid).toString());
		}
	}
	parent.removeChild (groupToRemove, nullptr);
}

void CtrlrLuaMethodManager::addGroup (const String &groupName, const Uuid parentUuid, const Uuid groupUuid)
{
	if (parentUuid.isNull())
	{
		managerTree.addChild (getDefaultGroupTree(groupName, groupUuid), -1, nullptr);
	}
	else
	{
		if (getGroupByUuid (parentUuid).isValid())
		{
			getGroupByUuid (parentUuid).addChild (getDefaultGroupTree(groupName, groupUuid), -1, nullptr);
		}
	}
	// Notify the panel about the modification
	owner.getOwner().luaManagerChanged();
}

void CtrlrLuaMethodManager::restoreMethod (const ValueTree &savedState, const Uuid parentUuid)
{
	if ((int)savedState.getProperty(Ids::luaMethodSource) == (int)CtrlrLuaMethod::codeInFile)
	{
		addMethodFromFile	(getGroupByUuid(parentUuid),
								owner.getOwner().getLuaMethodSourceFile(&savedState),
								Uuid(savedState.getProperty(Ids::uuid).toString()));
	}
	else
	{
		addMethod			(getGroupByUuid(parentUuid),
								savedState.getProperty(Ids::luaMethodName),
								savedState.getProperty(Ids::luaMethodCode),
								savedState.getProperty(Ids::luaMethodLinkedProperty),
								savedState.getProperty(Ids::uuid).toString());
	}
}

void CtrlrLuaMethodManager::restoreMethodsRecursivly(const ValueTree &savedState, const Uuid parentUuid)
{
	for (int i=0; i<savedState.getNumChildren(); i++)
	{
		if (savedState.getChild(i).hasType(Ids::luaMethodGroup))
		{
			restoreMethodsRecursivly (savedState.getChild(i), parentUuid);
		}

		if (savedState.getChild(i).hasType(Ids::luaMethod))
		{
			restoreMethod (savedState.getChild(i), savedState.getProperty(Ids::uuid).toString());
		}
	}
}

void CtrlrLuaMethodManager::addMethod (ValueTree groupToAddTo, const String &methodName, const String &initialCode, const String &linkedToProperty, const Uuid methodUid, const bool forceIfAlreadyExists)
{
	ValueTree group;

	if (groupToAddTo.isValid())
		group = groupToAddTo;
	else
		group = managerTree;

	if (group.getChildWithProperty(Ids::uuid, methodUid.toString()).isValid() && forceIfAlreadyExists)
	{
		group.removeChild (group.getChildWithProperty(Ids::uuid, methodUid.toString()), nullptr);
	}

	group.addChild (getDefaultMethodTree (methodName, initialCode, linkedToProperty, methodUid), -1, nullptr);

	// Notify the panel about the modification
	owner.getOwner().luaManagerChanged();
}

void CtrlrLuaMethodManager::addMethodFromFile (ValueTree groupToAddTo, const File &fileToUse, const Uuid methodUid)
{
	if (groupToAddTo.isValid())
	{
		groupToAddTo.addChild (getDefaultMethodTree (fileToUse, methodUid), -1, nullptr);
	}
	else
	{
		managerTree.addChild (getDefaultMethodTree (fileToUse, methodUid), -1, nullptr);
	}

	// Notify the panel about the modification
	owner.getOwner().luaManagerChanged();
}

void CtrlrLuaMethodManager::valueTreeChildAdded (ValueTree& parentTree, ValueTree& child)
{
	if (child.hasType(Ids::luaMethod))
	{
		methods.add (new CtrlrLuaMethod (*this, child));
	}
}

void CtrlrLuaMethodManager::deleteMethod(const Uuid &methodUuid)
{
}

void CtrlrLuaMethodManager::valueTreeChildRemoved (ValueTree& parentTree, ValueTree& child, int)
{
    if (child.hasType(Ids::luaMethod))
    {
        methods.removeObject (getMethodByUuid(child.getProperty(Ids::uuid).toString()));
    }
}

void CtrlrLuaMethodManager::setEditedMethod(const Uuid &methodUuid)
{
	if (currentMethodEditor)
	{
		currentMethodEditor->setEditedMethod (methodUuid);
	}
}

void CtrlrLuaMethodManager::setEditedMethod(const String &methodName)
{
	if (currentMethodEditor)
	{
		if (getMethodByName (methodName))
		{
			currentMethodEditor->setEditedMethod (getMethodByName (methodName)->getUuid());
		}
	}
}

const String CtrlrLuaMethodManager::getMethodListForCombo()
{
	String ret;
	return (ret.upToLastOccurrenceOf (":", false, false));
}

void CtrlrLuaMethodManager::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
}

CtrlrLuaMethod *CtrlrLuaMethodManager::getMethodByName(const String &methodName)
{
	for (int i=0; i<methods.size(); i++)
	{
		if (methods[i]->getName() == methodName)
		{
			return (methods[i]);
		}
	}
	return (nullptr);
}

CtrlrLuaMethod *CtrlrLuaMethodManager::getMethodByUuid(const Uuid &methodUuid)
{
	for (int i=0; i<methods.size(); i++)
	{
		if (methods[i]->getUuid() == methodUuid)
		{
			return (methods[i]);
		}
	}

	return (nullptr);
}

ValueTree CtrlrLuaMethodManager::getGroupByUuid(const Uuid &groupUuid)
{
	if (managerTree.getChildWithProperty (Ids::uuid, groupUuid.toString()).isValid())
	{
		return (managerTree.getChildWithProperty (Ids::uuid, groupUuid.toString()));
	}
	else
	{
		for (int i=0; i<managerTree.getNumChildren(); i++)
		{
			if (managerTree.getChild(i).hasType(Ids::luaMethodGroup) && managerTree.getChild(i).getNumChildren() > 0)
			{
				ValueTree foundGroup = findGroupRecursive (managerTree.getChild(i), groupUuid);
				if (foundGroup.isValid())
				{
					return (foundGroup);
				}
			}
		}
	}

	return (ValueTree());
}

ValueTree CtrlrLuaMethodManager::findGroupRecursive(ValueTree treeToSearch, const Uuid &groupUuid)
{
	for (int i=0; i<treeToSearch.getNumChildren(); i++)
	{
		if (treeToSearch.getChild(i).hasType(Ids::luaMethodGroup))
		{
			if (treeToSearch.getChild(i).getProperty(Ids::uuid) == groupUuid.toString())
			{
				return (treeToSearch.getChild(i));
			}
			else
			{
				ValueTree t = findGroupRecursive(treeToSearch.getChild(i), groupUuid);
				if (t.isValid())
				{
					return (t);
				}
			}
		}
	}
	return (ValueTree());
}

const String CtrlrLuaMethodManager::cleanupMethod(XmlElement *methodElement, const String &methodName)
{
    String methodCode = "";
    String value;
    StringArray lines;

    if (methodElement->hasAttribute("resource"))
    {
        const String resourceName = methodElement->getStringAttribute ("resource");
        int resourceSize = 0;
        const char *resourceData = BinaryData::getNamedResource (resourceName.toUTF8(), resourceSize);

        if (resourceData && resourceSize > 0)
        {
            value = String (CharPointer_UTF8(resourceData));
        }
    }
    else
    {
        methodCode = methodElement->getAllSubText();
        lines.addTokens (methodCode, "\n", "");

        for (int i=0; i<lines.size(); i++)
        {
            value << lines[i].trim() << "\n";
        }
    }

	return (value.replace ("__method_name", methodName, false).trim());
}

const String CtrlrLuaMethodManager::getTemplateForProperty(const String &methodName, const String &propertyName)
{
	forEachXmlChildElement (methodTemplates, e)
	{
		if (e->hasTagName("luaMethod"))
		{
			String linkedNames = e->getStringAttribute("name");
			StringArray ar;
			ar.addTokens (linkedNames, ",", "\"\'");

			for (int i=0; i<ar.size(); i++)
			{
				if (ar[i] == propertyName)
				{
                    return (cleanupMethod (e, methodName));
				}
			}
		}
	}

	_ERR("CtrlrLuaMethodManager::getTemplateForProperty failed to find template for this method \""+methodName+"\" propertyName \""+propertyName+"\"");
	return ("");
}

const StringArray CtrlrLuaMethodManager::getMethodList()
{
	StringArray ret;

	for (int i=0; i<methods.size(); i++)
	{
		ret.add (methods[i]->getName());
	}

	return (ret);
}

const StringArray CtrlrLuaMethodManager::getTemplateList()
{
	StringArray ret;
	ret.add(COMBO_NONE_ITEM);
	forEachXmlChildElement (methodTemplates, el)
	{
		if (el->hasTagName(Ids::luaMethod.toString()))
		{
			ret.add (el->getStringAttribute ("name", ""));
		}
	}

	return (ret);
}

const String CtrlrLuaMethodManager::getDefaultMethodCode(const String &methodName, const String &linkedToProperty)
{
	if (linkedToProperty.isEmpty() || linkedToProperty == COMBO_NONE_ITEM)
	{
		return ("function "+methodName+"()\n\t-- Your method code here\nend");
	}
	else
	{
		return (getTemplateForProperty(methodName, linkedToProperty));
	}
}

ValueTree CtrlrLuaMethodManager::getDefaultMethodTree(const String &methodName, const String &methodCode, const String &methodProperty, const Uuid methodUuid)
{
	ValueTree methodTree (Ids::luaMethod);
	methodTree.setProperty (Ids::luaMethodName, methodName, nullptr);

	if (methodCode.isEmpty())
		methodTree.setProperty (Ids::luaMethodCode, getDefaultMethodCode(methodName, methodProperty), nullptr);
	else
		methodTree.setProperty (Ids::luaMethodCode, methodCode, nullptr);

	methodTree.setProperty (Ids::luaMethodLinkedProperty, methodProperty, nullptr);
	methodTree.setProperty (Ids::luaMethodSource, (int)CtrlrLuaMethod::codeInProperty, nullptr);
	methodTree.setProperty (Ids::uuid, methodUuid.isNull() ? Uuid().toString() : methodUuid.toString(), nullptr);
	return (methodTree);
}

ValueTree CtrlrLuaMethodManager::getDefaultMethodTree(const File &methodFileSource, const Uuid methodUuid)
{
	ValueTree methodTree (Ids::luaMethod);
	methodTree.setProperty (Ids::luaMethodName, methodFileSource.getFileNameWithoutExtension(), nullptr);

	File panelLuaDir = getOwner().getOwner().getPanelLuaDir();
	if (panelLuaDir.exists() && panelLuaDir.isDirectory() && methodFileSource.isAChildOf(panelLuaDir))
	{	// Try and get realtive path
		methodTree.setProperty(Ids::luaMethodSourcePath, methodFileSource.getRelativePathFrom(panelLuaDir), nullptr);
	}
	else
	{
		methodTree.setProperty(Ids::luaMethodSourcePath, methodFileSource.getFullPathName(), nullptr);
	}
	methodTree.setProperty (Ids::luaMethodSource, (int)CtrlrLuaMethod::codeInFile, nullptr);
	methodTree.setProperty (Ids::uuid, methodUuid.isNull() ? Uuid().toString() : methodUuid.toString(), nullptr);
	return (methodTree);
}

ValueTree CtrlrLuaMethodManager::getDefaultGroupTree(const String &groupName, const Uuid groupUid)
{
	ValueTree group(Ids::luaMethodGroup);
	group.setProperty (Ids::name, groupName, nullptr);
	if (groupUid.isNull())
	{
		group.setProperty (Ids::uuid, Uuid().toString(), nullptr);
	}
	else
	{
		group.setProperty (Ids::uuid, groupUid.toString(), nullptr);
	}

	return (group);
}

bool CtrlrLuaMethodManager::isValidMethodName(const String &methodName)
{
	if (methodName.indexOfAnyOf ("0123456789", 0, false) == 0)
	{
		jassertfalse;			// functions cant start with numbers
		return (false);
	}

	if (!methodName.containsOnly ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"))
	{
		jassertfalse;			// functions can contain only numbers letter and underscores
		return (false);
	}

	return (true);
}

void CtrlrLuaMethodManager::setMethodEditor(CtrlrLuaMethodEditor *_currentMethodEditor)
{
	currentMethodEditor = _currentMethodEditor;
}

void CtrlrLuaMethodManager::removeMethod (const Uuid methodUuid)
{
	CtrlrLuaMethod *method = getMethodByUuid(methodUuid);
	if (method)
	{
		ValueTree child  = method->getMethodTree();
		ValueTree parent = child.getParent();

        method->remove();
		parent.removeChild (child, nullptr);

		methods.removeObject (method);
	}
}

const int CtrlrLuaMethodManager::getNumMethods()
{
	return (methods.size());
}

CtrlrLuaMethod *CtrlrLuaMethodManager::getMethodByIndex(const int index)
{
	return (methods[index]);
}

ValueTree CtrlrLuaMethodManager::getGroupByName(const String &groupName)
{
	for (int i=0; i<getManagerTree().getNumChildren(); i++)
	{
		if (getManagerTree().getChild(i).hasType(Ids::luaMethodGroup) && groupName == getManagerTree().getChild(i).getProperty(Ids::name).toString())
		{
			return (getManagerTree().getChild(i));
		}
	}

	return (ValueTree());
}

const bool CtrlrLuaMethodManager::attachDefaultGroups()
{
    bool ret = false;

    if (!getGroupByName("Built-In").isValid())
	{
		addGroup ("Built-In", Uuid::null(), Uuid());
		ret = true;
	}

	return (ret);
}

void CtrlrLuaMethodManager::wrapUtilities()
{
	if (getNumUtilities() > 0)
	{
	    attachDefaultGroups();

		for (int i=0; i<getNumUtilities(); i++)
		{
			addMethod (getGroupByName("Built-In"), getUtilityName(i), getUtilityCode(i).trim(), "", getUtilityUuid(i), getUtilityAlwaysUpdate(i));
		}
	}
}
