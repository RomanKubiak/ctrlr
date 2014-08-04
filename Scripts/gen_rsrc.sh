#!/bin/bash
RESULT_FILE="result_1.rsrc"
function fill
{
    # fill string to width of count from string chars 
    #
    # usage:
    #      fill count [chars]
    #
    # if count is zero a blank string is output
    # chars is optional, spaces used if missing
    #
    FILL="${2:- }"
    for ((c=0; c<=$1; c+=${#FILL}))
    do
        echo -n "${FILL:0:$1-$c}"
    done
}

function pad
{
    # Pad to right of string to required width, using chars.
    # Chars is repeated, as required, until width is reached.
    #
    # usage:
    #      pad width string [chars]
    #
    # if chars not specified spaces are used
    #
    BACK=$(fill $1 "$3")
    let PAD=$1-${#2}
    if [ $PAD -lt 1 ] 
    then
        echo -n ${2:0:$1-1}
    else
        echo -n "$2${BACK:${#2}}"
    fi
}

for i in `seq 1 128`; do
	RES=`pad $i "" N`
	RESULT_FILE="result_$i.rsrc"
	rm -f $RESULT_FILE
	echo "GEN[$i] $RES -> result_$i.rsrc"
/Applications/Xcode.app/Contents/Developer/usr/bin/Rez \
-d "gen_name=\"$RES\"" \
-o $RESULT_FILE \
-d SystemSevenOrLater=1 \
-useDF \
-script Roman \
-d "ppc_$ppc" \
-d i386_YES \
-d "ppc64_$ppc64" \
-d x86_64_YES \
-I /System/Library/Frameworks/CoreServices.framework/Frameworks/CarbonCore.framework/Versions/A/Headers \
-I /Applications/Xcode.app/Contents/Developer/Extras/CoreAudio/AudioUnits/AUPublic/AUBase \
-arch x86_64 \
-arch i386 \
-i /Users/atom/devel/ctrlr/Builds/Generated/Mac/AU/build/Debug \
-i /Applications/Xcode.app/Contents/Developer/Extras/CoreAudio/AudioUnits/AUPublic/AUCarbonViewBase \
-i /Applications/Xcode.app/Contents/Developer/Extras/CoreAudio/AudioUnits/AUPublic/Utility \
-i /Applications/Xcode.app/Contents/Developer/Extras/CoreAudio/AudioUnits/AUPublic/AUViewBase \
-i /Users/atom/devel/ctrlr/Builds/Generated/Mac/AU/../../../AU/JuceLibraryCode \
-i /Applications/Xcode.app/Contents/Developer/Extras/CoreAudio/AudioUnits/AUPublic/AUBase \
-i /Applications/Xcode.app/Contents/Developer/Extras/CoreAudio/PublicUtility \
-i /Applications/Xcode.app/Contents/Developer/Extras/CoreAudio/AudioUnits/AUPublic/OtherBases \
-i ../../../AU/JuceLibraryCode \
-i ../../../../Juce/modules \
-i /Applications/Xcode.app/Contents/Developer/Extras/CoreAudio/PublicUtility \
-i /Applications/Xcode.app/Contents/Developer/Extras/CoreAudio/AudioUnits/AUPublic/Utility \
-i /Applications/Xcode.app/Contents/Developer/Extras/CoreAudio/AudioUnits/AUPublic/AUBase \
-i /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include \
-i /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include \
-i /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include \
-isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.8.sdk \
input.r
#/Users/atom/devel/ctrlr/Builds/Generated/Mac/AU/../../../../Juce/modules/juce_audio_plugin_client/AU/input.r
done