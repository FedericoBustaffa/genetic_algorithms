CXX = g++
CXXFLAGS = -Wall -std=c++17 -O3 -march=native

OBJECTS = main.o
TARGETS = genetic.x

all: $(TARGETS)

genetic.x: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

main.o: main.cpp

clean:
	rm -f $(OBJECTS) $(TARGETS)

recompile: clean all

