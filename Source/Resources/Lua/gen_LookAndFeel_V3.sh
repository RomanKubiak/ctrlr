#!/bin/bash
HEADER="$1"

if [ ! -f "$HEADER" ]; then
	echo "Need the header as parameter"
	exit 1
fi

cat $HEADER | grep "def_" | awk '{
	constNow = 0
	hack = 0
	
	retTypeOffset  = 2;
	funcNameOffset = 3;
	paramsOffset   = 5;
	
	for (i=1; i<=NF; i++)
	{
		if (i == retTypeOffset)
		{
			# Return type
			if ($i == "const")
			{
				funcNameOffset++;
				paramsOffset++;
			}
				
			if ($i == "void")
				printf ("function ");
			else
				printf ("function ");
		}
		
		if (i == funcNameOffset)
		{
			# Function name
			printf ("__method_name:%s (", substr ($i,5));
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
			
			if (hack)
			{
				if (! (i%2)) printf ("%s", (i == NF ? $param : $param", ")); else printf ("--[[%s]] ", $param);
			}
			else
			{
				if (i%2) printf ("%s", (i == NF ? $param : $param", ")); else printf ("--[[%s]] ", $param);
			}
		}
	}
	
	printf (")\n\t-- Body\nend\n\n");
}'
