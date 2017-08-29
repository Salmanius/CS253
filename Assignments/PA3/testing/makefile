PA3: Main.o Histogram.o
	g++ -Wall -I. Main.o Histogram.o -o PA3
Main.o: Main.cpp Histogram.h
	g++ -Wall -I. -c Main.cpp
Histogram.o: Histogram.cpp Histogram.h
	g++ -Wall -I. -c Histogram.cpp

clean: 
	\rm *.o PA3
	
tar:
	tar -cvf PA3.tar Main.cpp Histogram.cpp Histogram.h makefile
	
backup:
	cp Main.cpp ~/BACKUPS/CS253/PA3 
	cp Histogram.h ~/BACKUPS/CS253/PA3
	cp Histogram.cpp ~/BACKUPS/CS253/PA3
	cp makefile ~/BACKUPS/CS253/PA3
