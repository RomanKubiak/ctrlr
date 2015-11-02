#ifndef __L_AUDIO_FORMAT__
#define __L_AUDIO_FORMAT__

#include "JuceHeader.h"
extern  "C"
{
	#include "lua.h"
}

class LAudioFormatManager : public AudioFormatManager
{
	public:
		LAudioFormatManager() : AudioFormatManager()
		{
			registerBasicFormats();
		}

		AudioFormatReader *createReaderFor(const File &file)
		{
			allocatedReaders.add (AudioFormatManager::createReaderFor(file));
			return (allocatedReaders.getLast());
		}

	private:
		OwnedArray <AudioFormatReader> allocatedReaders;
};

class LAudioFormat
{
	public:
		static void wrapForLua (lua_State *L);
};

#endif
