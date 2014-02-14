#ifndef __CTRLR_STANDALONE_WINDOW__
#define __CTRLR_STANDALONE_WINDOW__

#include "CtrlrMacros.h"
class CtrlrProcessor;

class CtrlrStandaloneWindow	: public DocumentWindow
{
	public:
		CtrlrStandaloneWindow (const String& title, const Colour& backgroundColour);
		~CtrlrStandaloneWindow();
		AudioProcessor *getFilter();
		virtual PropertySet* getGlobalSettings();
		void closeButtonPressed();
		void resized();
		void moveed();
		void openFileFromCli(const File &file);
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrStandaloneWindow);

	private:
		bool restoreState;
		AudioProcessor *filter;
		CtrlrProcessor *ctrlrProcessor;
		ApplicationProperties *appProperties;
		void deleteFilter();
};

#endif
