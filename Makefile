all:
	make sources && make clean

sources:	cpp/*.cpp cpp/*.h
	mkdir -p build
	cd build && g++ ../cpp/main.cpp -o ../main

clean:
	rm -fr build
