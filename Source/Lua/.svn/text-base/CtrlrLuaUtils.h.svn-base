#ifndef __CTRLR_LUA_UTILS__
#define __CTRLR_LUA_UTILS__

#pragma warning(disable:4100)

#include "MIDI/CtrlrMidiMessage.h"
#include "JuceHeader.h"
class LMemoryBlock;
/*! \class CtrlrModulator
    \brief Modulator class

    Blah blah
*/

//==============================================================================
/** \brief A collection of utility methods.

*/
class CtrlrLuaUtils
{
	public:
		/** @brief Internal

		*/
		static void wrapForLua(lua_State *L);

		/** @brief Unpack bytes from a SysEx message using the DSI method (Mopho, Evolver, Tetra)

			@param dataToUnpack		the data to unpack (this must not include the MIDI SysEx prefix or suffix, 
									and must be a multiple of 8)
		*/
		static LMemoryBlock *unpackDsiData (MemoryBlock &dataToUnpack);

		/** @brief Pack bytes from a SysEx message using the DSI method (Mopho, Evolver, Tetra)

			@param dataToUnpack		the data to pack
		*/
		static LMemoryBlock *packDsiData (MemoryBlock &dataToUnpack);

		/** @brief Show a messge window with a warning icon

			@param title	Window title
			@param message	Window message
		*/
		static void warnWindow (const String title, const String message);
		
		/** @brief Show a messge window with a info icon

			@param title	Window title
			@param message	Window message
		*/
		static void infoWindow (const String title, const String message);

		/** @brief Show a messge window with a message, and return a value that represents what the user clicked in that window (OK/Cancel, Yes/No)

			@param	title		Window title
			@param	message		Window message
			@param	button1Text	text for the first button
			@param	button2Text	text for the second button
		*/
		static bool questionWindow (const String title, const String message, const String button1Text, const String button2Text);

		/** @brief Show a messge window with a text input field for the user to type in

			@return Contents of the text input field

			@param	title					Window title
			@param	message					Window message
			@param	initialInputContent		The initial content for the text input field
			@param	onScreenLabel			A lanel for the text input field
			@param	isPassword				Set to true if the user input is a password
			@param	button1Text				text for the first button
			@param	button2Text				text for the second button
		*/
		static String askForTextInputWindow (const String title, const String message, const String initialInputContent, const String onScreenLabel, const bool isPassword, const String button1Text, const String button2Text);

		/** @brief Ask for a File to open

			@param dialogBoxTitle
			@param initialFileOrDirectory
			@param filePatternsAllowed
			@param useOSNativeDialogBox
		*/
		static File openFileWindow (const String &dialogBoxTitle, const File &initialFileOrDirectory, const String &filePatternsAllowed, bool useOSNativeDialogBox);

		/** @brief Ask for a File to save

			@param dialogBoxTitle
			@param initialFileOrDirectory
			@param filePatternsAllowed
			@param useOSNativeDialogBox
		*/
		static File saveFileWindow(const String &dialogBoxTitle, const File &initialFileOrDirectory, const String &filePatternsAllowed, bool useOSNativeDialogBox);

		/** @brief Ask for a directory

		*/
		static File getDirectoryWindow(const String &dialogBoxTitle, const File &initialFileOrDirectory);

		static StringArray getMidiInputDevices();
		static StringArray getMidiOutputDevices();

		JUCE_LEAK_DETECTOR(CtrlrLuaUtils)
};

#endif