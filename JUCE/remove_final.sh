#!/bin/bash

IFS="
"
FILES=`grep -oR "^class.*final" modules/* | awk -F: '{print $1}'`

for i in $FILES; do
	echo $i
	sed -i 's/final//g' $i
done
