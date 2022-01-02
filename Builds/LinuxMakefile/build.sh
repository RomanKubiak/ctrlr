#!/bin/bash -e
set -x

if [ $# -gt 0 ]
then
    CONFIG="$1"
    shift
else
    cat <<EOF
usage $0 [Debug|Release]

Please specify the configuration to be built. It should be either `Debug' or `Release'.
EOF
fi

MAXJOBS=`nproc`
for i in "$@"
do
    case $i in
	CFLAGS=*|CXXFLAGS=*) $i
    esac
done


echo "CTRLR[linux]: Building for $HOSTTYPE, JOBS $MAXJOBS"
#make -j$JOBS CONFIG=Release ARCH=$HOSTTYPE BINDIR=$BUILDDIR LIBDIR=$BUILDDIR OBJDIR=$BUILDDIR
cmake ../../libs/luabind 
make CONFIG=${CONFIG} -j${MAXJOBS} -f pchbuild.mk "$@"
if [ $? -ne 0 ]; then
	echo -e "CTRLR[linux]: build failed\n"
	exit 1
else
    make CONFIG=${CONFIG} -j${MAXJOBS} -f pchbuild.mk savedbg
    echo -e "CTRLR[linux]: build succeeded\n"
    exit 0
fi

# Local Variables:
# compile-command: "LANG=C ./build.sh Debug Standalone"
# End:
