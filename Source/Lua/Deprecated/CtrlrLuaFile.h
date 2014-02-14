#ifndef __CTRLR_LUA_FILE__
#define __CTRLR_LUA_FILE__

#pragma warning(disable:4100)


#include "JuceHeader.h"
#include "CtrlrLuaMemoryBlock.h"

//==============================================================================
/** @brief A class that represents a file see http://www.rawmaterialsoftware.com/juce/api/classFile.html for details
 *			Never use this class directly always use the File class
 *
 */
class CtrlrLuaFile : public File
{
	public:
		CtrlrLuaFile();
		CtrlrLuaFile (const File &file);
		CtrlrLuaFile (const String &path);
		~CtrlrLuaFile();

		/** @brief Replace the file content with a block of data

			@param	data	The data to be written to the file
		*/
		void replaceFileContentWithData (CtrlrLuaMemoryBlock &data);

		/** @brief Read the file contents as a block of data

			@return The memory block that holds the file contents
		*/
		CtrlrLuaMemoryBlock loadFileAsData();

		/** @brief Find files in a directory

			@param table				a table that will hold the results of the search
			@param whatToLookFor		findDirectories = 1, findFiles = 2, findFilesAndDirectories = 3, ignoreHiddenFiles = 4
			@param searchRecursively	if set to true it will do a recursive search
			@param wildcardPattern		a wildcard pattern to match against found files
		*/
		void findChildFiles(luabind::object const& table, int whatToLookFor, bool searchRecursively, const String &wildcardPattern="*");

		/** @brief Get a special location in the operating system.
					Look at http://www.rawmaterialsoftware.com/juce/api/classFile.html#a3e19cafabb03c5838160263a6e76313d for a list of
					locations defined.

			@param loc	The location to look for, to get the userHomeDirectory pass File.userHomeDirectory as a parameter

		*/
		static CtrlrLuaFile getSpecialLocation(const File::SpecialLocationType loc);
};

#endif