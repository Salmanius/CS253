SRC = Main.cpp Image.h Image.cpp Reader.h Reader.cpp Cluster.cpp Cluster.h
OBJ = Main.o   Image.o           Reader.o            Cluster.o
ANUM = PA5
CP = g++
FLAGS = -Wall -I.
CLASS = CS253

.cpp.o: 
	$(CP) $(FLAGS) -c $<

PA5: $(OBJ)
	$(CP) $(FLAGS) $(OBJ) -o $(ANUM)
	
clean: 
	rm -f *.o $(ANUM)
	
tar:
	tar -cvf $(ANUM).tar $(SRC) makefile
	
backup:
	mkdir -p ~/BACKUPS/$(CLASS)/$(ANUM)
	cp -f $(SRC) makefile ~/BACKUPS/$(CLASS)/$(ANUM)

	
