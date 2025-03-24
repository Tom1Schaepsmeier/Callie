CXX = g++
CXXFLAGS = -std=c++17 -Wall -Itests

ttexport: ttexport.cpp src/tasks_author.cpp
	g++ ttexport.cpp src/tasks_author.cpp -o ttexport
	./ttexport

test: tests/doctest.h
	$(CXX) $(CXXFLAGS) $(SUITE) -o test_runner
	./test_runner

clean:
	rm -f ./ttexport

clean-test:
	rm -f ./test_runner