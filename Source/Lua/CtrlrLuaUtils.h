#ifndef __CTRLR_LUA_UTILS__
#define __CTRLR_LUA_UTILS__

#ifdef _WIN32
#pragma warning(disable:4100)
#endif // _WIN32

#include "CtrlrMacros.h"
#include "CtrlrRevision.h"
#include "luabind/object_fwd.hpp"

#include <eh.h> 

extern "C"
{
	#include "lua.h"
}

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
		static String askForTextInputWindow (const String title, const String message, const String initialInputContent,
											const String onScreenLabel, const bool isPassword, const String button1Text,
											const String button2Text);

		/** @brief Ask for a File to open

			@param dialogBoxTitle
			@param initialFileOrDirectory
			@param filePatternsAllowed
			@param useOSNativeDialogBox

			@return If a valid file was selected, a File object that represents that file
		*/
		static File openFileWindow (const String &dialogBoxTitle, const File &initialFileOrDirectory,
									const String &filePatternsAllowed, bool useOSNativeDialogBox);

		/** @brief Ask for multiple files to open

			@param dialogBoxTitle
			@param initialFileOrDirectory
			@param filePatternsAllowed
			@param useOSNativeDialogBox
			@param resultArray

			@return A lua array of File objects selected
		*/
		void openMultipleFilesWindow(const String &dialogBoxTitle, const File &initialFileOrDirectory,
									const String &filePatternsAllowed, bool useOSNativeDialogBox,
									luabind::object const& table);

		/** @brief Ask for a File to save

			@param dialogBoxTitle
			@param initialFileOrDirectory
			@param filePatternsAllowed
			@param useOSNativeDialogBox
		*/
		static File saveFileWindow(const String &dialogBoxTitle, const File &initialFileOrDirectory,
									const String &filePatternsAllowed, bool useOSNativeDialogBox);

		/** @brief Ask for a directory

		*/
		static File getDirectoryWindow(const String &dialogBoxTitle, const File &initialFileOrDirectory);

        static int getVersionMajor() { return (_STR(ctrlrRevision).upToFirstOccurrenceOf(".", false, true).getIntValue()); }
        static int getVersionMinor() { return (_STR(ctrlrRevision).fromFirstOccurrenceOf(".", false, true).getIntValue()); }
        static int getVersionRevision() { return (_STR(ctrlrRevision).fromLastOccurrenceOf(".", false, true).getIntValue()); }
        static double getPi() { return (double_Pi); }
        static String getVersionString() { return (_STR(ctrlrRevision)); }
		static StringArray getMidiInputDevices();
		static StringArray getMidiOutputDevices();
		void testMethod(const String &haystack, const String &needle);
		JUCE_LEAK_DETECTOR(CtrlrLuaUtils)
};

#endif
/*
--
-- Called when the panel background needs repainting
--
drawPanel = function(canvas,g)
	p = Path()
	p:startNewSubPath (0, 100);
	p:lineTo (200, 100);
	p:lineTo (400, 200);
	p:lineTo (200, 300);
	p:lineTo (0, 100);
	stroke = PathStrokeType (2.0, PathStrokeType.curved, PathStrokeType.butt)
	trans = AffineTransform()
	dashes = { 7.0, 4.0 , 3.0, 2.0}
	stroke:createDashedStroke (p, p, dashes, trans, 1.0)
	g:strokePath (p, stroke, trans)
end

panel:getCanvas():repaint()
*/
