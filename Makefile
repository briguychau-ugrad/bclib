CC=g++
CFLAGS=-c -Wall

all: clean run.o smartobject.o smartpointer.o
	$(CC) run.o smartobject.o smartpointer.o

run.o: run.cpp
	$(CC) $(CFLAGS) run.cpp

smartobject.o: smartobject.cpp smartobject.h
	$(CC) $(CFLAGS) smartobject.cpp

smartpointer.o: smartpointer.cpp smartpointer.h
	$(CC) $(CFLAGS) smartpointer.cpp

clean:
	rm -f run.o smartobject.o smartpointer.o a.out
