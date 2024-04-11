CXX = g++
CXXFLAGS = -Wall -std=c++17 -O3 -march=native

TARGETS = memo.x greedy.x

all: $(TARGETS)

memo.x: memo.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

greedy.x: greedy.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@


clean:
	rm -f $(OBJECTS) $(TARGETS)

recompile: clean all

