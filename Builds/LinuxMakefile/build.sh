#!/bin/bash
MAXJOBS=`nproc`
echo "CTRLR[linux]: Building for $HOSTTYPE, JOBS $MAXJOBS"
#make -j$JOBS CONFIG=Release ARCH=$HOSTTYPE BINDIR=$BUILDDIR LIBDIR=$BUILDDIR OBJDIR=$BUILDDIR
#make CONFIG=Release -j $MAXJOBS -f pchbuild.mk "$@"
make CONFIG=Release -j$MAXJOBS "$@"
if [ $? -ne 0 ]; then
	echo -e "CTRLR[linux]: build failed\n"
	exit 1
else
	echo -e "CTRLR[linux]: build succeeded\n"
	exit 0
fi
