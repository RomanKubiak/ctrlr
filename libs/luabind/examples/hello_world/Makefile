all: helloworld_test

# if using fink on darwin
# you need these additional flags
CPPFLAGS = -I/sw/include -L/sw/lib

helloworld_test: hello_world.cpp
	$(CXX) -shared hello_world.cpp -o hello_world.so $(CPPFLAGS) \
	-I/usr/include/lua5.2 -I/usr/include/boost -fPIC \
	-llua5.2 -lluabind

clean:
	rm -f helloworld *.o *~
