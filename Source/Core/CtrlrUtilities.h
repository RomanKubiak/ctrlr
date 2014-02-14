#ifndef __CTRLR_UTILITIES__
#define __CTRLR_UTILITIES__

#include "CtrlrInlineUtilities.h"

class CtrlrToolbarButton;
class CtrlrPanel;
class CtrlrLookAndFeel;

/** MidiMessage and CtrlrMidiMessage operations **/
const String removeInvalidChars(const String &dataToValidate, const bool showSpecials=false, const char characterToReplace=' ');
const String midiMessageTypeToString (const CtrlrMidiMessageType messageType);
const CtrlrMidiMessageType midiMessageStringToType (const String &messageType);
const CtrlrMidiMessageType midiMessageToType (const MidiMessage &midiMessage);
const CtrlrSysExFormulaToken indirectFromString (const String &str);
const MidiMessageEx	midiMessageExfromString (const String &str, const int ch, const int number, const int value);
const MidiMessage createFromHexData (const String &hexData);
void addCtrlrMidiMessageToBuffer (MidiBuffer &bufferToAddTo, CtrlrMidiMessage &m);
const CtrlrMidiMessageType getMidiTypeFromModulator(CtrlrModulator *m, const int index=-1);
const String extractVendorId (const CtrlrMidiMessage &message);

/** Debugging info on some objects **/
const String dumpTree (const ValueTree &tree);
ValueTree valueTreeFromXml (const String &dumpedXmlAsString);

/** Generic utilites **/
void setComboContentFromString (ComboBox *box, const String &content);
const String generateRandomUnique(const String &additionalRandomData="");
void uniqueIntArray (Array <int> &arrayToModify);
void uniqueFontArray (Array <Font> &arrayToModify);
const String dataPrefix (const MemoryBlock &data, const int prefixLength);
const String dataPrefix (const CtrlrMidiMessage &data, const int prefixLength);
const bool isMonospaced(const Font &font);

/** Format a MidiMessage to something human readable, with details **/
const String getMidiMessageAsLogString (const MidiMessage &m, const bool name=false, const bool channel=false, const bool number=false, const bool value=false, const bool timestamp=false, const bool rawData=true, const bool rawInDecimcal=false, const bool rawDataSize=false);
const String getMidiChannel(const MidiMessage &m);
const String getMidiValue(const MidiMessage &m);
const String getMidiNumber(const MidiMessage &m);
const String getRawDataSize(const MidiMessage &m);
int getMidiNumberFromModulator(CtrlrModulator *m);
const int getMidiNumberFromMidiMessage (const MidiMessage &m);
const String labelFromProperty (CtrlrModulator *modulator, const String &formatText);

/** Bit options stored in one integer **/
void setBitOption (int &storage, const int optionToSet, const bool isSet);
const bool getBitOption (const int &storage, const int &optionToGet);

/** Evaluate functions in a formula (basic standard functions) **/
double evaluateFormulaFunction (CtrlrPanel &panel, const String& functionName, const double* parameters, int numParameters);

/** Get details about AudioFormat **/
const String getAudioFormatDetails(AudioFormat *format);
const String getAudioFormatReaderDetails(AudioFormatReader *reader);

/** Create some nice looking dialogs **/
const int customInfoDialog (const String &title, Component *customComponent);
#endif
