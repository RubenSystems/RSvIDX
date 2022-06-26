
COMPILER = g++
CXXFLAGS=-std=c++17 -fPIC

SOURCES=$(wildcard src/*.cpp)

all:
	$(COMPILER) $(CXXFLAGS) -shared -o bin/rsvidx.so Binding.cpp $(SOURCES)
