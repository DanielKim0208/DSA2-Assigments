dijkstra.exe: dijkstra.o heap.o hash.o
	g++ -o  dijkstra.exe dijkstra.o heap.o hash.o

dijkstra.o: dijkstra.cpp dijkstra.h heap.h
	g++ -c dijkstra.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~
