
COMPILER = g++
CXXFLAGS=-Wall -std=c++11 -fPIC

SOURCES=$(wildcard src/*.cpp)

all:
	$(COMPILER) -std=c++11 -shared -o bin/rsvidx.so Binding.cpp $(SOURCES)
