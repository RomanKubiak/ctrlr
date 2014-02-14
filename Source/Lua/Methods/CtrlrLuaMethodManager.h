#ifndef __CTRLR_LUA_METHOD_MANAGER__
#define __CTRLR_LUA_METHOD_MANAGER__

#include "CtrlrMidiMessage.h"
#include "CtrlrLuaMethod.h"
#include "MIDI/CtrlrMIDILibrary/CtrlrMIDILibrary.h"

class CtrlrPanel;
class CtrlrModulator;
class CtrlrLuaManager;
class CtrlrCustomComponent;
class CtrlrLuaGraphics;
class CtrlrLuaFile;
class CtrlrLuaMethodEditor;
class CtrlrWaveform;
class CtrlrPanelCanvas;
class CtrlrComponent;

class CtrlrLuaMethodManager : public ValueTree::Listener
{
	public:
		CtrlrLuaMethodManager(CtrlrLuaManager &_owner);
		~CtrlrLuaMethodManager();
		void restoreState (const ValueTree &savedState);
		CtrlrLuaManager &getOwner();

		CtrlrLuaMethod *getMethodByUuid(const Uuid &methodUuid);
		CtrlrLuaMethod *getMethodByName(const String &methodName);
		CtrlrLuaMethod *getMethod(const String &methodName) { return (getMethodByName(methodName)); }
		ValueTree getGroupByUuid(const Uuid &groupUuid);

		const String getMethodListForCombo();

		void restoreMethod (const ValueTree &savedState, const Uuid parentUuid=UID_NULL);
		void removeMethod (const Uuid methodUuid=UID_NULL);
		void restoreMethodsRecursivly(const ValueTree &savedState, const Uuid parentUuid=UID_NULL);
		void restoreGroup (const ValueTree &savedState, const Uuid parentUuid=UID_NULL);
		void removeGroup(ValueTree groupToRemove);
		void addGroup (const String &groupName, const Uuid parentUuid=UID_NULL, const Uuid groupUuid=UID_NULL);
		const bool attachDefaultGroups();
		ValueTree getGroupByName(const String &groupName);
		ValueTree findGroupRecursive(ValueTree treeToSearch, const Uuid &groupUuid);

		void addMethod (ValueTree groupToAddTo, const String &methodName, const String &initialCode, const String &linkedToProperty, const Uuid methodUuid=UID_NULL);
		void addMethodFromFile (ValueTree groupToAddTo, const File &fileToUse, const Uuid methodUuid=UID_NULL);
		void deleteMethod(const Uuid &methodUuid);

		void setEditedMethod(const Uuid &methodUid);
		void setEditedMethod(const String &methodName);
		void setMethodEditor(CtrlrLuaMethodEditor *_currentMethodEditor);

		const String getTemplateForProperty(const String &methodName, const String &propertyName);

		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
		void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
		void valueTreeChildAdded (ValueTree& parentTree, ValueTree& child);
		void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& child);
		void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}

		bool isLuaDisabled();
		ValueTree &getManagerTree()											{ return (managerTree); }
		void setDebug(const bool _debug)									{ debug = _debug; }
		const bool getDebug()												{ return (debug); }
		const StringArray getMethodList();
		const StringArray getTemplateList();
		const String getDefaultMethodCode (const String &methodName, const String &propertyToLinkTo);
		const int getNumMethods();
		CtrlrLuaMethod *getMethodByIndex(const int index);
		const String cleanupMethod(const String &methodCode, const String &methodName);
		ValueTree getDefaultGroupTree(const String &groupName, const Uuid groupUuid=UID_NULL);
		ValueTree getDefaultMethodTree(const String &methodName, const String &methodCode, const String &methodProperty, const Uuid methodUuid);
		ValueTree getDefaultMethodTree(const File &methodFileSource, const Uuid methodUuid);
		static bool isValidMethodName(const String &methodName);
		int getNumUtilities();
		String getUtilityCode(const int index);
		String getUtilityName(const int index);
		String getUtilityDescription(const int index);
		String getUtilityUuid(const int index);
		void wrapUtilities();

		/** Calls */
		const bool call(CtrlrLuaMethod *o, CtrlrModulator *param1, const int param2);
		const bool call(CtrlrLuaMethod *o, CtrlrModulator *param1, const String param2);
		const bool call(CtrlrLuaMethod *o, CtrlrComponent *param1, const String param2);
		const bool call(CtrlrLuaMethod *o, CtrlrModulator *param1, const File &param2);
		const bool call(CtrlrLuaMethod *o, CtrlrCustomComponent *param1);
		const bool call(CtrlrLuaMethod *o, CtrlrWaveform *param1);
		const bool call(CtrlrLuaMethod *o, CtrlrCustomComponent *param1, Graphics &param2);
		const bool call(CtrlrLuaMethod *o, CtrlrPanelCanvas *param1, Graphics &param2);
		const bool call(CtrlrLuaMethod *o, CtrlrPanel *param1);
		const bool call(CtrlrLuaMethod *o, CtrlrCustomComponent *param1, const MouseEvent &param2);
		const bool call(CtrlrLuaMethod *o, CtrlrCustomComponent *param1, const MouseEvent &param2, float param3, float param4);
		const bool call(CtrlrLuaMethod *o, const CtrlrMidiMessage &param1);
		const bool call(CtrlrLuaMethod *o, const MidiMessage &param1);
		const bool call(CtrlrLuaMethod *o, const int param1, const int param2, const int param3, luabind::object const &param4);
		const bool call(CtrlrLuaMethod *o, const int param1, const int param2, const int param3);
		const bool call(CtrlrLuaMethod *o, const int param1, const int param2);
		const bool call(CtrlrLuaMethod *o, const int param1, const File &param2);
		const bool call(CtrlrLuaMethod *o, const String &param1, const CtrlrNotificationType param2);
		const bool call(CtrlrLuaMethod *o);
		const bool call(CtrlrLuaMethod *o, const StringArray &param1, const int param2, const int param3);
		const bool call(CtrlrLuaMethod *o, const StringArray &param1);
		const bool call(CtrlrLuaMethod *o, CtrlrMIDITransaction *midiTransaction);
		const bool call(CtrlrLuaMethod *o, const ValueTree &param1, luabind::object &param2);
		const bool call(CtrlrLuaMethod *o, const ValueTree &param1, CtrlrMIDILibraryRequest *param2);
		const bool call(CtrlrLuaMethod *o, CtrlrMIDILibraryRequest *param2);
		const bool call(CtrlrLuaMethod *o, CtrlrMIDITransaction *midiTransaction, MemoryBlock *destinationMemoryBlock);

		int callWithRet(CtrlrLuaMethod *o, CtrlrMIDITransaction *midiTransaction, ValueTree valueTree);
		int callWithRet(CtrlrLuaMethod *o, ValueTree valueTree1, ValueTree valueTree2);
		int callWithRet(CtrlrLuaMethod *o, CtrlrModulator *param1, const int param2);
		int callWithRet(CtrlrLuaMethod *o, CtrlrModulator *param1, const CtrlrMidiMessage &param2, const int param3);

		JUCE_LEAK_DETECTOR(CtrlrLuaMethodManager)

	private:
		bool debug;
		String lastExecutionError;
		ValueTree managerTree;
		OwnedArray <CtrlrLuaMethod> methods;
		CtrlrLuaManager &owner;
		XmlElement methodTemplates;
		XmlElement *utilityMethods;
		CtrlrLuaMethod emptyMethod;
		CriticalSection methodManagerCriticalSection;
		WeakReference <CtrlrLuaMethodEditor> currentMethodEditor;
};

#endif
