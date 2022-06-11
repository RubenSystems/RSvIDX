
C=gcc
CCFLAGS=-Wall
LDFLAGS=
SOURCES=$(wildcard src/*.c)

all:
	C -fPIC -shared config.h -o bin/rsvidx.so SOURCES observe.h transmit.h
