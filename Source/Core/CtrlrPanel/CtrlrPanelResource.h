#ifndef __CTRLR_PANEL_RESOURCE__
#define __CTRLR_PANEL_RESOURCE__

#include "CtrlrPanelResourceManager.h"

class CtrlrPanel;

//==============================================================================
/** One Ctrlr resource, can be any block of data. Resources are stored in the resources
	folder in the user preferences directory.

*/
class CtrlrPanelResource : public ValueTree::Listener
{
	public:
		CtrlrPanelResource (CtrlrPanelResourceManager &_owner, const File &_resourceDataFile, const File &_resourceSourceFile, const String _resourceName=String::empty);
		~CtrlrPanelResource();
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &treeWhoseChildHasChanged){}
		void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged){}
		void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded){}
		void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved){}
		void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved){}
		const Image asImage();
		const String asText();
		const Font asFont();
		const XmlElement *asXml();
		AudioFormatReader *asAudioFormat();
		const MemoryBlock &asData();
		const int64 getHashCode();
		const String getName();
		const int64 getSize();
		const double getSizeDouble();
		const bool isLoaded();
		File &getFile();
		File getSourceFile();
		void load();
		void loadIfNeeded();
		ValueTree createTree();
		const CtrlrPanelResourceManager::CtrlrPanelResourceType getType();
		const String getTypeDescription();
		bool reloadFromSourceFile();
		ValueTree &getResourceTree();
		Time getLoadedTime();
		void setProperty (const Identifier& name, const var &newValue, const bool isUndoable=true);
		const var &getProperty (const Identifier& name) const											{ return resourceTree.getProperty (name); }
		const var getProperty (const Identifier& name, const var &defaultReturnValue) const				{ return resourceTree.getProperty (name, defaultReturnValue); }
		void calculateHash();
		JUCE_LEAK_DETECTOR(CtrlrPanelResource)

	private:
		ValueTree resourceTree;
		WeakReference<CtrlrPanelResource>::Master masterReference;
        friend class WeakReference<CtrlrPanelResource>;
		MemoryBlock data;
		String resourceName;
		int resourceHashCode;
		File resourceDataFile;
		bool resourceLoaded;
		AudioFormatReader *audioFormatReader;
		CtrlrPanelResourceManager::CtrlrPanelResourceType resourceType;
		CtrlrPanelResourceManager &owner;
};
#endif
