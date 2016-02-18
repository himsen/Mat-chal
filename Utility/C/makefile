CC=gcc
CFLAGS=-c -Wall -g

all: testencoding

testencoding: encoding.o testencoding.o
	$(CC) encoding.o testencoding.o -o testencoding
	$(CC) -dynamiclib -o libutility.dylib encoding.o
	cp ./libutility.dylib ./../../Set1/C

encoding.o: encoding.c
	$(CC) $(CFLAGS) encoding.c

testencoding.o: testencoding.c
	$(CC) $(CFLAGS) testencoding.c

clean:
	rm *.o
	rm testencoding
