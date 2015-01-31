I=../../../../include
CPP=g++
CFLAGS= -g -c -Wall -I$(I)

all : opengl

opengl.o : ../opengl.cpp
	$(CPP) $(CFLAGS) ../opengl.cpp


opengl : opengl.o
	$(CPP) -lprcore opengl.o -o opengl


.PHONY : clean
clean: 
	rm *.o
	rm -rf $(EXE)
