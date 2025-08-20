CXX = g++
CXXFLAGS = -std=c++20 -Wall -Itests -Isrc
SUITE ?= 
SOURCES ?=

ttexport: ttexport.cpp src/timetree_task.h
	g++ ttexport.cpp src/timetree_task.cpp -o ttexport
	./ttexport

test: tests/doctest.h
	$(CXX) $(CXXFLAGS) $(SUITE) $(SOURCES) -o test_runner
	./test_runner

timetree_task:	src/timetree_task.h
	g++	src/timetree_task.cpp

clean:
	rm -f ./ttexport

clean-test:
	rm -f ./test_runner