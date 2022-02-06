all: regexp_test

# if using fink on darwin
# you need these additional flags
CPPFLAGS = -I/sw/include -L/sw/lib

regexp_test: regex_wrap.cpp
	$(CXX) regex_wrap.cpp -o regex_wrap $(CPPFLAGS) \
	-I/usr/include/lua5.2 -I/usr/include/boost -fPIC \
	-llua5.2 -lluabind -lboost_regex

clean:
	rm -f regex_wrap *.o *~
