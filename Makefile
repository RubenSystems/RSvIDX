
COMPILER = g++
CXXFLAGS=-std=c++17 -fPIC

SOURCES=$(wildcard src/*.cpp)

all:
	$(COMPILER) $(CXXFLAGS) -shared -O2 -o bin/rsvidx_build.so binding.cpp $(SOURCES)

clean:
	rm bin/rsvidx_build.so
