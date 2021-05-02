#!/bin/bash
MAXJOBS=`nproc`
echo "CTRLR[linux]: Building for $HOSTTYPE, JOBS $MAXJOBS"
CFLAGS=""

if $(dpkg --compare-versions $(dpkg-query -f='${Version}' --show binutils-dev) gt 2.34); then
	CFLAGS="-DHAVE_BFD_2_34=1"
fi

eval CFLAGS=$CFLAGS CC=clang CXX=clang++ make V=1 CONFIG=Release -j$MAXJOBS "$@"

if [ $? -ne 0 ]; then
	echo -e "CTRLR[linux]: build failed\n"
	exit 1
else
	echo -e "CTRLR[linux]: build succeeded\n"
	exit 0
fi
