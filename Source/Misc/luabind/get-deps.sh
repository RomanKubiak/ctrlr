#!/bin/sh

set -ex
LUAV="$1"

curl -o lua-$LUAV.tar.gz https://www.lua.org/ftp/lua-$LUAV.tar.gz 
tar xzf lua-$LUAV.tar.gz
cd lua-$LUAV
if [ "$2" = "cxx" ]; then
    if [ -d cxx ]; then
        rm -r cxx
    fi
    mkdir cxx
    make clean
    make linux CC=g++ MYCFLAGS="-DLUA_USE_APICHECK -g"
    mv src/lua src/luac src/liblua.a cxx/
    cp src/lua.h src/luaconf.h src/lauxlib.h src/lualib.h cxx/
fi
make clean
make linux MYCFLAGS="-DLUA_USE_APICHECK -g"
