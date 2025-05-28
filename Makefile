CXX = g++
CXXFLAGS = -std=c++17 -Wall -Itests -Isrc
SUITE ?= 
SOURCES ?=

ttexport: ttexport.cpp src/tasks_author.cpp
	g++ ttexport.cpp src/tasks_author.cpp -o ttexport
	./ttexport

test: tests/doctest.h
	$(CXX) $(CXXFLAGS) $(SUITE) $(SOURCES) -o test_runner
	./test_runner

clean:
	rm -f ./ttexport

clean-test:
	rm -f ./test_runner