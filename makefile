CPP=g++

CPP_FLAGS=-Wall -std=c++1y

all: alloc_demo

alloc_demo: main.o
	$(CPP) main.o -o alloc_demo

main.o: main.cpp simple_allocator.hpp
	$(CPP) $(CPP_FLAGS) -c main.cpp

clean:
	rm -rf *.i *.s *.o
