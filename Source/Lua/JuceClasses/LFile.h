#ifndef __L_FILE__
#define __L_FILE__

#include "LMemoryBlock.h"

class LFile : public File
{
	public:
		LFile(const String &_path) : File(_path) {}
		LFile(const File &other) : File(other) {}
		void findChildFiles (luabind::object const& table, int whatToLookFor, bool searchRecursively, const String wildcardPattern) const;
		double getSize()
		{
			return ((double)File::getSize());
		}

		static File getSpecialLocation(const File::SpecialLocationType type)
		{
			return (File::getSpecialLocation(type));
		}

		bool replaceWithData (const LMemoryBlock &dataToWrite)
		{
			return (File::replaceWithData (dataToWrite.getData(), (size_t)dataToWrite.getSize()));
		}

        bool appendData (const LMemoryBlock &dataToAppend)
        {
            return (File::appendData (dataToAppend.getData(), (size_t)dataToAppend.getSize()));
        }

		static const String descriptionOfSizeInBytes(const double fileSize)
		{
			return (File::descriptionOfSizeInBytes ((juce::int64)fileSize));
		}

		bool isValid();
		static void wrapForLua (lua_State *L);
};

#endif
