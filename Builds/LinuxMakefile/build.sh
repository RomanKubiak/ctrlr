#!/bin/bash


if [ $# > 0 ]
then
    CONFIG="$1"
else
    cat <<EOF
usage $0 [Debug|Release]

Please specify the configuration to be built. It should be either Debug or Release.
EOF

MAXJOBS=`nproc`
echo "CTRLR[linux]: Building for $HOSTTYPE, JOBS $MAXJOBS"
#make -j$JOBS CONFIG=Release ARCH=$HOSTTYPE BINDIR=$BUILDDIR LIBDIR=$BUILDDIR OBJDIR=$BUILDDIR
make CONFIG=${CONFIG} -j${MAXJOBS} -f pchbuild.mk "$@"
if [ $? -ne 0 ]; then
	echo -e "CTRLR[linux]: build failed\n"
	exit 1
else
	echo -e "CTRLR[linux]: build succeeded\n"
	exit 0
fi
