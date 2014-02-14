#ifndef __CTRLR_MIDI_MON__
#define __CTRLR_MIDI_MON__

#include "CtrlrMacros.h"
#include "CtrlrLog.h"
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"
class CtrlrManager;

class CtrlrMIDIMon  : public CtrlrChildWindowContent,
                      public CtrlrLog::Listener
{

	public:
		CtrlrMIDIMon (CtrlrManager &_owner);
		~CtrlrMIDIMon();
		void messageLogged (CtrlrLog::CtrlrLogMessage _message);
		String getContentName()					{ return ("MIDI Monitor"); }
		uint8 getType()							{ return (CtrlrManagerWindowManager::MidiMonWindow); }

		void paint (Graphics& g);
		void resized();

		StringArray getMenuBarNames();
		PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName);
		void menuItemSelected(int menuItemID, int topLevelMenuIndex);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrMIDIMon)

	private:
		CtrlrManager &owner;
		CodeDocument docOut, docIn;
		StretchableLayoutManager layoutManager;
		bool logIn, logOut;
		CodeDocument outputDocument, inputDocument;
		StretchableLayoutResizerBar* resizer;
		CodeEditorComponent* outMon;
		CodeEditorComponent* inMon;
};


#endif
