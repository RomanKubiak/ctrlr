#!/bin/bash
HEADER="$1"

if [ ! -f "$HEADER" ]; then
	echo "Need the header as parameter"
	exit 1
fi

echo "class '__method_name' (LookAndFeel)"
echo
echo "function __method_name:__init()"
echo -e "\t--"
echo -e "\t-- This is needed for luabind, please don't remove this line"
echo -e "\t-- Add as much code as you like here, just leave this"
echo -e "\t--"
echo -e "\tLookAndFeel.__init(self)"
echo "end"
echo

cat $HEADER | grep "def_" | awk '{
	constNow = 0
	hack = 0
	numParams	= 0;
	retTypeOffset  	= 2;
	funcNameOffset 	= 3;
	paramsOffset   	= 5;
	needsToReturn  	= 0;
	
	for (i=1; i<=NF; i++)
	{
		if (i == retTypeOffset)
		{
			# Return type
			if ($i == "const")
			{
				funcNameOffset++;
				paramsOffset++;
				needsToReturn = 1;
				returnType = i+1;
			}
			else if ($i != "void")
			{
				needsToReturn = 1;
				returnType = i;
			}
				
			printf ("-- function ");
		}
		
		if (i == funcNameOffset)
		{
			# Function name
			methodName = substr ($i,5);
			printf ("__method_name:%s (--[[ ", methodName);
		}
		
		if (i > paramsOffset)
		{
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
					printf ("p.%s", (i == NF ? $param : $param", ")); 
				}
				else 
				{
					printf ("%s ", $param);
				}
			}
			else
			{
				if (i%2) 
				{
					paramArray[++numParams] = param;
					printf ("p.%s", (i == NF ? $param : $param", ")); 
				}
				else 
				{
					printf ("%s ", $param);
				}
			}
						
		}
	}
	
	printf (" --]] p)\n");

	if (needsToReturn == 1)
	{	
		printf ("--\t return %s\n", $returnType);
	}
			
	printf ("-- end\n\n");
}'
