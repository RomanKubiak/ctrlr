LUA_VERSION?=5.3

PREFIX?=/usr
INSTALL_LUA=$(PREFIX)/share/lua/$(LUA_VERSION)
INSTALL_BIN=$(PREFIX)/lib/lua/$(LUA_VERSION)
CPPFLAGS+=-Wall -Wextra -Werror -O2
CFLAGS+=-fvisibility=hidden

CPPFLAGS+=-I/usr/include/libusb-1.0 "-DLUAUSB_API=__attribute__((visibility(\"default\")))"
CFLAGS+=-fPIC
LDLIBS+=-lusb-1.0

build:usb.so

clean:
	rm -f usb.so *.o

cleandist:clean
	rm -f enums.c enums.h structs.c structs.h

install:build
	install -d $(INSTALL_BIN)
	install *.so $(INSTALL_BIN)

usb.so: CPPFLAGS+=-Dluaopen_module=luaopen_usb

%.so: %.c
	$(LINK.c) -shared $^ $(LOADLIBES) $(LDLIBS) -o $@

usb.so:enums.o structs.o compat.o

usb.c:enums.h structs.h

structs.c enums.c enums.h structs.h:gen.lua
	lua gen.lua

.PHONY:build clean cleandist pureinstall install

# Copyright (c) Jérôme Vuarand
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
