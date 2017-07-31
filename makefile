CXX=g++
CXXFLAGS=-std=c++11
LDFLAGS=
LDLIBS=

SRCDIR=src/
BINDIR=bin/
SRCS=src/compiler.cpp src/lexer.cpp

all: compiler

compiler:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(BINDIR)compiler

clean:
	rm -rf $(BINDIR)