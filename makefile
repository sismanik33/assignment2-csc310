INCLUDE_DIRS	:= 	/home/cicmanec/csc310/assignment2-csc310/headerFiles
CC				:= 	g++
CCFLAGS			:= 	-g -I$(INCLUDE_DIRS)
OBJECTS			:=	rbTree.o myException.o

assignment2: main.cpp $(OBJECTS)
	$(CC) -o $@ $^ $(CCFLAGS)

rbTree.o: rbTree.cpp $^
	$(CC) -c -o $@ $< $(CCFLAGS)

myException.o: myException.cpp $^
	$(CC) -c -o $@ $< $(CCFLAGS)

clean:
	rm *.o assignment2