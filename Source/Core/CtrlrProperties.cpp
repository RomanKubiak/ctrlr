#include "stdafx.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrLog.h"
#include "CtrlrProperties.h"
#include "CtrlrMacros.h"
#include "CtrlrIDs.h"


CtrlrProperties::CtrlrProperties(CtrlrManager &_owner) : owner(_owner)
{
	PropertiesFile::Options options;
	options.applicationName				= owner.getInstanceName();
	options.filenameSuffix				= ".settings";
	options.folderName					= File::createLegalFileName (owner.getInstanceName());
	options.storageFormat				= PropertiesFile::storeAsBinary;
	options.millisecondsBeforeSaving	= 250;
	options.osxLibrarySubFolder			= "Preferences";

	applicationProperties.setStorageParameters (options);
}
 
CtrlrProperties::~CtrlrProperties()
{
}

bool CtrlrProperties::saveIfNeeded()
{
	return (applicationProperties.saveIfNeeded());
}

ApplicationProperties &CtrlrProperties::getProperties()
{
	return (applicationProperties);
}