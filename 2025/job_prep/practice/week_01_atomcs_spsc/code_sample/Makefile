CXX := g++
CXXFLAGS := -std=c++17 -O2 -pthread -Wall -Wextra -pedantic

.PHONY: all clean ordering atomic_counter_tests

all: ordering atomic_counter_tests

ordering: ordering.cpp
	$(CXX) $(CXXFLAGS) -o ordering.exe ordering.cpp

atomic_counter_tests: atomic_counter_test.cpp atomic_counter.hpp
	$(CXX) $(CXXFLAGS) -o atomic_counter_tests.exe atomic_counter_test.cpp

clean:
	rm -f ordering.exe atomic_counter_tests.exe
