#!/bin/bash
cat << _EOF_
	static void wrapForLua (lua_State *L)
	{
		using namespace luabind;
		module(L)
		[
			class_<LookAndFeelParamWrapper>("LookAndFeelParamWrapper")
_EOF_

cat $1 | awk '{
	for (i=1; i<=NF; i++)
	{
		if (index($i, ";"))
		{
			param = sprintf ("%s", substr ($i, 0, index($i,";")-1));		
			
			if (index ($param, "*"))
				param = sprintf ("%s", substr (param, 2));
				
			printf ("\t\t\t\t.def_readonly (\"%s\", &LookAndFeelParamWrapper::%s)\n", param, param);
		}
	}
}'

echo -e "\t\t\t];"
echo -e "\t\t}"