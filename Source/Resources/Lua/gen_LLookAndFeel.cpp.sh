#!/bin/bash
HEADER="$1"

if [ ! -f "$HEADER" ]; then
	echo "Need the header as parameter"
	exit 1
fi

cat << _EOF_
#include "stdafx.h"
#include "LLookAndFeel.h"

void LLookAndFeel::wrapForLua (lua_State *L)
{
	using namespace luabind;	
	module(L)
	[			
		class_<LookAndFeelBase, LLookAndFeel>("LookAndFeel")					
			.def(constructor<>())
_EOF_

cat $HEADER | grep "def_" | awk '{
	constNow 	= 0;
	hack 		= 0;
	numParams	= 0;
	retTypeOffset  	= 2;
	funcNameOffset 	= 3;
	paramsOffset   	= 5;
	needsToReturn  	= 0;
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
			# printf ("[params] offset %d value %s\n", i, $i);
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
				$param = substr ($param, 2);
				
			if (index($param, "<"))
				$param = substr ($param, 0, index($param, "<") - 1);
			
			if (hack)
			{
				if (! (i%2)) 
				{
					paramArray[++numParams] = param;
					# printf ("p.%s", (i == NF ? $param : $param", ")); 
				}
				else 
				{
					# printf ("%s ", $param);
				}
			}
			else
			{
				if (i%2) 
				{
					paramArray[++numParams] = param;
					# printf ("p.%s", (i == NF ? $param : $param", ")); 
				}
				else 
				{
					# printf ("%s ", $param);
				}
			}
						
		}
	}
	
	printf ("\t\t\t.def (\"%s\", &LLookAndFeel::%s, &LLookAndFeel::def_%s)", methodName, methodName, methodName);
	
	printf ("\n");
}'

echo -e "\t];"
echo
echo "}"