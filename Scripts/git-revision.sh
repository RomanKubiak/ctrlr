#!/bin/bash
projecttag=`git describe --tags --long | cut -f1 -d'-'`
revisioncount=`git log "$projecttag".. --oneline | wc -l | tr -d ' '`
echo "$projecttag.$revisioncount"
