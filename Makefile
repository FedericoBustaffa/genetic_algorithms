CXX = g++
CXXFLAGS = -Wall -std=c++17 -O3

TARGETS = memo.x greedy.x genetic.x

all: $(TARGETS)

memo.x: memo.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

greedy.x: greedy.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

genetic.x: main.cpp genetic_algorithms.hpp genetic.hpp individual.hpp spawn.hpp selection.hpp crossover.hpp mutation.hpp replacement.hpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(OBJECTS) $(TARGETS)

recompile: clean all

