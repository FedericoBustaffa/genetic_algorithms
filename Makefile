CXX = g++
CXXFLAGS = -Wall -std=c++17 -O3 -march=native

OBJECTS = memo_knapsack.o
TARGETS = memo_knapsack.x

all: $(TARGETS)

memo_knapsack.x: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

memo_knapsack.o: memo_knapsack.cpp

clean:
	rm -f $(OBJECTS) $(TARGETS)

recompile: clean all

