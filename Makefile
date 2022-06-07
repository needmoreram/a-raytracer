SOURCES = $(wildcard *.cc)
PROGRAMS = $(patsubst %.cc,%,$(SOURCES))

CXXFLAGS = -std=c++20 -Wall

all: $(PROGRAMS)

%: %.cc
	g++ $(CXXFLAGS) -o $@ $<
