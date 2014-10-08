#!/bin/bash
HEADER="$1"

if [ ! -f "$HEADER" ]; then
	echo "Need the header as parameter"
	exit 1
fi

cat << _EOF_
#ifndef LOOK_AND_FEEL_BASE
#define LOOK_AND_FEEL_BASE

#include "CtrlrLuaManager.h"
#include "LookAndFeelParamWrapper.h"

class LLookAndFeel;

class LookAndFeelBase : public LookAndFeel_V3
{
	public:
		LookAndFeelBase(LLookAndFeel &_owner) : owner(_owner) {}
		LookAndFeel_V3 v3;
_EOF_

cat $HEADER | grep "def_" | awk '{
	constNow 	= 0;
	hack 		= 0;
	numParams	= 0;
	numRefParams	= 0;
	retTypeOffset  	= 2;
	funcNameOffset 	= 3;
	paramsOffset   	= 5;
	needsToReturn  	= 0;
	numRawParams	= 0;
	methodName	= "";
	returnType	= "";
	returnTypeStr	= "";
	
	for (i=1; i<=NF; i++)
	{
		if (i == retTypeOffset)
		{
			# Return type
			# printf ("[rettype] offset %d value %s\n", i, $i);
			if ($i == "const")
			{
				funcNameOffset++;
				paramsOffset++;
				needsToReturn = 1;
				returnType = sprintf ("const %s", $(i+1));
			}
			else if ($i != "void")
			{
				needsToReturn = 1;
				returnType = sprintf ("%s", $i);
			}
			else
			{
				needsToReturn = 0;
				returnType = sprintf ("void");
			}
			
			# printf ("returnType=%s funcNameOffset=%d\n", returnType, funcNameOffset);
		}
		
		if (i == funcNameOffset)
		{
			# printf ("[method] offset %d value %s\n", i, $i);
			methodName = sprintf ("%s", substr ($i,5));
			# printf ("methodName=%s\n", methodName);
		}
		if (i > paramsOffset)
		{
			printf ("\n[params] offset %d value [%s]\n", i, $i);
			
			param = i;
			
			if (index($param, ")"))
				$param = substr ($param, 0, index($param, ")") - 1);
				
			rawParams[++numRawParams] = sprintf ("%s", $param);
		}
	}
	
	printf ("\n");
	
	printf ("\t\t%s %s (", returnType, methodName);
	
	for (x=1;x<=numRawParams;x++)
	{
		if (x == numRawParams || numRawParams == 0)
			printf ("%s", rawParams[x])
		else
			printf ("%s ", rawParams[x]);
	}
	printf (");");
}'

echo -e "\n\n\tprivate:"
echo -e "\t\tLLookAndFeel &owner;"
echo "};"
echo
echo "#endif"