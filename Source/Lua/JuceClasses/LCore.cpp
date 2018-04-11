#include "stdafx.h"
#include "LJuce.h"
#include "Native/CtrlrNative.h"
#include "CtrlrMacros.h"
#include "CtrlrLog.h"
#include "CtrlrUtilities.h"
#include "CtrlrManager/CtrlrManager.h"

void LExpression::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Expression::Scope>("Scope")
		,
		class_<Expression::Symbol>("Symbol")
		,
		class_<Expression>("Expression")
			.def(constructor<>())
			.def(constructor<double>())
			//.def(constructor<const String &>())
			.def(constructor<const Expression &>())
			.def("toString", &Expression::toString)
			.def("evaluate", (double (Expression::*) () const) &Expression::evaluate)
			.def("evaluate", (double (Expression::*) (const Expression::Scope &) const) &Expression::evaluate)
			.def("evaluate", (double (Expression::*) (const Expression::Scope &, String &) const) &Expression::evaluate)
			.def("adjustedToGiveNewResult", &Expression::adjustedToGiveNewResult)
			.def("withRenamedSymbol", &Expression::withRenamedSymbol)
			.def("referencesSymbol", &Expression::referencesSymbol)
			.def("usesAnySymbols", &Expression::usesAnySymbols)
			.def("findReferencedSymbols", &Expression::findReferencedSymbols)
			.def("getType", &Expression::getType)
			.def("getSymbolOrFunction", &Expression::getSymbolOrFunction)
			.def("getNumInputs", &Expression::getNumInputs)
			.def("getInput", &Expression::getInput)
	];
}

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
			.def("appendData", &LFile::appendData)
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

static const String getNativeKeyMapping()
{
    String ret;
    for (int i=0; i<1024; i++)
    {
        if (KeyPress(i).isValid())
        {
            if (! KeyPress(i).getTextDescription().startsWith("#") && KeyPress(i).getTextDescription().isNotEmpty())
                ret << i << ": " << KeyPress(i).getTextDescriptionWithIcons() << "\n";
        }
    }
    return (ret);
}

LGlobalFunctions::LGlobalFunctions()
{
}

double LGlobalFunctions::double_Pi()
{
	return (juce::double_Pi);
}

float LGlobalFunctions::float_Pi()
{
	return (juce::float_Pi);
}

void LGlobalFunctions::debug(const String &argument)
{
    _LUA(argument);
}

void LGlobalFunctions::debug(const std::string &argument)
{
    _LUA(_STR(argument.c_str()));
}

std::string LGlobalFunctions::stringToLua (const String &string)
{
    return (string.toUTF8().getAddress());
}

String LGlobalFunctions::toJuceString (const std::string &string)
{
    return (String(string.c_str()));
}

void LGlobalFunctions::console (const String &arg)
{
    _LUA(removeInvalidChars(arg, true));
}

void LGlobalFunctions::console (const std::string &arg)
{
    _LUA(removeInvalidChars(_STR(arg), true));
}

void LGlobalFunctions::sleep(const int milliseconds)
{
    Thread::sleep(milliseconds);
}

void LGlobalFunctions::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
        def("getNativeKeyMapping", &getNativeKeyMapping)
        ,
        //def("console", (void (*) (const std::string &)) &LGlobalFunctions::console),
        def("console", (void (*) (const String &)) &LGlobalFunctions::console)
        ,
		def("J", (const String (*) (const std::string &)) &LGlobalFunctions::toJuceString),
		def("toJuceString", (const String (*) (const std::string &)) &LGlobalFunctions::toJuceString)
		,
		def("L", &LGlobalFunctions::stringToLua),
		def("toLuaString", &LGlobalFunctions::stringToLua)
        ,
        def("print_debug", (void (*)(const String &))&LGlobalFunctions::debug),
        def("print_d", (void (*)(const String &))&LGlobalFunctions::debug),
        def("_DBG", (void (*)(const String &))&LGlobalFunctions::debug),
        def("_debug", (void (*)(const String &))&LGlobalFunctions::debug)
        ,
        def("sleep", &LGlobalFunctions::sleep)
        ,
		class_<LGlobalFunctions>("juce")
			.def(constructor<>())
			.scope
			[
				def("double_Pi", &LGlobalFunctions::double_Pi),
				def("float_Pi", &LGlobalFunctions::float_Pi)
			]
		,
		class_<CtrlrNative>("CtrlrNative")
            .def("sendKeyPressEvent", (const Result (CtrlrNative::*) (const KeyPress &, const String &)) &CtrlrNative::sendKeyPressEvent)
			.def("sendKeyPressEvent", (const Result (CtrlrNative::*) (const KeyPress &)) &CtrlrNative::sendKeyPressEvent)
            .scope
            [
                def("getNativeObject", &CtrlrNative::getNativeObject)
            ]
		,
		def("jmax", (double (*) (const double, const double))&juce::jmax<double>),
		def("jmax", (double (*) (const double, const double, const double))&juce::jmax<double>),
		def("jmax", (double (*) (const double, const double, const double, const double))&juce::jmax<double>),
		def("jmin", (double (*) (const double, const double))&juce::jmin<double>),
		def("jmin", (double (*) (const double, const double, const double))&juce::jmin<double>),
		def("jmin", (double (*) (const double, const double, const double, const double))&juce::jmin<double>),
		def("jlimit", (double (*) (const double, const double, const double))&juce::jlimit<double>),
		def("isPositiveAndBelow", (bool (*) (const double, const double))&juce::isPositiveAndBelow<double>),
		def("isPositiveAndNotGreaterThan", (bool (*) (const double, const double))&juce::isPositiveAndNotGreaterThan<double>),
        def("roundToInt", &juce::roundToInt<double>),
		def("roundToIntAccurate", &juce::roundToIntAccurate),
		def("roundDoubleToInt", &juce::roundDoubleToInt),
		def("roundFloatToInt", &juce::roundFloatToInt),
		def("isPowerOfTwo", (bool (*) (int))&juce::isPowerOfTwo<int>),
		def("nextPowerOfTwo", &juce::nextPowerOfTwo),

		def("cos", (double (*) (double))&cos),
		def("cosf", (float (*) (float))&cosf),
		def("sin", (double (*) (double))&sin),
		def("sinf", (float (*) (float))&sinf),
		def("tan", (double (*) (double))&tan),
		def("acos", (double (*) (double))&acos),
		def("asin", (double (*) (double))&asin),
		def("atan", (double (*) (double))&atan),
		def("atan2", (double (*) (double, double))&atan2),
		def("cosh", (double (*) (double))&cosh),
		def("sinh", (double (*) (double))&sinh),
		def("tanh", (double (*) (double))&tanh),
		def("exp", (double (*) (double))&exp),
		def("frexp", (double (*) (double, int *))&frexp),
		def("ldexp", (double (*) (double, int))&ldexp),
		def("log", (double (*) (double))&log),
		def("log10", (double (*) (double))&log10),
		def("modf", (double (*) (double, double *))&modf),
		def("pow", (double (*) (double, double))&pow),
		def("powf", (float (*) (float, float))&powf),
		def("sqrt", (double (*) (double))&sqrt),
		def("ceil", (double (*) (double))&ceil),
		def("ceilf", (float (*) (float))&ceilf),
		def("fabs", (double (*) (double))&fabs),
		def("fabsf", (float (*) (float))&fabsf),
		def("floor", (double (*) (double))&floor),
		def("floorf", (float (*) (float))&floorf),
		def("fmod", (double (*) (double, double))&fmod),
		def("fmodf", (float (*) (float, float))&fmodf)
	];
}

void LKeyPress::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<KeyPress>("KeyPress")
			.def(constructor<>())
			.def(constructor<const KeyPress &>())
			.def(constructor<int>())
			.def(constructor<int, const ModifierKeys &, juce_wchar>())
			.def("isValid", &KeyPress::isValid)
			.def("getKeyCode", &KeyPress::getKeyCode)
			.def("getModifiers", &KeyPress::getModifiers)
			.def("getTextCharacter", &KeyPress::getTextCharacter)
			.def("isKeyCode", &KeyPress::isKeyCode)
			.def("getTextDescription", &KeyPress::getTextDescription)
			.def("getTextDescriptionWithIcons", &KeyPress::getTextDescriptionWithIcons)
			.def("isCurrentlyDown", &KeyPress::isCurrentlyDown)
			.scope
			[
                def("createFromDescription", &KeyPress::createFromDescription),
                def("isKeyCurrentlyDown", &KeyPress::isKeyCurrentlyDown)
			]
			.enum_("KeyCode")
			[
				value("spaceKey", KeyPress::spaceKey),
				value("escapeKey", KeyPress::escapeKey),
				value("returnKey", KeyPress::returnKey),
				value("tabKey", KeyPress::tabKey),
				value("deleteKey", KeyPress::deleteKey),
				value("backspaceKey", KeyPress::backspaceKey),
				value("insertKey", KeyPress::insertKey),
				value("upKey", KeyPress::upKey),
				value("downKey", KeyPress::downKey),
				value("leftKey", KeyPress::leftKey),
				value("rightKey", KeyPress::rightKey)
			]
	];
}

void LModifierKeys::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<ModifierKeys>("ModifierKeys")
			.def(constructor<int>())
			.def(constructor<const ModifierKeys &>())
			.def("isCommandDown", &ModifierKeys::isCommandDown)
			.def("isPopupMenu", &ModifierKeys::isPopupMenu)
			.def("isLeftButtonDown", &ModifierKeys::isLeftButtonDown)
			.def("isRightButtonDown", &ModifierKeys::isRightButtonDown)
			.def("isMiddleButtonDown", &ModifierKeys::isMiddleButtonDown)
			.def("isAnyModifierKeyDown", &ModifierKeys::isAnyModifierKeyDown)
			.def("isShiftDown", &ModifierKeys::isShiftDown)
			.def("isCtrlDown", &ModifierKeys::isCtrlDown)
			.def("isAltDown", &ModifierKeys::isAltDown)
			.def("getRawFlags", &ModifierKeys::getRawFlags)
			.def("testFlags", &ModifierKeys::testFlags)
			.def("getNumMouseButtonsDown", &ModifierKeys::getNumMouseButtonsDown)
			.scope
			[
				def("getCurrentModifiers", &ModifierKeys::getCurrentModifiers),
				def("getCurrentModifiersRealtime", &ModifierKeys::getCurrentModifiersRealtime)
			]
			.enum_("Flags")
			[
				value ("shiftModifier", 1),
				value ("ctrlModifier", 2),
				value ("altModifier", 4),
				value ("leftButtonModifier", 16),
				value ("rightButtonModifier", 32),
				value ("middleButtonModifier", 64),
				value ("commandModifier", 8),
				value ("popupMenuClickModifier", 34),
				value ("allKeyboardModifiers", 15),
				value ("allMouseButtonModifiers ", 112)
			]
	];
}

void LMouseCursor::wrapForLua(lua_State *L)
{
    using namespace luabind;

	module(L)
    [
		class_<MouseCursor>("MouseCursor")
            .def(constructor<>())
            .def(constructor<MouseCursor::StandardCursorType>())
            .def(constructor<const Image &, int, int>())
            .def(constructor<const Image &, int, int, float>())
            .def(constructor<const MouseCursor &>())
            .enum_("StandardCursorType")
            [
                value("ParentCursor", MouseCursor::ParentCursor),
                value("NoCursor", MouseCursor::NoCursor),
                value("NormalCursor", MouseCursor::NormalCursor),
                value("WaitCursor", MouseCursor::WaitCursor)
            ]
            .scope
            [
                def("showWaitCursor", &MouseCursor::showWaitCursor),
                def("hideWaitCursor", &MouseCursor::hideWaitCursor)
            ]
    ];
}

void LMouseEvent::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<MouseEvent>("MouseEvent")
			.def("getMouseDownX", &MouseEvent::getMouseDownX)
			.def("getMouseDownY", &MouseEvent::getMouseDownY)
			.def("getDistanceFromDragStart", &MouseEvent::getDistanceFromDragStart)
			.def("getDistanceFromDragStartX", &MouseEvent::getDistanceFromDragStartX)
			.def("getDistanceFromDragStartY", &MouseEvent::getDistanceFromDragStartY)
			.def("mouseWasClicked", &MouseEvent::mouseWasClicked)
			.def("getNumberOfClicks", &MouseEvent::getNumberOfClicks)
			.def("getLengthOfMousePress", &MouseEvent::getLengthOfMousePress)
			.def("getScreenX", &MouseEvent::getScreenX)
			.def("getScreenY", &MouseEvent::getScreenY)
			.def("getMouseDownScreenX", &MouseEvent::getMouseDownScreenX)
			.def("getMouseDownScreenY", &MouseEvent::getMouseDownScreenY)
			.def_readonly("x", &MouseEvent::x)
			.def_readonly("y", &MouseEvent::y)
			.def_readonly("mods", &MouseEvent::mods)
			.def_readonly("eventTime", &MouseEvent::eventTime)
			.def_readonly("eventComponent", &MouseEvent::eventComponent)
			.def_readonly("originalComponent", &MouseEvent::originalComponent)
			.def_readonly("eventTime", &MouseEvent::eventTime)
			.def("getMouseDownPosition", &MouseEvent::getMouseDownPosition)
			.def("getOffsetFromDragStart", &MouseEvent::getOffsetFromDragStart)
			.def("getPosition", &MouseEvent::getPosition)
			.def("getScreenPosition", &MouseEvent::getScreenPosition)
			.def("getMouseDownScreenPosition", &MouseEvent::getMouseDownScreenPosition)
	];
}
void LRandom::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Random>("Random")
				.def(constructor<int64>())
				.def(constructor<>())
				.def("nextInt", (int (Random::*)(void) noexcept)&Random::nextInt)
				.def("nextInt", (int (Random::*)(int) noexcept)&Random::nextInt)
				.def("nextInt64", &Random::nextInt64)
				.def("nextFloat", &Random::nextFloat)
				.def("nextDouble", &Random::nextDouble)
				.def("nextBool", &Random::nextBool)
				.def("nextLargeNumber", &Random::nextLargeNumber)
				.def("fillBitsRandomly", (void (Random::*) (void *, size_t))&Random::fillBitsRandomly)
				.def("fillBitsRandomly", (void (Random::*) (BigInteger &, int, int))&Random::fillBitsRandomly)
				.def("setSeed", &Random::setSeed)
				.def("combineSeed", &Random::combineSeed)
				.def("setSeedRandomly", &Random::setSeedRandomly)
				.scope
				[
					def("getSystemRandom", &Random::getSystemRandom)
				]
	];
}

void LRange::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Range<int> >("Range")
		.def(constructor<>())
		.def(constructor<const Range<int> &>())
		.def(constructor<int,int>())
		.def("getStart", &Range<int>::getStart)
		.def("getLength", &Range<int>::getLength)
		.def("getEnd", &Range<int>::getEnd)
		.def("isEmpty", &Range<int>::isEmpty)
		.def("setStart", &Range<int>::setStart)
		.def("withStart", &Range<int>::withStart)
		.def("movedToStartAt", &Range<int>::movedToStartAt)
		.def("setEnd", &Range<int>::setEnd)
		.def("withEnd", &Range<int>::withEnd)
		.def("movedToEndAt", &Range<int>::movedToEndAt)
		.def("setLength", &Range<int>::setLength)
		.def("withLength", &Range<int>::withLength)
		.def("clipValue", &Range<int>::clipValue)
		.def("intersects", &Range<int>::intersects)
		.def("getIntersectionWith", &Range<int>::getIntersectionWith)
		.def("getUnionWith", (Range<int> (Range<int>::*)(Range<int>) const)&Range<int>::getUnionWith)

		.def("constrainRange", &Range<int>::constrainRange)
		.def("contains", (bool (Range<int>::*)(const int) const) &Range<int>::contains)
		.def("contains", (bool (Range<int>::*)(const Range<int>) const) &Range<int>::contains)
	];
}

void LResult::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Result>("Result")
				.def("wasOk", &Result::wasOk)
				.def("failed", &Result::failed)
				.def("getErrorMessage", &Result::getErrorMessage)
				.def("fail", &Result::fail)
				.def("ok", &Result::ok)
	];
}

void LString::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<String>("String")
			.def(constructor<const char *>())
			//.def(constructor<const char *, const int>())
			.def(constructor<double>())
			.def(constructor<double,int>())
			.def(self + other<const String &>())
			.def("hashCode", &String::hashCode)
			.def("length", &String::length)
			.def("append", &String::append)
			.def("isEmpty", &String::isEmpty)
			.def("isNotEmpty", &String::isNotEmpty)
			.def("equalsIgnoreCase", (bool (String::*)(const String &) const) &String::equalsIgnoreCase)
			.def("equalsIgnoreCase", (bool (String::*)(const char *) const) &String::equalsIgnoreCase)
			.def("compare", (int (String::*)(const String &) const) &String::compare)
			.def("compare", (int (String::*)(const char *) const) &String::compare)
			.def("compareIgnoreCase", (int (String::*)(const String &) const) &String::compareIgnoreCase)
			.def("compareIgnoreCase", (int (String::*)(const char *) const) &String::compareIgnoreCase)
			.def("compareNatural", &String::compareNatural)
			.def("startsWith", (bool (String::*)(const String &) const) &String::startsWith)
			.def("startsWithIgnoreCase", (bool (String::*)(const String &) const) &String::startsWithIgnoreCase)
			.def("endsWith",  &String::endsWith)
			.def("contains",  &String::contains)
			.def("containsIgnoreCase", &String::containsIgnoreCase)
			.def("containsWholeWord", &String::containsWholeWord)
			.def("containsWholeWordIgnoreCase", &String::containsWholeWordIgnoreCase)
			.def("indexOfWholeWord", &String::indexOfWholeWord)
			.def("indexOfWholeWordIgnoreCase", &String::indexOfWholeWordIgnoreCase)
			.def("containsAnyOf", &String::containsAnyOf)
			.def("containsOnly", &String::containsOnly)
			.def("containsNonWhitespaceChars", &String::containsNonWhitespaceChars)
			.def("matchesWildcard", &String::matchesWildcard)
			.def("indexOfAnyOf", &String::indexOfAnyOf)
			.def("indexOf", (int (String::*)(StringRef) const) &String::indexOf)
			.def("indexOf", (int (String::*)(const int, StringRef) const) &String::indexOf)
			.def("indexOfIgnoreCase", (int (String::*)(StringRef) const) &String::indexOfIgnoreCase)
			.def("lastIndexOf", &String::lastIndexOf)
			.def("lastIndexOfIgnoreCase", &String::lastIndexOfIgnoreCase)
			.def("lastIndexOfAnyOf", &String::lastIndexOfAnyOf)
			.def("substring", (String (String::*)(int,int) const) &String::substring)
			.def("substring", (String (String::*)(int) const) &String::substring)
			.def("dropLastCharacters", &String::dropLastCharacters)
			.def("getLastCharacters", &String::getLastCharacters)
			.def("fromFirstOccurrenceOf", &String::fromFirstOccurrenceOf)
			.def("fromLastOccurrenceOf", &String::fromLastOccurrenceOf)
			.def("upToFirstOccurrenceOf", &String::upToFirstOccurrenceOf)
			.def("upToLastOccurrenceOf", &String::upToLastOccurrenceOf)
			.def("trim", &String::trim)
			.def("trimEnd", &String::trimEnd)
			.def("trimCharactersAtStart", &String::trimCharactersAtStart)
			.def("trimCharactersAtEnd", &String::trimCharactersAtEnd)
			.def("toUpperCase", &String::toUpperCase)
			.def("toLowerCase", &String::toLowerCase)
			.def("replaceSection", &String::replaceSection)
			.def("replace", &String::replace)
			.def("replaceCharacters", &String::replaceCharacters)
			.def("retainCharacters", &String::retainCharacters)
			.def("removeCharacters", &String::removeCharacters)
			.def("initialSectionContainingOnly", &String::initialSectionContainingOnly)
			.def("initialSectionNotContaining", &String::initialSectionNotContaining)
			.def("isQuotedString", &String::isQuotedString)
			.def("unquoted", &String::unquoted)
			.def("quoted", &String::quoted)
			.def("repeatedString", &String::repeatedString)
			.def("paddedLeft", &String::paddedLeft)
			.def("paddedRight", &String::paddedRight)
			.def("getIntValue", &String::getIntValue)
			.def("getTrailingIntValue", &String::getTrailingIntValue)
			.def("getFloatValue", &String::getFloatValue)
			.def("getDoubleValue", &String::getDoubleValue)
			.def("getHexValue32", &String::getHexValue32)
			.def("swapWith", &String::swapWith)
			.def("toUTF8", &String::toUTF8)
		,

		class_<CharPointer_UTF8>("CharPointer_UTF8")
			.def("getAddress", &CharPointer_UTF8::getAddress)
		,
		class_<CharPointer_UTF8::CharType>("CharType")
		,
		class_<StringPairArray>("StringPairArray")
			.def("getValue", &StringPairArray::getValue)
			.def("getAllKeys", &StringPairArray::getAllKeys)
			.def("getAllValues", &StringPairArray::getAllValues)
			.def("size", &StringPairArray::size)
			.def("set", &StringPairArray::set)
			.def("addArray", &StringPairArray::addArray)
			.def("clear", &StringPairArray::clear)
			.def("remove", (void (StringPairArray::*)(int)) &StringPairArray::remove)
			//.def("remove", (void (StringPairArray::*)(const String &))&StringPairArray::remove)
			.def("setIgnoresCase", &StringPairArray::setIgnoresCase)
			.def("getDescription", &StringPairArray::getDescription)
			.def("minimiseStorageOverheads", &StringPairArray::minimiseStorageOverheads)

		,
        class_<StringRef>("StringRef")
            .def(constructor<>())
            .def(constructor<const char *>())
            .def(constructor<const String &>())
        ,
        class_<LStringArray>("LStringArray")
        ,
		class_<StringArray, bases<LStringArray> >("StringArray")
			.def(constructor<>())
			.def(constructor<const String &>())
//			.def(constructor<const char *const *, const int>())
			.def(constructor<const char *const *>())
			.def(constructor<const StringArray &>())
			.def("size", &StringArray::size)
			.def("get", &LStringArray::get)
			.def("contains", &StringArray::contains)
			.def("indexOf", &StringArray::indexOf)
			.def("getReference", &StringArray::getReference)
			.def("add", (void (StringArray::*)(const String &))&StringArray::add)
			.def("insert", &StringArray::insert)
			.def("addIfNotAlreadyThere", &StringArray::addIfNotAlreadyThere)
			.def("set", &StringArray::set)
			.def("addArray", &StringArray::addArray)
			.def("addTokens", (int (StringArray::*)(StringRef, bool)) &StringArray::addTokens)
			.def("addTokens", (int (StringArray::*)(StringRef, StringRef, StringRef)) &StringArray::addTokens)
			.def("addLines", &StringArray::addLines)
			.def("clear", &StringArray::clear)
			.def("remove", &StringArray::remove)
			.def("removeString", &StringArray::removeString)
			.def("removeRange", &StringArray::removeRange)
			.def("removeDuplicates", &StringArray::removeDuplicates)
			.def("removeEmptyStrings", &StringArray::removeEmptyStrings)
			.def("move", &StringArray::move)
			.def("trim", &StringArray::trim)
			.def("appendNumbersToDuplicates", &StringArray::appendNumbersToDuplicates)
			.def("joinIntoString", &StringArray::joinIntoString)
			.def("sort", &StringArray::sort)
			.def("minimiseStorageOverheads", &StringArray::minimiseStorageOverheads)
		];
}

void LTime::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Time>("JTime")
		,
		class_<LTime, bases<Time> >("Time")
				.def(constructor<>())
				.def(constructor<int,int,int,int,int,int,int,bool>())
				.def(constructor<double>())
				.def(constructor<const LTime &>())
				.def(constructor<const Time &>())
				.def("toMilliseconds", &LTime::toMilliseconds)
				.def("getYear", &Time::getYear)
				.def("getMonth", &Time::getMonth)
				.def("getMonthName", (String (Time::*)(bool) const)&Time::getMonthName)
				.def("getDayOfMonth", &Time::getDayOfMonth)
				.def("getDayOfWeek", &Time::getDayOfWeek)
				.def("getDayOfYear", &Time::getDayOfYear)
				.def("getWeekdayName", (String (Time::*)(bool) const)&Time::getWeekdayName)
				.def("getHours", &Time::getHours)
				.def("isAfternoon", &Time::isAfternoon)
				.def("getHoursInAmPmFormat", &Time::getHoursInAmPmFormat)
				.def("getMinutes", &Time::getMinutes)
				.def("getSeconds", &Time::getSeconds)
				.def("getMilliseconds", &Time::getMilliseconds)
				.def("isDaylightSavingTime", &Time::isDaylightSavingTime)
				.def("getTimeZone", &Time::getTimeZone)
				.def("toString", &Time::toString)
				.def("formatted", &Time::formatted)
				.def("setSystemTimeToThisTime", &Time::setSystemTimeToThisTime)
				.scope
				[
					def("getCurrentTime", &LTime::getCurrentTime),
					def("currentTimeMillis", &LTime::currentTimeMillis),
					def("getMillisecondCounter", &Time::getMillisecondCounter),
					def("getMillisecondCounterHiRes", &Time::getMillisecondCounterHiRes),
					def("waitForMillisecondCounter", &Time::waitForMillisecondCounter),
					def("getApproximateMillisecondCounter", &Time::getApproximateMillisecondCounter),
					def("getHighResolutionTicks", &LTime::getHighResolutionTicks),
					def("getHighResolutionTicksPerSecond", &LTime::getHighResolutionTicksPerSecond),
					def("highResolutionTicksToSeconds", &LTime::highResolutionTicksToSeconds),
					def("secondsToHighResolutionTicks", &LTime::secondsToHighResolutionTicks)
				]
	];
}

void LTimer::setCallback (luabind::object _callback)
{
	callback = _callback;
}

void LTimer::timerCallback()
{
	if (callback)
	{
		luabind::call_function<void>(callback);
	}
}

void LTimer::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Timer, LTimer>("Timer")
			.def("setCallback", &LTimer::setCallback)
			.def("startTimer", &Timer::startTimer)
			.def("stopTimer", &Timer::stopTimer)
			.def("isTimerRunning", &Timer::isTimerRunning)
			.def("getTimerInterval", &Timer::getTimerInterval)
	];
}

void LURL::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<URL>("URL")
			.def(constructor<const String &>())
			.def("toString", &URL::toString)
			.def("isWellFormed", &URL::isWellFormed)
			.def("getDomain", &URL::getDomain)
			.def("getSubPath", &URL::getSubPath)
			.def("getScheme", &URL::getScheme)
			.def("withNewSubPath", &URL::withNewSubPath)
			.def("withParameter", &URL::withParameter)
			.def("withFileToUpload", &URL::withFileToUpload)
			.def("withPOSTData", (URL (URL::*)(const String &) const) &URL::withPOSTData)
			.def("withPOSTData", (URL (URL::*)(const MemoryBlock &) const) &URL::withPOSTData)
			.def("getPostData", &URL::getPostData)
			.def("launchInDefaultBrowser", &URL::launchInDefaultBrowser)
			.def("isProbablyAWebsiteURL", &URL::isProbablyAWebsiteURL)
			.def("isProbablyAnEmailAddress", &URL::isProbablyAnEmailAddress)
			.def("readEntireTextStream", &URL::readEntireTextStream)
			.def("readEntireXmlStream", &URL::readEntireXmlStream)
			.def("readEntireBinaryStream", &URL::readEntireBinaryStream)
			.def("addEscapeChars", &URL::addEscapeChars)
			.def("removeEscapeChars", &URL::removeEscapeChars)
	];
}

void LValue::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Value>("Value")
			.def(constructor<>())
			.def(constructor<const Value &>())
			.def(constructor<const var &>())
			.def("getValue", &Value::getValue)
			.def("toString", &Value::toString)
			.def("setValue", &Value::setValue)
			.def("referTo", &Value::referTo)
			.def("refersToSameSourceAs", &Value::refersToSameSourceAs)
			.def("addListener", &Value::addListener)
			.def("removeListener", &Value::removeListener)
			.def("getValueSource", &Value::getValueSource)
	];
}

void LValueTree::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Identifier>("Identifier")
				.def(constructor<const char *>())
				.def(constructor<const String &>())
				.def("toString", &Identifier::toString)
				.scope
				[
					def("isValidIdentifier", &Identifier::isValidIdentifier)
				]
		,
			class_<var>("var")
				.def(constructor<const var &>())
				.def(constructor<int>())
				.def(constructor<int64>())
				.def(constructor<bool>())
				.def(constructor<double>())
				.def(constructor<const char *>())
				.def(constructor<const wchar_t *>())
				.def(constructor<const String &>())
		,
			class_<ValueTree>("ValueTree")
				.def(constructor<>())
				.def(constructor<const ValueTree &>())
				.def(constructor<const Identifier &>())
				.def("isEquivalentTo", &ValueTree::isEquivalentTo)
				.def("isValid", &ValueTree::isValid)
				.def("createCopy", &ValueTree::createCopy)
				.def("getType", &ValueTree::getType)
				.def("hasType", &ValueTree::hasType)
				.def("getProperty", (var (ValueTree::*)(const Identifier &, const var &) const) &ValueTree::getProperty)
				.def("getProperty", (const var &(ValueTree::*)(const Identifier &) const) &ValueTree::getProperty)
				.def("setProperty", &ValueTree::setProperty)
				.def("hasProperty", &ValueTree::hasProperty)
				.def("removeProperty", &ValueTree::removeProperty)
				.def("removeAllProperties", &ValueTree::removeAllProperties)
				.def("getNumProperties", &ValueTree::getNumProperties)
				.def("getPropertyName", &ValueTree::getPropertyName)
				.def("getNumChildren", &ValueTree::getNumChildren)
				.def("getChild", &ValueTree::getChild)
				.def("getChildWithName", &ValueTree::getChildWithName)
				.def("getOrCreateChildWithName", &ValueTree::getOrCreateChildWithName)
				.def("getChildWithProperty", &ValueTree::getChildWithProperty)
				.def("addChild", &ValueTree::addChild)
				.def("removeChild", (void(ValueTree::*)(const ValueTree &, UndoManager *))&ValueTree::removeChild)
				.def("removeChild", (void(ValueTree::*)(const int, UndoManager *))&ValueTree::removeChild)
				.def("removeAllChildren", &ValueTree::removeAllChildren)
				.def("moveChild", &ValueTree::moveChild)
				.def("isAChildOf", &ValueTree::isAChildOf)
				.def("indexOf", &ValueTree::indexOf)
				.def("getParent", &ValueTree::getParent)
				.def("getSibling", &ValueTree::getSibling)
				.def("createXml", &ValueTree::createXml)
				.def("toXmlString", &ValueTree::toXmlString)
				.def("writeToStream", &ValueTree::writeToStream)
				.def("addListener", &ValueTree::addListener)
				.def("removeListener", &ValueTree::removeListener)
				.def("sendPropertyChangeMessage", &ValueTree::sendPropertyChangeMessage)
	];
}

void LXmlElement::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<XmlElement>("XmlElement")
			.def(constructor<const String &>())
			.def(constructor<const XmlElement &>())
			.def(constructor<const char *>())
			.def("isEquivalentTo", &XmlElement::isEquivalentTo)
			.def("createDocument", &XmlElement::createDocument)
			.def("writeToStream", &XmlElement::writeToStream)
			.def("writeToFile", &XmlElement::writeToFile)
			.def("getTagName", &XmlElement::getTagName)
			.def("getNamespace", &XmlElement::getNamespace)
			.def("getTagNameWithoutNamespace", &XmlElement::getTagNameWithoutNamespace)
			.def("hasTagName", &XmlElement::hasTagName)
			.def("hasTagNameIgnoringNamespace", &XmlElement::hasTagNameIgnoringNamespace)
			.def("getNumAttributes", &XmlElement::getNumAttributes)
			.def("getAttributeName", &XmlElement::getAttributeName)
			.def("getAttributeValue", &XmlElement::getAttributeValue)
			.def("hasAttribute", &XmlElement::hasAttribute)
			.def("getStringAttribute", (const String &(XmlElement::*)(StringRef) const) &XmlElement::getStringAttribute)
			.def("getStringAttribute", (String (XmlElement::*)(StringRef, const String &) const) &XmlElement::getStringAttribute)
			.def("compareAttribute", &XmlElement::compareAttribute)
			.def("getIntAttribute", &XmlElement::getIntAttribute)
			.def("getDoubleAttribute", &XmlElement::getDoubleAttribute)
			.def("getBoolAttribute", &XmlElement::getBoolAttribute)
			.def("setAttribute", (void (XmlElement::*)(const Identifier &, const String &)) &XmlElement::setAttribute)
			.def("setAttribute", (void (XmlElement::*)(const Identifier &, int)) &XmlElement::setAttribute)
			.def("setAttribute", (void (XmlElement::*)(const Identifier &, double)) &XmlElement::setAttribute)
			.def("removeAttribute", &XmlElement::removeAttribute)
			.def("removeAllAttributes", &XmlElement::removeAllAttributes)
			.def("getFirstChildElement", &XmlElement::getFirstChildElement)
			.def("getNextElement", &XmlElement::getNextElement)
			.def("getNextElementWithTagName", &XmlElement::getNextElementWithTagName)
			.def("getNumChildElements", &XmlElement::getNumChildElements)
			.def("getChildElement", &XmlElement::getChildElement)
			.def("getChildByName", &XmlElement::getChildByName)
			.def("getChildByAttribute", &XmlElement::getChildByAttribute)
			.def("addChildElement", &XmlElement::addChildElement)
			.def("insertChildElement", &XmlElement::insertChildElement)
			.def("prependChildElement", &XmlElement::prependChildElement)
			.def("createNewChildElement", &XmlElement::createNewChildElement)
			.def("replaceChildElement", &XmlElement::replaceChildElement)
			.def("removeChildElement", &XmlElement::removeChildElement)
			.def("deleteAllChildElements", &XmlElement::deleteAllChildElements)
			.def("deleteAllChildElementsWithTagName", &XmlElement::deleteAllChildElementsWithTagName)
			.def("containsChildElement", &XmlElement::containsChildElement)
			.def("findParentElementOf", &XmlElement::findParentElementOf)
            .def("isTextElement", &XmlElement::isTextElement)
            .def("getText", &XmlElement::getText)
            .def("setText", &XmlElement::setText)
            .def("getAllSubText", &XmlElement::getAllSubText)
            .def("getChildElementAllSubText", &XmlElement::getChildElementAllSubText)
            .def("addTextElement", &XmlElement::addTextElement)
            .def("deleteAllTextElements", &XmlElement::deleteAllTextElements)
            .def("getChildElementAllSubText", &XmlElement::getChildElementAllSubText)
            .scope[
                def("createTextElement", &XmlElement::createTextElement)
            ]
        ,
        class_<XmlDocument>("XmlDocument")
            .def(constructor<const String &>())
            .def(constructor<const File &>())
            .def("getDocumentElement", &XmlDocument::getDocumentElement)
            .def("getLastParseError", &XmlDocument::getLastParseError)
            .def("setInputSource", &XmlDocument::setInputSource)
            .def("setEmptyTextElementsIgnored", &XmlDocument::setEmptyTextElementsIgnored)
            .scope[
                def("parse", (XmlElement *(*)(const File &))&XmlDocument::parse),
                def("parse", (XmlElement *(*)(const String &))&XmlDocument::parse)
            ]
    ];
}

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
			//.def("getEntry", (const ZipFile::ZipEntry *(ZipFile::*)(const String &) const noexcept) &ZipFile::getEntry)
			.def("sortEntriesByFilename", &ZipFile::sortEntriesByFilename)
			//.def("createStreamForEntry", (InputStream *(ZipFile::*)(int)) &ZipFile::createStreamForEntry, adopt(result))
			//.def("createStreamForEntry", (InputStream *(ZipFile::*)(const ZipFile::ZipEntry &)) &ZipFile::createStreamForEntry, adopt(result))
			.def("uncompressTo", &ZipFile::uncompressTo)
			.def("uncompressEntry", &ZipFile::uncompressEntry)
	];
}


void LInputStream::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<InputStream>("InputStream")
	];
}
