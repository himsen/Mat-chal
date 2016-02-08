#include <stdio.h>
#include <stdlib.h>
#include "encoding.h"

/*
* Converts hex encoded data (hex)
* of length hexlen, into binary (bin)
* of length binlen.
*/
void h2b(char* hex, int hexlen, unsigned char* bin, int* binlen) {

	*binlen = hexlen;	

	int i;
	char temp;
	for(i = 0; i < hexlen; i++) {
		
		temp = *(hex + i);
		if( '0' <= temp && temp <= '9' ) {
			*(bin + i) = temp - '0';
		}
		else if( 'A' <= temp && temp <= 'F' ) {
			*(bin + i) = temp - 'A' + 10;
		}
		else {
			*(bin + i) = temp - 'a' + 10;
		}
	}
}


void base64_encode(unsigned char* bin, int binlen, char* b64, int* b64len) {



}


void base64_decode() {}
