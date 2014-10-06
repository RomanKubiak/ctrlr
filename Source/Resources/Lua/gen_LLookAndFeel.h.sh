#!/bin/bash
HEADER="$1"

if [ ! -f "$HEADER" ]; then
	echo "Need the header as parameter"
	exit 1
fi

cat << _EOF_
#ifndef L_LOOK_AND_FEEL
#define L_LOOK_AND_FEEL

#include "LookAndFeelBase.h"

class LLookAndFeel : public LookAndFeelBase, public luabind::wrap_base
{
	public:
  		LLookAndFeel() : LookAndFeelBase(*this){}
	 	static void wrapForLua (lua_State *L);	 	
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
	
	printf ("\t\t%s %s ", returnType, methodName);
	
	printf ("(LookAndFeelParamWrapper &p)\n");
	if (needsToReturn)
	{
		printf ("\t\t{ try { return (call<%s>(\"%s\", p)); } catch (luabind::error e) { _WRN(\"%s \"+_STR(e.what())); return (LookAndFeelBase::v3.%s (", returnType, methodName, methodName, methodName);

		for (x=1; x<=numParams; x++)
		{
			if (x == numParams || numParams == 0)
				printf ("%sp.%s", paramRefArray[x] == 1 ? "*" : "", $paramArray[x]);
			else
				printf ("%sp.%s, ", paramRefArray[x] == 1 ? "*" : "", $paramArray[x]);
		}
		printf (")); } }");
	}
	else
	{
		printf ("\t\t{ try { call<void>(\"%s\", p); } catch (luabind::error e) { _WRN(\"%s \"+_STR(e.what())); } }", methodName, methodName);
	}
	
	printf ("\n");
	
	printf ("\t\tstatic %s def_%s", returnType, methodName);
	printf ("(LookAndFeelBase *ptr, LookAndFeelParamWrapper &p)\n");
	printf ("\t\t{ ");
	
	if (needsToReturn)
		printf ("return (ptr->LookAndFeelBase::v3.%s (", methodName);
	else
		printf ("ptr->LookAndFeelBase::v3.%s (", methodName);

	for (x=1; x<=numParams; x++)
	{
		if (x == numParams || numParams == 0)
			printf ("%sp.%s", paramRefArray[x] == 1 ? "*" : "", $paramArray[x]);
		else
			printf ("%sp.%s, ", paramRefArray[x] == 1 ? "*" : "", $paramArray[x]);
	}
	
	if (needsToReturn)
		printf (")");
		
	printf ("); }");	
	printf ("\n");
}'

echo
echo "};"
echo
echo "#endif"