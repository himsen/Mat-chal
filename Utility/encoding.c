#include <stdio.h>
#include <stdlib.h>
#include "encoding.h"

/*
* Converts hex encoded data (hex)
* of length hexlen, into binary (bin)
* of length binlen.
* Caller has the responsibility of freeing memory.
*/
void h2b(char* hex, int hexlen, unsigned char** bin, int** binlen) {

	*binlen = (int*) malloc(sizeof(int) * 1);
	if( !(*binlen) ) {
		printf( "Memory allocation failed\n" );
		exit(0);
	}
	**binlen = hexlen;	
	*bin = (unsigned char*) malloc(sizeof(char) * hexlen);
	if( !(*bin) ) {
		printf( "Memory allocation failed\n" );
		exit(0);
	}

	int i;
	char temp;
	for(i = 0; i < hexlen; i++) {
		
		temp = *(hex + i);
		if( '0' <= temp && temp <= '9' ) {
			*(*bin + i) = temp - '0';
		}
		else if( 'A' <= temp && temp <= 'F' ) {
			*(*bin + i) = temp - 'A' + 10;
		}
		else {
			*(*bin + i) = temp - 'a' + 10;
		}
	}
}


void base64_encode(unsigned char* bin, int binlen, char* b64, int* b64len) {



}


void base64_decode() {}
