#!/bin/bash

FILES=`find JUCE/modules/ -name "*.h"`

for file in $FILES; do
	echo $file;
	sed -i -e 's/final//' $file
done

