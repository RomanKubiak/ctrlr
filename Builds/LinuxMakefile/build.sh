#!/bin/bash
MAXJOBS=`nproc`
echo "CTRLR[linux]: Building for $HOSTTYPE, JOBS $MAXJOBS"
CFLAGS=""

if command -v dpkg >/dev/null; then
	echo "dpkg found"
	if $(dpkg --compare-versions $(dpkg-query -f='${Version}' --show binutils-dev) gt 2.34); then
		echo "libbfd 2.34 or newer found"
		CFLAGS="-DHAVE_BFD_2_34=1"
	fi
elif command -v rpm >/dev/null; then
	echo "rpm found"
	if rpm -q --qf '%{Version}' binutils-devel | awk -F . '{ exit ($1 >= 2 && $2 >= 34) ? 0 : 1 }'; then
		echo "libbfd 2.34 or newer found"
		CFLAGS="-DHAVE_BFD_2_34=1"
	fi
fi

eval CFLAGS=$CFLAGS CC=clang CXX=clang++ make V=1 CONFIG=Release -j$MAXJOBS "$@"

if [ $? -ne 0 ]; then
	echo -e "CTRLR[linux]: build failed\n"
	exit 1
else
	echo -e "CTRLR[linux]: build succeeded\n"
	exit 0
fi
