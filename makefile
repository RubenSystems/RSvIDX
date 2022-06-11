
COMPILER=clang++
CCFLAGS=-Wall

HEADERS=$(wildcard headers/*.hpp)
SOURCES=$(wildcard src/*.cpp)

all:
	$(COMPILER) -std=c++11 -shared -o bin/rsvidx.so Binding.cpp $(SOURCES)
