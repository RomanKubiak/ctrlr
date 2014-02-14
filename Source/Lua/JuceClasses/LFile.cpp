#include "stdafx.h"
#include "LFile.h"

void LFile::findChildFiles (luabind::object const& table, int whatToLookFor, bool searchRecursively, const String wildcardPattern) const
{
	Array<File> files;
	File::findChildFiles (files, whatToLookFor, searchRecursively, wildcardPattern);

	for (int i=1; i<=files.size(); i++)
	{
		table[i] = files[i-1];
	}
}

bool LFile::isValid()
{
	if (*this == File::nonexistent)
	{
		return (false);
	}

	return (true);
}

void LFile::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<LFile>("LFile")
		,
		class_<File, bases<LFile> >("File")
			.def(constructor<const String &>())
			.def(constructor<const File &>())
			.def("exists", &File::exists)
			.def("existsAsFile", &File::existsAsFile)
			.def("isDirectory", &File::isDirectory)
			.def("getSize", &LFile::getSize)
			.def("getFullPathName", &File::getFullPathName)
			.def("getFileName", &File::getFileName)
			.def("getRelativePathFrom", &File::getRelativePathFrom)
			.def("getFileExtension", &File::getFileExtension)
			.def("hasFileExtension", &File::hasFileExtension)
			.def("withFileExtension", &File::withFileExtension)
			.def("getFileNameWithoutExtension", &File::getFileNameWithoutExtension)
			.def("hashCode", &File::hashCode)
			.def("hashCode64", &File::hashCode64)
			.def("getChildFile", &File::getChildFile)
			.def("getSiblingFile", &File::getSiblingFile)
			.def("getParentDirectory", &File::getParentDirectory)
			.def("isAChildOf", &File::isAChildOf)
			.def("getNonexistentChildFile", &File::getNonexistentChildFile)
			.def("getNonexistentSibling", &File::getNonexistentSibling)
			.def("hasWriteAccess", &File::hasWriteAccess)
			.def("setReadOnly", &File::setReadOnly)
			.def("isHidden", &File::isHidden)
			.def("getLinkedTarget", &File::getLinkedTarget)
			.def("isHidden", &File::isHidden)
			.def("getLastModificationTime", &File::getLastModificationTime)
			.def("getLastAccessTime", &File::getLastAccessTime)
			.def("getCreationTime", &File::getCreationTime)
			.def("setLastModificationTime", &File::setLastModificationTime)
			.def("setLastAccessTime", &File::setLastAccessTime)
			.def("setCreationTime", &File::setCreationTime)
			.def("getVersion", &File::getVersion)
			.def("create", &File::create)
			.def("createDirectory", &File::createDirectory)
			.def("deleteFile", &File::deleteFile)
			.def("deleteRecursively", &File::deleteRecursively)
			.def("moveToTrash", &File::moveToTrash)
			.def("moveFileTo", &File::moveFileTo)
			.def("copyFileTo", &File::copyFileTo)
			.def("getNumberOfChildFiles", &File::getNumberOfChildFiles)
			.def("containsSubDirectories", &File::containsSubDirectories)
			.def("loadFileAsString", &File::loadFileAsString)
			.def("appendData", &File::appendData)
			.def("replaceWithData", &File::replaceWithData)
			.def("replaceWithData", &LFile::replaceWithData)
			.def("appendText", &File::appendText)
			.def("replaceWithText", &File::replaceWithText)
			.def("hasIdenticalContentTo", &File::hasIdenticalContentTo)
			.def("getVolumeLabel", &File::getVolumeLabel)
			.def("getVolumeSerialNumber", &File::getVolumeSerialNumber)
			.def("getBytesFreeOnVolume", &File::getBytesFreeOnVolume)
			.def("getVolumeTotalSize", &File::getVolumeTotalSize)
			.def("isOnCDRomDrive", &File::isOnCDRomDrive)
			.def("isOnHardDisk", &File::isOnHardDisk)
			.def("isOnRemovableDrive", &File::isOnRemovableDrive)
			.def("startAsProcess", &File::startAsProcess)
			.def("revealToUser", &File::revealToUser)
			.def("loadFileAsData", &File::loadFileAsData)
			.def("findChildFiles", &LFile::findChildFiles)
			.def("setAsCurrentWorkingDirectory", &File::setAsCurrentWorkingDirectory)
			.def("isValid", &LFile::isValid)
			.enum_("TypesOfFileToFind")
			[
				value("findDirectories", 1),
				value("findFiles", 2),
				value("findFilesAndDirectories", 3),
				value("ignoreHiddenFiles", 4)
			]
			.enum_("SpecialLocationType")
			[
				value("userHomeDirectory", 0),
				value("userDocumentsDirectory", 1),
				value("userDesktopDirectory", 2),
				value("userApplicationDataDirectory", 3),
				value("commonApplicationDataDirectory", 4),
				value("tempDirectory", 5),
				value("currentExecutableFile", 6),
				value("currentApplicationFile", 7),
				value("invokedExecutableFile", 8),
				value("globalApplicationsDirectory", 9),
				value("userMusicDirectory", 10),
				value("userMoviesDirectory", 11),
				value("userPicturesDirectory", 12)
			]
			.scope
			[
				def("descriptionOfSizeInBytes", &LFile::descriptionOfSizeInBytes),
				def("findFileSystemRoots", &File::findFileSystemRoots),
				def("getSpecialLocation", &LFile::getSpecialLocation),
				def("createTempFile", &File::createTempFile),
				def("getCurrentWorkingDirectory", &File::getCurrentWorkingDirectory),
				def("createLegalFileName", &File::createLegalFileName),
				def("createLegalPathName", &File::createLegalPathName),
				def("areFileNamesCaseSensitive", &File::areFileNamesCaseSensitive),
				def("isAbsolutePath", &File::isAbsolutePath),
				def("createFileWithoutCheckingPath", &File::createFileWithoutCheckingPath),
				def("addTrailingSeparator", &File::addTrailingSeparator)
			]
	];
}
