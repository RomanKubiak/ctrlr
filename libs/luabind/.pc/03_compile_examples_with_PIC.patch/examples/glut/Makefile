all: glutbind_test

# if using fink on darwin
# you need these additional flags
CPPFLAGS = -I/sw/include -L/sw/lib

glutbind_test: glut_bind.cpp
	$(CXX) glut_bind.cpp -o glut_bind $(CPPFLAGS) \
	-I/usr/include/lua5.2 -I/usr/include/boost \
	-llua5.2 -lluabind -lGL -lGLU -lglut

clean:
	rm -f glut_bind *.o *~
