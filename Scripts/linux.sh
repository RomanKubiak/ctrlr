#!/bin/bash

REVISION=`git log -1 | grep commit | awk '{print $2}' | tail -c 8`
ARCH=`uname -m`
PACKAGE="installers/Ctrlr_"$REVISION".sh"

echo Create the package
rm -rf installers/Ctrlr
rm -f $PACKAGE
mkdir -p installers/Ctrlr

echo Copy binaries
cp ../Bin/Ctrlr* installers/Ctrlr/

echo Copy Panels
cp -r ../Panels installers/Ctrlr/

echo Copy Doc
cp -r ../Doc installers/Ctrlr/

echo Makeself
./installers/makeself.sh --bzip2 --notemp installers/Ctrlr $PACKAGE "Ctrlr"

echo "Copy to Ctrlr"
scp $PACKAGE ctrlrorg@ctrlr.org:/home/ctrlrorg/public_html/nightly/
