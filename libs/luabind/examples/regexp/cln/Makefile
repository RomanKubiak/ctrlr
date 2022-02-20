all: cln_test

cln_test: cln_test.cpp
	$(CXX) cln_test.cpp -o cln_test \
	-I/usr/include/lua5.2 -I/usr/include/boost \ 
	-lluabind -llua -llualib -lcln

clean:
	rm -f cln_test *.o *~
