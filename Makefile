CXX = g++
CXXFLAGS = -Wall -std=c++17 -O3

HEADERS = genetic_algorithms.hpp genetic.hpp individual.hpp spawn.hpp selection.hpp crossover.hpp mutation.hpp replacement.hpp evaluation.hpp

TARGETS = knapsack.x tsp.x

all: $(TARGETS)

knapsack.x: knapsack.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) knapsack.cpp -o $@

tsp.x: tsp.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) tsp.cpp -o $@

clean:
	rm -f $(OBJECTS) $(TARGETS)

recompile: clean all

