#include "stdafx.h"
#include "CtrlrLuaFile.h"

CtrlrLuaFile::CtrlrLuaFile()
{
}

CtrlrLuaFile::CtrlrLuaFile (const String &path) : File(path)
{
}

CtrlrLuaFile::CtrlrLuaFile (const File &file) : File(file)
{
}

CtrlrLuaFile::~CtrlrLuaFile()
{
}

void CtrlrLuaFile::replaceFileContentWithData (CtrlrLuaMemoryBlock &data)
{
	File::replaceWithData (data.getData(), data.getSize());
}

CtrlrLuaMemoryBlock CtrlrLuaFile::loadFileAsData()
{
	MemoryBlock mb;
	File::loadFileAsData (mb);

	return (CtrlrLuaMemoryBlock(mb));
}

void CtrlrLuaFile::findChildFiles (luabind::object const& table, int whatToLookFor, bool searchRecursively, const String &wildcardPattern)
{
	if (luabind::type(table) == LUA_TTABLE)
	{
		Array <File> ar;

		File::findChildFiles (ar, whatToLookFor, searchRecursively, wildcardPattern);

		for (int i=0; i<ar.size(); i++)
		{
			table[i+1] = CtrlrLuaFile(ar[i]);
		}
	}
}

CtrlrLuaFile CtrlrLuaFile::getSpecialLocation(const File::SpecialLocationType loc)
{
	return (CtrlrLuaFile(File::getSpecialLocation (loc)));
}