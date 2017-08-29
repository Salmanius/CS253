SRC = Main.cpp Image.h Image.cpp Reader.h Reader.cpp Cluster.cpp Cluster.h Perceptron.cpp Perceptron.h
OBJ = Main.o   Image.o           Reader.o            Cluster.o		   Perceptron.o
ANUM = PA10
CXX = g++
FLAGS = -Wall -I.
CLASS = CS253

.cpp.o: 
	$(CXX) $(FLAGS) -c $<

$(ANUM): $(OBJ)
	$(CXX) $(FLAGS) $(OBJ) -o $(ANUM)
	
clean: 
	rm -f *.o $(ANUM)
	
tar:
	tar -cvf $(ANUM).tar $(SRC) makefile
	
backup:
	mkdir -p ~/BACKUPS/$(CLASS)/$(ANUM)
	cp -f $(SRC) makefile ~/BACKUPS/$(CLASS)/$(ANUM)

test:
	PA10 trainingfiles.txt trainingfiles.txt 3 > output.txt
	diff output.txt correct.txt
	
