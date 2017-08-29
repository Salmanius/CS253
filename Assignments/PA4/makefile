PA4: Main.o Reader.o Image.o
	g++ -Wall -I. Main.o Reader.o Image.o -o PA4
Main.o: Main.cpp Reader.h Image.h
	g++ -Wall -I. -c Main.cpp
Reader.o: Reader.cpp Reader.h
	g++ -Wall -I. -c Reader.cpp
Image.o: Image.cpp Image.h
	g++ -Wall -I. -c Image.cpp

clean: 
	rm *.o PA4
	
tar:
	tar -cvf PA4.tar Main.cpp Image.h Image.cpp Reader.h Reader.cpp makefile
	
backup:
	cp Main.cpp ~/BACKUPS/CS253/PA4 
	cp Image.h ~/BACKUPS/CS253/PA4
	cp Image.cpp ~/BACKUPS/CS253/PA4
	cp Reader.h ~/BACKUPS/CS253/PA4
	cp Reader.cpp ~/BACKUPS/CS253/PA4
	cp makefile ~/BACKUPS/CS253/PA4
