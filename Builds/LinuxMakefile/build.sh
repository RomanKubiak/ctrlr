#!/bin/bash
MAXJOBS=`cat /proc/cpuinfo | grep processor | wc -l`
echo "CTRLR[linux]: Building for $HOSTTYPE, JOBS $MAXJOBS"

if [ "$1" == "-f" ]; then
	echo "CTRLR[linux]: Compile PCH"
	echo "stadfx.h"
	g++  -w -std=c++14 -D "LINUX=1" -D "NDEBUG=1" \
		-D "JUCE_FORCE_DEBUG=0" -D "CTRLR_NIGHTLY=1" \
		-D "JucePlugin_Build_Standalone" -D "LUA_USE_LINUX" \
		-D "_LINUX=1" -D "JUCER_LINUX_MAKE_CC96CACF=1" \
		-I /usr/include -I /usr/include/freetype2 \
		-I ../../JuceLibraryCode \
		-I ../../JUCE/modules \
		-I ../../Source/Misc/boost -I ../../../../Source/Lua/luabind \
		-I ../../Source/Misc -I ../../../../Source/MIDI \
		-I ../../Source -I ../../../../Source/UIComponents \
		-I ../../Source/Core -I ../../../../Source/Plugin \
		-I ../../Source/Application \
		-I ../../Source/Misc/include \
		-I ../../Source/Misc/lua/include \
		-march=native -Os -fpermissive \
		-o "../../Source/Core/stdafx.h.gch" -c "../../Source/Core/stdafx.h"
	echo "stdafx_luabind.h"
	g++  -w -std=c++14 -D "LINUX=1" -D "NDEBUG=1" \
		-D "JUCE_FORCE_DEBUG=0" -D "CTRLR_NIGHTLY=1" \
		-D "JucePlugin_Build_Standalone" -D "LUA_USE_LINUX" \
		-D "_LINUX=1" -D "JUCER_LINUX_MAKE_CC96CACF=1" \
		-I /usr/include -I /usr/include/freetype2 \
		-I ../../JuceLibraryCode \
		-I ../../JUCE/modules \
		-I ../../Source/Misc/boost \
		-I ../../Source/Misc/luabind \
		-I ../../Source/Misc -I ../../../../Source/MIDI \
		-I ../../Source -I ../../../../Source/UIComponents \
		-I ../../Source/Core -I ../../../../Source/Plugin \
		-I ../../Source/Application \
		-I ../../Source/Misc/include \
		-I ../../Source/Misc/lua/include \
		-march=native -Os -fpermissive \
		-o "../../Source/Core/stdafx_luabind.h.gch" -c "../../Source/Core/stdafx_luabind.h"
else
	echo "CTRLR[linux]: PCH not rebuilt, use -f to force"
fi

echo "CTRLR[linux]: Build now"
echo
#make -j$JOBS CONFIG=Release ARCH=$HOSTTYPE BINDIR=$BUILDDIR LIBDIR=$BUILDDIR OBJDIR=$BUILDDIR
make CONFIG=Release -j$MAXJOBS
if [ $? -ne 0 ]; then
	echo -e "CTRLR[linux]: build failed\n"
	exit 1
else
	echo -e "CTRLR[linux]: build succeeded\n"
	exit 0
fi
