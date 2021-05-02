#ifndef __CTRLR_STANDALONE_WINDOW__
#define __CTRLR_STANDALONE_WINDOW__

#include "CtrlrMacros.h"
class CtrlrProcessor;

class CtrlrStandaloneWindow	: public DocumentWindow, public ActionListener, public ChangeListener
{
	public:
		CtrlrStandaloneWindow (const String& title, const Colour& backgroundColour);
		~CtrlrStandaloneWindow();
		AudioProcessor *getFilter();
		virtual PropertySet* getGlobalSettings();
		void closeButtonPressed() override;
        void maximiseButtonPressed() override;
		void resized();
		void moved();
		void openFileFromCli(const File &file);
		void saveStateNow();
		void actionListenerCallback(const String &message);
		void changeListenerCallback(ChangeBroadcaster* source);
		void toggleFullscreen();
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrStandaloneWindow);

	private:
		bool restoreState;
		AudioProcessor *filter;
		CtrlrProcessor *ctrlrProcessor;
		ApplicationProperties *appProperties;
		void deleteFilter();
};

#endif
