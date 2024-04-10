CXX = g++
CXXFLAGS = -Wall -std=c++17 -O3 -march=native

OBJECTS = knapsack.o
TARGETS = knapsack.x

all: $(TARGETS)

knapsack.x: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

knapsack.o: knapsack.cpp

clean:
	rm -f $(OBJECTS) $(TARGETS)

recompile: clean all

