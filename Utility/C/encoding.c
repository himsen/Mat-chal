#include <stdio.h>
#include <stdlib.h>
#include "encoding.h"

/*
* Converts hex characters (hex)
* of length hexlen, into binary (bin)
* of length binlen.
* Caller has the responsibility of freeing memory.
*/
void hc2b(char* hex, int hexlen, unsigned char** bin, int** binlen) {

	//Allocate memory for output buffer length.
	*binlen = (int*) malloc(sizeof(int) * 1);
	if( !(*binlen) ) {
		printf( "Memory allocation failed\n" );
		exit(0);
	}
	**binlen = hexlen;	
	
	//Allocate memory for output buffer.
	*bin = (unsigned char*) malloc(sizeof(char) * (**binlen));
	if( !(*bin) ) {
		printf( "Memory allocation failed\n" );
		exit(0);
	}

	int i;
	char temp;
	for(i = 0; i < hexlen; i++) {
		
		//Takes each hex charecter and converts to its numeric value.
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
//ADD ERROR FILE, ADD PRINT FILE, ADD HEADER FILES


/*
*	Converts a hex character to its numeric value.
*/
int h2int(char hex) {

	if( '0' <= hex && hex <= '9' ) {
		return hex - '0';
	}
	else if( 'A' <= hex && hex <= 'F' ) {
		return hex - 'A' + 10;
	}
	else {
		return hex - 'a' + 10;
	}

}


/* 
*	Converts hex encoded string (hex),
*	of length hexlen, into binary (bin),
* 	of length binlen. 
*	Caller is responsible of freeing memory.
*/
void h2b(char* hex, int hexlen, unsigned char** bin, int** binlen) {

	//Allocate memory for output length buffer.
	*binlen = (int*) malloc(sizeof(int) * 1);
	if( !(*binlen) ) {
		printf( "Memory allocation failed\n" );
		exit(0);
	}

	//Every hex represents one ASCII character. Hence
	//must be a multiple of 2 and the number of bytes
	//is equal to half the number of hex characters.
	if( hexlen % 2 != 0 ) {
		printf( "Hex string should be a multiple of two" );
		exit(0);
	}
	**binlen = hexlen / 2;

	//Allocate memory for output buffer.
	*bin = (unsigned char*) malloc(sizeof(char) * (**binlen));
	if( !(*bin) ) {
		printf( "Memory allocation failed\n" );
		exit(0);
	}	

	int temp1 = 0;
	int temp2 = 0;
	int j = 0;
	for(int i = 0; i < hexlen; i = i + 2) {

		//Convert each hex character to its numeric value
		temp1 = h2int( *(hex + i) );
		temp2 = h2int( *(hex + i + 1) );
		//Combines the numeric value of two hex characters 
		//to obtaion their ASCII value (the byte they represent). 
		*(*bin + j) = temp1*16 + temp2;
		j++;

	}
	
}


/*
*	Encodes a binary sequence (bin), of length binlen 
*	into base64 (b64), of length b64len. Note that b64 
* 	is not zero terminated.
*	Caller is repsonsible of freeing memory.
*	TODO: Add optional line feed option (newline every 76 char by flag).
*/
void base64_encode(unsigned char* bin, int binlen, char** b64, int** b64len) {

	/* Character set string */
	static const char* base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	//Allocate memory for output length buffer.
	*b64len = (int*) malloc(sizeof(int) * 1) ;
	if( !(*b64len) ) {
		printf( "Memory allocation failed\n" );
		exit(0);
	}

	//Compute the length of output by first culculating the number of padding bytes
	//(must be a multiple of 3). Then compute the number of bytes needed
	//to represent (4 bytes is needed for each 3 bytes of input (input length + padding length))
	int codelen =  binlen;
	int mod = binlen % 3;
	int padlen = mod ? (3 - mod) : 0;
	**b64len = 4*( (codelen + padlen) / 3);
	
	//Can now allocate memory for output buffer.
	*b64 = (char*) malloc( sizeof(char) * (**b64len) );
	if( !(*b64) ) {
		printf( "Memory allocation failed\n" );
		exit(0);
	}

	int i = 0;
	int j = 0;
	while(i < binlen) {

		/* Add zero bytes if binlen is not a multiple of 3 */
		int b1 = (i < binlen) ? *(bin + i) : 0;
		i++;
		int b2 = (i < binlen) ? *(bin + i) : 0;
		i++;
		int b3 = (i < binlen) ? *(bin + i) : 0;
		i++;

		/* b1 || b2 || b3 */
		int three_bytes = (b1 << 0x10) + (b2 << 0x08) + b3;

		/* Convert blocks of 6 bits to char */
		*(*b64 + j) = *(base64 + ((three_bytes >> 18) & 0x3F));
		j++;
		*(*b64 + j) = *(base64 + ((three_bytes >> 12) & 0x3F));
		j++;
		*(*b64 + j) = *(base64 + ((three_bytes >> 6) & 0x3F));
		j++;
		*(*b64 + j) = *(base64 + (three_bytes & 0x3F));
		j++;

	}

	//Add padding in the end
	for(i = 0; i < padlen; i++) {
		*(*b64 + (**b64len - 1 - i)) = '=';
	}

}


/* 
*	Decode a base64 encoded string (b64), of length b64len
*	into binary (bin), of length binlen.
*	Caller is responsible of freeing memory.
*/
void base64_decode(unsigned char* b64, int b64len, char** bin, int** binlen) {
	//TODO...
}
