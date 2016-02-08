#include "encoding.h"
#include <stdio.h>
#include <stdlib.h>


void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for( i=0; i<size; i++ )
    {
        for( j=7; j>=0; j-- )
        {
            byte = b[i] & (1<<j);
            byte >>= j;
            printf("%u", byte);
        }
    }

    puts("");
}


int main(int argc, char** argv) {

	/* h2b test */
	char* hex = "4a2e432e";
	int hexlen = 8;
	int* binlen = (int*) malloc(sizeof(int)*1);
	unsigned char* bin = (unsigned char*) malloc(sizeof(char) * hexlen);
	if( !bin ) {
		printf("Memory allocation failed\n");
		exit(0);
	}
	
	h2b(hex, hexlen, bin, binlen);

	printBits(*binlen, bin);

	/* On 32 bit architecture, should produce: */
	char* expres = "0000010000001010000000100000111000000100000000110000001000001110";
	printf("Should equal: %s\n", expres);	

	free(bin);
	free(binlen);

	return 0;
} 



