CC=g++
CFLAGS=-c -Wall

all: clean run.o smartarray.o smartobject.o smartpointer.o
	$(CC) run.o smartarray.o smartobject.o smartpointer.o

run.o: run.cpp
	$(CC) $(CFLAGS) run.cpp

smartarray.o: smartarray.cpp smartarray.h
	$(CC) $(CFLAGS) smartarray.cpp

smartobject.o: smartobject.cpp smartobject.h
	$(CC) $(CFLAGS) smartobject.cpp

smartpointer.o: smartpointer.cpp smartpointer.h
	$(CC) $(CFLAGS) smartpointer.cpp

clean:
	rm -f run.o smartarray.o smartobject.o smartpointer.o a.out
