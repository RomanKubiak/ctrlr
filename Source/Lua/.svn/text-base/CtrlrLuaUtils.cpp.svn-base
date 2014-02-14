#include "stdafx.h"
#include "CtrlrLuaUtils.h"
#include "CtrlrLog.h"
#include "JuceClasses/LMemoryBlock.h"

/*
 * Copyright (c) 2010 The Beige Maze Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#define DSI_VOICE_DATA_MAX 16535

struct DSIVoiceData 
{
	int size;
	unsigned char* data;
};

typedef struct DSIVoiceData UnpackedVoice, PackedVoice;

UnpackedVoice unpackDsiMidiData(PackedVoice packed)
{
	unsigned char data[DSI_VOICE_DATA_MAX];
    int packbyte = 0;  /* Composite of high bits of next 7 bytes */
    int pos = 0;       /* Current position of 7 */
    int ixp;           /* Packed byte index */
    int size = 0;      /* Unpacked voice size */
    unsigned char c;   /* Current source byte */
    for (ixp = 0; ixp < packed.size; ixp++)
    {
        c = packed.data[ixp];
        if (pos == 0) {
            packbyte = c;
        } else {
            if (packbyte & (1 << (pos - 1))) {c |= 0x80;}
            data[size++] = c;
        }
        pos++;
        pos &= 0x07;
        if (size > DSI_VOICE_DATA_MAX) break;
    }

    UnpackedVoice unpacked = {size, data};
    return unpacked;
}

PackedVoice packDsiMidiData(UnpackedVoice unpacked)
{
	uint8 data[DSI_VOICE_DATA_MAX];
    uint8 packbyte = 0;  /* Composite of high bits of next 7 bytes */
    int pos = 0;       /* Current position of 7 */
    int ixu;           /* Unpacked byte index */
    int size = 0;      /* Packed voice size */
    uint8 packet[7];     /* Current packet */
    uint8 i;             /* Packet output index */
    unsigned char c;   /* Current source byte */
    for (ixu = 0; ixu < unpacked.size; ixu++)
    {
        c = unpacked.data[ixu];
        if (pos == 7) {
        	data[size++] = (uint8)packbyte;
            for (i = 0; i < pos; i++)
            {
            	data[size++] = packet[i];
            }
            packbyte = 0;
            pos = 0;
        }
        if (c & 0x80) {
            packbyte += (1 << pos);
            c &= 0x7f;
        }
        packet[pos] = c;
        pos++;
        if ((size + 8) > DSI_VOICE_DATA_MAX) break;
    }
    data[size++] = packbyte;
    for (i = 0; i < pos; i++)
    {
    	data[size++] = packet[i];
    }

	PackedVoice packed = {size, data};
    return packed;
}

LMemoryBlock *CtrlrLuaUtils::unpackDsiData (MemoryBlock &dataToUnpack)
{
	PackedVoice packed;
	packed.data = (uint8 *)dataToUnpack.getData();
	packed.size = dataToUnpack.getSize();

	UnpackedVoice unpacked = unpackDsiMidiData(packed);

	return (new LMemoryBlock ((uint8 *)unpacked.data, unpacked.size));
}

LMemoryBlock *CtrlrLuaUtils::packDsiData (MemoryBlock &dataToPack)
{
	UnpackedVoice unpacked,packed;
	unpacked.data = (uint8*)dataToPack.getData();
	unpacked.size = dataToPack.getSize();

	packed = packDsiMidiData(unpacked);

	return (new LMemoryBlock ((uint8 *)packed.data, packed.size));
}

void CtrlrLuaUtils::warnWindow (const String title, const String message)
{
	AlertWindow::showMessageBox (AlertWindow::WarningIcon, title, message);
}

void CtrlrLuaUtils::infoWindow (const String title, const String message)
{
	AlertWindow::showMessageBox (AlertWindow::InfoIcon, title, message);
}

bool CtrlrLuaUtils::questionWindow (const String title, const String message, const String button1Text, const String button2Text)
{
	return (AlertWindow::showOkCancelBox (AlertWindow::QuestionIcon, title, message, button1Text, button2Text));
}

File CtrlrLuaUtils::openFileWindow(const String &dialogBoxTitle, const File &initialFileOrDirectory, const String &filePatternsAllowed, bool useOSNativeDialogBox)
{
	FileChooser dialog(dialogBoxTitle, initialFileOrDirectory, filePatternsAllowed, useOSNativeDialogBox);
	if (dialog.browseForFileToOpen(0))
	{
		return (dialog.getResult());
	}
	else
	{
		return (File::nonexistent);
	}
}

File CtrlrLuaUtils::saveFileWindow(const String &dialogBoxTitle, const File &initialFileOrDirectory, const String &filePatternsAllowed, bool useOSNativeDialogBox)
{
	FileChooser dialog(dialogBoxTitle, initialFileOrDirectory, filePatternsAllowed, useOSNativeDialogBox);
	if (dialog.browseForFileToSave (true))
	{
		return (dialog.getResult());
	}
	else
	{
		return (File::nonexistent);
	}
}

File CtrlrLuaUtils::getDirectoryWindow(const String &dialogBoxTitle, const File &initialFileOrDirectory)
{
	FileChooser dialog(dialogBoxTitle, initialFileOrDirectory);
	if (dialog.browseForDirectory())
	{
		return (dialog.getResult());
	}
	else
	{
		return (File());
	}
}

String CtrlrLuaUtils::askForTextInputWindow (const String title, const String message, const String initialInputContent, const String onScreenLabel, const bool isPassword, const String button1Text, const String button2Text)
{
	AlertWindow w(title, message, AlertWindow::QuestionIcon, 0);
	w.addTextEditor ("userInput", initialInputContent,  onScreenLabel, isPassword);
	w.addButton (button1Text, 1);
	w.addButton (button2Text, 0);
	w.runModalLoop();
	return (w.getTextEditorContents("userInput"));
}

StringArray CtrlrLuaUtils::getMidiInputDevices()
{
	return ( MidiInput::getDevices() );
}

StringArray CtrlrLuaUtils::getMidiOutputDevices()
{
	return ( MidiOutput::getDevices() );
}

void CtrlrLuaUtils::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrLuaUtils>("CtrlrLuaUtils")
			.def("unpackDsiData", &CtrlrLuaUtils::unpackDsiData, adopt(result))
			.def("packDsiData", &CtrlrLuaUtils::packDsiData, adopt(result))
			.def("warnWindow", &CtrlrLuaUtils::warnWindow)
			.def("infoWindow", &CtrlrLuaUtils::infoWindow)
			.def("questionWindow", &CtrlrLuaUtils::questionWindow)
			.def("openFileWindow", &CtrlrLuaUtils::openFileWindow)
			.def("saveFileWindow", &CtrlrLuaUtils::saveFileWindow)
			.def("getDirectoryWindow", &CtrlrLuaUtils::getDirectoryWindow)
			.def("askForTextInputWindow", &CtrlrLuaUtils::askForTextInputWindow)
			.def("getMidiInputDevices", &CtrlrLuaUtils::getMidiInputDevices)
			.def("getMidiOutputDevices", &CtrlrLuaUtils::getMidiOutputDevices)
	];
}