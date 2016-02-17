CC=gcc
CFLAGS=-c -Wall -g
INC=-I../../Utility/C
LIBS=-L../../Utility/C

all: test

test: base64.o test.o
	$(CC) $(INC) $(LIBS) base64.o test.o -o test -lutility	

base64.o: base64.c
	$(CC) $(INC) $(CFLAGS) base64.c

test.o: test.c
	$(CC) $(INC) $(CFLAGS) test.c

clean:
	rm *.o
	rm test