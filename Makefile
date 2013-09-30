all : robolearn

pokeranch : training.o ann.o robolearn.o

training.o : training.cpp
	g++ -c training.cpp
    
ann.o : ann.cpp
	g++ -c ann.cpp
    
robolearn.o : robolearn.cpp
	g++ -c robolearn.cpp

run:
	./robolearn
    
clean:
	rm -rf robolearn *.o *.exe *.h.gch