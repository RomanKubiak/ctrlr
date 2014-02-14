#!/bin/bash
BUILDDIR=../build/$HOSTTYPE
JOBS=`cat /proc/cpuinfo  | grep processor | wc -l`
echo "Building for $HOSTTYPE"

echo "Compile PCH"
if [ ! -f ../../../../Source/Core/stdafx.h.gch ]; then
	g++  -D "LINUX=1" -D "NDEBUG=1" -D "JUCE_FORCE_DEBUG=0" -D "CTRLR_NIGHTLY=1" -D "JucePlugin_Build_Standalone" -D "LUA_USE_LINUX" -D "_LINUX=1" -D "JUCER_LINUX_MAKE_CC96CACF=1" -I /usr/include -I /usr/include/freetype2 -I ../../../Standalone/JuceLibraryCode -I ../../../../Boost -I ../../../../Source/Lua/luabind -I ../../../../Source/Misc -I ../../../../Source/MIDI -I ../../../../Source -I ../../../../Source/UIComponents -I ../../../../Source/Core -I ../../../../Source/Plugin -I ../../../../Source/Application -I ../../../../Source/Lua -I ../../../../Source/Lua/lua -march=native -Os -fpermissive -o "../../../../Source/Core/stdafx.h.gch" -c "../../../../Source/Core/stdafx.h"
fi

echo "Remove the shared source, for main() compatibility"
rm -f ../build/$HOSTTYPE/CtrlrStandaloneApplication*

echo "Build now"
time make -j$JOBS CONFIG=Release_Nightly ARCH=$HOSTTYPE BINDIR=$BUILDDIR LIBDIR=$BUILDDIR OBJDIR=$BUILDDIR