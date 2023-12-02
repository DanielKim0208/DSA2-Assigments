merge.exe: Mergechecker.o
	g++ -o merge.exe Mergechecker.o

Mergechecker.o: Mergechecker.cpp
	g++ -c Mergechecker.cpp

clean:
	rm -f *.exe *.o *.stackdump *~
	find . -name '*.txt' ! -name 'input.txt' -exec rm {} \;

