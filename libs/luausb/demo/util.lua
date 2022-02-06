module(... or 'test', package.seeall)

function bin2hex(bin)
	local hex = {}
	bin = {bin:byte(1,#bin)}
	for i=1,#bin do
		table.insert(hex, string.format("%X%X", math.floor(bin[i]/16), bin[i]%16))
	end
	return table.concat(hex)
end

function hex2bin(hex)
	local bin = {}
	for i=1,#hex/2 do
		table.insert(bin, string.char(tonumber("0X"..hex:sub(2*i-1, 2*i))))
	end
	return table.concat(bin)
end

local conversion = {}
conversion.b16b2 = {
	["0"] = "0000",
	["1"] = "0001",
	["2"] = "0010",
	["3"] = "0011",
	["4"] = "0100",
	["5"] = "0101",
	["6"] = "0110",
	["7"] = "0111",
	["8"] = "1000",
	["9"] = "1001",
	["a"] = "1010", ["A"] = "1010",
	["b"] = "1011", ["B"] = "1011",
	["c"] = "1100", ["C"] = "1100",
	["d"] = "1101", ["D"] = "1101",
	["e"] = "1110", ["E"] = "1110",
	["f"] = "1111", ["F"] = "1111",
}
conversion.b2b16 = {
	["0000"] = "0",
	["0001"] = "1",
	["0010"] = "2",
	["0011"] = "3",
	["0100"] = "4",
	["0101"] = "5",
	["0110"] = "6",
	["0111"] = "7",
	["1000"] = "8",
	["1001"] = "9",
	["1010"] = "A",
	["1011"] = "B",
	["1100"] = "C",
	["1101"] = "D",
	["1110"] = "E",
	["1111"] = "f",
}
conversion.b32b2 = {
	["a"] = "00000", ["A"] = "00000",
	["b"] = "00001", ["B"] = "00001",
	["c"] = "00010", ["C"] = "00010",
	["d"] = "00011", ["D"] = "00011",
	["e"] = "00100", ["E"] = "00100",
	["f"] = "00101", ["F"] = "00101",
	["g"] = "00110", ["G"] = "00110",
	["h"] = "00111", ["H"] = "00111",
	["i"] = "01000", ["I"] = "01000",
	["j"] = "01001", ["J"] = "01001",
	["k"] = "01010", ["K"] = "01010",
	["l"] = "01011", ["L"] = "01011",
	["m"] = "01100", ["M"] = "01100",
	["n"] = "01101", ["N"] = "01101",
	["o"] = "01110", ["O"] = "01110",
	["p"] = "01111", ["P"] = "01111",
	["q"] = "10000", ["Q"] = "10000",
	["r"] = "10001", ["R"] = "10001",
	["s"] = "10010", ["S"] = "10010",
	["t"] = "10011", ["T"] = "10011",
	["u"] = "10100", ["U"] = "10100",
	["v"] = "10101", ["V"] = "10101",
	["w"] = "10110", ["W"] = "10110",
	["x"] = "10111", ["X"] = "10111",
	["y"] = "11000", ["Y"] = "11000",
	["z"] = "11001", ["Z"] = "11001",
	["2"] = "11010",
	["3"] = "11011",
	["4"] = "11100",
	["5"] = "11101",
	["6"] = "11110",
	["7"] = "11111",
}
conversion.b2b32 = {
	["00000"] = "A",
	["00001"] = "B",
	["00010"] = "C",
	["00011"] = "D",
	["00100"] = "E",
	["00101"] = "F",
	["00110"] = "G",
	["00111"] = "H",
	["01000"] = "I",
	["01001"] = "J",
	["01010"] = "K",
	["01011"] = "L",
	["01100"] = "M",
	["01101"] = "N",
	["01110"] = "O",
	["01111"] = "P",
	["10000"] = "Q",
	["10001"] = "R",
	["10010"] = "S",
	["10011"] = "T",
	["10100"] = "U",
	["10101"] = "V",
	["10110"] = "W",
	["10111"] = "X",
	["11000"] = "Y",
	["11001"] = "Z",
	["11010"] = "2",
	["11011"] = "3",
	["11100"] = "4",
	["11101"] = "5",
	["11110"] = "6",
	["11111"] = "7",
}

function hex2base32(str)
	assert(#str % 5 == 0, "hex string must have a size multiple of 5")
	str = str:gsub(".", conversion.b16b2)
	str = str:gsub(".....", conversion.b2b32)
	return str
end

function base322hex(str)
	assert(#str % 4 == 0, "hex string must have a size multiple of 4")
	str = str:gsub(".", conversion.b32b2)
	str = str:gsub("....", conversion.b2b16)
	return str
end

function base322bin(value)
	return hex2bin(base322hex(value))
end

function bin2base32(value)
	return hex2base32(bin2hex(value))
end

function dumppair(table, file, level, k, v)
	local success,err
	success,err = file:write(("\t"):rep(level))
	if not success then return nil,err end
	local assignment = " = "
	if type(k)=='string' then
		if k:match("^[_a-zA-Z][_a-zA-Z0-9]*$") then
			success,err = file:write(k)
			if not success then return nil,err end
		else
			success,err = file:write(string.format('[%q]', k))
			if not success then return nil,err end
		end
	elseif type(k)=='number' then
		success,err = file:write('['..k..']')
		if not success then return nil,err end
	elseif type(k)=='nil' then
		-- we are in the array part
		assignment = ""
	else
		error("unsupported key type '"..type(k).."'")
	end
	success,err = file:write(assignment)
	if not success then return nil,err end
	if type(v)=='string' then
		success,err = file:write((string.format('%q', v):gsub("\t", "\\t"):gsub("\\\n", "\\n")))
		if not success then return nil,err end
	elseif type(v)=='number' then
		success,err = file:write(v)
		if not success then return nil,err end
	elseif type(v)=='boolean' then
		if v then
			success,err = file:write('true')
			if not success then return nil,err end
		else
			success,err = file:write('false')
			if not success then return nil,err end
		end
	elseif type(v)=='table' then
		success,err = file:write("{\n")
		if not success then return nil,err end
		success,err = dumptable(v, file, level+1)
		if not success then return nil,err end
		success,err = file:write(("\t"):rep(level).."}")
		if not success then return nil,err end
	else
		error("unsupported value type '"..type(v).."'")
	end
	success,err = file:write(",\n")
	if not success then return nil,err end
	return true
end

local function keycomp(a, b)
	local ta,tb = type(a),type(b)
	if ta==tb then
		return a < b
	else
		return ta=='string'
	end
end

local tsort = table.sort
local function dumptablesection(table, file, level, keys)
	-- sort keys
	local skeys = {}
	for k in pairs(keys) do skeys[#skeys+1] = k end
	tsort(skeys, keycomp)
	-- dump pairs
	for _,k in pairs(skeys) do
		local v = table[k]
		local success,err = dumppair(table, file, level, k, v)
		if not success then return nil,err end
	end
	return true
end

local function dumptableimplicitsection(table, file, level)
	for k,v in ipairs(table) do
		local success,err = dumppair(table, file, level, nil, v)
		if not success then return nil,err end
	end
	return true
end

function dumptable(table, file, level)
	assert(type(table)=='table', "dumptable can only dump tables")

	-- order of groups:
	-- - explicit keys
	--   - keys with simple values
	--   - keys with structure values (table with only explicit keys)
	--   - keys with mixed values (table with both exiplicit and implicit keys)
	--   - keys with array values (table with only implicit keys)
	-- - set part (explicit key with boolean value)
	-- - implicit keys
	-- order within a group:
	-- - string keys in lexicographic order
	-- - numbers in increasing order

	-- extract implicit keys
	local implicit = {}
	for k,v in ipairs(table) do
		implicit[k] = true
	end
	-- categorize explicit keys
	local set = {}
	local simples = {}
	local structures = {}
	local mixeds = {}
	local arrays = {}
	for k,v in pairs(table) do
		if not implicit[k] then
			if type(v)=='table' then
				if v[1]==nil then
					structures[k] = true
				else
					local implicit = {}
					for k in ipairs(v) do
						implicit[k] = true
					end
					local mixed = false
					for k in pairs(v) do
						if not implicit[k] then
							mixed = true
							break
						end
					end
					if mixed then
						mixeds[k] = true
					else
						arrays[k] = true
					end
				end
			else
				simples[k] = true
			end
		end
	end

	local success,err
	success,err = dumptablesection(table, file, level, simples)
	if not success then return nil,err end
	success,err = dumptablesection(table, file, level, structures)
	if not success then return nil,err end
	success,err = dumptablesection(table, file, level, mixeds)
	if not success then return nil,err end
	success,err = dumptablesection(table, file, level, arrays)
	if not success then return nil,err end
	success,err = dumptableimplicitsection(table, file, level)
	if not success then return nil,err end
	return true

	--[[
	local done = {}
	for k,v in ipairs(table) do
		local success,err = dumppair(table, file, level, nil, v)
		if not success then return nil,err end
		done[k] = true
	end
	for k,v in pairs(table) do
		if not done[k] then
			local success,err = dumppair(table, file, level, k, v)
			if not success then return nil,err end
			done[k] = true
		end
	end
	return true
	--]]
end

function dumptabletofile(table, filename, oldsuffix)
	local lfs = require 'lfs'
	if oldsuffix and lfs.attributes(filename, 'mode') then
		local i,suffix = 0,oldsuffix
		while io.open(filename..suffix, "rb") do
			i = i+1
			suffix = oldsuffix..i
		end
		assert(os.rename(filename, filename..suffix))
	end
	local err,file,success
	file,err = io.open(filename, "wb")
	if not file then return nil,err end
	success,err = file:write"return {\n"
	if not success then return nil,err end
	success,err = dumptable(table, file, 1)
	if not success then return nil,err end
	success,err = file:write"}\n"
	if not success then return nil,err end
	success,err = file:write("\n-- v".."i: encoding=utf-8\n")
	if not success then return nil,err end
	success,err = file:close()
	if not success then return nil,err end
	return true
end

function restorebackup(filename, suffix)
	local lfs = require 'lfs'
	local oldfilename = filename..suffix
	local i = 1
	while lfs.attributes(filename..suffix..i, 'mode') do
		oldfilename = filename..suffix..i
		i = i+1
	end
	assert(lfs.attributes(oldfilename, 'mode'))
	assert(os.remove(filename))
	assert(os.rename(oldfilename, filename))
end

function link(from, to)
	if from:find("'") then
		from = '"'..from:gsub("$", "\\$")..'"'
	else
		from = "'"..from.."'"
	end
	if to:find("'") then
		to = '"'..to:gsub("%$", "\\$")..'"'
	else
		to = "'"..to.."'"
	end
	assert(0==os.execute("ln -s "..from.." "..to))
end

function loadrecord(root, hash)
	local filename = root.."/"..hash..".lua"
	local success,record = pcall(dofile, filename)
	if not success then
		io.write'\n'
		local msg = "error while reading '"..filename.."': "..record
		print(msg)
		restorebackup(filename, ".old")
		return nil,msg
	elseif not record then
		io.write'\n'
		local msg = "error while reading '"..filename.."': no value returned"
		print(msg)
		restorebackup(filename, ".old")
		return nil,msg
	else
		return record
	end
end

function table.val_to_str ( v )
  if "string" == type( v ) then
	v = string.gsub( v, "\n", "\\n" )
	if string.match( string.gsub(v,"[^'\"]",""), '^"+$' ) then
	  return "'" .. v .. "'"
	end
	return '"' .. string.gsub(v,'"', '\\"' ) .. '"'
  else
	return "table" == type( v ) and table.tostring( v ) or
	  tostring( v )
  end
end

function table.key_to_str ( k )
  if "string" == type( k ) and string.match( k, "^[_%a][_%a%d]*$" ) then
	return k
  else
	return "[" .. table.val_to_str( k ) .. "]"
  end
end

function table.tostring( tbl )
  local result, done = {}, {}
  for k, v in ipairs( tbl ) do
	table.insert( result, table.val_to_str( v ) )
	done[ k ] = true
  end
  for k, v in pairs( tbl ) do
	if not done[ k ] then
	  table.insert( result,
		table.key_to_str( k ) .. "=" .. table.val_to_str( v ) )
	end
  end
  return "{" .. table.concat( result, "," ) .. "}"
end

if _NAME=='test' then
	local str = [[
return {
	Abc = false,
	FOO = 42,
	Foo = "42",
	abc = true,
	["f O"] = 42,
	fOO = 42,
	foo = "42",
	[-1] = 37,
	[0] = 37,
	[42] = 37,
	Bar = {
		foo = 142,
	},
	bar = {
		foo = 142,
	},
	Baz = {
		foo = 242,
		237,
	},
	baz = {
		foo = 242,
		237,
	},
	Baf = {
		337,
	},
	baf = {
		337,
	},
	37,
}

-- v]]..[[i: encoding=utf-8
]]
	local t = assert(loadstring(str))()

	local filename = os.tmpname()
	_M.dumptabletofile(t, filename)
	local file = assert(io.open(filename, "rb"))
	local content = assert(file:read"*a")
	assert(file:close())
--	print("=================================")
--	print(content)
--	print("=================================")
	assert(content==str, "tested string and dumped equivalent mismatch")
	print("all tests passed successfully")
end

function dist(a, b)
	return math.sqrt((a.x-b.x)^2 + (a.y-b.y)^2)
end

local pi,fmod,abs,atan2 = math.pi,math.fmod,math.abs,math.atan2

function angle(from, to)
	return atan2(to.y-from.y, to.x-from.x)
end

function angle_diff(angle1, angle2)
	local diff = fmod(angle1 - angle2, pi*2)
	if diff > pi then diff = diff - 2*pi end
	if diff <= -pi then diff = diff + 2*pi end
	return diff
end

function angle_match(angle1, angle2, max_diff)
	if not max_diff then max_diff = pi/2 end
	local diff = angle_diff(angle1, angle2)
	return abs(diff) <= max_diff
end

