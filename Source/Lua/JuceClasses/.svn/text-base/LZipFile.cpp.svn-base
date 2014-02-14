#include "stdafx.h"
#include "LZipFile.h"

void LZipEntry::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<ZipFile::ZipEntry>("ZipEntry")
			.def_readwrite("filename", &ZipFile::ZipEntry::filename)
			.def_readwrite("uncompressedSize", &ZipFile::ZipEntry::uncompressedSize)
			.def_readwrite("fileTime", &ZipFile::ZipEntry::fileTime)
	];
}

void LZipFile::wrapForLua (lua_State *L)
{
	LZipEntry::wrapForLua (L);

	using namespace luabind;

	module(L)
    [
		class_<ZipFile>("ZipFile")
			.def(constructor<const File &>())
			.def(constructor<InputStream *, bool>())
			.def(constructor<InputStream &>())
			.def(constructor<InputSource *>())
			.def("getNumEntries", &ZipFile::getNumEntries)
			.def("getEntry", (const ZipFile::ZipEntry *(ZipFile::*)(int) const noexcept) &ZipFile::getEntry)
			.def("getIndexOfFileName", &ZipFile::getIndexOfFileName)
			.def("getEntry", (const ZipFile::ZipEntry *(ZipFile::*)(const String &) const noexcept) &ZipFile::getEntry)
			.def("sortEntriesByFilename", &ZipFile::sortEntriesByFilename)
			.def("createStreamForEntry", (InputStream *(ZipFile::*)(int)) &ZipFile::createStreamForEntry, adopt(result))
			.def("createStreamForEntry", (InputStream *(ZipFile::*)(const ZipFile::ZipEntry &)) &ZipFile::createStreamForEntry, adopt(result))
			.def("uncompressTo", &ZipFile::uncompressTo)
			.def("uncompressEntry", &ZipFile::uncompressEntry)
	];
}