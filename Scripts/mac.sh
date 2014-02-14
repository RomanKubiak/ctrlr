#!/bin/bash
REVISION=`svn info | grep Revision | awk '{print $2}'`
FILELIST="../Bin/Ctrlr.app ../Bin/Ctrlr.vst ../Bin/Ctrlr.component ../Panels ../Doc"
TDMG_SRC="installers/Ctrlr_template.dmg"
TDMG_MOUNT="/Volumes/Ctrlr"
TDMG_TMP="/tmp/Ctrlr_temp.dmg"
TDMG_DST="/tmp/Ctrlr_$REVISION.dmg"

if [ -e $TDMG_TMP ]; then
	umount /Volumes/Ctrlr 2>/dev/null
	rm -f $TDMG_TMP
fi

echo "Unpack template to $TDMG_TMP"
if [ ! -e $TDMG_SRC.bz2 ]; then
	echo -ne "\t FAILED $TDMG_SRC.bz2 does not exit\n"
	exit 1
fi

bzip2 -d $TDMG_SRC.bz2 -c > $TDMG_TMP	
if [ $? -ne 0 ]; then
	echo -ne "\t FAILED\n"
else
	echo -ne "\t DONE $TDMG_TMP\n"
fi
echo

echo "Resize $TDMG_TMP"
hdiutil resize -size 300m $TDMG_TMP
if [ $? -ne 0 ]; then
	echo -ne "\t FAILED\n"
else
	echo -ne "\t DONE\n"
fi
echo

echo "Mount $TDMG_TMP"
DEV=`hdiutil attach -readwrite -noverify -noautoopen $TDMG_TMP | tail -n 1 | grep "/dev/disk" | awk '{print $1}'`
if [ $? -ne 0 ]; then
	echo -ne "\t FAILED\n"
	exit 1
else
	echo -ne "\t DONE ($DEV)\n"
fi
echo

echo "Copy to template"
for f in $FILELIST; do
	cp -r $f /Volumes/Ctrlr/
done
	
echo "Unmount"
umount /Volumes/Ctrlr

if [ $? -ne 0 ]; then
	echo -ne "\t FAILED\n"
	exit 1
fi
echo

echo "Kill diskimage helpers"
PID=`lsof /tmp/Ctrlr_temp.dmg | tail -n 1 | awk '{print $2}'`
if [ $PID != "" ]; then
	kill -9 $PID
	echo -ne "\t DONE\n"
fi
echo

echo "Compact $TDMG_TMP to $TDMG_DST"
rm -f $TDMG_DST
hdiutil convert $TDMG_TMP -format UDBZ -o $TDMG_DST
if [ $? -ne 0 ]; then
	echo -ne "\t FAILED\n"
	exit 1
fi

echo "Copy to Ctrlr"
scp $TDMG_DST ctrlrorg@ctrlr.org:/home/ctrlrorg/public_html/nightly/
