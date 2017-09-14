#ifndef __CTRLR_UTILITIES__
#define __CTRLR_UTILITIES__

#include "stdafx.h"
#include "CtrlrMidiMessage.h"
class CtrlrToolbarButton;
class CtrlrPanel;
class CtrlrModulator;

/** MidiMessage and CtrlrMidiMessage operations **/
const String removeInvalidChars(const String &dataToValidate, const bool showSpecials=false, const char characterToReplace=' ');
const String midiMessageTypeToString (const CtrlrMidiMessageType messageType);
CtrlrMidiMessageType midiMessageStringToType (const String &messageType);
CtrlrMidiMessageType midiMessageToType (const MidiMessage &midiMessage);
CtrlrSysExFormulaToken indirectFromString (const String &str);
const CtrlrMidiMessageEx midiMessageExfromString (const String &str, const int ch, const int number, const int value);
const MidiMessage createFromHexData (const String &hexData);
void addCtrlrMidiMessageToBuffer (MidiBuffer &bufferToAddTo, CtrlrMidiMessage &m);
CtrlrMidiMessageType getMidiTypeFromModulator(CtrlrModulator *m, const int index=-1, CtrlrMIDIDeviceType source = inputDevice);
const String extractVendorId (const CtrlrMidiMessage &message);

/** Debugging info on some objects **/
const String dumpTree (const ValueTree &tree);
ValueTree valueTreeFromXml (const String &dumpedXmlAsString);

/** Generic utilites **/
const String generateRandomUnique(const String &additionalRandomData="");
const String generateRandomUniquePluginId();
void uniqueFontArray (Array <juce::Font> &arrayToModify);
const String dataPrefix (const MemoryBlock &data, const int prefixLength);
const String dataPrefix (const CtrlrMidiMessage &data, const int prefixLength);
bool isMonospaced(const juce::Font &font);

/** Format a MidiMessage to something human readable, with details **/
const String getMidiMessageAsLogString (const MidiMessage &m, const double customTimestamp = -1, const bool name=false, const bool channel=false, const bool number=false, const bool value=false, const bool timestamp=false, const bool rawData=true, const bool rawInDecimcal=false, const bool rawDataSize=false);
const String getMidiChannel(const MidiMessage &m);
const String getMidiValue(const MidiMessage &m);
const String getMidiNumber(const MidiMessage &m);
const String getRawDataSize(const MidiMessage &m);
int getMidiNumberFromModulator(CtrlrModulator *m, const CtrlrMIDIDeviceType source = inputDevice);
int getMidiNumberFromMidiMessage (const MidiMessage &m);
const String labelFromProperty (CtrlrModulator *modulator, const String &formatText);

/** Bit options stored in one integer **/
void setBitOption (int &storage, const int optionToSet, const bool isSet);
bool getBitOption (const int &storage, const int &optionToGet);

/** Evaluate functions in a formula (basic standard functions) **/
double evaluateFormulaFunction (CtrlrPanel &panel, const String& functionName, const double* parameters, int numParameters);

class CtrlrUInt16;
int getVersionAsHexInteger(const String version);
const MemoryBlock signData(const MemoryBlock &dataToSign, const RSAKey keyToSign);
static const String versionNumberToString2(const int versionNumber);
static const String versionNumberToString(const int versionNumber);
bool stringIsHexadecimal(const String &hexData);
static const String dumpMemoryBlock(const MemoryBlock &data);
const String memoryBlockToString(const MemoryBlock &data);
static const MemoryBlock hexStringToMemoryBlock(const String &hexData);
static const MemoryBlock stringToMemoryBlock(const String &stringToConvert);
Array<float> luaArrayToFloat(const luabind::object &luaArray);
const MemoryBlock luaArrayTomemoryBlock(const luabind::object &luaArray);
bool isInvalidMethodName(const String &name);
int add_file_and_line(lua_State* L);
double denormalizeValue(const float& normalized, const double& minValue, const double& maxValue);
float normalizeValue(const double& value, const double& minValue, const double& maxValue);
void channelizeBuffer(MidiBuffer &inputBuffer, MidiBuffer &outputBuffer, const int channel, const bool channelizeAllowed);
const BigInteger memoryToBits(const MemoryBlock &mb);
bool compareMemory(const MemoryBlock &haystack, const MemoryBlock &needle);
const MemoryBlock midiMessagePattern(const CtrlrMidiMessageEx &mEx, const Array<CtrlrSysexToken> tokens, const Array <int, CriticalSection> &globalVariables);
const BigInteger getValueAsBigInteger(const int inValue, const CtrlrSysExFormulaToken op);
int indirectReverseOperation(const int inValue, const CtrlrSysExFormulaToken op);
int	indirectOperation(const int inValue, const CtrlrSysExFormulaToken op);
static float getFloatValue(const int intValueToUse, const int maxValue);
static int getIntValue(const float newValue, const int maxValue);
const void mergeMidiData(const CtrlrMidiMessage &source, CtrlrMidiMessage &destination);
void restoreProperties(const ValueTree &sourceTree, ValueTree &destinationTree, UndoManager *undoManager = 0, const String &propertyPrefix = String::empty);

#endif
