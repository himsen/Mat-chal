/* langeuage: C
 * Set: 1
 * Challenge: 2 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>

void fixed_xor(char *, char *, char **, u_int *);


int main(int argc, char *argv[]) {

	char hex1[] = "1c0111001f010100061a024b53535009181c";
	char hex2[] = "686974207468652062756c6c277320657965";

	char *fixedxor = NULL;
	int fixedxorlen = 0;

	fixed_xor(hex1, hex2, &fixedxor, &fixedxorlen);

	return 0;
}

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

void h2b(char* hex, int hexlen, unsigned char** bin, int* binlen) {

	//Allocate memory for output length buffer.
	//binlen = (int*) malloc(sizeof(int) * 1);
	//if( !binlen ) {
	//	printf( "Memory allocation failed\n" );
	//	exit(0);
	//}

	//Every hex represents one ASCII character. Hence
	//must be a multiple of 2 and the number of bytes
	//is equal to half the number of hex characters.
	if( hexlen % 2 != 0 ) {
		printf( "Hex string should be a multiple of two" );
		exit(0);
	}
	*binlen = hexlen / 2;

	//Allocate memory for output buffer.
	*bin = (unsigned char*) malloc(sizeof(char) * (*binlen));
	if( !(*bin) ) {
		printf( "Memory allocation failed\n" );
		exit(0);
	}	

	int temp1 = 0;
	int temp2 = 0;
	int j = 0;
	int i;
	for(i = 0; i < hexlen; i = i + 2) {

		//Convert each hex character to its numeric value
		temp1 = h2int( *(hex + i) );
		temp2 = h2int( *(hex + i + 1) );
		//Combines the numeric value of two hex characters 
		//to obtain the byte they represent. 
		*(*bin + j) = temp1*16 + temp2;
		j++;

	}
	
}

static char byteMap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
static int byteMapLen = sizeof(byteMap);


/* Utility function to convert nibbles (4 bit values) into a hex character representation */
static char
nibbleToChar(uint8_t nibble)
{
	if(nibble < byteMapLen) return byteMap[nibble];
	return '*';
}

/* Convert a buffer of binary values into a hex string representation */
char
*bytesToHexString(uint8_t *bytes, size_t buflen)
{
	char *retval;
	int i;
	
	retval = malloc(buflen*2 + 1);
	for(i=0; i<buflen; i++) {
		retval[i*2] = nibbleToChar(bytes[i] >> 4);
		retval[i*2+1] = nibbleToChar(bytes[i] & 0x0f);
	}
    retval[2*i] = '\0';
	return retval;
}


void fixed_xor(char *hex1, char *hex2, char **fixedxor, u_int *fixedxorlen) {

	int hex1len = strlen(hex1);
	int hex2len = strlen(hex2);

	u_char *bin1 = NULL;
	int bin1len = 0;

	u_char *bin2 = NULL;
	int bin2len = 0;

	h2b(hex1, hex1len, &bin1, &bin1len);
	h2b(hex2, hex2len, &bin2, &bin2len);

	int size = bin1len < bin2len ? bin1len : bin2len;

	u_char *fixedxorbin = (u_char *) malloc(sizeof(u_char) * size);

	int i;
	for (i = 0; i < size; i++) {
		fixedxorbin[i] = bin1[i] ^ bin2[i];
	}

	*fixedxor = (char *) malloc(sizeof(char) * size * 2);
	*fixedxor = bytesToHexString(fixedxorbin, size);

	free(bin1);
	free(bin2);
}