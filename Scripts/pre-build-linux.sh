#!/bin/bash
#[atom@localhost Scripts]$ lsb_release -s -i
#Fedora
#[atom@localhost Scripts]$ lsb_release -s -r
#18
OSVER=`lsb_release -s -r`
OSNAME=`lsb_release -s -i`
STDCPP_PATH=`/sbin/ldconfig -p | grep libstdc++ | cut -f4 -d" "`
STDCPP_LINK=`ls -l $STDCPP_PATH | sed -n 's/.*-> //p'`

REVISION=`svn info . | grep Revision | awk '{print $2}'`
OS_VERSION="$OSNAME.$OSVER"
IDE_VERSION=`g++ -dumpversion`
SDK_NAME=${STDCPP_LINK#*.so.}

echo "Revision: $REVISION"
echo "OS: $OS_VERSION"
echo "IDE: $IDE_VERSION"
echo "SDK: $SDK_NAME"

REVISION_H=../Source/Core/CtrlrRevision.h
REVISION_T=../Source/Core/CtrlrRevision.template
REVISION_TEMP=/tmp/CtrlrRevision.template

cp $REVISION_T $REVISION_TEMP

sed -e 's/__IDE_VERSION__/'$IDE_VERSION'/g' -i $REVISION_TEMP
sed -e 's/__OS_VERSION__/'$OS_VERSION'/g' -i $REVISION_TEMP
sed -e 's/__SDK_COMPAT__/'$SDK_NAME'/g' -i $REVISION_TEMP
sed -e 's/__SDK_BASE__/'$SDK_NAME'/g' -i $REVISION_TEMP
sed -e 's/\$WCREV\$/'$REVISION'/g' -i $REVISION_TEMP

cat $REVISION_TEMP > $REVISION_H