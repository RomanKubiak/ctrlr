#include "stdafx.h"

#include "CtrlrLuaManager.h"
#include "CtrlrMacros.h"
#include "CtrlrLog.h"
#include "Native/CtrlrNative.h"
#include "CtrlrUtilities.h"
#include "CtrlrManager/CtrlrManager.h"

#include "LFileListComponent.h"
#include "LFileTreeComponent.h"
#include "LMidiKeyboardComponent.h"
#include "LAudioThumbnail.h"
#include "LAudioPlayHead.h"
#include "LButton.h"
#include "LTextButton.h"
#include "LToggleButton.h"
#include "LAffineTransform.h"
#include "LAudioFile.h"
#include "LAudioFormat.h"
#include "LAudioSampleBuffer.h"
#include "LBigInteger.h"
#include "LColourGradient.h"
#include "LColour.h"
#include "LComponent.h"
#include "LFile.h"
#include "LGraphics.h"
#include "LImage.h"
#include "LJustification.h"
#include "LLine.h"
#include "LMemoryBlock.h"
#include "LMidiMessage.h"
#include "LMidiBuffer.h"
#include "LModifierKeys.h"
#include "LMouseCursor.h"
#include "LMouseEvent.h"
#include "LPath.h"
#include "LPoint.h"
#include "LPopupMenu.h"
#include "LRandom.h"
#include "LRectangle.h"
#include "LResult.h"
#include "LString.h"
#include "LTime.h"
#include "LURL.h"
#include "LValue.h"
#include "LValueTree.h"
#include "LLookAndFeel.h"
#include "LLabel.h"
#include "LSlider.h"
#include "LTimer.h"
#include "LFont.h"
#include "LBubbleMessageComponent.h"
#include "LAttributedString.h"
#include "LRange.h"
#include "LComponentPeer.h"
#include "LGlyphArrangement.h"
#include "LZipFile.h"
#include "LMemoryInputStream.h"
#include "LInputStream.h"
#include "LDrawable.h"
#include "LRelativeCoordinate.h"
#include "LExpression.h"
#include "LSparseSet.h"
#include "LAlertWindow.h"
#include "LComboBox.h"
#include "LTextEditor.h"
#include "LKeyPress.h"
#include "LThread.h"
#include "LThreadWithProgressWindow.h"
#include "LXmlElement.h"
#include "LTypeface.h"
#include "LBorderSize.h"
#include "LGlobalFunctions.h"
#include "LAsyncUpdater.h"

void CtrlrLuaManager::wrapJuceCoreClasses(lua_State *L)
{
	LBigInteger::wrapForLua(L);
	LXmlElement::wrapForLua(L);
	LFile::wrapForLua(L);
	LMemoryBlock::wrapForLua(L);
	LMidiMessage::wrapForLua(L);
	LMidiBuffer::wrapForLua(L);
	LString::wrapForLua(L);
	LResult::wrapForLua(L);
	LTime::wrapForLua(L);
	LURL::wrapForLua(L);
	LValue::wrapForLua(L);
	LTimer::wrapForLua(L);
	LTypeface::wrapForLua(L);
	LFont::wrapForLua(L);
	LZipFile::wrapForLua(L);
	LMemoryInputStream::wrapForLua(L);
	LInputStream::wrapForLua(L);
	LRange::wrapForLua(L);
	LSparseSet::wrapForLua(L);
	LAudioFile::wrapForLua(L);
	LAudioFormat::wrapForLua(L);
	LAudioSampleBuffer::wrapForLua(L);
	LBorderSize::wrapForLua(L);
}

void CtrlrLuaManager::wrapJuceClasses(lua_State *L)
{
	wrapJuceCoreClasses(L);

	LAffineTransform::wrapForLua(L);
	LColourGradient::wrapForLua(L);
	LColour::wrapForLua(L);
	LComponent::wrapForLua(L);
	LGraphics::wrapForLua(L);
	LImage::wrapForLua(L);
	LJustification::wrapForLua(L);
	LLine::wrapForLua(L);
	LModifierKeys::wrapForLua(L);
	LMouseEvent::wrapForLua(L);
	LMouseCursor::wrapForLua(L);
	LPath::wrapForLua(L);
	LPoint::wrapForLua(L);
	LButton::wrapForLua(L);
	LTextButton::wrapForLua(L);
	LToggleButton::wrapForLua(L);
	LPopupMenu::wrapForLua(L);
	LRandom::wrapForLua(L);
	LRectangle::wrapForLua(L);
	LValueTree::wrapForLua(L);
	LookAndFeelBase::wrapForLua(L);
	LLabel::wrapForLua(L);
	LSlider::wrapForLua(L);
	LBubbleMessageComponent::wrapForLua(L);
	LAttributedString::wrapForLua(L);
	LComponentPeer::wrapForLua(L);
	LGlyphArrangement::wrapForLua(L);
	LDrawable::wrapForLua(L);
	LRelativeCoordinate::wrapForLua(L);
	LAlertWindow::wrapForLua(L);
	LComboBox::wrapForLua(L);
	LTextEditor::wrapForLua(L);
	LKeyPress::wrapForLua(L);
	LThread::wrapForLua(L);
	LThreadWithProgressWindow::wrapForLua(L);
}

void LAffineTransform::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<AffineTransform>("AffineTransform")
				.def(constructor<float, float, float, float, float, float>())
				.def(constructor<>())
				.def(constructor<const AffineTransform &>())
				.def("translated", (AffineTransform (AffineTransform::*)(float, float) const noexcept)&AffineTransform::translated)
				.def("rotated", (AffineTransform (AffineTransform::*)(float) const noexcept) &AffineTransform::rotated)
				.def("rotated", (AffineTransform (AffineTransform::*)(float, float, float) const noexcept) &AffineTransform::rotated)
				.def("scaled",  (AffineTransform (AffineTransform::*)(float, float) const noexcept) &AffineTransform::scaled)
				.def("scaled",  (AffineTransform (AffineTransform::*)(float, float, float, float) const noexcept) &AffineTransform::scaled)
				.def("sheared", &AffineTransform::sheared)
				.def("inverted", &AffineTransform::inverted)
				.def("followedBy", &AffineTransform::followedBy)
				.def("isIdentity", &AffineTransform::isIdentity)
				.def("isSingularity", &AffineTransform::isSingularity)
				.def("isOnlyTranslation", &AffineTransform::isOnlyTranslation)
				.def("getTranslationX", &AffineTransform::getTranslationX)
				.def("getTranslationY", &AffineTransform::getTranslationY)
				.def("getScaleFactor", &AffineTransform::getScaleFactor)
				//.def("translation", &AffineTransform::translation)
				.scope
				[
					def("translation", (AffineTransform (*)(float, float) noexcept)&AffineTransform::translation),
					def("rotation", (AffineTransform (*)(float) noexcept)&AffineTransform::rotation),
					def("rotation", (AffineTransform (*)(float, float, float) noexcept)&AffineTransform::rotation),
					def("scale", (AffineTransform (*)(float) noexcept)&AffineTransform::scale),
					def("scale", (AffineTransform (*)(float, float) noexcept)&AffineTransform::scale),
					def("scale", (AffineTransform (*)(float, float, float, float) noexcept)&AffineTransform::scale),
					def("shear", (AffineTransform (*)(float, float) noexcept)&AffineTransform::shear),
					def("verticalFlip", (AffineTransform (*)(float) noexcept)&AffineTransform::verticalFlip),
					def("fromTargetPoints", (AffineTransform (*)(float, float, float, float, float, float) noexcept)&AffineTransform::fromTargetPoints)
				]
	];
}

LAlertWindow::LAlertWindow(const String &title, const String &message, AlertIconType iconType)
	: AlertWindow(title,message,iconType,nullptr)
{
}

LAlertWindow::~LAlertWindow()
{
}

void LAlertWindow::showMessageBox (AlertIconType iconType, const String& title, const String& message, const String& buttonText)
{
	AlertWindow::showMessageBox (iconType, title, message, buttonText, nullptr);
}

void LAlertWindow::showMessageBoxAsync (AlertIconType iconType, const String& title, const String& message, const String& buttonText)
{
	AlertWindow::showMessageBoxAsync (iconType, title, message, buttonText, nullptr);
}

bool LAlertWindow::showOkCancelBox (AlertIconType iconType, const String& title, const String& message, const String& button1Text, const String& button2Text)
{
	return (AlertWindow::showOkCancelBox (iconType, title, message, button1Text, button2Text, nullptr, nullptr));
}

int LAlertWindow::showYesNoCancelBox (AlertIconType iconType, const String& title, const String& message, const String& button1Text, const String& button2Text, const String& button3Text)
{
	return (AlertWindow::showYesNoCancelBox (iconType, title, message, button1Text, button2Text, button3Text, nullptr, nullptr));
}

bool LAlertWindow::showNativeDialogBox (const String& title, const String& bodyText, bool isOkCancel)
{
	return (AlertWindow::showNativeDialogBox (title, bodyText, isOkCancel));
}

void LAlertWindow::queryText(AlertIconType iconType, const String &title, const String &textMessage, const String &textAreaContent, const String &textAreaLabel, const String &button1Text, const String &button2Text, bool isContentPassword, luabind::object const &result)
{
	AlertWindow w(title, textMessage, iconType, 0);
	w.addTextEditor ("userInput", textAreaContent,  textAreaLabel, isContentPassword);
	w.addButton (button1Text, 1);
	w.addButton (button2Text, 0);
	result[1] = w.runModalLoop();
	result[2] = w.getTextEditorContents("userInput");
}

ComboBox *LAlertWindow::getComboBoxComponent(const String &comboName)
{
	ComboBox *box = AlertWindow::getComboBoxComponent (comboName);
	return (box);
}

int LAlertWindow::runModalLoop()
{
	const int ret = AlertWindow::runModalLoop();

	if (o.is_valid())
	{
		luabind::call_function<void> (o, ret, this);
	}

	return (ret);
}

void LAlertWindow::setModalHandler(luabind::object const& _o)
{
	o = _o;
}

void LAlertWindow::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<AlertWindow>("JAlertWindow")
		,
		class_<LAlertWindow, bases<AlertWindow, Component> >("AlertWindow")
			.def(constructor<const String &, const String &, AlertIconType>())
			.def("getAlertType", &AlertWindow::getAlertType)
			.def("setMessage", &AlertWindow::setMessage)
			.def("addButton", &AlertWindow::addButton)
			.def("getNumButtons", &AlertWindow::getNumButtons)
			.def("triggerButtonClick", &AlertWindow::triggerButtonClick)
			.def("setEscapeKeyCancels", &AlertWindow::setEscapeKeyCancels)
			.def("addTextEditor", &AlertWindow::addTextEditor)
			.def("getTextEditorContents", &AlertWindow::getTextEditorContents)
			.def("getTextEditor", &AlertWindow::getTextEditor)
			.def("addComboBox", &AlertWindow::addComboBox)
			.def("getComboBoxComponent", &LAlertWindow::getComboBoxComponent)
			.def("addTextBlock", &AlertWindow::addTextBlock)
			.def("addProgressBarComponent", &AlertWindow::addProgressBarComponent)
			.def("addCustomComponent", &AlertWindow::addCustomComponent)
			.def("getNumCustomComponents", &AlertWindow::getNumCustomComponents)
			.def("getCustomComponent", &AlertWindow::getCustomComponent)
			.def("removeCustomComponent", &AlertWindow::removeCustomComponent)
			.def("containsAnyExtraComponents", &AlertWindow::containsAnyExtraComponents)
			.def("setModalHandler", &LAlertWindow::setModalHandler)
			.def("runModalLoop", &LAlertWindow::runModalLoop)
			.def("exitModalState", &Component::exitModalState)
			.enum_("AlertIconType")
			[
				value("NoIcon", 0),
				value("QuestionIcon", 1),
				value("WarningIcon", 2),
				value("InfoIcon", 3)
			]
			.scope
			[
				def("showMessageBox", &LAlertWindow::showMessageBox),
				def("showMessageBoxAsync", &LAlertWindow::showMessageBoxAsync),
				def("showOkCancelBox", &LAlertWindow::showOkCancelBox),
				def("showYesNoCancelBox", &LAlertWindow::showYesNoCancelBox),
				def("showNativeDialogBox", &LAlertWindow::showNativeDialogBox),
				def("queryText", &LAlertWindow::queryText)
			]
	];
}

void LAsyncUpdater::handleAsyncUpdate()
{
}

void LAsyncUpdater::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<LAsyncUpdater>("AsyncUpdater")
            .def("triggerAsyncUpdate", &AsyncUpdater::triggerAsyncUpdate)
            .def("cancelPendingUpdate", &AsyncUpdater::cancelPendingUpdate)
            .def("handleUpdateNowIfNeeded", &AsyncUpdater::handleUpdateNowIfNeeded)
            .def("isUpdatePending", &AsyncUpdater::isUpdatePending)
            .def("handleAsyncUpdate", &LAsyncUpdater::handleAsyncUpdate)
	];
}

void LAttributedString::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<AttributedString>("AttributedString")
			.def(constructor<const String &>())
			.def("getText", &AttributedString::getText)
			.def("setText", &AttributedString::setText)
			.def("append", (void (AttributedString::*) (const String &)) &AttributedString::append)
			.def("append", (void (AttributedString::*) (const String &, const Font &)) &AttributedString::append)
			.def("append", (void (AttributedString::*) (const String &, const Colour)) &AttributedString::append)
			.def("append", (void (AttributedString::*) (const String &, const Font &, const Colour)) &AttributedString::append)
			.def("append", (void (AttributedString::*) (const AttributedString &)) &AttributedString::append)
			.def("clear", &AttributedString::clear)
			.def("getJustification", &AttributedString::getJustification)
			.def("setJustification", &AttributedString::setJustification)
			.def("getWordWrap", &AttributedString::getWordWrap)
			.def("setWordWrap", &AttributedString::setWordWrap)
			.def("getReadingDirection", &AttributedString::getReadingDirection)
			.def("setReadingDirection", &AttributedString::setReadingDirection)
			.def("getLineSpacing", &AttributedString::getLineSpacing)
			.def("setLineSpacing", &AttributedString::setLineSpacing)
			.def("getNumAttributes", &AttributedString::getNumAttributes)
			.def("getAttribute", &AttributedString::getAttribute)
			.def("setColour", (void (AttributedString::*) (const Range<int>, const Colour)) &AttributedString::setColour)
			.def("setColour", (void (AttributedString::*) (const Colour)) &AttributedString::setColour)
			.def("setFont", (void (AttributedString::*) (const Range<int>, const Font &)) &AttributedString::setFont)
			.def("setFont", (void (AttributedString::*) (const Font &)) &AttributedString::setFont)
			.enum_("WordWrap")
			[
				value("none", 0),
				value("byWord", 1),
				value("byChar", 2)
			]
			.enum_("ReadingDirection")
			[
				value("natural", 0),
				value("leftToRight", 1),
				value("rightToLeft", 2)
			]
			.scope
			[
				class_<AttributedString::Attribute>("Attribute")
				.def(constructor<const Range<int> &, const Colour &>())
				.def(constructor<const Range<int> &, const Font &>())
				.def("getFont", &AttributedString::Attribute::getFont)
				.def("getColour", &AttributedString::Attribute::getColour)
			]
	];
}

void LAudioFile::wrapForLua(lua_State *L)
{
	using namespace luabind;
	module(L)
    [
		class_<AiffAudioFormat>("AiffAudioFormat")
			.def(constructor<>())
			.def("canDoStereo", &AiffAudioFormat::canDoStereo)
			.def("canDoMono", &AiffAudioFormat::canDoMono)
			.def("canHandleFile", &AiffAudioFormat::canHandleFile)
			.def("createReaderFor", &AiffAudioFormat::createReaderFor)
			.def("createWriterFor", &AiffAudioFormat::createWriterFor)
		,
		class_<WavAudioFormat>("WavAudioFormat")
			.def(constructor<>())
			.def("canDoStereo", &WavAudioFormat::canDoStereo)
			.def("canDoMono", &WavAudioFormat::canDoMono)
			.def("canHandleFile", &WavAudioFormat::canHandleFile)
			.def("createReaderFor", &WavAudioFormat::createReaderFor)
			.def("createWriterFor", &WavAudioFormat::createWriterFor)
			.def("replaceMetadataInFile", &WavAudioFormat::replaceMetadataInFile)
			.def("createBWAVMetadata", &WavAudioFormat::createBWAVMetadata)
		,
		class_<OggVorbisAudioFormat>("OggVorbisAudioFormat")
			.def(constructor<>())
			.def("canDoStereo", &OggVorbisAudioFormat::canDoStereo)
			.def("canDoMono", &OggVorbisAudioFormat::canDoMono)
			.def("canHandleFile", &OggVorbisAudioFormat::canHandleFile)
			.def("createReaderFor", &OggVorbisAudioFormat::createReaderFor)
			.def("createWriterFor", &OggVorbisAudioFormat::createWriterFor)
			.def("isCompressed", &OggVorbisAudioFormat::isCompressed)
			.def("getQualityOptions", &OggVorbisAudioFormat::getQualityOptions)
			.def("estimateOggFileQuality", &OggVorbisAudioFormat::estimateOggFileQuality)
		,
		class_<FlacAudioFormat>("FlacAudioFormat")
			.def(constructor<>())
			.def("canDoStereo", &FlacAudioFormat::canDoStereo)
			.def("canDoMono", &FlacAudioFormat::canDoMono)
			.def("canHandleFile", &FlacAudioFormat::canHandleFile)
			.def("createReaderFor", &FlacAudioFormat::createReaderFor)
			.def("createWriterFor", &FlacAudioFormat::createWriterFor)
			.def("isCompressed", &FlacAudioFormat::isCompressed)
			.def("getQualityOptions", &FlacAudioFormat::getQualityOptions)
	];
}

void LAudioFormat::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<int64>("int64")
		,
		class_<AudioFormatReader>("AudioFormatReader")
				.def("getFormatName", &AudioFormatReader::getFormatName)
				.def("read", (bool (AudioFormatReader::*)(int *const *, int, int64, int, bool))&AudioFormatReader::read)
				.def("read", (void (AudioFormatReader::*)(AudioSampleBuffer *, int, int, int64, bool, bool))&AudioFormatReader::read)
				.def("readMaxLevels", (void (AudioFormatReader::*)(int64, int64, float&, float&, float&, float&))&AudioFormatReader::readMaxLevels)
				.def("searchForLevel", &AudioFormatReader::searchForLevel)
				.def_readonly("sampleRate", &AudioFormatReader::sampleRate)
				.def_readonly("bitsPerSample", &AudioFormatReader::bitsPerSample)
				.def_readonly("lengthInSamples", &AudioFormatReader::lengthInSamples)
				.def_readonly("numChannels", &AudioFormatReader::numChannels)
				.def_readonly("usesFloatingPointData", &AudioFormatReader::usesFloatingPointData)
				.def_readonly("metadataValues", &AudioFormatReader::metadataValues)
				.def_readonly("input", &AudioFormatReader::input)
		,
			class_<AudioFormatWriter>("AudioFormatWriter")
				.def("getFormatName", &AudioFormatWriter::getFormatName)
				.def("writeFromAudioReader", &AudioFormatWriter::writeFromAudioReader)
				.def("writeFromAudioSource", &AudioFormatWriter::writeFromAudioSource)
				.def("writeFromAudioSampleBuffer", &AudioFormatWriter::writeFromAudioSampleBuffer)
				.def("getSampleRate", &AudioFormatWriter::getSampleRate)
				.def("getNumChannels", &AudioFormatWriter::getNumChannels)
				.def("getBitsPerSample", &AudioFormatWriter::getBitsPerSample)
				.def("isFloatingPoint", &AudioFormatWriter::isFloatingPoint)
		,
			class_<AudioFormat>("AudioFormat")
				.def("getFormatName", &AudioFormat::getFormatName)
				.def("getFileExtensions", &AudioFormat::getFileExtensions)
				.def("canHandleFile", &AudioFormat::canHandleFile)
				.def("canDoStereo", &AudioFormat::canDoStereo)
				.def("canDoMono", &AudioFormat::canDoMono)
				.def("isCompressed", &AudioFormat::isCompressed)
				.def("getQualityOptions", &AudioFormat::getQualityOptions)
				.def("canDoMono", &AudioFormat::canDoMono)
		,
			class_<AudioFormatManager>("JAudioFormatManager")
			,
			class_<LAudioFormatManager, bases<AudioFormatManager> >("AudioFormatManager")
				.def(constructor<>())
				.def("registerBasicFormats", &AudioFormatManager::registerBasicFormats)
				.def("getNumKnownFormats", &AudioFormatManager::getNumKnownFormats)
				.def("getKnownFormat", &AudioFormatManager::getKnownFormat)
				.def("findFormatForFileExtension", &AudioFormatManager::findFormatForFileExtension)
				.def("getDefaultFormat", &AudioFormatManager::getDefaultFormat)
				.def("getWildcardForAllFormats", &AudioFormatManager::getWildcardForAllFormats)
				.def("createReaderFor", &LAudioFormatManager::createReaderFor)
		,
			class_<AudioThumbnailCache>("AudtioThumbnailCache")
				.def(constructor<int>())
				.def("clear", &AudioThumbnailCache::clear)
				.def("loadThumb", &AudioThumbnailCache::loadThumb)
				.def("storeThumb", &AudioThumbnailCache::storeThumb)
				.def("removeThumb", &AudioThumbnailCache::removeThumb)
				.def("readFromStream", &AudioThumbnailCache::readFromStream)
				.def("writeToStream", &AudioThumbnailCache::writeToStream)
				.def("getTimeSliceThread", &AudioThumbnailCache::getTimeSliceThread)
	];
}

void LAudioPlayHead::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<AudioPlayHead>("AudioPlayHead")
			.def("getCurrentPosition", &AudioPlayHead::getCurrentPosition)
			.enum_("FrameRateType")
			[
                value("fps24", AudioPlayHead::fps24),
                value("fps25", AudioPlayHead::fps25),
                value("fps2997", AudioPlayHead::fps2997),
                value("fps30", AudioPlayHead::fps30),
                value("fps2997drop", AudioPlayHead::fps2997drop),
                value("fps30drop", AudioPlayHead::fps30drop),
                value("fpsUnknown", AudioPlayHead::fpsUnknown)
			]
        ,
        class_<AudioPlayHead::CurrentPositionInfo>("CurrentPositionInfo")
            .def_readonly ("bpm", &AudioPlayHead::CurrentPositionInfo::bpm)
            .def_readonly ("timeSignNumerator", &AudioPlayHead::CurrentPositionInfo::timeSigNumerator)
            .def_readonly ("timeSigDenominator", &AudioPlayHead::CurrentPositionInfo::timeSigDenominator)
            .def_readonly ("timeInSamples", &AudioPlayHead::CurrentPositionInfo::timeInSamples)
            .def_readonly ("timeInSeconds", &AudioPlayHead::CurrentPositionInfo::timeInSeconds)
            .def_readonly ("editOriginTime", &AudioPlayHead::CurrentPositionInfo::editOriginTime)
            .def_readonly ("ppqPosition", &AudioPlayHead::CurrentPositionInfo::ppqPosition)
            .def_readonly ("ppqPositionOfLastBarStart", &AudioPlayHead::CurrentPositionInfo::ppqPositionOfLastBarStart)
            .def_readonly ("frameRate", &AudioPlayHead::CurrentPositionInfo::frameRate)
            .def_readonly ("isPlaying", &AudioPlayHead::CurrentPositionInfo::isPlaying)
            .def_readonly ("isRecording", &AudioPlayHead::CurrentPositionInfo::isRecording)
            .def_readonly ("ppqLoopStart", &AudioPlayHead::CurrentPositionInfo::ppqLoopStart)
            .def_readonly ("ppqLoopEnd", &AudioPlayHead::CurrentPositionInfo::ppqLoopEnd)
            .def_readonly ("isLooping", &AudioPlayHead::CurrentPositionInfo::isLooping)
	];
}

void LAudioSampleBuffer::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<AudioSampleBuffer>("AudioSampleBuffer")
				.def(constructor<int, int>())
				.def(constructor<float *const *, int, int>())
				.def(constructor<float *const *, int, int, int>())
				.def("getNumChannels", &AudioSampleBuffer::getNumChannels)
				.def("getNumSamples", &AudioSampleBuffer::getNumSamples)
				//.def("getSampleData", (float *(AudioSampleBuffer::*)(int) noexcept)&AudioSampleBuffer::getSampleData)
				//.def("getSampleData", (float *(AudioSampleBuffer::*)(int, int) noexcept)&AudioSampleBuffer::getSampleData)
				.def("getArrayOfChannels", &AudioSampleBuffer::getArrayOfWritePointers)
				.def("getArrayOfWritePointers", &AudioSampleBuffer::getArrayOfWritePointers)
				.def("setSize", &AudioSampleBuffer::setSize)
				.def("setDataToReferTo", &AudioSampleBuffer::setDataToReferTo)
				.def("clear", (void (AudioSampleBuffer::*)(void))&AudioSampleBuffer::clear)
				.def("clear", (void (AudioSampleBuffer::*)(int,int))&AudioSampleBuffer::clear)
				.def("clear", (void (AudioSampleBuffer::*)(int,int,int))&AudioSampleBuffer::clear)
				.def("applyGain", (void (AudioSampleBuffer::*)(int,int,int,float))&AudioSampleBuffer::applyGain)
				.def("applyGain", (void (AudioSampleBuffer::*)(int,int,float))&AudioSampleBuffer::applyGain)
				// .def("applyGainRamp", &AudioSampleBuffer::applyGainRamp)
				.def("addFrom", (void (AudioSampleBuffer::*)(int,int,const AudioSampleBuffer&, int, int, int, float))&AudioSampleBuffer::addFrom)
				.def("addFrom", (void (AudioSampleBuffer::*)(int,int,const float *, int, float))&AudioSampleBuffer::addFrom)
				.def("addFromWithRamp", (void (AudioSampleBuffer::*)(int,int,const float *,int,float,float))&AudioSampleBuffer::addFromWithRamp)
				.def("copyFrom", (void (AudioSampleBuffer::*)(int,int,const AudioSampleBuffer&, int, int, int))&AudioSampleBuffer::copyFrom)
				.def("copyFrom", (void (AudioSampleBuffer::*)(int,int,const float *, int))&AudioSampleBuffer::copyFrom)
				.def("copyFrom", (void (AudioSampleBuffer::*)(int,int,const float *, int, float))&AudioSampleBuffer::copyFrom)
				.def("copyFromWithRamp", (void (AudioSampleBuffer::*)(int,int,const float *,int,float,float) const noexcept)&AudioSampleBuffer::copyFromWithRamp)
				.def("findMinMax", &AudioSampleBuffer::findMinMax)
				.def("getMagnitude", (float (AudioSampleBuffer::*)(int,int,int) const noexcept)&AudioSampleBuffer::getMagnitude)
				.def("getMagnitude", (float (AudioSampleBuffer::*)(int,int) const noexcept)&AudioSampleBuffer::getMagnitude)
				.def("getRMSLevel", &AudioSampleBuffer::getRMSLevel)
	];
}

void LAudioThumbnail::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<AudioThumbnail>("AudioThumbnail")
			.def(constructor<int, AudioFormatManager &, AudioThumbnailCache &>())
			.def("clear", &AudioThumbnail::clear)
			.def("setSource", &AudioThumbnail::setSource)
			.def("setReader", &AudioThumbnail::setReader)
			.def("reset", &AudioThumbnail::reset)
			.def("addBlock", &AudioThumbnail::addBlock)
			.def("loadFrom", &AudioThumbnail::loadFrom)
			.def("saveTo", &AudioThumbnail::saveTo)
			.def("getNumChannels", &AudioThumbnail::getNumChannels)
			.def("getTotalLength", &AudioThumbnail::getNumChannels)
			.def("drawChannel", &AudioThumbnail::drawChannel)
			.def("drawChannels", &AudioThumbnail::drawChannels)
			.def("isFullyLoaded", &AudioThumbnail::isFullyLoaded)
			.def("getProportionComplete", &AudioThumbnail::getProportionComplete)
			.def("getNumSamplesFinished", &AudioThumbnail::getNumSamplesFinished)
			.def("getApproximatePeak", &AudioThumbnail::getApproximatePeak)
			.def("getApproximateMinMax", &AudioThumbnail::getApproximateMinMax)
			.def("getHashCode", &AudioThumbnail::getHashCode)
	];
}

void LBigInteger::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
			class_<BigInteger>("JUCEBigInteger")
		,
			class_<LBigInteger,BigInteger>("BigInteger")
				.def(constructor<>())
				.def(constructor<int>())
				.def(const_self + BigInteger ())
				.def(const_self - BigInteger ())
				.def(const_self * BigInteger ())
				.def(const_self / BigInteger ())
				.def(const_self < BigInteger ())
				.def(const_self <= BigInteger ())
				.def(const_self == BigInteger ())
				//.def("xor", &LBigInteger::xor)
				//.def("and", &LBigInteger::and)
				//.def("or", &LBigInteger::or)
				.def("swapWith", &BigInteger::swapWith)
				.def("isZero", &BigInteger::isZero)
				.def("isOne", &BigInteger::isOne)
				.def("toInteger", &BigInteger::toInteger)
				.def("clear", &BigInteger::clear)
				.def("clearBit", &BigInteger::clearBit)
				.def("setBit", (void (BigInteger::*)(int))&BigInteger::setBit)
				.def("setBit", (void (BigInteger::*)(int,bool))&BigInteger::setBit)
				.def("setRange", &BigInteger::setRange)
				.def("insertBit", &BigInteger::insertBit)
				.def("getBitRange", &BigInteger::getBitRange)
				.def("getBitRangeAsInt", &BigInteger::getBitRangeAsInt)
				.def("setBitRangeAsInt", &BigInteger::setBitRangeAsInt)
				.def("shiftBits", &BigInteger::shiftBits)
				.def("countNumberOfSetBits", &BigInteger::countNumberOfSetBits)
				.def("findNextSetBit", &BigInteger::findNextSetBit)
				.def("findNextClearBit", &BigInteger::findNextClearBit)
				.def("getHighestBit", &BigInteger::getHighestBit)
				.def("compare", &BigInteger::compare)
				.def("compareAbsolute", &BigInteger::compareAbsolute)
				.def("divideBy", &BigInteger::divideBy)
				.def("findGreatestCommonDivisor", &BigInteger::findGreatestCommonDivisor)
				.def("exponentModulo", &BigInteger::exponentModulo)
				.def("inverseModulo", &BigInteger::inverseModulo)
				.def("isNegative", &BigInteger::isNegative)
				.def("setNegative", &BigInteger::setNegative)
				.def("negate", &BigInteger::negate)
				.def("toString", &BigInteger::toString)
				.def("parseString", &BigInteger::parseString)
				.def("toMemoryBlock", &BigInteger::toMemoryBlock)
				.def("loadFromMemoryBlock", &BigInteger::loadFromMemoryBlock)
	];
}

void LBorderSize::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<BorderSize<int> >("BorderSize")
	];
}

LBubbleMessageComponent::LBubbleMessageComponent(int fadeOutLengthMs) : BubbleMessageComponent(fadeOutLengthMs)
{
}

void LBubbleMessageComponent::showAt (Component *component, const String &message, int numMillisecondsBeforeRemoving, bool removeWhenMouseClicked, bool deleteSelfAfterUse)
{
	addToDesktop (0, nullptr);
	BubbleMessageComponent::showAt (component, AttributedString(message), numMillisecondsBeforeRemoving, removeWhenMouseClicked, deleteSelfAfterUse);
}

void LBubbleMessageComponent::showAt (Component *component, const AttributedString &message, int numMillisecondsBeforeRemoving, bool removeWhenMouseClicked, bool deleteSelfAfterUse)
{
	addToDesktop (0, nullptr);
	BubbleMessageComponent::showAt (component, AttributedString(message), numMillisecondsBeforeRemoving, removeWhenMouseClicked, deleteSelfAfterUse);
}

void LBubbleMessageComponent::showAt (const Rectangle<int> &rectangle, const AttributedString &message, int numMillisecondsBeforeRemoving, bool removeWhenMouseClicked, bool deleteSelfAfterUse)
{
	addToDesktop (0, nullptr);
	BubbleMessageComponent::showAt (rectangle, message, numMillisecondsBeforeRemoving, removeWhenMouseClicked, deleteSelfAfterUse);
}

void LBubbleMessageComponent::showAt (const Rectangle<int> &rectangle, const String &message, int numMillisecondsBeforeRemoving, bool removeWhenMouseClicked, bool deleteSelfAfterUse)
{
	addToDesktop (0, nullptr);
	BubbleMessageComponent::showAt (rectangle, AttributedString(message), numMillisecondsBeforeRemoving, removeWhenMouseClicked, deleteSelfAfterUse);
}

void LBubbleMessageComponent::getContentSize (int &w, int &h)
{
	BubbleMessageComponent::getContentSize(w,h);
}

void LBubbleMessageComponent::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<LBubbleMessageComponent, bases<Component> >("BubbleMessageComponent")
			.def(constructor<int>())
			.def("showAt", (void (LBubbleMessageComponent::*)(const Rectangle<int> &, const AttributedString &, int, bool, bool)) &LBubbleMessageComponent::showAt)
			.def("showAt", (void (LBubbleMessageComponent::*)(const Rectangle<int> &, const String &, int, bool, bool)) &LBubbleMessageComponent::showAt)
			.def("showAt", (void (LBubbleMessageComponent::*)(Component *, const AttributedString &, int, bool, bool)) &LBubbleMessageComponent::showAt)
			.def("showAt", (void (LBubbleMessageComponent::*)(Component *, const String &, int, bool, bool)) &LBubbleMessageComponent::showAt)
			.def("getContentSize", &LBubbleMessageComponent::getContentSize)
	];
}

void LButton::wrapForLua (lua_State *L)
{
    using namespace luabind;

	module(L)
    [
        class_<SettableTooltipClient>("SettableTooltipClient")
        ,
		class_<Button, bases<Component, SettableTooltipClient> >("Button")
            .def("setButtonText", &Button::setButtonText)
            .def("getButtonText", &Button::getButtonText)
            .def("isDown", &Button::isDown)
            .def("isOver", &Button::isOver)
            .def("setToggleState", (void (Button::*)(bool, NotificationType))&Button::setToggleState)
            .def("setToggleState", (void (Button::*)(bool, bool))&Button::setToggleState)
            .def("getToggleState", &Button::getToggleState)
            .def("getToggleStateValue", &Button::getToggleStateValue)
            .def("setClickingTogglesState", &Button::setClickingTogglesState)
            .def("getClickingTogglesState", &Button::getClickingTogglesState)
            .def("setRadioGroupId", &Button::setRadioGroupId)
            .def("getRadioGroupId", &Button::getRadioGroupId)
            .def("addListener", &Button::addListener)
            .def("removeListener", &Button::removeListener)
            .def("triggerClick", &Button::triggerClick)
            .def("setCommandToTrigger", &Button::setCommandToTrigger)
            .def("getCommandID", &Button::getCommandID)
            .def("addShortcut", &Button::addShortcut)
            .def("clearShortcuts", &Button::clearShortcuts)
            .def("isRegisteredForShortcut", &Button::isRegisteredForShortcut)
            .def("setRepeatSpeed", &Button::setRepeatSpeed)
            .def("setTriggeredOnMouseDown", &Button::setTriggeredOnMouseDown)
            .def("getMillisecondsSinceButtonDown", &Button::getMillisecondsSinceButtonDown)
            .def("setTooltip", &Button::setTooltip)
            .def("getTooltip", &Button::getTooltip)
            .def("setConnectedEdges", &Button::setConnectedEdges)
            .def("getConnectedEdgeFlags", &Button::getConnectedEdgeFlags)
            .def("isConnectedOnLeft", &Button::isConnectedOnLeft)
            .def("isConnectedOnRight", &Button::isConnectedOnRight)
            .def("isConnectedOnTop", &Button::isConnectedOnTop)
            .def("isConnectedOnBottom", &Button::isConnectedOnBottom)
            .def("setState", &Button::setState)
    ];
}

void LColour::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Colour>("Colour")
			.def(constructor<uint32>())
			.def(constructor<const Colour &>())
			.def(constructor<uint8, uint8, uint8, uint8>())
			.def("getRed", &Colour::getRed)
			.def("getGreen", &Colour::getGreen)
			.def("getBlue", &Colour::getBlue)
			.def("getFloatRed", &Colour::getFloatRed)
			.def("getFloatGreen", &Colour::getFloatGreen)
			.def("getFloatBlue", &Colour::getFloatBlue)
			.def("getARGB", &Colour::getARGB)
			.def("getAlpha", &Colour::getAlpha)
			.def("getFloatAlpha", &Colour::getFloatAlpha)
			.def("isOpaque", &Colour::isOpaque)
			.def("isTransparent", &Colour::isTransparent)
			.def("withAlpha", (Colour (Colour::*) (float) const noexcept)&Colour::withAlpha)
			.def("withMultipliedAlpha", &Colour::withMultipliedAlpha)
			.def("overlaidWith", &Colour::overlaidWith)
			.def("interpolatedWith", &Colour::interpolatedWith)
			.def("getHue", &Colour::getHue)
			.def("getSaturation", &Colour::getSaturation)
			.def("withHue", &Colour::withHue)
			.def("withSaturation", &Colour::withSaturation)
			.def("withBrightness", &Colour::withBrightness)
			.def("withRotatedHue", &Colour::withRotatedHue)
			.def("withMultipliedSaturation", &Colour::withMultipliedSaturation)
			.def("withMultipliedBrightness", &Colour::withMultipliedBrightness)
			.def("brighter", &Colour::brighter)
			.def("darker", &Colour::darker)
			.def("toString", &Colour::toString)
			.def("toDisplayString", &Colour::toDisplayString)
			.scope
			[
                def("fromRGB", &Colour::fromRGB),
                def("fromRGBA", &Colour::fromRGBA),
                def("fromFloatRGBA", &Colour::fromFloatRGBA),
                def("fromHSV", &Colour::fromHSV),
                def("contrasting", (Colour (*)(Colour, Colour) noexcept) &Colour::contrasting),
                def("greyLevel", (Colour (*)(float)) &Colour::greyLevel),
                def("fromString", &Colour::fromString)
			]
	];
}

void LColourGradient::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<ColourGradient>("ColourGradient")
			.def(constructor<const Colour &, float, float, const Colour &, float, float, bool>())
			.def(constructor<>())
			.def("clearColours", &ColourGradient::clearColours)
			.def("addColour", &ColourGradient::addColour)
			.def("removeColour", &ColourGradient::removeColour)
			.def("multiplyOpacity", &ColourGradient::multiplyOpacity)
			.def("getNumColours", &ColourGradient::getNumColours)
			.def("getColourPosition", &ColourGradient::getColourPosition)
			.def("getColour", &ColourGradient::getColour)
			.def("setColour", &ColourGradient::setColour)
			.def("getColourAtPosition", &ColourGradient::getColourAtPosition)
			.def("isOpaque", &ColourGradient::isOpaque)
			.def("isInvisible", &ColourGradient::isInvisible)
		,
		class_<FillType>("FillType")
			.def(constructor<FillType &>())
			.def(constructor<const Colour &>())
			.def(constructor<const ColourGradient &>())
			.def(constructor<const Image &, const AffineTransform &>())
			.def("isColour", &FillType::isColour)
			.def("isGradient", &FillType::isGradient)
			.def("isTiledImage", &FillType::isTiledImage)
			.def("setColour", &FillType::setColour)
			.def("setGradient", &FillType::setGradient)
			.def("setTiledImage", &FillType::setTiledImage)
			.def("setOpacity", &FillType::setOpacity)
			.def("getOpacity", &FillType::getOpacity)
			.def("isInvisible", &FillType::isInvisible)
	];
}

void LComboBox::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<ComboBox, bases<Component> >("ComboBox")
			.def(constructor<>())
			.def(constructor<const String &>())
			.def("setEditableText", &ComboBox::setEditableText)
			.def("isTextEditable", &ComboBox::isTextEditable)
			.def("setJustificationType", &ComboBox::setJustificationType)
			.def("getJustificationType", &ComboBox::getJustificationType)
			.def("addItem", &ComboBox::addItem)
			.def("addItemList", &ComboBox::addItemList)
			.def("addSeparator", &ComboBox::addSeparator)
			.def("addSectionHeading", &ComboBox::addSectionHeading)
			.def("setItemEnabled", &ComboBox::setItemEnabled)
			.def("isItemEnabled", &ComboBox::isItemEnabled)
			.def("changeItemText", &ComboBox::changeItemText)
			.def("clear", (void (ComboBox::*)(NotificationType))&ComboBox::clear)
			.def("getNumItems", &ComboBox::getNumItems)
			.def("getItemText", &ComboBox::getItemText)
			.def("getItemId", &ComboBox::getItemId)
			.def("indexOfItemId", &ComboBox::indexOfItemId)
			.def("getSelectedId", &ComboBox::getSelectedId)
			.def("getSelectedIdAsValue", &ComboBox::getSelectedIdAsValue)
			.def("setSelectedId", (void (ComboBox::*)(int, NotificationType))&ComboBox::setSelectedId)
			.def("getSelectedItemIndex", &ComboBox::getSelectedItemIndex)
			.def("setSelectedItemIndex", (void (ComboBox::*)(int, NotificationType))&ComboBox::setSelectedItemIndex)
			.def("getText", &ComboBox::getText)
			.def("setText", (void (ComboBox::*)(const String &, NotificationType))&ComboBox::setText)
			.def("showEditor", &ComboBox::showEditor)
			.def("showPopup", &ComboBox::showPopup)
			.def("addListener", &ComboBox::addListener)
			.def("removeListener", &ComboBox::removeListener)
			.def("setTextWhenNothingSelected", &ComboBox::setTextWhenNothingSelected)
			.def("getTextWhenNothingSelected", &ComboBox::getTextWhenNothingSelected)
			.def("setTextWhenNoChoicesAvailable", &ComboBox::setTextWhenNoChoicesAvailable)
			.def("setTooltip", &ComboBox::setTooltip)
	];
}

void LComponent::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
        class_<DropShadow>("DropShadow")
            .def(constructor<>())
            .def(constructor<Colour, int, Point<int> >())
            .def("drawForImage", &DropShadow::drawForImage)
            .def("drawForPath", &DropShadow::drawForPath)
            .def("drawForRectangle", &DropShadow::drawForRectangle)
        ,
        class_<DropShadower>("DropShadower")
            .def(constructor<const DropShadow &>())
            .def("setOwner", &DropShadower::setOwner)
        ,
		class_<LComponent>("LComponent")
		,
		class_<Component, LComponent>("Component")
			.def(constructor<>())
			.def(constructor<const String &>())
			.def("setName", &Component::setName)
			.def("getComponentID", &Component::getComponentID)
			.def("setComponentID", &Component::setComponentID)
			.def("setVisible", &Component::setVisible)
			.def("isVisible", &Component::isVisible)
			.def("visibilityChanged", &Component::visibilityChanged)
			.def("isShowing", &Component::isShowing)
			.def("addToDesktop", &LComponent::addToDesktop)
			.def("removeFromDesktop", &Component::removeFromDesktop)
			.def("isOnDesktop", &Component::isOnDesktop)
			.def("getPeer", &Component::getPeer)
			.def("userTriedToCloseWindow", &Component::userTriedToCloseWindow)
			.def("minimisationStateChanged", &Component::minimisationStateChanged)
			.def("toFront", &Component::toFront)
			.def("toBack", &Component::toBack)
			.def("toBehind", &Component::toBehind)
			.def("setAlwaysOnTop", &Component::setAlwaysOnTop)
			.def("isAlwaysOnTop", &Component::isAlwaysOnTop)
			.def("getX", &Component::getX)
			.def("getY", &Component::getY)
			.def("getWidth", &Component::getWidth)
			.def("getHeight", &Component::getHeight)
			.def("getRight", &Component::getRight)
			.def("getPosition", &Component::getPosition)
			.def("getBottom", &Component::getBottom)
			.def("getBounds", &Component::getBounds)
			.def("getLocalBounds", &Component::getLocalBounds)
			.def("getBoundsInParent", &Component::getBoundsInParent)
			.def("getScreenX", &Component::getScreenX)
			.def("getScreenY", &Component::getScreenY)
			.def("getScreenPosition", &Component::getScreenPosition)
			.def("getScreenBounds", &Component::getScreenBounds)
			.def("getLocalPoint", (Point<int> (Component::*)(const Component *, Point<int>) const) &Component::getLocalPoint)
			.def("getLocalArea", &Component::getLocalArea)
			.def("localPointToGlobal", (Point<int> (Component::*)(Point<int>) const) &Component::localPointToGlobal)
			.def("localAreaToGlobal", &Component::localAreaToGlobal)
			.def("setTopLeftPosition", (void (Component::*)(int,int))&Component::setTopLeftPosition)
			.def("setTopLeftPosition", (void (Component::*)(const Point<int>))&Component::setTopLeftPosition)
			.def("setTopRightPosition", &Component::setTopRightPosition)
			.def("setSize", &Component::setSize)
			.def("setBounds", (void (Component::*)(int,int,int,int))&Component::setBounds)
			.def("setBounds", (void (Component::*)(const Rectangle<int> &))&Component::setBounds)
			.def("setBounds", (void (Component::*)(const RelativeRectangle &))&Component::setBounds)
			.def("setBounds", (void (Component::*)(const String &))&Component::setBounds)
			.def("setBoundsRelative", &Component::setBoundsRelative)
			.def("setBoundsInset", &Component::setBoundsInset)
			.def("setBoundsToFit", &Component::setBoundsToFit)
			.def("setCentrePosition", &Component::setCentrePosition)
			.def("setCentreRelative", &Component::setCentreRelative)
			.def("centreWithSize", &Component::centreWithSize)
			.def("setTransform", &Component::setTransform)
			.def("getTransform", &Component::getTransform)
			.def("isTransformed", &Component::isTransformed)
			.def("proportionOfWidth", &Component::proportionOfWidth)
			.def("proportionOfHeight", &Component::proportionOfHeight)
			.def("getParentWidth", &Component::getParentWidth)
			.def("getParentHeight", &Component::getParentHeight)
			.def("getParentMonitorArea", &Component::getParentMonitorArea)
			.def("getNumChildComponents", &Component::getNumChildComponents)
			.def("getChildComponent", &Component::getChildComponent)
			.def("getIndexOfChildComponent", &Component::getIndexOfChildComponent)
			.def("findChildWithID", &Component::findChildWithID)
			.def("addChildComponent", (void (Component::*)(Component *, int))&Component::addChildComponent)
			.def("addChildComponent", (void (Component::*)(Component &, int))&Component::addChildComponent)
			.def("addAndMakeVisible", (void (Component::*)(Component *, int))&Component::addAndMakeVisible)
			.def("addAndMakeVisible", (void (Component::*)(Component &, int))&Component::addAndMakeVisible)
			.def("addChildAndSetID", &Component::addChildAndSetID)
			.def("removeChildComponent", (void (Component::*)(Component *))&Component::removeChildComponent)
			.def("removeChildComponent", (Component *(Component::*)(int))&Component::removeChildComponent)
			.def("removeAllChildren", &Component::removeAllChildren)
			.def("deleteAllChildren", &Component::deleteAllChildren)
			.def("getParentComponent", &Component::getParentComponent)
			.def("getTopLevelComponent", &Component::getTopLevelComponent)
			.def("isParentOf", &Component::isParentOf)
			.def("parentHierarchyChanged", &Component::parentHierarchyChanged)
			.def("childrenChanged", &Component::childrenChanged)
			.def("hitTest", &Component::hitTest)
			.def("setInterceptsMouseClicks", &Component::setInterceptsMouseClicks)
			.def("getInterceptsMouseClicks", &Component::getInterceptsMouseClicks)
			.def("contains", (bool (Component::*)(const Point<int>))&Component::contains)
			.def("reallyContains", &Component::reallyContains)
			.def("getComponentAt", (Component *(Component::*)(int,int))&Component::getComponentAt)
			.def("getComponentAt", (Component *(Component::*)(const Point<int>))&Component::getComponentAt)
			.def("repaint", (void (Component::*)(void))&Component::repaint)
			.def("repaint", (void (Component::*)(int,int,int,int))&Component::repaint)
			.def("repaint", (void (Component::*)(const Rectangle<int> &))&Component::repaint)
			.def("setBufferedToImage", &Component::setBufferedToImage)
			.def("createComponentSnapshot", &Component::createComponentSnapshot)
			.def("paintEntireComponent", &Component::paintEntireComponent)
			.def("setPaintingIsUnclipped", &Component::setPaintingIsUnclipped)
			.def("setComponentEffect", &Component::setComponentEffect)
			.def("getComponentEffect", &Component::getComponentEffect)
			.def("getLookAndFeel", &Component::getLookAndFeel)
			.def("setLookAndFeel", &Component::setLookAndFeel)
			.def("lookAndFeelChanged", &Component::lookAndFeelChanged)
			.def("sendLookAndFeelChange", &Component::sendLookAndFeelChange)
			.def("setOpaque", &Component::setOpaque)
			.def("isOpaque", &Component::isOpaque)
			.def("setBroughtToFrontOnMouseClick", &Component::setBroughtToFrontOnMouseClick)
			.def("isBroughtToFrontOnMouseClick", &Component::isBroughtToFrontOnMouseClick)
			.def("setWantsKeyboardFocus", &Component::setWantsKeyboardFocus)
			.def("getWantsKeyboardFocus", &Component::getWantsKeyboardFocus)
			.def("setMouseClickGrabsKeyboardFocus", &Component::setMouseClickGrabsKeyboardFocus)
			.def("getMouseClickGrabsKeyboardFocus", &Component::getMouseClickGrabsKeyboardFocus)
			.def("grabKeyboardFocus", &Component::grabKeyboardFocus)
			.def("hasKeyboardFocus", &Component::hasKeyboardFocus)
			.def("moveKeyboardFocusToSibling", &Component::moveKeyboardFocusToSibling)
			.def("createFocusTraverser", &Component::createFocusTraverser)
			.def("getExplicitFocusOrder", &Component::getExplicitFocusOrder)
			.def("setExplicitFocusOrder", &Component::setExplicitFocusOrder)
			.def("setFocusContainer", &Component::setFocusContainer)
			.def("isFocusContainer", &Component::isFocusContainer)
			.def("isEnabled", &Component::isEnabled)
			.def("setEnabled", &Component::setEnabled)
			.def("enablementChanged", &Component::enablementChanged)
			.def("setAlpha", &Component::setAlpha)
			.def("getAlpha", &Component::getAlpha)
			.def("setMouseCursor", &Component::setMouseCursor)
			.def("getMouseCursor", &Component::getMouseCursor)
			.def("updateMouseCursor", &Component::updateMouseCursor)
			.def("paint", &Component::paint)
			.def("paintOverChildren", &Component::paintOverChildren)
			.def("mouseMove", &Component::mouseMove)
			.def("mouseEnter", &Component::mouseEnter)
			.def("mouseExit", &Component::mouseExit)
			.def("mouseDown", &Component::mouseDown)
			.def("mouseDrag", &Component::mouseDrag)
			.def("mouseUp", &Component::mouseUp)
			.def("mouseDoubleClick", &Component::mouseDoubleClick)
			.def("mouseWheelMove", &Component::mouseWheelMove)
			.def("setRepaintsOnMouseActivity", &Component::setRepaintsOnMouseActivity)
			.def("addMouseListener", &Component::addMouseListener)
			.def("removeMouseListener", &Component::removeMouseListener)
			.def("addKeyListener", &Component::addKeyListener)
			.def("removeKeyListener", &Component::removeKeyListener)
			.def("keyPressed", &Component::keyPressed)
			.def("keyStateChanged", &Component::keyStateChanged)
			.def("modifierKeysChanged", &Component::modifierKeysChanged)
			.def("focusGained", &Component::focusGained)
			.def("focusLost", &Component::focusLost)
			.def("focusOfChildComponentChanged", &Component::focusOfChildComponentChanged)
			.def("isMouseOver", &Component::isMouseOver)
			.def("isMouseButtonDown", &Component::isMouseButtonDown)
			.def("isMouseOverOrDragging", &Component::isMouseOverOrDragging)
			.def("getMouseXYRelative", &Component::getMouseXYRelative)
			.def("resized", &Component::resized)
			.def("moved", &Component::moved)
			.def("childBoundsChanged", &Component::childBoundsChanged)
			.def("parentSizeChanged", &Component::parentSizeChanged)
			.def("broughtToFront", &Component::broughtToFront)
			.def("addComponentListener", &Component::addComponentListener)
			.def("removeComponentListener", &Component::removeComponentListener)
			.def("postCommandMessage", &Component::postCommandMessage)
			.def("handleCommandMessage", &Component::handleCommandMessage)
			.def("enterModalState", &Component::enterModalState)
			.def("exitModalState", &Component::exitModalState)
			.def("isCurrentlyModal", &Component::isCurrentlyModal)
			.def("isCurrentlyBlockedByAnotherModalComponent", &Component::isCurrentlyBlockedByAnotherModalComponent)
			.def("canModalEventBeSentToComponent", &Component::canModalEventBeSentToComponent)
			.def("inputAttemptWhenModal", &Component::inputAttemptWhenModal)
			.def("getProperties", (NamedValueSet &(Component::*)() noexcept)&Component::getProperties)
			.def("getProperties", (const NamedValueSet &(Component::*)() const noexcept)&Component::getProperties)
			.def("findColour", &Component::findColour)
			.def("setColour", &Component::setColour)
			.def("removeColour", &Component::removeColour)
			.def("isColourSpecified", &Component::isColourSpecified)
			.def("copyAllExplicitColoursTo", &Component::copyAllExplicitColoursTo)
			.def("colourChanged", &Component::colourChanged)
			.def("getMarkers", &Component::getMarkers)
			.def("getWindowHandle", &Component::getWindowHandle)
			.def("getPositioner", &Component::getPositioner)
			.def("setPositioner", &Component::setPositioner)
			.def("setCachedComponentImage", &Component::setCachedComponentImage)
			.def("getCachedComponentImage", &Component::getCachedComponentImage)
			.scope
			[
				def("getCurrentlyFocusedComponent", &LComponent::getCurrentlyFocusedComponent),
				def("beginDragAutoRepeat", &LComponent::beginDragAutoRepeat),
				def("isMouseButtonDownAnywhere", &LComponent::isMouseButtonDownAnywhere),
				def("getNumCurrentlyModalComponents", &LComponent::getNumCurrentlyModalComponents),
				def("getCurrentlyModalComponent", &LComponent::getCurrentlyModalComponent)
			]
	];
}

void LComponentPeer::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<ComponentPeer>("ComponentPeer")
			.enum_("StyleFlags")
			[
				value("windowAppearsOnTaskbar", (1 << 0)),
				value("windowIsTemporary", (1 << 1)),
				value("windowIgnoresMouseClicks", (1 << 2)),
				value("windowHasTitleBar", (1 << 3)),
				value("windowIsResizable", (1 << 4)),
				value("windowHasMinimiseButton", (1 << 5)),
				value("windowHasMaximiseButton", (1 << 6)),
				value("windowHasCloseButton", (1 << 7)),
				value("windowHasDropShadow", (1 << 8)),
				value("windowRepaintedExplictly", (1 << 9)),
				value("windowIgnoresKeyPresses", (1 << 10)),
				value("windowIsSemiTransparent", (1 << 31))
			]
	];
}

void LDrawable::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Drawable>("Drawable")
			.def("createCopy", &Drawable::createCopy)
			.def("draw", &Drawable::draw)
			.def("drawAt", &Drawable::drawAt)
			.def("drawWithin", &Drawable::drawWithin)
			.def("setOriginWithOriginalSize", &Drawable::setOriginWithOriginalSize)
			.def("setTransformToFit", &Drawable::setTransformToFit)
			.def("getParent", &Drawable::getParent)
			.def("createFromImageFile", &Drawable::createFromValueTree)
			.def("getDrawableBounds", &Drawable::getDrawableBounds)
			.scope
			[
				def("createFromImageData", &Drawable::createFromImageData, adopt(result)),
				def("createFromImageDataStream", &Drawable::createFromImageDataStream, adopt(result)),
				def("createFromImageFile", &Drawable::createFromImageFile, adopt(result)),
				def("createFromSVG", &Drawable::createFromSVG, adopt(result)),
				def("createFromValueTree", &Drawable::createFromValueTree, adopt(result)),
				def("toDrawableComposite", &LDrawable::toDrawableComposite)
			]
		,
		class_<DrawableComposite, bases<Drawable> >("DrawableComposite")
			.def(constructor<>())
			.def(constructor<const DrawableComposite &>())
			.def("setBoundingBox", &DrawableComposite::setBoundingBox)
			.def("getBoundingBox", &DrawableComposite::getBoundingBox)
			.def("resetBoundingBoxToContentArea", &DrawableComposite::resetBoundingBoxToContentArea)
			.def("getContentArea", &DrawableComposite::getContentArea)
			.def("setContentArea", &DrawableComposite::setContentArea)
			.def("resetContentAreaAndBoundingBoxToFitChildren", &DrawableComposite::resetContentAreaAndBoundingBoxToFitChildren)
			.def("createCopy", &DrawableComposite::createCopy)
			.def("refreshFromValueTree", &DrawableComposite::refreshFromValueTree)
			.def("createValueTree", &DrawableComposite::createValueTree)
			.def("getDrawableBounds", &DrawableComposite::getDrawableBounds)
			.def("getMarkers", &DrawableComposite::getMarkers)
	];
}

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
			.def(constructor<const String &>())
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

void LFileListComponent::wrapForLua (lua_State *L)
{
	using namespace luabind;
}

void LFileTreeComponent::wrapForLua (lua_State *L)
{
	using namespace luabind;
}

void LFont::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<LFont>("LFont")
		,
		class_<Font,bases<LFont> >("Font")
			.def(constructor<float,int>())
			.def(constructor<const String &, float, int>())
			.def(constructor<const String &, const String &, float>())
			.def(constructor<const Typeface::Ptr &>())
			.def("setTypefaceName", &Font::setTypefaceName)
			.def("getTypefaceName", &Font::getTypefaceName)
			.def("getTypefaceStyle", &Font::getTypefaceStyle)
			.def("setTypefaceStyle", &Font::setTypefaceStyle)
			.def("withTypefaceStyle", &Font::withTypefaceStyle)
			.def("getAvailableStyles", &Font::getAvailableStyles)
			.def("withHeight", &Font::withHeight)
			.def("withPointHeight", &Font::withPointHeight)
			.def("setHeight", &Font::setHeight)
			.def("setHeightWithoutChangingWidth", &Font::setHeightWithoutChangingWidth)
			.def("getHeight", &Font::getHeight)
			.def("getHeightInPoints", &Font::getHeightInPoints)
			.def("getAscent", &Font::getAscent)
			.def("getAscentInPoints", &Font::getAscentInPoints)
			.def("getDescent", &Font::getDescent)
			.def("getDescentInPoints", &Font::getDescentInPoints)
			.def("getStyleFlags", &Font::getStyleFlags)
			.def("withStyle", &Font::withStyle)
			.def("setStyleFlags", &Font::setStyleFlags)
			.def("setBold", &Font::setBold)
			.def("boldened", &Font::boldened)
			.def("isBold", &Font::isBold)
			.def("setItalic", &Font::setItalic)
			.def("italicised", &Font::italicised)
			.def("setUnderline", &Font::setUnderline)
			.def("isUnderlined", &Font::isUnderlined)
			.def("getHorizontalScale", &Font::getHorizontalScale)
			.def("setHorizontalScale", &Font::setHorizontalScale)
			.def("getExtraKerningFactor", &Font::getExtraKerningFactor)
			.def("withExtraKerningFactor", &Font::withExtraKerningFactor)
			.def("setExtraKerningFactor", &Font::setExtraKerningFactor)
			.def("setSizeAndStyle", (void (Font::*)(float, int, float, float))&Font::setSizeAndStyle)
			.def("setSizeAndStyle", (void (Font::*)(float, const String &, float, float))&Font::setSizeAndStyle)
			.def("getStringWidth", &Font::getStringWidth)
			.def("getStringWidthFloat", &Font::getStringWidthFloat)
			.def("getGlyphPositions", &Font::getGlyphPositions)
			.def("getTypeface", &Font::getTypeface)
			.def("toString", &Font::toString)
			.scope
			[
				def("getDefaultSansSerifFontName", &Font::getDefaultSansSerifFontName),
				def("getDefaultSerifFontName", &Font::getDefaultSerifFontName),
				def("getDefaultMonospacedFontName ", &Font::getDefaultMonospacedFontName),
				def("getDefaultStyle", &Font::getDefaultStyle),
				def("getDefaultTypefaceForFont", &Font::getDefaultTypefaceForFont),
				def("findAllTypefaceNames", &Font::findAllTypefaceNames),
				def("findAllTypefaceStyles", &Font::findAllTypefaceStyles),
				def("getFallbackFontName", &Font::getFallbackFontName),
				def("setFallbackFontName", &Font::setFallbackFontName),
				def("getFallbackFontStyle", &Font::getFallbackFontStyle),
				def("setFallbackFontStyle", &Font::setFallbackFontStyle),
				def("fromString", &Font::fromString)
			]
			.enum_("FontStyleFlags")
			[
				value("plain", 0),
				value("bold", 1),
				value("italic", 2),
				value("underlined", 3)
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
        def("console", (void (*) (const std::string &)) &LGlobalFunctions::console),
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

void LGlyphArrangement::wrapForLua(lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<GlyphArrangement>("GlyphArrangement")
			.def(constructor<>())
			.def(constructor<const GlyphArrangement &>())
			.def("getNumGlyphs", &GlyphArrangement::getNumGlyphs)
			.def("getGlyph", &GlyphArrangement::getGlyph)
			.def("clear", &GlyphArrangement::clear)
			.def("addLineOfText", &GlyphArrangement::addLineOfText)
			.def("addCurtailedLineOfText", &GlyphArrangement::addCurtailedLineOfText)
			.def("addJustifiedText", &GlyphArrangement::addJustifiedText)
			.def("addFittedText", &GlyphArrangement::addFittedText)
			.def("addGlyphArrangement", &GlyphArrangement::addGlyphArrangement)
			.def("addGlyph", &GlyphArrangement::addGlyph)
			.def("draw", (void (GlyphArrangement::*) (const Graphics &) const) &GlyphArrangement::draw)
			.def("draw", (void (GlyphArrangement::*) (const Graphics &, const AffineTransform &) const) &GlyphArrangement::draw)
			.def("createPath", &GlyphArrangement::createPath)
			.def("findGlyphIndexAt", &GlyphArrangement::findGlyphIndexAt)
			.def("getBoundingBox", &GlyphArrangement::getBoundingBox)
			.def("moveRangeOfGlyphs", &GlyphArrangement::moveRangeOfGlyphs)
			.def("removeRangeOfGlyphs", &GlyphArrangement::removeRangeOfGlyphs)
			.def("stretchRangeOfGlyphs", &GlyphArrangement::stretchRangeOfGlyphs)
			.def("justifyGlyphs", &GlyphArrangement::justifyGlyphs)
	];
}

void LGraphics::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Graphics>("Graphics")
			.def(constructor<Image &>())
			.def("setColour", &Graphics::setColour)
			.def("setOpacity", &Graphics::setOpacity)

			.def("setGradientFill", &Graphics::setGradientFill)
			.def("setTiledImageFill", &Graphics::setTiledImageFill)
			.def("setFillType", &Graphics::setFillType)

			.def("setFont", (void (Graphics::*)(const Font &))&Graphics::setFont)
			.def("setFont", (void (Graphics::*)(float))&Graphics::setFont)
			.def("getCurrentFont", &Graphics::getCurrentFont)

			.def("drawSingleLineText", &Graphics::drawSingleLineText)
			.def("drawMultiLineText", &Graphics::drawMultiLineText)

			.def("drawText", (void (Graphics::*)(const String &, int, int, int, int, const Justification , bool) const)&Graphics::drawText)
			.def("drawText", (void (Graphics::*)(const String &, const Rectangle<int> &, const Justification , bool) const)&Graphics::drawText)

			.def("drawFittedText", (void (Graphics::*)(const String &, int, int, int, int, const Justification , int, float) const)&Graphics::drawFittedText)
			.def("drawFittedText", (void (Graphics::*)(const String &, const Rectangle<int> &, const Justification , int, float) const)&Graphics::drawFittedText)

			.def("fillAll", (void (Graphics::*)() const)&Graphics::fillAll)
			.def("fillAll", (void (Graphics::*)(const Colour) const)&Graphics::fillAll)

			.def("fillRect", (void (Graphics::*)(int,int,int,int) const)&Graphics::fillRect)
			.def("fillRect", (void (Graphics::*)(const Rectangle<int> &) const)&Graphics::fillRect)

			.def("fillRoundedRectangle", (void (Graphics::*)(float, float, float, float, float) const)&Graphics::fillRoundedRectangle)
			.def("fillRoundedRectangle", (void (Graphics::*)(const Rectangle<float> &, float) const)&Graphics::fillRoundedRectangle)

			.def("fillCheckerBoard", &Graphics::fillCheckerBoard)

			.def("drawRect", (void (Graphics::*)(int, int, int, int, int) const)&Graphics::drawRect)
			.def("drawRect", (void (Graphics::*)(const Rectangle<int> &, int) const)&Graphics::drawRect)

			.def("drawRoundedRectangle", (void (Graphics::*)(float, float, float, float, float, float) const)&Graphics::drawRoundedRectangle)
			.def("drawRoundedRectangle", (void (Graphics::*)(const Rectangle<float>&, float, float) const)&Graphics::drawRoundedRectangle)

			.def("setPixel", &Graphics::setPixel)

			.def("fillEllipse", (void (Graphics::*)(float, float, float, float) const)&Graphics::fillEllipse)
			.def("fillEllipse", (void (Graphics::*)(const Rectangle<float> &) const)&Graphics::fillEllipse)

			.def("drawEllipse", (void (Graphics::*)(float, float, float, float, float) const)&Graphics::drawEllipse)
			.def("drawEllipse", (void (Graphics::*)(const Rectangle<float> &, float) const)&Graphics::drawEllipse)

			.def("drawLine", (void (Graphics::*)(float, float, float, float) const)&Graphics::drawLine)
			.def("drawLine", (void (Graphics::*)(float, float, float, float, float) const)&Graphics::drawLine)
			.def("drawLine", (void (Graphics::*)(const Line<float> &) const)&Graphics::drawLine)
			.def("drawLine", (void (Graphics::*)(const Line<float> &, float) const)&Graphics::drawLine)
			.def("drawDashedLine", (void (Graphics::*)(const Line<float> &, const float *, int, float, int) const)&Graphics::drawDashedLine)
			.def("drawVerticalLine", (void (Graphics::*)(int, float, float) const)&Graphics::drawVerticalLine)
			.def("drawHorizontalLine", (void (Graphics::*)(int, float, float) const)&Graphics::drawHorizontalLine)

			.def("fillPath", &Graphics::fillPath)
			.def("strokePath", (void (Graphics::*)(const Path &, const PathStrokeType &, const AffineTransform &) const)&Graphics::strokePath)

			.def("drawArrow", &Graphics::drawArrow)

			.def("setImageResamplingQuality", &Graphics::setImageResamplingQuality)
			.def("drawImageAt", &Graphics::drawImageAt)
			.def("drawImage", &Graphics::drawImage)
			.def("drawImageTransformed", &Graphics::drawImageTransformed)
			.def("drawImageWithin", &Graphics::drawImageWithin)

			.def("getClipBounds", &Graphics::getClipBounds)
			.def("clipRegionIntersects", &Graphics::clipRegionIntersects)
			.def("reduceClipRegion", (bool (Graphics::*)(int,int,int,int))&Graphics::reduceClipRegion)
			.def("reduceClipRegion", (bool (Graphics::*)(const Rectangle<int> &))&Graphics::reduceClipRegion)
			.def("reduceClipRegion", (bool (Graphics::*)(const RectangleList<int> &))&Graphics::reduceClipRegion)
			.def("reduceClipRegion", (bool (Graphics::*)(const Path &path, const AffineTransform &))&Graphics::reduceClipRegion)
			.def("reduceClipRegion", (bool (Graphics::*)(const Image &, const AffineTransform &))&Graphics::reduceClipRegion)
			.def("excludeClipRegion", (bool (Graphics::*)(const Rectangle<int> &))&Graphics::excludeClipRegion)
			.def("isClipEmpty", &Graphics::isClipEmpty)
			.def("saveState", &Graphics::saveState)
			.def("restoreState", &Graphics::restoreState)
			.def("beginTransparencyLayer", &Graphics::beginTransparencyLayer)
			.def("endTransparencyLayer", &Graphics::endTransparencyLayer)
			.def("setOrigin", (void (Graphics::*)(int, int))&Graphics::setOrigin)
			.def("setOrigin", (void (Graphics::*)(Point<int>))&Graphics::setOrigin)
			.def("addTransform", &Graphics::addTransform)
			.def("resetToDefaultState", &Graphics::resetToDefaultState)
			.def("isVectorDevice", &Graphics::isVectorDevice)

			.enum_("ResamplingQuality")
			[
				value("lowResamplingQuality", 0),
				value("mediumResamplingQuality", 1),
				value("highResamplingQuality", 2)
			]
	];
}

void LImage::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
        class_<ImageType>("ImageType")
            .def("create", &ImageType::create)
            .def("getTypeID", &ImageType::getTypeID)
            .def("convert", &ImageType::convert)
        ,
		class_<Image>("Image")
            .enum_("PixelFormat")
			[
				value("UnknownFormat", Image::UnknownFormat),
				value("RGB", Image::RGB),
				value("ARGB", Image::ARGB),
				value("SingleChannel", Image::SingleChannel)
			]
            .def(constructor<Image::PixelFormat, int, int, bool>())
            .def(constructor<Image::PixelFormat, int, int, bool, const ImageType &>())
			.def(constructor<const Image &>())
			.def(constructor<>())
			.def("isValid", &Image::isValid)
			.def("isNull", &Image::isNull)
			.def("getWidth", &Image::getWidth)
			.def("getHeight", &Image::getHeight)
			.def("isRGB", &Image::isRGB)
			.def("isARGB", &Image::isARGB)
			.def("isSingleChannel", &Image::isSingleChannel)
			.def("hasAlphaChannel", &Image::hasAlphaChannel)
			.def("rescaled", &Image::rescaled)
			.def("duplicateIfShared", &Image::duplicateIfShared)
			.def("getPixelAt", &Image::getPixelAt)
			.def("setPixelAt", &Image::setPixelAt)
			.def("multiplyAlphaAt", &Image::multiplyAlphaAt)
			.def("multiplyAllAlphas", &Image::multiplyAllAlphas)
			.def("desaturate", &Image::desaturate)
			.def("moveImageSection", &Image::moveImageSection)
			.def("getReferenceCount", &Image::getReferenceCount)
			.scope
			[
                def("null", &LImage::null)
			]
		,
		class_<ImageFileFormat>("ImageFileFormat")
			.def("getFormatName", &ImageFileFormat::getFormatName)
			.def("canUnderstand", &ImageFileFormat::canUnderstand)
			.def("loadFrom", (Image (*)(const File &)) &ImageFileFormat::loadFrom)
	];
}

/*
double LInputStream::getTotalLength()
{
	return ( (double) InputStream::getTotalLength());
}

bool LInputStream::isExhausted()
{
}

double LInputStream::getPosition()
{
}

bool LInputStream::setPosition (double newPosition)
{
}

void LInputStream::skipNextBytes (double numBytesToSkip)
{
}

int LInputStream::readIntoMemoryBlock (LMemoryBlock &destBlock, double maxNumBytesToRead)
{
}
*/
void LInputStream::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<InputStream>("InputStream")
	];
}

void LJustification::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Justification>("Justification")
			.def(constructor<int>())
			.def("getFlags", &Justification::getFlags)
			.def("testFlags", &Justification::testFlags)
			.def("getOnlyVerticalFlags", &Justification::getOnlyVerticalFlags)
			.def("getOnlyHorizontalFlags", &Justification::getOnlyHorizontalFlags)
			.enum_("Flags")
			[
				value("left", 1),
				value("right", 2),
				value("horizontallyCentred", 4),
				value("top", 8),
				value("bottom", 16),
				value("verticallyCentred", 32),
				value("horizontallyJustified", 64),
				value("centred", 36),
				value("centredLeft", 33),
				value("centredRight", 34),
				value("centredTop", 12),
				value("centredBottom", 20),
				value("topLeft", 9),
				value("topRight", 10),
				value("bottomLeft", 17),
				value("bottomRight", 18)
			]
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

void LLabel::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Label, bases<Component> >("Label")
			.def("setText", (void (Label::*)(const String &, NotificationType))&Label::setText)
			.def("getText", &Label::getText)
			.def("getTextValue", &Label::getTextValue)
			.def("setFont", &Label::setFont)
			.def("getFont", &Label::getFont)
			.def("setJustificationType", &Label::setJustificationType)
			.def("getJustificationType", &Label::getJustificationType)
			.def("setBorderSize", &Label::setBorderSize)
			.def("attachToComponent", &Label::attachToComponent)
			.def("getAttachedComponent", &Label::getAttachedComponent)
			.def("isAttachedOnLeft", &Label::isAttachedOnLeft)
			.def("setMinimumHorizontalScale", &Label::setMinimumHorizontalScale)
			.def("getMinimumHorizontalScale", &Label::getMinimumHorizontalScale)
			.def("addListener", &Label::addListener)
			.def("removeListener", &Label::removeListener)
			.def("setEditable", &Label::setEditable)
			.def("isEditableOnSingleClick", &Label::isEditableOnSingleClick)
			.def("isEditableOnDoubleClick", &Label::isEditableOnDoubleClick)
			.def("doesLossOfFocusDiscardChanges", &Label::doesLossOfFocusDiscardChanges)
			.def("isEditable", &Label::isEditable)
			.def("showEditor", &Label::showEditor)
			.def("hideEditor", &Label::hideEditor)
			.def("isBeingEdited", &Label::isBeingEdited)
			.enum_("ColourIds")
			[
				value("backgroundColourId ", 0x1000280),
				value("textColourId", 0x1000281),
				value("outlineColourId", 0x1000282)
			]
	];
}

void LLine::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Line<float> >("Line")
			.def(constructor<>())
			.def(constructor<float,float,float,float>())
			.def(constructor<const Point<float> &, const Point<float>& >())
			.def(constructor<const Line<float> &>())
			.def("getStartX", &Line<float>::getStartX)
			.def("getStartY", &Line<float>::getStartY)
			.def("getEndX", &Line<float>::getEndX)
			.def("getEndY", &Line<float>::getEndY)
			.def("getStart", &Line<float>::getStart)
			.def("getEnd", &Line<float>::getEnd)
			.def("setStart", (void (Line<float>::*)(float,float) noexcept)&Line<float>::setStart)
			.def("setEnd", (void (Line<float>::*)(float,float) noexcept)&Line<float>::setEnd)
			.def("setStart", (void (Line<float>::*)(const Point<float> ) noexcept)&Line<float>::setStart)
			.def("setEnd", (void (Line<float>::*)(const Point<float> ) noexcept)&Line<float>::setEnd)
			.def("reversed", &Line<float>::reversed)
			.def("applyTransform", &Line<float>::applyTransform)
			.def("getLength", &Line<float>::getLength)
			.def("isVertical", &Line<float>::isVertical)
			.def("isHorizontal", &Line<float>::isHorizontal)
			.def("getAngle", &Line<float>::getAngle)
			//.def("intersects", &Line<float>::intersects)
			.def("getIntersection", &Line<float>::getIntersection )
			.def("getPointAlongLine", (Point<float> (Line<float>::*)(float) const noexcept)&Line<float>::getPointAlongLine)
			.def("getPointAlongLine", (Point<float> (Line<float>::*)(float,float) const noexcept)&Line<float>::getPointAlongLine)
			.def("getPointAlongLineProportionally", &Line<float>::getPointAlongLineProportionally)
			.def("getDistanceFromPoint", &Line<float>::getDistanceFromPoint)
			.def("findNearestProportionalPositionTo", &Line<float>::findNearestProportionalPositionTo)
			.def("findNearestPointTo", &Line<float>::findNearestPointTo)
			.def("isPointAbove", &Line<float>::isPointAbove)
			.def("withShortenedStart", &Line<float>::withShortenedStart)
			.def("withShortenedEnd", &Line<float>::withShortenedEnd)
	];
}

#define TRY_CALL(method,...)\
if (methods.contains(#method))\
{\
    try \
    {\
        luabind::call_function<void>(methods[#method], __VA_ARGS__);\
    }\
    catch (luabind::error &e)\
    {\
        _WRN(luabind::object_cast <std::string> (luabind::object(luabind::from_stack(e.state(), -1))));\
    }\
}\
else\
{\
   LookAndFeel_V3::method(__VA_ARGS__);\
}

#define TRY_CALL_RET(method,ReturnType,ReturnWhenError,...)\
if (methods.contains(#method))\
{\
    try \
    {\
        return (luabind::call_function<ReturnType>(methods[#method], ##__VA_ARGS__));\
    }\
    catch (luabind::error &e)\
    {\
        _WRN(luabind::object_cast <std::string> (luabind::object(luabind::from_stack(e.state(), -1))));\
		return (ReturnWhenError);\
    }\
}\
else\
{\
   return (LookAndFeel_V3::method(__VA_ARGS__));\
}

#define TRY_CALL_RET_NOP(method,ReturnType,ReturnWhenError,...)\
if (methods.contains(#method))\
{\
    try \
    {\
        return (luabind::call_function<ReturnType>(methods[#method]));\
    }\
    catch (luabind::error &e)\
    {\
        _WRN(luabind::object_cast <std::string> (luabind::object(luabind::from_stack(e.state(), -1))));\
		return (ReturnWhenError);\
    }\
}\
else\
{\
   return (LookAndFeel_V3::method());\
}

LookAndFeelBase::LookAndFeelBase()
{
}

void LookAndFeelBase::setMethod (const String &methodName, const luabind::object &method)
{
    if (luabind::type(method) != LUA_TNIL)
    {
        methods.set (methodName, method);
    }
    else
    {
        methods.remove(methodName);
    }
}

void LookAndFeelBase::setImplementation (const luabind::object &implementationAsTable)
{
    if (luabind::type(implementationAsTable) == LUA_TTABLE)
    {
        for (luabind::iterator i(implementationAsTable), end; i!=end; ++i)
        {
            String key          = luabind::object_cast<std::string>(i.key());
            luabind::object val = *i;

            if (luabind::type(val) == LUA_TFUNCTION)
            {
                setMethod (key, val);
            }
        }
    }
}

void LookAndFeelBase::wrapForLua (lua_State *L)
{
    using namespace luabind;

	module(L)
    [
		class_<LookAndFeelBase>("LookAndFeel")
            .def(constructor<>())
            .def("setMethod", &LookAndFeelBase::setMethod)
            .def("setImplementation", &LookAndFeelBase::setImplementation)
            .scope
            [
                def("createLabel", &LookAndFeelBase::createLabel),
                def("createTextButton", &LookAndFeelBase::createTextButton),
                def("createImageButton", &LookAndFeelBase::createImageButton),
                def("createToggleButton", &LookAndFeelBase::createToggleButton),
                def("createDropShadowEffect", &LookAndFeelBase::createDropShadowEffect),
                def("createGlowEffect", &LookAndFeelBase::createGlowEffect),
                def("createDrawableComposite", &LookAndFeelBase::createDrawableComposite),
                def("createDrawableImage", &LookAndFeelBase::createDrawableImage),
                def("createDrawablePath", &LookAndFeelBase::createDrawablePath),
                def("createDrawableRectangle", &LookAndFeelBase::createDrawableRectangle),
                def("createDrawableText", &LookAndFeelBase::createDrawableText)
            ]
    ];
}

Colour LookAndFeelBase::findColour(int colourId)
{
	TRY_CALL_RET (findColour, Colour, Colour(), colourId);
}

void LookAndFeelBase::setColour(int colourId, Colour colour)
{
    TRY_CALL(setColour, colourId, colour);
}

bool LookAndFeelBase::isColourSpecified(int colourId)
{
	TRY_CALL_RET (isColourSpecified, bool, false, colourId);
}

Typeface::Ptr LookAndFeelBase::getTypefaceForFont(const Font &font)
{
	TRY_CALL_RET (getTypefaceForFont, Typeface::Ptr, Typeface::Ptr(), font);
}

MouseCursor LookAndFeelBase::getMouseCursorFor(Component &component)
{
	TRY_CALL_RET (getMouseCursorFor, MouseCursor, MouseCursor(), boost::ref(component));
}

void LookAndFeelBase::drawButtonBackground(Graphics &g, Button &button, const Colour &backgroundColourRef, bool isMouseOverButton, bool isButtonDown)
{
    TRY_CALL(drawButtonBackground, boost::ref(g), boost::ref(button), backgroundColourRef, isMouseOverButton, isButtonDown);
}

void LookAndFeelBase::drawButtonText(Graphics &g, TextButton &textButton, bool isMouseOverButton, bool isButtonDown)
{
    TRY_CALL(drawButtonText, boost::ref(g), boost::ref(textButton), isMouseOverButton, isButtonDown);
}

void LookAndFeelBase::drawToggleButton(Graphics &g, ToggleButton &toggleButton, bool isMouseOverButton, bool isButtonDown)
{
    TRY_CALL(drawToggleButton, boost::ref(g), boost::ref(toggleButton), isMouseOverButton, isButtonDown);
}

void LookAndFeelBase::changeToggleButtonWidthToFitText(ToggleButton &toggleButton)
{
    TRY_CALL(changeToggleButtonWidthToFitText, boost::ref(toggleButton));
}

void LookAndFeelBase::drawTickBox(Graphics &g, Component &component, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown)
{
    TRY_CALL(drawTickBox, boost::ref(g), boost::ref(component), x, y, w, h, ticked, isEnabled, isMouseOverButton, isButtonDown);
}

AlertWindow* LookAndFeelBase::createAlertWindow(const String &title, const String &message, const String &button1, const String &button2, const String &button3, AlertWindow::AlertIconType iconType, int numButtons, Component* component)
{
	using namespace luabind;

    if (methods.contains("createAlertWindow"))
    {
        try
        {
            AlertWindow *wnd = call_function<AlertWindow*>(
                methods["createAlertWindow"], title, message, button1, button2, button3, iconType, numButtons, component
            );

            if (wnd != nullptr)
            {
                return (wnd);
            }

            return (LookAndFeel_V3::createAlertWindow(title, message, button1, button2, button3, iconType, numButtons, component));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createAlertWindow(title, message, button1, button2, button3, iconType, numButtons, component));
        }
    }
    else
    {
        return (LookAndFeel_V3::createAlertWindow(title, message, button1, button2, button3, iconType, numButtons, component));
    }
}

void LookAndFeelBase::drawAlertBox(Graphics &g, AlertWindow &window, const Rectangle<int> &textArea, TextLayout &layout)
{
    TRY_CALL(drawAlertBox,boost::ref(g), boost::ref(window), textArea, boost::ref(layout));
}

int LookAndFeelBase::getAlertBoxWindowFlags()
{
	TRY_CALL_RET_NOP(getAlertBoxWindowFlags, int, 0);
}

int LookAndFeelBase::getAlertWindowButtonHeight()
{
	TRY_CALL_RET_NOP(getAlertWindowButtonHeight, int, 0);
}

Font LookAndFeelBase::getAlertWindowMessageFont()
{
	TRY_CALL_RET_NOP(getAlertWindowMessageFont, Font, Font());
}

Font LookAndFeelBase::getAlertWindowFont()
{
	TRY_CALL_RET_NOP(getAlertWindowFont, Font, Font());
}

void LookAndFeelBase::drawProgressBar(Graphics &g, ProgressBar &progressBar, int width, int height, double progress, const String &textToShow)
{
    TRY_CALL(drawProgressBar, boost::ref(g), boost::ref(progressBar), width, height, progress, textToShow);
}

void LookAndFeelBase::drawSpinningWaitAnimation(Graphics &g, const Colour &colourRef, int x, int y, int w, int h)
{
    TRY_CALL(drawSpinningWaitAnimation, boost::ref(g), colourRef, x, y, w, h);
}

bool LookAndFeelBase::areScrollbarButtonsVisible()
{
	TRY_CALL_RET_NOP(areScrollbarButtonsVisible, bool, true);
}

ImageEffectFilter* LookAndFeelBase::getScrollbarEffect()
{
	using namespace luabind;

    if (methods.contains("getSliderEffect"))
    {
        try
        {
            ImageEffectFilter *eff = call_function<ImageEffectFilter*>(
                methods["getScrollbarEffect"]
            );

            if (eff != nullptr)
            {
                return (eff);
            }

            return (LookAndFeel_V3::getScrollbarEffect());
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::getScrollbarEffect());
        }
    }
    else
    {
        return (LookAndFeel_V3::getScrollbarEffect());
    }
}

int LookAndFeelBase::getMinimumScrollbarThumbSize(ScrollBar &scrollBar)
{
	TRY_CALL_RET(getMinimumScrollbarThumbSize, int, 0, boost::ref(scrollBar));
}

int LookAndFeelBase::getDefaultScrollbarWidth()
{
	TRY_CALL_RET_NOP(getDefaultScrollbarWidth, int, 0);
}

int LookAndFeelBase::getScrollbarButtonSize(ScrollBar &scrollBar)
{
	TRY_CALL_RET(getScrollbarButtonSize, int, 0, boost::ref(scrollBar));
}

Path LookAndFeelBase::getTickShape(float height)
{
	TRY_CALL_RET(getTickShape, Path, Path(), height);
}

Path LookAndFeelBase::getCrossShape(float height)
{
	TRY_CALL_RET(getCrossShape, Path, Path(), height);
}

void LookAndFeelBase::drawTreeviewPlusMinusBox(Graphics &g, const Rectangle<float> &area, Colour backgroundColour, bool isOpen, bool isMouseOver)
{
    TRY_CALL(drawTreeviewPlusMinusBox, boost::ref(g), area, backgroundColour, isOpen, isMouseOver);
}

void LookAndFeelBase::fillTextEditorBackground(Graphics &g, int width, int height, TextEditor &editor)
{
    TRY_CALL(fillTextEditorBackground, boost::ref(g), width, height, boost::ref(editor));
}

void LookAndFeelBase::drawTextEditorOutline(Graphics &g, int width, int height, TextEditor &editor)
{
    TRY_CALL(drawTextEditorOutline, boost::ref(g), width, height, boost::ref(editor));
}

CaretComponent* LookAndFeelBase::createCaretComponent(Component* component)
{
	TRY_CALL_RET(createCaretComponent, CaretComponent*, nullptr, component);
}

const Drawable* LookAndFeelBase::getDefaultFolderImage()
{
    using namespace luabind;

    if (methods.contains("getDefaultFolderImage"))
    {
        try
        {
            Drawable *drw = call_function<Drawable*>(
                methods["getDefaultFolderImage"]
            );

            if (drw != nullptr)
            {
                return (drw);
            }

            return (LookAndFeel_V3::getDefaultFolderImage());
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::getDefaultFolderImage());
        }
    }
    else
    {
        return (LookAndFeel_V3::getDefaultFolderImage());
    }
}

const Drawable* LookAndFeelBase::getDefaultDocumentFileImage()
{
	using namespace luabind;

    if (methods.contains("getDefaultDocumentFileImage"))
    {
        try
        {
            Drawable *drw = call_function<Drawable*>(
                methods["getDefaultDocumentFileImage"]
            );

            if (drw != nullptr)
            {
                return (drw);
            }

            return (LookAndFeel_V3::getDefaultDocumentFileImage());
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::getDefaultDocumentFileImage());
        }
    }
    else
    {
        return (LookAndFeel_V3::getDefaultDocumentFileImage());
    }
}

AttributedString LookAndFeelBase::createFileChooserHeaderText(const String &title, const String &instructions)
{
	TRY_CALL_RET(createFileChooserHeaderText, AttributedString, AttributedString(title+instructions), title, instructions);
}

void LookAndFeelBase::drawFileBrowserRow(Graphics &g, int width, int height, const String &filename, Image* icon, const String &fileSizeDescription, const String &fileTimeDescription, bool isDirectory, bool isItemSelected, int itemIndex, DirectoryContentsDisplayComponent &directoryContentsDisplayComponent)
{
    TRY_CALL(drawFileBrowserRow, boost::ref(g), width, height, filename, icon, fileSizeDescription, fileTimeDescription, isDirectory, isItemSelected, itemIndex, boost::ref(directoryContentsDisplayComponent));
}

Button* LookAndFeelBase::createFileBrowserGoUpButton()
{
	using namespace luabind;

    if (methods.contains("createFileBrowserGoUpButton"))
    {
        try
        {
            Button *b = call_function<Button*>(
                methods["createFileBrowserGoUpButton"]
            );

            if (b != nullptr)
            {
                return (b);
            }

            return (LookAndFeel_V3::createFileBrowserGoUpButton());
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createFileBrowserGoUpButton());
        }
    }
    else
    {
        return (LookAndFeel_V3::createFileBrowserGoUpButton());
    }
}

void LookAndFeelBase::layoutFileBrowserComponent(FileBrowserComponent &fileBrowserComponent, DirectoryContentsDisplayComponent *directoryContentsDisplayComponent, FilePreviewComponent *filePreviewComponent, ComboBox *comboBox, TextEditor *textEditor, Button *goUpButton)
{
    TRY_CALL(layoutFileBrowserComponent, boost::ref(fileBrowserComponent), directoryContentsDisplayComponent, filePreviewComponent, comboBox, textEditor, goUpButton);
}

void LookAndFeelBase::drawBubble(Graphics &g, BubbleComponent &bubbleComponent, const Point<float> &tip, const Rectangle<float> &body)
{
    TRY_CALL(drawBubble, boost::ref(g), boost::ref(bubbleComponent), tip, body);
}

void LookAndFeelBase::drawLasso(Graphics &g, Component &component)
{
    TRY_CALL(drawLasso, boost::ref(g), boost::ref(component));
}

void LookAndFeelBase::drawPopupMenuBackground(Graphics &g, int width, int height)
{
    TRY_CALL(drawPopupMenuBackground, boost::ref(g), width, height);
}

void LookAndFeelBase::drawPopupMenuItem(Graphics &g, const Rectangle<int> &area, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const String &text, const String &shortcutKeyText, const Drawable* icon, const Colour *textColour)
{
	TRY_CALL(drawPopupMenuItem, boost::ref(g),boost::ref(area),isSeparator,isActive,isHighlighted,isTicked,hasSubMenu,text,shortcutKeyText,icon,textColour);
}

Font LookAndFeelBase::getPopupMenuFont()
{
	TRY_CALL_RET_NOP(getPopupMenuFont, Font, Font());
}

void LookAndFeelBase::drawPopupMenuUpDownArrow(Graphics &g, int width, int height, bool isScrollUpArrow)
{
    TRY_CALL(drawPopupMenuUpDownArrow, boost::ref(g), width, height, isScrollUpArrow);
}

void LookAndFeelBase::getIdealPopupMenuItemSize(const String &text, bool isSeparator, int standardMenuItemHeight, int &idealWidth, int &idealHeight)
{
    TRY_CALL(getIdealPopupMenuItemSize, text, isSeparator, standardMenuItemHeight, boost::ref(idealWidth), boost::ref(idealHeight));
}

int LookAndFeelBase::getMenuWindowFlags()
{
	TRY_CALL_RET_NOP(getMenuWindowFlags, int, 0);
}

void LookAndFeelBase::drawMenuBarBackground(Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &menuBarComponent)
{
    TRY_CALL(drawMenuBarBackground, boost::ref(g), width, height, isMouseOverBar, boost::ref(menuBarComponent));
}

int LookAndFeelBase::getMenuBarItemWidth(MenuBarComponent &menuBarComponent, int itemIndex, const String &itemText)
{
	TRY_CALL_RET(getMenuBarItemWidth, int, 0, boost::ref(menuBarComponent), itemIndex, itemText);
}

Font LookAndFeelBase::getMenuBarFont(MenuBarComponent &menuBarComponent, int itemIndex, const String &itemText)
{
	TRY_CALL_RET(getMenuBarFont, Font, Font(), boost::ref(menuBarComponent), itemIndex, itemText);
}

void LookAndFeelBase::drawMenuBarItem(Graphics &g, int width, int height, int itemIndex, const String &itemText, bool isMouseOverItem, bool isMenuOpen, bool isMouseOverBar, MenuBarComponent &menuBarComponent)
{
    TRY_CALL(drawMenuBarItem, boost::ref(g), width, height, itemIndex, itemText, isMouseOverItem, isMenuOpen, isMouseOverBar, boost::ref(menuBarComponent));
}

void LookAndFeelBase::drawComboBox(Graphics &g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, ComboBox &comboBox)
{
    TRY_CALL(drawComboBox, boost::ref(g), width, height, isButtonDown, buttonX, buttonY, buttonW, buttonH, boost::ref(comboBox));
}

Font LookAndFeelBase::getComboBoxFont(ComboBox &comboBox)
{
	TRY_CALL_RET(getComboBoxFont, Font, Font(), boost::ref(comboBox));
}

Label* LookAndFeelBase::createComboBoxTextBox(ComboBox &comboBox)
{
    using namespace luabind;

    if (methods.contains("createComboBoxTextBox"))
    {
        try
        {
            Label *l = call_function<Label*>(
                methods["createComboBoxTextBox"],
                boost::ref(comboBox)
            );

            if (l != nullptr)
            {
                return (l);
            }

            return (LookAndFeel_V3::createComboBoxTextBox(comboBox));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createComboBoxTextBox(comboBox));
        }
    }
    else
    {
        return (LookAndFeel_V3::createComboBoxTextBox(comboBox));
    }
}

void LookAndFeelBase::positionComboBoxText(ComboBox &comboBox, Label &label)
{
    TRY_CALL(positionComboBoxText, boost::ref(comboBox), boost::ref(label));
}

void LookAndFeelBase::drawLabel(Graphics &g, Label &label)
{
	TRY_CALL(drawLabel, boost::ref(g),boost::ref(label));
}

void LookAndFeelBase::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle sliderStyle, Slider &slider)
{
    TRY_CALL(drawLinearSlider, boost::ref(g), x, y, width, height, sliderPos, minSliderPos, maxSliderPos, sliderStyle, boost::ref(slider));
}

void LookAndFeelBase::drawLinearSliderBackground(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle sliderStyle, Slider &slider)
{
    TRY_CALL(drawLinearSliderBackground, boost::ref(g), x, y, width, height, sliderPos, minSliderPos, maxSliderPos, sliderStyle, boost::ref(slider));
}

void LookAndFeelBase::drawLinearSliderThumb(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle sliderStyle, Slider &slider)
{
    TRY_CALL(drawLinearSliderThumb, boost::ref(g), x, y, width, height, sliderPos, minSliderPos, maxSliderPos, sliderStyle, boost::ref(slider));
}

int LookAndFeelBase::getSliderThumbRadius(Slider &slider)
{
	TRY_CALL_RET(getSliderThumbRadius, int, 0, boost::ref(slider));
}

void LookAndFeelBase::drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider)
{
	TRY_CALL(drawRotarySlider,boost::ref(g),x,y,width,height,sliderPosProportional,rotaryStartAngle,rotaryEndAngle,boost::ref(slider));
}

Button* LookAndFeelBase::createSliderButton(Slider &slider, bool isIncrement)
{
	using namespace luabind;

    if (methods.contains("createSliderButton"))
    {
        try
        {
            Button *b = call_function<Button*>(
                methods["createSliderButton"],
                boost::ref(slider), isIncrement
            );

            if (b != nullptr)
            {
                return (b);
            }

            return (LookAndFeel_V3::createSliderButton(slider, isIncrement));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createSliderButton(slider, isIncrement));
        }
    }
    else
    {
        return (LookAndFeel_V3::createSliderButton(slider, isIncrement));
    }
}

Label* LookAndFeelBase::createSliderTextBox(Slider &slider)
{
	using namespace luabind;

    if (methods.contains("createSliderTextBox"))
    {
        try
        {
            Label *l = call_function<Label*>(
                methods["createSliderTextBox"],
                boost::ref(slider)
            );

            if (l != nullptr)
            {
                return (l);
            }

            return (LookAndFeel_V3::createSliderTextBox(slider));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createSliderTextBox(slider));
        }
    }
    else
    {
        return (LookAndFeel_V3::createSliderTextBox(slider));
    }
}

ImageEffectFilter* LookAndFeelBase::getSliderEffect(Slider &slider)
{
    using namespace luabind;

    if (methods.contains("getSliderEffect"))
    {
        try
        {
            ImageEffectFilter *b = call_function<ImageEffectFilter*>(
                methods["getSliderEffect"],
                boost::ref(slider)
            );

            if (b != nullptr)
            {
                return (b);
            }

            return (LookAndFeel_V3::getSliderEffect(slider));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::getSliderEffect(slider));
        }
    }
    else
    {
        return (LookAndFeel_V3::getSliderEffect(slider));
    }
}

Rectangle<int> LookAndFeelBase::getTooltipBounds(const String &tipText, Point<int> screenPos, Rectangle<int> parentArea)
{
    TRY_CALL_RET(getTooltipBounds, Rectangle<int>, Rectangle<int>(), tipText, screenPos, parentArea);
}

void LookAndFeelBase::drawTooltip(Graphics &g, const String &text, int width, int height)
{
    TRY_CALL(drawTooltip, boost::ref(g), text, width, height);
}

Button* LookAndFeelBase::createFilenameComponentBrowseButton(const String &text)
{
	using namespace luabind;

    if (methods.contains("createFilenameComponentBrowseButton"))
    {
        try
        {
            Button *b = call_function<Button*>(
                methods["createFilenameComponentBrowseButton"],
                text
            );

            if (b != nullptr)
            {
                return (b);
            }

            return (LookAndFeel_V3::createFilenameComponentBrowseButton(text));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createFilenameComponentBrowseButton(text));
        }
    }
    else
    {
        return (LookAndFeel_V3::createFilenameComponentBrowseButton(text));
    }
}

void LookAndFeelBase::layoutFilenameComponent(FilenameComponent &filenameComponent, ComboBox* comboBox, Button* button)
{
    TRY_CALL(layoutFilenameComponent, boost::ref(filenameComponent), comboBox, button);
}

void LookAndFeelBase::drawConcertinaPanelHeader(Graphics &g, const Rectangle<int> &areaInt, bool isMouseOver, bool isMouseDown, ConcertinaPanel &concertinaPanel, Component &component)
{
    TRY_CALL(drawConcertinaPanelHeader, boost::ref(g), areaInt, isMouseOver, isMouseDown, boost::ref(concertinaPanel), boost::ref(component));
}

void LookAndFeelBase::drawCornerResizer(Graphics &g, int w, int h, bool isMouseOver, bool isMouseDragging)
{
    TRY_CALL(drawCornerResizer, boost::ref(g), w, h, isMouseOver, isMouseDragging);
}

void LookAndFeelBase::drawResizableFrame(Graphics &g, int w, int h, const BorderSize<int> &borderSize)
{
    TRY_CALL(drawResizableFrame, boost::ref(g), w, h, borderSize);
}

void LookAndFeelBase::fillResizableWindowBackground(Graphics &g, int w, int h, const BorderSize<int> &borderSize, ResizableWindow &resizableWindow)
{
    TRY_CALL(fillResizableWindowBackground, boost::ref(g), w, h, borderSize, boost::ref(resizableWindow));
}

void LookAndFeelBase::drawResizableWindowBorder(Graphics &g, int w, int h, const BorderSize<int> &borderSize, ResizableWindow &resizableWindow)
{
    TRY_CALL(drawResizableWindowBorder, boost::ref(g), w, h, borderSize, boost::ref(resizableWindow));
}

void LookAndFeelBase::drawDocumentWindowTitleBar(DocumentWindow &documentWindow, Graphics &g, int w, int h, int titleSpaceX, int titleSpaceW, const Image* icon, bool drawTitleTextOnLeft)
{
    TRY_CALL(drawDocumentWindowTitleBar, boost::ref(documentWindow), boost::ref(g), w, h, titleSpaceX, titleSpaceW, icon, drawTitleTextOnLeft);
}

Button* LookAndFeelBase::createDocumentWindowButton(int buttonType)
{
	using namespace luabind;

    if (methods.contains("createDocumentWindowButton"))
    {
        try
        {
            Button *b = call_function<Button*>(
                methods["createDocumentWindowButton"],
                buttonType
            );

            if (b != nullptr)
            {
                return (b);
            }

            return (LookAndFeel_V3::createDocumentWindowButton(buttonType));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createDocumentWindowButton(buttonType));
        }
    }
    else
    {
        return (LookAndFeel_V3::createDocumentWindowButton(buttonType));
    }
}

void LookAndFeelBase::positionDocumentWindowButtons(DocumentWindow &documentWindow, int titleBarX, int titleBarY, int titleBarW, int titleBarH, Button* minimiseButton, Button* maximiseButton, Button* closeButton, bool positionTitleBarButtonsOnLeft)
{
    TRY_CALL(positionDocumentWindowButtons, boost::ref(documentWindow), titleBarX, titleBarY, titleBarW, titleBarH, minimiseButton, maximiseButton, closeButton, positionTitleBarButtonsOnLeft);
}

int LookAndFeelBase::getDefaultMenuBarHeight()
{
	TRY_CALL_RET_NOP(getDefaultMenuBarHeight, int, 0);
}

DropShadower* LookAndFeelBase::createDropShadowerForComponent(Component* component)
{
	using namespace luabind;

    if (methods.contains("createDropShadowerForComponent"))
    {
        try
        {
            DropShadower *s = call_function<DropShadower*>(
                methods["createDropShadowerForComponent"],
                component
            );

            if (s != nullptr)
            {
                return (s);
            }

            return (LookAndFeel_V3::createDropShadowerForComponent(component));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createDropShadowerForComponent(component));
        }
    }
    else
    {
        return (LookAndFeel_V3::createDropShadowerForComponent(component));
    }
}

void LookAndFeelBase::drawGroupComponentOutline(Graphics &g, int w, int h, const String &text, const Justification &justification, GroupComponent &groupComponent)
{
    TRY_CALL(drawGroupComponentOutline, boost::ref(g), w, h, text, justification, boost::ref(groupComponent));
}

int LookAndFeelBase::getTabButtonSpaceAroundImage()
{
	TRY_CALL_RET_NOP(getTabButtonSpaceAroundImage, int, 0);
}

int LookAndFeelBase::getTabButtonOverlap(int tabDepth)
{
	TRY_CALL_RET(getTabButtonOverlap, int, 0, tabDepth);
}

int LookAndFeelBase::getTabButtonBestWidth(TabBarButton &tabBarButton, int tabDepth)
{
	TRY_CALL_RET(getTabButtonBestWidth, int, 0, boost::ref(tabBarButton), tabDepth);
}

Rectangle<int> LookAndFeelBase::getTabButtonExtraComponentBounds(const TabBarButton &tabBarButton, Rectangle<int> &areaInt, Component &component)
{
	TRY_CALL_RET(getTabButtonExtraComponentBounds, Rectangle<int>, Rectangle<int>(), boost::ref(tabBarButton), areaInt, boost::ref(component));
}

void LookAndFeelBase::drawTabButton(TabBarButton &tabBarButton, Graphics &g, bool isMouseOver, bool isMouseDown)
{
    TRY_CALL(drawTabButton, boost::ref(tabBarButton), boost::ref(g), isMouseOver, isMouseDown);
}

void LookAndFeelBase::drawTabButtonText(TabBarButton &tabBarButton, Graphics &g, bool isMouseOver, bool isMouseDown)
{
    TRY_CALL(drawTabButtonText, boost::ref(tabBarButton), boost::ref(g), isMouseOver, isMouseDown);
}

void LookAndFeelBase::drawTabAreaBehindFrontButton(TabbedButtonBar &tabbedButtonBar, Graphics &g, int w, int h)
{
    TRY_CALL(drawTabAreaBehindFrontButton, boost::ref(tabbedButtonBar), boost::ref(g), w, h);
}

void LookAndFeelBase::createTabButtonShape(TabBarButton &tabBarButton, Path &path, bool isMouseOver, bool isMouseDown)
{
    TRY_CALL(createTabButtonShape, boost::ref(tabBarButton), boost::ref(path), isMouseOver, isMouseDown);
}

void LookAndFeelBase::fillTabButtonShape(TabBarButton &tabBarButton, Graphics &g, const Path &path, bool isMouseOver, bool isMouseDown)
{
    TRY_CALL(drawTabButton, boost::ref(tabBarButton), boost::ref(g), isMouseOver, isMouseDown);
}

Button* LookAndFeelBase::createTabBarExtrasButton()
{
	using namespace luabind;

    if (methods.contains("createTabBarExtrasButton"))
    {
        try
        {
            Button *b = call_function<Button*>(
                methods["createTabBarExtrasButton"]
            );

            if (b != nullptr)
            {
                return (b);
            }

            return (LookAndFeel_V3::createTabBarExtrasButton());
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createTabBarExtrasButton());
        }
    }
    else
    {
        return (LookAndFeel_V3::createTabBarExtrasButton());
    }
}

void LookAndFeelBase::drawImageButton(Graphics &g, Image* image, int imageX, int imageY, int imageW, int imageH, const Colour &overlayColourRef, float imageOpacity, ImageButton &imageButton)
{
    TRY_CALL(drawImageButton, boost::ref(g), image, imageX, imageY, imageW, imageH, overlayColourRef, imageOpacity, boost::ref(imageButton));
}

void LookAndFeelBase::drawTableHeaderBackground(Graphics &g, TableHeaderComponent &tableHeaderComponent)
{
    TRY_CALL(drawTableHeaderBackground, boost::ref(g), boost::ref(tableHeaderComponent));
}

void LookAndFeelBase::drawTableHeaderColumn(Graphics &g, const String &columnName, int columnId, int width, int height, bool isMouseOver, bool isMouseDown, int columnFlags)
{
    TRY_CALL(drawTableHeaderColumn, boost::ref(g), columnName, columnId, width, height, isMouseOver, isMouseDown, columnFlags);
}

void LookAndFeelBase::paintToolbarBackground(Graphics &g, int width, int height, Toolbar &toolbar)
{
    TRY_CALL(paintToolbarBackground, boost::ref(g), width, height, boost::ref(toolbar));
}

Button* LookAndFeelBase::createToolbarMissingItemsButton(Toolbar &toolbar)
{
	using namespace luabind;

    if (methods.contains("createToolbarMissingItemsButton"))
    {
        try
        {
            Button *b = call_function<Button*>(
                methods["createToolbarMissingItemsButton"],
                boost::ref(toolbar)
            );

            if (b != nullptr)
            {
                return (b);
            }

            return (LookAndFeel_V3::createToolbarMissingItemsButton(toolbar));
        }
        catch (luabind::error &e)
        {
            _WRN(object_cast <std::string> (object(luabind::from_stack(e.state(), -1))));
            return (LookAndFeel_V3::createToolbarMissingItemsButton(toolbar));
        }
    }
    else
    {
        return (LookAndFeel_V3::createToolbarMissingItemsButton(toolbar));
    }
}

void LookAndFeelBase::paintToolbarButtonBackground(Graphics &g, int width, int height, bool isMouseOver, bool isMouseDown, ToolbarItemComponent &toolbarItemComponent)
{
    TRY_CALL(paintToolbarButtonBackground, boost::ref(g), width, height, isMouseOver, isMouseDown, boost::ref(toolbarItemComponent));
}

void LookAndFeelBase::paintToolbarButtonLabel(Graphics &g, int x, int y, int width, int height, const String &text, ToolbarItemComponent &toolbarItemComponent)
{
    TRY_CALL(paintToolbarButtonLabel, boost::ref(g), x, y, width, height, text, boost::ref(toolbarItemComponent));
}

void LookAndFeelBase::drawStretchableLayoutResizerBar(Graphics &g, int w, int h, bool isVerticalBar, bool isMouseOver, bool isMouseDragging)
{
    TRY_CALL(drawStretchableLayoutResizerBar, boost::ref(g), w, h, isVerticalBar, isMouseOver, isMouseDragging);
}

void LookAndFeelBase::drawPropertyPanelSectionHeader(Graphics &g, const String &name, bool isOpen, int width, int height)
{
    TRY_CALL(drawPropertyPanelSectionHeader, boost::ref(g), name, isOpen, width, height);
}

void LookAndFeelBase::drawPropertyComponentBackground(Graphics &g, int width, int height, PropertyComponent &propertyComponent)
{
    TRY_CALL(drawPropertyComponentBackground, boost::ref(g), width, height, boost::ref(propertyComponent));
}

void LookAndFeelBase::drawPropertyComponentLabel(Graphics &g, int width, int height, PropertyComponent &propertyComponent)
{
    TRY_CALL(drawPropertyComponentLabel, boost::ref(g), width, height, boost::ref(propertyComponent));
}

Rectangle<int> LookAndFeelBase::getPropertyComponentContentPosition(PropertyComponent &propertyComponent)
{
	TRY_CALL_RET(getPropertyComponentContentPosition, Rectangle<int>, Rectangle<int>(), boost::ref(propertyComponent));
}

void LookAndFeelBase::drawCallOutBoxBackground(CallOutBox &callOutBox, Graphics &g, const Path &path, Image &image)
{
    TRY_CALL(drawCallOutBoxBackground, boost::ref(callOutBox), boost::ref(g), path, boost::ref(image));
}

void LookAndFeelBase::drawLevelMeter(Graphics &g, int width, int height, float level)
{
    TRY_CALL(drawLevelMeter, boost::ref(g), width, height, level);
}

void LookAndFeelBase::drawKeymapChangeButton(Graphics &g, int width, int height, Button &button, const String &keyDescription)
{
    TRY_CALL(drawKeymapChangeButton, boost::ref(g), width, height, boost::ref(button), keyDescription);
}

LMemoryBlock::LMemoryBlock(const String &hexData)
{
	MemoryBlock::loadFromHexString (hexData);
}

LMemoryBlock::LMemoryBlock(luabind::object const& table)
	: MemoryBlock(luaArrayTomemoryBlock(table))
{
}

LMemoryBlock LMemoryBlock::fromLuaTable (luabind::object const& table)
{
	return (luaArrayTomemoryBlock(table));
}

LMemoryBlock::LMemoryBlock (const void *dataToInitialiseFrom, size_t sizeInBytes)
	: MemoryBlock (dataToInitialiseFrom, sizeInBytes)
{
}

char LMemoryBlock::operator [] (const int offset) const noexcept
{
	return (*((uint8 *)getData()+offset));
}

void LMemoryBlock::insertIntoTable(luabind::object const& table)
{
	if (luabind::type(table) == LUA_TTABLE)
	{
		uint8 *ptr = (uint8 *)MemoryBlock::getData();

		for (unsigned int i=0; i<MemoryBlock::getSize(); i++)
		{
			table[i+1] = (uint8)*(ptr+i);
		}
	}
}

void LMemoryBlock::createFromTable(luabind::object const &table)
{
	for(luabind::iterator i(table), end; i != end; i++)
	{
		const uint8 v = luabind::object_cast<uint8>(*i);
		MemoryBlock::append (&v, 1);
	}
}

void LMemoryBlock::toLuaTable(luabind::object tableToWriteTo)
{
	for (int i=0; i<getSize(); i++)
	{
		tableToWriteTo[i+1] = getByte(i);
	}
}

uint8 LMemoryBlock::getByte(const int position) const
{
	uint8 *ptr = (uint8 *)getData();

	if (getSize() >= position)
		return (*(ptr + position));

	return (0);
}

LMemoryBlock LMemoryBlock::getRange(const int startingPosition, const int numBytes) const
{
	MemoryBlock bl;

	if (getSize() >= (startingPosition + numBytes))
	{
		bl.append ((uint8 *)getData() + startingPosition, numBytes);
	}
	return (bl);
}

String LMemoryBlock::toHexString(const int groupSize)
{
	return (String::toHexString(getData(), getSize(), groupSize));
}

void LMemoryBlock::insert (MemoryBlock &dataToInsert, int insertPosition)
{
	MemoryBlock::insert (dataToInsert.getData(), dataToInsert.getSize(), insertPosition);
}

void LMemoryBlock::insert (MemoryBlock &dataToInsert, int dataSize, int insertPosition)
{
	MemoryBlock::insert (dataToInsert.getData(), dataSize, insertPosition);
}

void LMemoryBlock::append (MemoryBlock &dataToAppend)
{
	MemoryBlock::append (dataToAppend.getData(), dataToAppend.getSize());
}

void LMemoryBlock::copyFrom(MemoryBlock &dataToCopy, int destinationOffset, int numBytes)
{
	MemoryBlock::copyFrom(dataToCopy.getData(), destinationOffset, numBytes);
}

void LMemoryBlock::copyTo(MemoryBlock &dataToCopy, int sourceOffset, int numBytes)
{
	MemoryBlock::copyTo(dataToCopy.getData(), sourceOffset, numBytes);
}

void LMemoryBlock::replaceWith(MemoryBlock &dataToReplace)
{
	MemoryBlock::replaceWith (dataToReplace.getData(), dataToReplace.getSize());
}

void LMemoryBlock::setByte (const int bytePosition, const uint8 byteValue)
{
	if (getSize() >= bytePosition)
	{
		*((uint8 *)getData() + bytePosition) = byteValue;
	}
}

double LMemoryBlock::getSize() const noexcept
{
	return ((double)MemoryBlock::getSize());
}

void LMemoryBlock::removeSection(const int startByte, const int dataSize)
{
    MemoryBlock::removeSection (startByte, dataSize);
}

int LMemoryBlock::getBitRange (int bitRangeStart, int numBits)
{
    return (MemoryBlock::getBitRange(bitRangeStart, numBits));
}

void LMemoryBlock::setBitRange(int bitRangeStart, int numBits, int binaryNumberToApply)
{
    return (MemoryBlock::setBitRange(bitRangeStart, numBits, binaryNumberToApply));
}

void LMemoryBlock::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<MemoryBlock>("JMemoryBlock")
		,
		class_<LMemoryBlock,bases<MemoryBlock> >("MemoryBlock")
				.def(constructor<>())
				.def(constructor<const size_t,bool>())
				.def(constructor<const MemoryBlock &>())
				.def(constructor<luabind::object const&>())
				.def(constructor<const String &>())
				.def("insertIntoTable", &LMemoryBlock::insertIntoTable)
				.def("createFromTable", &LMemoryBlock::createFromTable)
				.def("getByte", &LMemoryBlock::getByte)
				.def("setByte", &LMemoryBlock::setByte)
				.def("getRange", &LMemoryBlock::getRange)
				.def("toHexString", &LMemoryBlock::toHexString)
				.def("getData", &MemoryBlock::getData)
				.def("getSize", &LMemoryBlock::getSize)
				.def("setSize", &MemoryBlock::setSize)
				.def("ensureSize", &MemoryBlock::ensureSize)
				.def("fillWith", &MemoryBlock::fillWith)
				.def("append", &LMemoryBlock::append)
				.def("replaceWith", &LMemoryBlock::replaceWith)
				.def("insert", (void (LMemoryBlock::*) (MemoryBlock &, int)) &LMemoryBlock::insert)
				.def("insert", (void (LMemoryBlock::*) (MemoryBlock &, int, int)) &LMemoryBlock::insert)
				.def("removeSection", &LMemoryBlock::removeSection)
				.def("copyFrom", &LMemoryBlock::copyFrom)
				.def("copyTo", &LMemoryBlock::copyTo)
				.def("swapWith", &MemoryBlock::swapWith)
				.def("toString", &MemoryBlock::toString)
				.def("loadFromHexString", &MemoryBlock::loadFromHexString)
				.def("setBitRange", &LMemoryBlock::setBitRange)
				.def("getBitRange", &LMemoryBlock::getBitRange)
				.def("toBase64Encoding", &MemoryBlock::toBase64Encoding)
				.def("fromBase64Encoding", &MemoryBlock::fromBase64Encoding)
				.def("toLuaTable", &LMemoryBlock::toLuaTable)
				.scope
				[
					def("fromLuaTable", &LMemoryBlock::fromLuaTable)
				]
	];
}

void LMemoryInputStream::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<MemoryInputStream>("MemoryInputStream")
	];
}

void LMidiBuffer::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<MidiBuffer>("MidiBuffer")
            .def(constructor<>())
            .def(constructor<const MidiMessage &>())
            .def(constructor<const MidiBuffer &>())
            .def("clear", (void (MidiBuffer::*)(void))&MidiBuffer::clear)
            .def("clear", (void (MidiBuffer::*)(int, int)) &MidiBuffer::clear)
            .def("isEmpty", &MidiBuffer::isEmpty)
            .def("getNumEvents", &MidiBuffer::getNumEvents)
            .def("addEvent", (void (MidiBuffer::*)(const MidiMessage &, int)) &MidiBuffer::addEvent)
            .def("addEvents", (void (MidiBuffer::*)(const MidiBuffer &, int, int, int)) &MidiBuffer::addEvents)
            .def("getFirstEventTime", &MidiBuffer::getFirstEventTime)
            .def("getLastEventTime", &MidiBuffer::getLastEventTime)
            .def("swapWith", &MidiBuffer::swapWith)
            .def("ensureSize", &MidiBuffer::ensureSize)
        ,
        class_<MidiBuffer::Iterator>("MidiBufferIterator")
            .def(constructor<const MidiBuffer &>())
            .def("setNextSamplePosition", &MidiBuffer::Iterator::setNextSamplePosition)
            .def("getNextEvent", (bool (MidiBuffer::Iterator::*)(MidiMessage &, int &)) &MidiBuffer::Iterator::getNextEvent)
    ];
}

void LMidiKeyboardComponent::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<MidiKeyboardComponent>("MidiKeyboardComponent")
	];
}

void LMidiMessage::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<MidiMessage>("MidiMessage")
				.def(constructor<>())
				.def(constructor<const MidiMessage &>())
				.def(constructor<const MidiMessage &,double>())
				.def(constructor<int,int,int,double>())
				.def(constructor<int,int,double>())
				.def(constructor<int,double>())
				.def(constructor<const void *,int, double>())
				.def(constructor<const void *,int, int, uint8, double>())
				.def("getRawData", &MidiMessage::getRawData)
				.def("getRawDataSize", &MidiMessage::getRawDataSize)
				.def("getTimeStamp", &MidiMessage::getTimeStamp)
				.def("setTimeStamp", &MidiMessage::setTimeStamp)
				.def("addToTimeStamp", &MidiMessage::addToTimeStamp)
				.def("getChannel", &MidiMessage::getChannel)
				.def("isForChannel", &MidiMessage::isForChannel)
				.def("setChannel", &MidiMessage::setChannel)
				.def("isSysEx", &MidiMessage::isSysEx)
				.def("getSysExData", &MidiMessage::getSysExData)
				.def("getSysExDataSize", &MidiMessage::getSysExDataSize)
				.def("isNoteOn", &MidiMessage::isNoteOn)
				.def("isNoteOff", &MidiMessage::isNoteOff)
				.def("isNoteOnOrOff", &MidiMessage::isNoteOnOrOff)
				.def("getNoteNumber", &MidiMessage::getNoteNumber)
				.def("setNoteNumber", &MidiMessage::setNoteNumber)
				.def("getVelocity", &MidiMessage::getVelocity)
				.def("getFloatVelocity", &MidiMessage::getFloatVelocity)
				.def("setVelocity", &MidiMessage::setVelocity)
				.def("multiplyVelocity", &MidiMessage::multiplyVelocity)
				.def("isSustainPedalOn", &MidiMessage::isSustainPedalOn)
				.def("isSustainPedalOff", &MidiMessage::isSustainPedalOff)
				.def("isSostenutoPedalOn", &MidiMessage::isSostenutoPedalOn)
				.def("isSostenutoPedalOff", &MidiMessage::isSostenutoPedalOff)
				.def("isSoftPedalOn", &MidiMessage::isSoftPedalOn)
				.def("isSoftPedalOff", &MidiMessage::isSoftPedalOff)
				.def("isProgramChange", &MidiMessage::isProgramChange)
				.def("getProgramChangeNumber", &MidiMessage::getProgramChangeNumber)
				.def("isPitchWheel", &MidiMessage::isPitchWheel)
				.def("getPitchWheelValue", &MidiMessage::getPitchWheelValue)
				.def("isAftertouch", &MidiMessage::isAftertouch)
				.def("getAfterTouchValue", &MidiMessage::getAfterTouchValue)
				.def("isChannelPressure", &MidiMessage::isChannelPressure)
				.def("getChannelPressureValue", &MidiMessage::getChannelPressureValue)
				.def("isController", &MidiMessage::isController)
				.def("getControllerNumber", &MidiMessage::getControllerNumber)
				.def("getControllerValue", &MidiMessage::getControllerValue)
				.def("isControllerOfType", &MidiMessage::isControllerOfType)
				.def("isAllNotesOff", &MidiMessage::isAllNotesOff)
				.def("isAllSoundOff", &MidiMessage::isAllSoundOff)
				.def("isMetaEvent", &MidiMessage::isMetaEvent)
				.def("getMetaEventType", &MidiMessage::getMetaEventType)
				.def("getMetaEventData", &MidiMessage::getMetaEventData)
				.def("getMetaEventLength", &MidiMessage::getMetaEventLength)
				.def("isTrackMetaEvent", &MidiMessage::isTrackMetaEvent)
				.def("isEndOfTrackMetaEvent", &MidiMessage::isEndOfTrackMetaEvent)
				.def("isTrackNameEvent", &MidiMessage::isTrackNameEvent)
				.def("isTextMetaEvent", &MidiMessage::isTextMetaEvent)
				.def("getTextFromTextMetaEvent", &MidiMessage::getTextFromTextMetaEvent)
				.def("isTempoMetaEvent", &MidiMessage::isTempoMetaEvent)
				.def("getTempoMetaEventTickLength", &MidiMessage::getTempoMetaEventTickLength)
				.def("getTempoSecondsPerQuarterNote", &MidiMessage::getTempoSecondsPerQuarterNote)
				.def("isTimeSignatureMetaEvent", &MidiMessage::isTimeSignatureMetaEvent)
				.def("getTimeSignatureInfo", &MidiMessage::getTimeSignatureInfo)
				.def("isKeySignatureMetaEvent", &MidiMessage::isKeySignatureMetaEvent)
				.def("getKeySignatureNumberOfSharpsOrFlats", &MidiMessage::getKeySignatureNumberOfSharpsOrFlats)
				.def("isMidiChannelMetaEvent", &MidiMessage::isMidiChannelMetaEvent)
				.def("getMidiChannelMetaEventChannel", &MidiMessage::getMidiChannelMetaEventChannel)
				.def("isActiveSense", &MidiMessage::isActiveSense)
				.def("isMidiStart", &MidiMessage::isMidiStart)
				.def("isMidiContinue", &MidiMessage::isMidiContinue)
				.def("isMidiStop", &MidiMessage::isMidiStop)
				.def("isMidiClock", &MidiMessage::isMidiClock)
				.def("isSongPositionPointer", &MidiMessage::isSongPositionPointer)
				.def("getSongPositionPointerMidiBeat", &MidiMessage::getSongPositionPointerMidiBeat)
				.def("isQuarterFrame", &MidiMessage::isQuarterFrame)
				.def("getQuarterFrameSequenceNumber", &MidiMessage::getQuarterFrameSequenceNumber)
				.def("getQuarterFrameValue", &MidiMessage::getQuarterFrameValue)
				.def("isFullFrame", &MidiMessage::isFullFrame)
				.def("isMidiMachineControlMessage", &MidiMessage::isMidiMachineControlMessage)
				.def("getMidiMachineControlCommand", &MidiMessage::getMidiMachineControlCommand)
				.def("isMidiMachineControlGoto", &MidiMessage::isMidiMachineControlGoto)
				.enum_("SmtpeTimecodeType")
				[
					value("fps24", 0),
					value("fps25", 1),
					value("fps30drop", 2),
					value("fps30", 3)
				]
				// CAUSES COMPILATION ERROR .def("getFullFrameParameters", (void (MidiMessage::*)(int &, int &, int &, int &, MidiMessage::SmpteTimecodeType &) const noexcept)&MidiMessage::getFullFrameParameters)
				.enum_("MidiMachineControlCommand")
				[
					value("mmc_stop", 1),
					value("mmc_play", 2),
					value("mmc_deferredplay", 3),
					value("mmc_fastforward", 4),
					value("mmc_rewind", 5),
					value("mmc_recordStart", 6),
					value("mmc_recordStop", 7),
					value("mmc_pause", 9)
				]
				.scope
				[
					def("noteOn", (MidiMessage (*)(int, int, float) noexcept)&MidiMessage::noteOn),
					def("noteOn", (MidiMessage (*)(int, int, uint8) noexcept)&MidiMessage::noteOn),
					def("noteOff", &MidiMessage::noteOff),
					def("programChange", &MidiMessage::programChange),
					def("pitchWheel", &MidiMessage::pitchWheel),
					def("aftertouchChange", &MidiMessage::aftertouchChange),
					def("channelPressureChange", &MidiMessage::channelPressureChange),
					def("controllerEvent", &MidiMessage::controllerEvent),
					def("allNotesOff", &MidiMessage::allNotesOff),
					def("allSoundOff", &MidiMessage::allSoundOff),
					def("allControllersOff", &MidiMessage::allControllersOff),
					def("endOfTrack", &MidiMessage::endOfTrack),
					def("tempoMetaEvent", &MidiMessage::tempoMetaEvent),
					def("timeSignatureMetaEvent", &MidiMessage::timeSignatureMetaEvent),
					def("midiChannelMetaEvent", &MidiMessage::midiChannelMetaEvent),
					def("midiStart", &MidiMessage::midiStart),
					def("midiContinue", &MidiMessage::midiContinue),
					def("midiStop", &MidiMessage::midiStop),
					def("midiClock", &MidiMessage::midiClock),
					def("songPositionPointer", &MidiMessage::songPositionPointer),
					def("quarterFrame", &MidiMessage::quarterFrame),
					def("fullFrame", (MidiMessage (*)(int,int,int,int,MidiMessage::SmpteTimecodeType))&MidiMessage::fullFrame),
					def("midiMachineControlCommand", &MidiMessage::midiMachineControlCommand),
					def("midiMachineControlGoto", &MidiMessage::midiMachineControlGoto),
					def("masterVolume", &MidiMessage::masterVolume),
					def("createSysExMessage", &MidiMessage::createSysExMessage),
					def("readVariableLengthVal", &MidiMessage::readVariableLengthVal),
					def("getMessageLengthFromFirstByte", &MidiMessage::getMessageLengthFromFirstByte),
					def("getMidiNoteName", &MidiMessage::getMidiNoteName),
					def("getMidiNoteInHertz", &MidiMessage::getMidiNoteInHertz),
					def("getGMInstrumentName", &MidiMessage::getGMInstrumentName),
					def("getGMInstrumentBankName", &MidiMessage::getGMInstrumentBankName),
					def("getRhythmInstrumentName", &MidiMessage::getRhythmInstrumentName),
					def("getControllerName", &MidiMessage::getControllerName)
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

void LPath::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Path>("Path")
			.def(constructor<>())
			.def(constructor<const Path &>())
			.def("isEmpty", &Path::isEmpty)
			.def("getBounds", &Path::getBounds)
			.def("getBoundsTransformed", &Path::getBoundsTransformed)
			.def("contains", (bool (Path::*)(float, float, float) const) &Path::contains)
			.def("contains", (bool (Path::*)(const Point<float>, float) const) &Path::contains)
			.def("intersectsLine", &Path::intersectsLine)
			.def("getClippedLine", &Path::getClippedLine)
			.def("getLength", &Path::getLength)
			.def("getPointAlongPath", &Path::getPointAlongPath)
			.def("getNearestPoint", &Path::getNearestPoint)
			.def("clear", &Path::clear)
			.def("startNewSubPath", (void (Path::*)(float, float)) &Path::startNewSubPath)
			.def("startNewSubPath", (void (Path::*)(const Point<float>)) &Path::startNewSubPath)
			.def("closeSubPath", &Path::closeSubPath)
			.def("lineTo", (void (Path::*)(float, float)) &Path::lineTo)
			.def("lineTo", (void (Path::*)(const Point<float>)) &Path::lineTo)
			.def("quadraticTo", (void (Path::*)(float, float, float, float)) &Path::quadraticTo)
			.def("quadraticTo", (void (Path::*)(const Point<float>, const Point<float>)) &Path::quadraticTo)
			.def("cubicTo", (void (Path::*)(float, float, float, float, float, float)) &Path::cubicTo)
			.def("cubicTo", (void (Path::*)(const Point<float>, const Point<float>, const Point<float>)) &Path::cubicTo)
			.def("getCurrentPosition", &Path::getCurrentPosition)
			.def("addRectangle", (void (Path::*)(float, float, float, float)) &Path::addRectangle)
			.def("addRoundedRectangle", (void (Path::*)(float, float, float, float, float)) &Path::addRoundedRectangle)
			.def("addRoundedRectangle", (void (Path::*)(float, float, float, float, float, float)) &Path::addRoundedRectangle)
			.def("addRoundedRectangle", (void (Path::*)(float, float, float, float, float, float, bool, bool, bool, bool)) &Path::addRoundedRectangle)
			.def("addTriangle", (void (Path::*)(float, float, float, float, float, float)) &Path::addTriangle)
			.def("addQuadrilateral", &Path::addQuadrilateral)
			.def("addEllipse", (void(Path::*)(float, float, float, float))&Path::addEllipse)
			.def("addEllipse", (void(Path::*)(Rectangle<float>))&Path::addEllipse)
			.def("addArc", &Path::addArc)
			.def("addCentredArc", &Path::addCentredArc)
			.def("addPieSegment", (void(Path::*)(float, float, float, float, float, float, float)) &Path::addPieSegment)
			.def("addPieSegment", (void(Path::*)(Rectangle<float>, float, float, float)) &Path::addPieSegment)
			.def("addLineSegment", &Path::addLineSegment)
			.def("addArrow", &Path::addArrow)
			.def("addPolygon", &Path::addPolygon)
			.def("addStar", &Path::addStar)
			.def("addBubble", &Path::addBubble)
			.def("addPath", &Path::addQuadrilateral)
			.def("addPath", &Path::addQuadrilateral)
			.def("swapWithPath", &Path::swapWithPath)
			.def("applyTransform", &Path::applyTransform)
			.def("scaleToFit", &Path::scaleToFit)
			.def("getTransformToScaleToFit", (AffineTransform (Path::*)(float, float, float, float, bool, Justification) const)&Path::getTransformToScaleToFit)
			.def("getTransformToScaleToFit", (AffineTransform (Path::*)(const Rectangle<float> &, bool, Justification) const)&Path::getTransformToScaleToFit)
			.def("createPathWithRoundedCorners", &Path::createPathWithRoundedCorners)
			.def("setUsingNonZeroWinding", &Path::setUsingNonZeroWinding)
			.def("isUsingNonZeroWinding", &Path::isUsingNonZeroWinding)
			.def("loadPathFromStream", &Path::loadPathFromStream)
			.def("loadPathFromData", &Path::loadPathFromData)
			.def("writePathToStream", &Path::writePathToStream)
			.def("toString", &Path::toString)
			.def("restoreFromString", &Path::restoreFromString)
		,
        class_<LPathStrokeType>("PathStrokeType")
		,
		class_<PathStrokeType, bases<LPathStrokeType> >("PathStrokeType")
			.def(constructor<float>())
			.def(constructor<float, PathStrokeType::JointStyle, PathStrokeType::EndCapStyle>())
			.def(constructor<const PathStrokeType &>())
			.def("createStrokedPath", &PathStrokeType::createStrokedPath)
			.def("createDashedStroke", &LPathStrokeType::createDashedStrokeWrap)
			.def("createStrokeWithArrowheads", &PathStrokeType::createStrokeWithArrowheads)
			.def("getStrokeThickness", &PathStrokeType::getStrokeThickness)
			.def("setStrokeThickness", &PathStrokeType::setStrokeThickness)
			.def("getJointStyle", &PathStrokeType::getJointStyle)
			.def("setJointStyle", &PathStrokeType::setJointStyle)
			.def("getEndStyle", &PathStrokeType::getEndStyle)
			.def("setEndStyle", &PathStrokeType::setEndStyle)
			.enum_("JoinStyle")
			[
				value("mitered", PathStrokeType::mitered),
				value("curved", PathStrokeType::curved),
				value("beveled", PathStrokeType::beveled)
			]
			.enum_("EndCapStyle")
			[
				value("butt", PathStrokeType::butt),
				value("square", PathStrokeType::square),
				value("rounded", PathStrokeType::rounded)
			]
	];
}

void LPathStrokeType::createDashedStrokeWrap (Path &destPath, const Path &sourcePath, const luabind::object dashLengths, const AffineTransform &transform, float extraAccuracy)
{
    Array<float> dashLengthsFloat = luaArrayToFloat (dashLengths);
    PathStrokeType::createDashedStroke (destPath, sourcePath, dashLengthsFloat.getRawDataPointer(), dashLengthsFloat.size(), transform, extraAccuracy);
}

void LPoint::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Point<float> >("Point")
			.def(constructor<>())
			.def(constructor<const Point<float> &>())
			.def(constructor<float,float>())
			.def("isOrigin", &Point<float>::isOrigin)
			.def("getX", &Point<float>::getX)
			.def("getY", &Point<float>::getY)
			.def("setX", &Point<float>::setX)
			.def("setY", &Point<float>::setY)
			.def("withX", &Point<float>::withX)
			.def("withY", &Point<float>::withY)
			.def("setXY", &Point<float>::setXY)
			.def("addXY", &Point<float>::addXY)
			.def("translated", &Point<float>::translated)
			.def("getDistanceFromOrigin", &Point<float>::getDistanceFromOrigin)
			.def("getDistanceFrom", &Point<float>::getDistanceFrom)
			.def("getAngleToPoint", &Point<float>::getAngleToPoint)
			.def("getPointOnCircumference", (Point<float> (Point<float>::*)(const float, const float) const noexcept)&Point<float>::getPointOnCircumference)
			.def("getPointOnCircumference", (Point<float> (Point<float>::*)(const float, const float, const float) const noexcept)&Point<float>::getPointOnCircumference)
			.def("applyTransform", &Point<float>::applyTransform)
			.def("transformedBy", &Point<float>::transformedBy)
			.def("toString", &Point<float>::toString)
			.def_readwrite("x",&Point<float>::x)
			.def_readwrite("y",&Point<float>::y)
	];
}

LPopupMenu::LPopupMenu()
{
}

int LPopupMenu::show(int itemIDThatMustBeVisible,
              int minimumWidth,
              int maximumNumColumns,
              int standardItemHeight)
{
	return (PopupMenu::show(itemIDThatMustBeVisible,minimumWidth,maximumNumColumns,standardItemHeight));
}

int LPopupMenu::show(int itemHeight)
{
    return (PopupMenu::show(-1,-1,-1,itemHeight));
}

void LPopupMenu::addSubMenu (const String& subMenuName,
                     const LPopupMenu& subMenu,
                     bool isEnabled,
                     const Image& iconToUse,
                     bool isTicked,
                     int itemResultID)
{
	PopupMenu::addSubMenu (subMenuName, subMenu, isEnabled, iconToUse, isTicked, itemResultID);
}

int LPopupMenu::showAt(Component *componentToAttachTo, int standardItemHeight)
{
    return (PopupMenu::showAt (componentToAttachTo, -1, -1, -1, standardItemHeight, nullptr));
}

int LPopupMenu::showAt(Rectangle<int> &areaToAttachTo, int standardItemHeight)
{
    return (PopupMenu::showAt (areaToAttachTo, -1, -1, -1, standardItemHeight, nullptr));
}

void LPopupMenu::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<PopupMenu>("JPopupMenu")
		,
		class_<LPopupMenu, bases<PopupMenu> >("PopupMenu")
				.def(constructor<>())
				.def("clear", &PopupMenu::clear)
				.def("addItem", (void(PopupMenu::*)(int , const String& , bool , bool , const Image&))&PopupMenu::addItem)
				.def("addItem", (void(PopupMenu::*)(int , const String& , bool , bool , Drawable*))&PopupMenu::addItem)
				.def("addItem", (void(PopupMenu::*)(int , const String& , bool , bool))&PopupMenu::addItem)
				.def("addColouredItem", &PopupMenu::addColouredItem)
				.def("addSubMenu", &LPopupMenu::addSubMenu)
				.def("addSeparator", &PopupMenu::addSeparator)
				.def("addSectionHeader", &PopupMenu::addSectionHeader)
				.def("getNumItems", &PopupMenu::getNumItems)
				.def("show", (int(PopupMenu::*)(int, int, int, int))&LPopupMenu::show)
				.def("show", (int(LPopupMenu::*)(int))&LPopupMenu::show)
				.def("showAt", (int(LPopupMenu::*)(Component*, int)) &LPopupMenu::showAt)
				.def("showAt", (int(LPopupMenu::*)(Rectangle<int> &, int)) &LPopupMenu::showAt)
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

void LRectangle::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Rectangle<int> >("Rectangle")
			.def(constructor<>())
			.def(constructor<const Rectangle<int> &>())
			.def(constructor<int,int,int,int>())
			.def(constructor<int,int>())
			.def(constructor<const Point<int> &, const Point <int> &>())
			.def("isEmpty", &Rectangle<int>::isEmpty)
			.def("getX", &Rectangle<int>::getX)
			.def("getY", &Rectangle<int>::getY)
			.def("getWidth", &Rectangle<int>::getWidth)
			.def("getHeight", &Rectangle<int>::getHeight)
			.def("getRight", &Rectangle<int>::getRight)
			.def("getBottom", &Rectangle<int>::getBottom)
			.def("getCentreX", &Rectangle<int>::getCentreX)
			.def("getCentreY", &Rectangle<int>::getCentreY)
			.def("getCentre", &Rectangle<int>::getCentre)
			.def("getAspectRatio", &Rectangle<int>::getAspectRatio)
			.def("getPosition", &Rectangle<int>::getPosition)
			.def("setPosition", (void (Rectangle<int>::*)(const Point<int> ) noexcept)&Rectangle<int>::setPosition)
			.def("setPosition", (void (Rectangle<int>::*)(const int, const int) noexcept)&Rectangle<int>::setPosition)
			.def("getTopLeft", &Rectangle<int>::getTopLeft)
			.def("getTopRight", &Rectangle<int>::getTopRight)
			.def("getBottomLeft", &Rectangle<int>::getBottomLeft)
			.def("getBottomRight", &Rectangle<int>::getBottomRight)
			.def("setSize", &Rectangle<int>::setSize)
			.def("setBounds", &Rectangle<int>::setBounds)
			.def("setX", &Rectangle<int>::setX)
			.def("setY", &Rectangle<int>::setY)
			.def("setWidth", &Rectangle<int>::setWidth)
			.def("setHeight", &Rectangle<int>::setHeight)
			.def("withX", &Rectangle<int>::withX)
			.def("withY", &Rectangle<int>::withY)
			.def("withPosition", (Rectangle<int> (Rectangle<int>::*)(const Point<int> ) const noexcept)&Rectangle<int>::withPosition)
			.def("withPosition", (Rectangle<int> (Rectangle<int>::*)(const int, const int) const noexcept)&Rectangle<int>::withPosition)
			.def("withZeroOrigin", &Rectangle<int>::withZeroOrigin)
			.def("withWidth", &Rectangle<int>::withWidth)
			.def("withHeight", &Rectangle<int>::withHeight)
			.def("withSize", &Rectangle<int>::withSize)
			.def("setLeft", &Rectangle<int>::setLeft)
			.def("withLeft", &Rectangle<int>::withLeft)
			.def("setTop", &Rectangle<int>::setTop)
			.def("withTop", &Rectangle<int>::withTop)
			.def("setRight", &Rectangle<int>::setRight)
			.def("withRight", &Rectangle<int>::withRight)
			.def("setBottom", &Rectangle<int>::setBottom)
			.def("withBottom", &Rectangle<int>::withBottom)
			.def("translate", &Rectangle<int>::translate)
			.def("translated", &Rectangle<int>::translated)
			.def("expand", &Rectangle<int>::expand)
			.def("expanded", (Rectangle<int> (Rectangle<int>::*)(const int, const int) const noexcept)&Rectangle<int>::expanded)
			.def("expanded", (Rectangle<int> (Rectangle<int>::*)(const int) const noexcept)&Rectangle<int>::expanded)
			.def("reduce", &Rectangle<int>::reduce)
			.def("reduced", (Rectangle<int> (Rectangle<int>::*)(const int, const int) const noexcept)&Rectangle<int>::reduced)
			.def("reduced", (Rectangle<int> (Rectangle<int>::*)(const int) const noexcept)&Rectangle<int>::reduced)
			.def("removeFromTop", &Rectangle<int>::removeFromTop)
			.def("removeFromLeft", &Rectangle<int>::removeFromLeft)
			.def("removeFromRight", &Rectangle<int>::removeFromRight)
			.def("removeFromBottom", &Rectangle<int>::removeFromBottom)
			.def("contains", (bool (Rectangle<int>::*)(const int, const int) const noexcept)&Rectangle<int>::contains)
			.def("contains", (bool (Rectangle<int>::*)(const Point<int> ) const noexcept)&Rectangle<int>::contains)
			.def("contains", (bool (Rectangle<int>::*)(const Rectangle<int> &) const noexcept)&Rectangle<int>::contains)
			.def("getConstrainedPoint", &Rectangle<int>::getConstrainedPoint)
			// .def("intersects", (bool (Rectangle<int>::*)(Rectangle<int> &) const noexcept) &Rectangle<int>::intersects)
			.def("getIntersection", &Rectangle<int>::getIntersection)
			.def("getUnion", &Rectangle<int>::getUnion)
			.def("enlargeIfAdjacent", &Rectangle<int>::enlargeIfAdjacent)
			.def("reduceIfPartlyContainedIn", &Rectangle<int>::reduceIfPartlyContainedIn)
			.def("transformedBy", &Rectangle<int>::transformedBy)
			.def("getSmallestIntegerContainer", &Rectangle<int>::getSmallestIntegerContainer)
			.def("toFloat", &Rectangle<int>::toFloat)
			.def("toString", &Rectangle<int>::toString)
			.def("leftTopRightBottom", &Rectangle<int>::leftTopRightBottom)
			.def("findAreaContainingPoints", &Rectangle<int>::findAreaContainingPoints)
			.def("intersectRectangles", &Rectangle<int>::intersectRectangles)
			.def("fromString", &Rectangle<int>::fromString)
		,
		class_<RectanglePlacement>("RectanglePlacement")
			.def(constructor<int>())
			.def("getFlags", &RectanglePlacement::getFlags)
			.def("testFlags", &RectanglePlacement::testFlags)
			.def("applyTo", &RectanglePlacement::applyTo)
			.enum_("flags")
			[
				value("xLeft", 1),
				value("xRight", 2),
				value("xMid", 4),
				value("yTop", 8),
				value("yBottom", 16),
				value("yMid", 32),
				value("stretchToFit", 64),
				value("fillDestination", 128),
				value("onlyReduceInSize", 256),
				value("onlyIncreaseInSize", 512),
				value("doNotResize", 768),
				value("centred", 36)
			]
    ,
        class_<LRectangle>("LRectangle")
    ,
        class_<Rectangle<float>, bases<LRectangle> >("RectangleFloat")
            .def(constructor<>())
            .def(constructor<const Rectangle<float> &>())
			.def(constructor<float,float,float,float>())
			.def(constructor<float,float>())
			.def(constructor<const Point<float> &, const Point <float> &>())
			.def("isEmpty", &Rectangle<float>::isEmpty)
			.def("getX", &Rectangle<float>::getX)
			.def("getY", &Rectangle<float>::getY)
			.def("getWidth", &Rectangle<float>::getWidth)
			.def("getHeight", &Rectangle<float>::getHeight)
			.def("getRight", &Rectangle<float>::getRight)
			.def("getBottom", &Rectangle<float>::getBottom)
			.def("getCentreX", &Rectangle<float>::getCentreX)
			.def("getCentreY", &Rectangle<float>::getCentreY)
			.def("getCentre", &Rectangle<float>::getCentre)
			.def("getAspectRatio", &Rectangle<float>::getAspectRatio)
			.def("getPosition", &Rectangle<float>::getPosition)
			.def("setPosition", (void (Rectangle<float>::*)(const Point<float> ) noexcept)&Rectangle<float>::setPosition)
			.def("setPosition", (void (Rectangle<float>::*)(const float, const float) noexcept)&Rectangle<float>::setPosition)
			.def("getTopLeft", &Rectangle<float>::getTopLeft)
			.def("getTopRight", &Rectangle<float>::getTopRight)
			.def("getBottomLeft", &Rectangle<float>::getBottomLeft)
			.def("getBottomRight", &Rectangle<float>::getBottomRight)
			.def("setSize", &Rectangle<float>::setSize)
			.def("setBounds", &Rectangle<float>::setBounds)
			.def("setX", &Rectangle<float>::setX)
			.def("setY", &Rectangle<float>::setY)
			.def("setWidth", &Rectangle<float>::setWidth)
			.def("setHeight", &Rectangle<float>::setHeight)
			.def("withX", &Rectangle<float>::withX)
			.def("withY", &Rectangle<float>::withY)
			.def("withPosition", (Rectangle<float> (Rectangle<float>::*)(const Point<float> ) const noexcept)&Rectangle<float>::withPosition)
			.def("withPosition", (Rectangle<float> (Rectangle<float>::*)(const float, const float) const noexcept)&Rectangle<float>::withPosition)
			.def("withZeroOrigin", &Rectangle<float>::withZeroOrigin)
			.def("withWidth", &Rectangle<float>::withWidth)
			.def("withHeight", &Rectangle<float>::withHeight)
			.def("withSize", &Rectangle<float>::withSize)
			.def("setLeft", &Rectangle<float>::setLeft)
			.def("withLeft", &Rectangle<float>::withLeft)
			.def("setTop", &Rectangle<float>::setTop)
			.def("withTop", &Rectangle<float>::withTop)
			.def("setRight", &Rectangle<float>::setRight)
			.def("withRight", &Rectangle<float>::withRight)
			.def("setBottom", &Rectangle<float>::setBottom)
			.def("withBottom", &Rectangle<float>::withBottom)
			.def("translate", &Rectangle<float>::translate)
			.def("translated", &Rectangle<float>::translated)
			.def("expand", &Rectangle<float>::expand)
			.def("expanded", (Rectangle<float> (Rectangle<float>::*)(const float, const float) const noexcept)&Rectangle<float>::expanded)
			.def("expanded", (Rectangle<float> (Rectangle<float>::*)(const float) const noexcept)&Rectangle<float>::expanded)
			.def("reduce", &Rectangle<float>::reduce)
			.def("reduced", (Rectangle<float> (Rectangle<float>::*)(const float, const float) const noexcept)&Rectangle<float>::reduced)
			.def("reduced", (Rectangle<float> (Rectangle<float>::*)(const float) const noexcept)&Rectangle<float>::reduced)
			.def("removeFromTop", &Rectangle<float>::removeFromTop)
			.def("removeFromLeft", &Rectangle<float>::removeFromLeft)
			.def("removeFromRight", &Rectangle<float>::removeFromRight)
			.def("removeFromBottom", &Rectangle<float>::removeFromBottom)
			.def("contains", (bool (Rectangle<float>::*)(const float, const float) const noexcept)&Rectangle<float>::contains)
			.def("contains", (bool (Rectangle<float>::*)(const Point<float> ) const noexcept)&Rectangle<float>::contains)
			.def("contains", (bool (Rectangle<float>::*)(const Rectangle<float> &) const noexcept)&Rectangle<float>::contains)
			.def("getConstrainedPoint", &Rectangle<float>::getConstrainedPoint)
			.def("getIntersection", &Rectangle<float>::getIntersection)
			.def("getUnion", &Rectangle<float>::getUnion)
			.def("enlargeIfAdjacent", &Rectangle<float>::enlargeIfAdjacent)
			.def("reduceIfPartlyContainedIn", &Rectangle<float>::reduceIfPartlyContainedIn)
			.def("transformedBy", &Rectangle<float>::transformedBy)
			.def("toString", &Rectangle<float>::toString)
			.def("leftTopRightBottom", &Rectangle<float>::leftTopRightBottom)
			.def("findAreaContainingPoints", &Rectangle<float>::findAreaContainingPoints)
			.def("intersectRectangles", &Rectangle<float>::intersectRectangles)
			.def("fromString", &Rectangle<float>::fromString)
			.def("toInt", &LRectangle::toInt)
	];
}

void LRelativeCoordinate::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<RelativePoint>("RelativePoint")
			.def(constructor<>())
			.def(constructor<const Point<float> &>())
			.def(constructor<float, float>())
			.def(constructor<const RelativeCoordinate &, const RelativeCoordinate &>())
			.def(constructor<const String &>())
			.def("resolve", &RelativePoint::resolve)
			.def("moveToAbsolute", &RelativePoint::moveToAbsolute)
			.def("toString", &RelativePoint::toString)
			.def("isDynamic", &RelativePoint::isDynamic)
		,
		class_<RelativeCoordinate>("JRelativeCoordinate")
		,
		class_<LRelativeCoordinate, bases<RelativeCoordinate> >("RelativeCoordinate")
			.def(constructor<const Expression &>())
			.def(constructor<const RelativeCoordinate &>())
			.def(constructor<double>())
			.def(constructor<const String &>())
			.def("resolve", &RelativeCoordinate::resolve)
			// .def("references", &LRelativeCoordinate::references) LINKER ERROR when using that
			.def("isRecursive", &RelativeCoordinate::isRecursive)
			.def("isDynamic", &RelativeCoordinate::isDynamic)
			.def("moveToAbsolute", &RelativeCoordinate::moveToAbsolute)
			.def("getExpression", &RelativeCoordinate::getExpression)
			.def("toString", &RelativeCoordinate::toString)
		,
		class_<RelativeParallelogram>("RelativeParallelogram")
			.def(constructor<>())
			.def(constructor<const Rectangle<float> &>())
			.def(constructor<const RelativePoint &, const RelativePoint &, const RelativePoint &>())
			.def(constructor<const String &, const String &, const String &>())
			.def("resolveThreePoints", &RelativeParallelogram::resolveThreePoints)
			.def("resolveFourCorners", &RelativeParallelogram::resolveFourCorners)
			.def("getBounds", &RelativeParallelogram::getBounds)
			.def("getPath", &RelativeParallelogram::getPath)
			.def("resetToPerpendicular", &RelativeParallelogram::resetToPerpendicular)
			.scope
			[
				def("getInternalCoordForPoint", &RelativeParallelogram::getInternalCoordForPoint),
				def("getPointForInternalCoord", &RelativeParallelogram::getPointForInternalCoord),
				def("getBoundingBox", &RelativeParallelogram::getBoundingBox)
			]
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

void LSlider::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
        class_<NotificationType>("NotificationType")
        ,
		class_<Slider, bases<Component> >("Slider")
			.def("setSliderStyle", &Slider::setSliderStyle)
			.def("getSliderStyle", &Slider::getSliderStyle)
			.def("setRotaryParameters", &Slider::setRotaryParameters)
			.def("setMouseDragSensitivity", &Slider::setMouseDragSensitivity)
			.def("getMouseDragSensitivity", &Slider::getMouseDragSensitivity)
			.def("setVelocityBasedMode", &Slider::setVelocityBasedMode)
			.def("getVelocityBasedMode", &Slider::getVelocityBasedMode)
			.def("setVelocityModeParameters", &Slider::setVelocityModeParameters)
			.def("getVelocitySensitivity", &Slider::getVelocitySensitivity)
			.def("getVelocityThreshold", &Slider::getVelocityThreshold)
			.def("getVelocityOffset", &Slider::getVelocityOffset)
			.def("getVelocityModeIsSwappable", &Slider::getVelocityModeIsSwappable)
			.def("setSkewFactor", &Slider::setSkewFactor)
			.def("setSkewFactorFromMidPoint", &Slider::setSkewFactorFromMidPoint)
			.def("getSkewFactor", &Slider::getSkewFactor)
			.def("setIncDecButtonsMode", &Slider::setIncDecButtonsMode)
			.def("setTextBoxStyle", &Slider::setTextBoxStyle)
			.def("getTextBoxPosition", &Slider::getTextBoxPosition)
			.def("getTextBoxWidth", &Slider::getTextBoxWidth)
			.def("getTextBoxHeight", &Slider::getTextBoxHeight)
			.def("setTextBoxIsEditable", &Slider::setTextBoxIsEditable)
			.def("isTextBoxEditable", &Slider::isTextBoxEditable)
			.def("showTextBox", &Slider::showTextBox)
			.def("hideTextBox", &Slider::hideTextBox)
			.def("setValue", (void (Slider::*)(double,NotificationType))&Slider::setValue)
			.def("getValue", &Slider::getValue)
			.def("getValueObject", &Slider::getValueObject)
			.def("setRange", &Slider::setRange)
			.def("getMaximum", &Slider::getMaximum)
			.def("getMinimum", &Slider::getMinimum)
			.def("getInterval", &Slider::getInterval)
			.def("getMinValue", &Slider::getMinValue)
			.def("getMinValueObject", &Slider::getMinValueObject)
			.def("setMinValue", (void (Slider::*)(double,NotificationType,bool))&Slider::setMinValue)
			.def("getMaxValue", &Slider::getMaxValue)
			.def("getMaxValueObject", &Slider::getMaxValueObject)
			.def("setMaxValue", (void (Slider::*)(double,NotificationType,bool))&Slider::setMaxValue)
			.def("setMinAndMaxValues", (void (Slider::*)(double,double,NotificationType))&Slider::setMinAndMaxValues)
			.def("addListener", &Slider::addListener)
			.def("removeListener", &Slider::removeListener)
			.def("setDoubleClickReturnValue", &Slider::setDoubleClickReturnValue)
			.def("getDoubleClickReturnValue", &Slider::getDoubleClickReturnValue)
			.def("setChangeNotificationOnlyOnRelease", &Slider::setChangeNotificationOnlyOnRelease)
			.def("setSliderSnapsToMousePosition", &Slider::setSliderSnapsToMousePosition)
			.def("getSliderSnapsToMousePosition", &Slider::getSliderSnapsToMousePosition)
			.def("setPopupDisplayEnabled", &Slider::setPopupDisplayEnabled)
			.def("getCurrentPopupDisplay", &Slider::getCurrentPopupDisplay)
			.def("setPopupMenuEnabled", &Slider::setPopupMenuEnabled)
			.def("setScrollWheelEnabled", &Slider::setScrollWheelEnabled)
			.def("getThumbBeingDragged", &Slider::getThumbBeingDragged)
			.def("startedDragging", &Slider::startedDragging)
			.def("stoppedDragging", &Slider::stoppedDragging)
			.def("valueChanged", &Slider::valueChanged)
			.def("getValueFromText", &Slider::getValueFromText)
			.def("getTextFromValue", &Slider::getTextFromValue)
			.def("setTextValueSuffix", &Slider::setTextValueSuffix)
			.def("getTextValueSuffix", &Slider::getTextValueSuffix)
			.def("proportionOfLengthToValue", &Slider::proportionOfLengthToValue)
			.def("valueToProportionOfLength", &Slider::valueToProportionOfLength)
			.def("getPositionOfValue", &Slider::getPositionOfValue)
			.def("updateText", &Slider::updateText)
			.def("isHorizontal", &Slider::isHorizontal)
			.def("isVertical", &Slider::isVertical)
			.enum_("TextEntryBoxPosition")
			[
                value("NoTextBox", Slider::NoTextBox),
                value("TextBoxLeft", Slider::TextBoxLeft),
                value("TextBoxRight", Slider::TextBoxRight),
                value("TextBoxAbove", Slider::TextBoxAbove),
                value("TextBoxBelow", Slider::TextBoxBelow)
			]
			.enum_("SliderStyle")
			[
                value("LinearHorizontal", Slider::LinearHorizontal),
                value("LinearVertical", Slider::LinearVertical),
                value("LinearBar", Slider::LinearBar),
                value("LinearBarVertical", Slider::LinearBarVertical),
                value("Rotary", Slider::Rotary),
                value("RotaryHorizontalDrag", Slider::RotaryHorizontalDrag),
                value("RotaryVerticalDrag", Slider::RotaryVerticalDrag),
                value("RotaryHorizontalVerticalDrag", Slider::RotaryHorizontalVerticalDrag),
                value("IncDecButtons", Slider::IncDecButtons),
                value("TwoValueHorizontal", Slider::TwoValueHorizontal),
                value("TwoValueVertical", Slider::TwoValueVertical),
                value("ThreeValueHorizontal", Slider::ThreeValueHorizontal),
                value("ThreeValueVertical", Slider::ThreeValueVertical)
			]
			.enum_("DragMode")
			[
                value("notDragging", Slider::notDragging),
                value("absoluteDrag", Slider::absoluteDrag),
                value("velocityDrag", Slider::velocityDrag)
			]
	];
}

int LSparseSet::get(int index)
{
	SparseSet<int> *s = dynamic_cast <SparseSet<int> *>(this);
	return ((*s)[index]);
}

void LSparseSet::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<SparseSet<int> >("JSparseSet")
		,
		class_<LSparseSet, bases<SparseSet<int> > >("SparseSet")
				.def(constructor<const SparseSet<int> &>())
				.def(constructor<>())
				.def("clear", &SparseSet<int>::clear)
				.def("isEmpty", &SparseSet<int>::isEmpty)
				.def("size", &SparseSet<int>::size)
				.def("contains", &SparseSet<int>::contains)
				.def("getNumRanges", &SparseSet<int>::getNumRanges)
				.def("getRange", &SparseSet<int>::getRange)
				.def("getTotalRange", &SparseSet<int>::getTotalRange)
				.def("addRange", &SparseSet<int>::addRange)
				.def("removeRange", &SparseSet<int>::removeRange)
				.def("invertRange", &SparseSet<int>::invertRange)
				.def("overlapsRange", &SparseSet<int>::overlapsRange)
				.def("containsRange", &SparseSet<int>::containsRange)
				.def("get", &LSparseSet::get)
	];
}

void LString::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<String>("String")
			.def(constructor<const char *>())
			.def(constructor<const char *, const int>())
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
			.def(constructor<const char *const *, const int>())
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

void LTextButton::wrapForLua (lua_State *L)
{
    using namespace luabind;

	module(L)
    [
		class_<TextButton, Button>("TextButton")
            .def(constructor<const String &>())
            .def(constructor<const String &, const String &>())
    ];
}

void LTextEditor::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<TextEditor, bases<Component> >("TextEditor")
			.def(constructor<>())
			.def(constructor<const String &>())
			.def("setMultiLine", &TextEditor::setMultiLine)
			.def("isMultiLine", &TextEditor::isMultiLine)
			.def("setReturnKeyStartsNewLine", &TextEditor::setReturnKeyStartsNewLine)
			.def("getReturnKeyStartsNewLine", &TextEditor::getReturnKeyStartsNewLine)
			.def("setTabKeyUsedAsCharacter", &TextEditor::setTabKeyUsedAsCharacter)
			.def("isTabKeyUsedAsCharacter", &TextEditor::isTabKeyUsedAsCharacter)
			.def("setEscapeAndReturnKeysConsumed", &TextEditor::setEscapeAndReturnKeysConsumed)
			.def("setReadOnly", &TextEditor::setReadOnly)
			.def("isReadOnly", &TextEditor::isReadOnly)
			.def("setCaretVisible", &TextEditor::setCaretVisible)
			.def("isCaretVisible", &TextEditor::isCaretVisible)
			.def("setScrollbarsShown", &TextEditor::setScrollbarsShown)
			.def("areScrollbarsShown", &TextEditor::areScrollbarsShown)
			.def("setPasswordCharacter", &TextEditor::setPasswordCharacter)
			.def("getPasswordCharacter", &TextEditor::getPasswordCharacter)
			.def("setPopupMenuEnabled", &TextEditor::setPopupMenuEnabled)
			.def("isPopupMenuEnabled", &TextEditor::isPopupMenuEnabled)
			.def("isPopupMenuCurrentlyActive", &TextEditor::isPopupMenuCurrentlyActive)
			.def("setFont", &TextEditor::setFont)
			.def("applyFontToAllText", &TextEditor::applyFontToAllText)
			.def("getFont", &TextEditor::getFont)
			.def("setSelectAllWhenFocused", &TextEditor::setSelectAllWhenFocused)
			.def("setTextToShowWhenEmpty", &TextEditor::setTextToShowWhenEmpty)
			.def("setScrollBarThickness", &TextEditor::setScrollBarThickness)
			.def("addListener", &TextEditor::addListener)
			.def("removeListener", &TextEditor::removeListener)
			.def("getText", &TextEditor::getText)
			.def("getTextInRange", &TextEditor::getTextInRange)
			.def("isEmpty", &TextEditor::isEmpty)
			.def("setText", &TextEditor::setText)
			.def("getTextValue", &TextEditor::getTextValue)
			.def("insertTextAtCaret", &TextEditor::insertTextAtCaret)
			.def("clear", &TextEditor::clear)
			.def("cut", &TextEditor::cut)
			.def("copy", &TextEditor::copy)
			.def("paste", &TextEditor::paste)
			.def("getCaretPosition", &TextEditor::getCaretPosition)
			.def("setCaretPosition", &TextEditor::setCaretPosition)
			.def("scrollEditorToPositionCaret", &TextEditor::scrollEditorToPositionCaret)
			.def("getCaretRectangle", &TextEditor::getCaretRectangle)
			.def("setHighlightedRegion", &TextEditor::setHighlightedRegion)
			.def("getHighlightedRegion", &TextEditor::getHighlightedRegion)
			.def("getHighlightedText", &TextEditor::getHighlightedText)
			.def("getTextIndexAt", &TextEditor::getTextIndexAt)
			.def("getTotalNumChars", &TextEditor::getTotalNumChars)
			.def("getTextWidth", &TextEditor::getTextWidth)
			.def("setIndents", &TextEditor::setIndents)
			.def("setBorder", &TextEditor::setBorder)
			.def("getBorder", &TextEditor::getBorder)
			.def("setScrollToShowCursor", &TextEditor::setScrollToShowCursor)
			.def("moveCaretToEnd", (void (TextEditor::*)()) &TextEditor::moveCaretToEnd)
			.def("moveCaretLeft", &TextEditor::moveCaretLeft)
			.def("moveCaretRight", &TextEditor::moveCaretRight)
			.def("moveCaretUp", &TextEditor::moveCaretUp)
			.def("moveCaretDown", &TextEditor::moveCaretDown)
			.def("pageUp", &TextEditor::pageUp)
			.def("pageDown", &TextEditor::pageDown)
			.def("scrollDown", &TextEditor::scrollDown)
			.def("scrollUp", &TextEditor::scrollUp)
			.def("moveCaretToTop", &TextEditor::moveCaretToTop)
			.def("moveCaretToStartOfLine", &TextEditor::moveCaretToStartOfLine)
			.def("moveCaretToEnd", (bool (TextEditor::*)(bool)) &TextEditor::moveCaretToEnd)
			.def("moveCaretToEndOfLine", &TextEditor::moveCaretToEndOfLine)
			.def("deleteBackwards", &TextEditor::deleteBackwards)
			.def("deleteForwards", &TextEditor::deleteForwards)
			.def("copyToClipboard", &TextEditor::copyToClipboard)
			.def("cutToClipboard", &TextEditor::cutToClipboard)
			.def("pasteFromClipboard", &TextEditor::pasteFromClipboard)
			.def("selectAll", &TextEditor::selectAll)
			.def("undo", &TextEditor::undo)
			.def("redo", &TextEditor::redo)
			.def("addPopupMenuItems", &TextEditor::addPopupMenuItems)
			.def("setInputFilter", &TextEditor::setInputFilter)
			.def("setInputRestrictions", &TextEditor::setInputRestrictions)
			.def("redo", &TextEditor::redo)
	];
}

LThread::LThread(const String &threadName) : Thread(threadName)
{
}

void LThread::run()
{
	if (functionToRunOnThread.is_valid())
	{
		luabind::call_function<void>(functionToRunOnThread);
	}
}

void LThread::setThreadFunction(luabind::object const& _functionToRunOnThread)
{
	functionToRunOnThread = _functionToRunOnThread;
}

void LThread::startThread()
{
	Thread::startThread();
}

void LThread::startThread(int priority)
{
	Thread::startThread(priority);
}

bool LThread::isThreadRunning()
{
	return (Thread::isThreadRunning());
}

void LThread::signalThreadShouldExit()
{
	Thread::signalThreadShouldExit();
}

bool LThread::threadShoudExit() const
{
	return (Thread::threadShouldExit());
}

bool LThread::waitForThreadToExit(int timeOutMilliseconds) const
{
	return (Thread::waitForThreadToExit(timeOutMilliseconds));
}

bool LThread::setPriority(int priority)
{
	return (Thread::setPriority(priority));
}

void LThread::setAffinityMask(int affinityMask)
{
	Thread::setAffinityMask(affinityMask);
}

bool LThread::wait(int timeOutMilliseconds) const
{
	return (Thread::wait(timeOutMilliseconds));
}

void LThread::notify() const
{
	Thread::notify();
}

int LThread::getThreadId() const noexcept
{
    int *id = static_cast<int*>(Thread::getThreadId());

	return (*id);
}

const String &LThread::getThreadName() const
{
	return (Thread::getThreadName());
}

void LThread::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<LThread>("Thread")
			.def(constructor<const String &>())
			.def("setThreadFunction", &LThread::setThreadFunction)
			.def("startThread", (void (LThread::*)(void))&LThread::startThread)
			.def("startThread", (void (LThread::*)(int))&LThread::startThread)
			.def("isThreadRunning", &LThread::isThreadRunning)
			.def("signalThreadShouldExit", &LThread::signalThreadShouldExit)
			.def("threadShoudExit", &LThread::threadShoudExit)
			.def("waitForThreadToExit", &LThread::waitForThreadToExit)
			.def("setPriority", (void (LThread::*)(int))&LThread::setPriority)
			.def("setAffinityMask", &LThread::setAffinityMask)
			.def("wait", &LThread::wait)
			.def("notify", &LThread::notify)
			.def("getThreadId", &LThread::getThreadId)
			.def("getThreadName", &LThread::getThreadName)
		,
		class_<CriticalSection>("CriticalSection")
			.def(constructor<>())
			.def("enter", &CriticalSection::enter)
			.def("tryEnter", &CriticalSection::tryEnter)
			.def("exit", &CriticalSection::exit)
		,
		class_<ScopedLock>("ScopedLock")
			.def(constructor<CriticalSection &>())
		,
		class_<ScopedUnlock>("ScopedUnlock")
			.def(constructor<CriticalSection &>())
		,
		class_<ScopedTryLock>("ScopedTryLock")
			.def(constructor<CriticalSection &>())
			.def("isLocked", &ScopedTryLock::isLocked)
	];
}

LThreadWithProgressWindow::LThreadWithProgressWindow(const String &windowTitle, bool hasProgressBar, bool hasCancelButton, int timeOutMsWhenCancelling, const String &cancelButtonText)
	: ThreadWithProgressWindow(windowTitle, hasProgressBar, hasCancelButton, timeOutMsWhenCancelling, cancelButtonText, nullptr)
{
}

LThreadWithProgressWindow::~LThreadWithProgressWindow()
{
}

void LThreadWithProgressWindow::run()
{
	try
	{
		if (functionToRunOnThread.is_valid())
		{
			luabind::call_function<void>(functionToRunOnThread);
		}
	}
	catch (luabind::error& e)
	{
		_ERR("ThreadWithProgressWindow function set to run inside thread causes problems ["+STR(e.what())+"]");
	}
}

void LThreadWithProgressWindow::setThreadFunction(luabind::object const& _functionToRunOnThread)
{
	functionToRunOnThread = _functionToRunOnThread;
}

void LThreadWithProgressWindow::setProgress(double newProgress)
{
	ThreadWithProgressWindow::setProgress(newProgress);
}

void LThreadWithProgressWindow::setStatusMessage(const String &newStatusMessage)
{
	ThreadWithProgressWindow::setStatusMessage(newStatusMessage);
}

void LThreadWithProgressWindow::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<ThreadWithProgressWindow> ("JThreadWithProgressWindow")
		,
		class_<Thread>("JThread")
		,
		class_<LThreadWithProgressWindow,bases<Thread,ThreadWithProgressWindow> >("ThreadWithProgressWindow")
			.def(constructor<const String &, bool, bool, int, const String &>())
			.def("runThread", &ThreadWithProgressWindow::runThread)
			.def("setThreadFunction", &LThreadWithProgressWindow::setThreadFunction)
			.def("wait", &Thread::wait)
			.def("setProgress", &LThreadWithProgressWindow::setProgress)
			.def("setStatusMessage", &LThreadWithProgressWindow::setStatusMessage)
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

void LToggleButton::wrapForLua (lua_State *L)
{
    using namespace luabind;

	module(L)
    [
		class_<ToggleButton, Button>("ToggleButton")
            .def(constructor<>())
            .def(constructor<const String &>())
            .def("changeWidthToFitText", &ToggleButton::changeWidthToFitText)

    ];
}

void LTypeface::wrapForLua (lua_State *L)
{
    using namespace luabind;

	module(L)
    [
        class_<Typeface::Ptr>("TypefacePtr")
        ,
		class_<Typeface>("Typeface")
            .def("getName", &Typeface::getName)
            .def("getStyle", &Typeface::getStyle)
            .def("isSuitableForFont", &Typeface::isSuitableForFont)
            .def("getAscent", &Typeface::getAscent)
            .def("getDescent", &Typeface::getDescent)
            .def("getHeightToPointsFactor", &Typeface::getHeightToPointsFactor)
            .def("getStringWidth", &Typeface::getStringWidth)
            .def("getGlyphPositions", &Typeface::getGlyphPositions)
            .def("getOutlineForGlyph", &Typeface::getOutlineForGlyph)
            .def("getEdgeTableForGlyph", &Typeface::getEdgeTableForGlyph)
            .def("isHinted", &Typeface::isHinted)
            .def("applyVerticalHintingTransform",  &Typeface::applyVerticalHintingTransform)
            .scope
            [
                def("createSystemTypefaceFor", (Typeface::Ptr (*) (const Font &))&Typeface::createSystemTypefaceFor),
                def("createSystemTypefaceFor", (Typeface::Ptr (*) (const void *, size_t))&Typeface::createSystemTypefaceFor),
                def("setTypefaceCacheSize", &Typeface::setTypefaceCacheSize),
                def("clearTypefaceCache", &Typeface::clearTypefaceCache),
                def("scanFolderForFonts", &Typeface::scanFolderForFonts)
            ]
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
			.def("withPOSTData", &URL::withPOSTData)
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
				.def("getProperty", (var (ValueTree::*)(const Identifier, const var &) const) &ValueTree::getProperty)
				.def("getProperty", (const var &(ValueTree::*)(const Identifier) const) &ValueTree::getProperty)
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
			.def("getEntry", (const ZipFile::ZipEntry *(ZipFile::*)(const String &) const noexcept) &ZipFile::getEntry)
			.def("sortEntriesByFilename", &ZipFile::sortEntriesByFilename)
			.def("createStreamForEntry", (InputStream *(ZipFile::*)(int)) &ZipFile::createStreamForEntry, adopt(result))
			.def("createStreamForEntry", (InputStream *(ZipFile::*)(const ZipFile::ZipEntry &)) &ZipFile::createStreamForEntry, adopt(result))
			.def("uncompressTo", &ZipFile::uncompressTo)
			.def("uncompressEntry", &ZipFile::uncompressEntry)
	];
}
