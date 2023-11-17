interface.exe: interface.o graph.o heap.o hash.o
	g++ -o interface.exe interface.o graph.o heap.o hash.o

interface.o: interface.cpp
	g++ -c interface.cpp
    
graph.o: graph.cpp graph.h heap.h
	g++ -c graph.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~
