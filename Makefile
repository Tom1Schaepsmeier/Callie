ttexport: ttexport.cpp src/tasks_author.cpp
	g++ ttexport.cpp src/tasks_author.cpp -o ttexport
	./ttexport

clean:
	rm -f ./ttexport