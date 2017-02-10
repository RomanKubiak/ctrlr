#!/bin/bash
HEADER="$1"

if [ ! -f "$HEADER" ]; then
	echo "Need the header as parameter"
	exit 1
fi

cat << _EOF_
#include "stdafx.h"
#include "LookAndFeelBase.h"
#include "LLookAndFeel.h"
#include "LookAndFeelParamWrapper.h"

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
			#printf ("[params] offset %d value [%s]\n", i, $i);
			rawParams[++numRawParams] = sprintf ("%s", $i);
			
			isReference 	= 0;
			
			if ($i == "const" && constNow == 0)
			{
				constNow = 1;
				continue;
			}
			
			if (constNow == 1)
			{
				if ($i == "const")
				{
					hack = 0;
					constNow = 0;
					continue;
				}
				else
				{
					hack = 1;
				}
			}
				
			param = i;			
			
			if (index($param, ","))
				$param = substr ($param, 0, index($param, ",") - 1);
				
			if (index($param, ")"))
				$param = substr ($param, 0, index($param, ")") - 1);
				
			if (index($param, "&"))
			{
				isReference = 1;
				$param = substr ($param, 2);
			}
			
			if (index($param, "*"))
			{
				$param = substr ($param, 2);
			}
			
			if (index($param, "<"))
				$param = substr ($param, 0, index($param, "<") - 1);
			
			
			if (hack)
			{
				if (! (i%2)) 
				{
					paramArray[++numParams] 	= param;
					paramRefArray[numParams] 	= isReference;
				}
			}
			else
			{
				if (i%2) 
				{
					paramArray[++numParams] 	= param;
					paramRefArray[numParams]	= isReference;
				}
			}			
		}
	}
	
	printf ("\n");
	
	printf ("%s LookAndFeelBase::%s(", returnType, methodName);
	
	for (x=1;x<=numRawParams;x++)
	{
		if (x == numRawParams || numRawParams == 0)
			printf ("%s", rawParams[x])
		else
			printf ("%s ", rawParams[x]);
	}
	
	if (numRawParams == 0)
	{
		printf (")");
	}
	
	printf ("\n{\n\tLookAndFeelParamWrapper p");
	
	if (numParams > 0)
	{
		printf ("(");
		for (x=1; x<=numParams; x++)
		{
			if (x == numParams || numParams == 0)
				printf ("%s", $paramArray[x]);
			else
				printf ("%s, ", $paramArray[x]);
		}
		printf (");\n");
	}
	else
	{
		printf (";\n");
	}
	if (needsToReturn)
		printf ("\treturn (owner.%s(p));\n", methodName);
	else
		printf ("\towner.%s(p);\n", methodName);
		
	printf ("}\n");	
}'

echo
