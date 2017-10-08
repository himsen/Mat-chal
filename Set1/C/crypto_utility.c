/*
 * Cryptography utility functions
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Hex character set */
static const char hexCharSet[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
static int hexCharSetLen = sizeof(hexCharSet);

/* Base64 character set */
static const char* base64CharSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static int base64CharSetLen = sizeof(base64CharSet);

 /*
 * Converts a hex character to its numeric value.
 */
int h2i(char hex) {

	if ('0' <= hex && hex <= '9') {
		return hex - '0';
	}
	else if ('A' <= hex && hex <= 'F') {
		return hex - 'A' + 10;
	}
	else {
		return hex - 'a' + 10;
	}

}

/*
 * Takes a nible (4 bits) and converts it
 * to a (hex) character
 */
char nibble_to_char(uint8_t nibble)
{
	if (nibble < hexCharSetLen) 
		return hexCharSet[nibble];
	return '*';
}

/* 
 * Converts hex encoded string 'hex',
 * of length hexLen, into binary 'bin'
 * Returns length of 'bin'
 * Caller is responsible of freeing 'bin'.
*/
size_t h2b(char *hex, size_t hexLen, uint8_t **bin) {

	size_t binLen = 0;
	size_t j = 0;
	size_t i = 0;
	int temp1 = 0;
	int temp2 = 0;

	/*
	 * Every hex represents one ASCII character. Hence
	 * must be a multiple of 2. In addition, the number of bytes
	 * in 'bin' must be equal to half the number of hex characters.
	 */
	if( hexLen % 2 != 0 ) {
		printf( "Hex string should be a multiple of two" );
		exit(0);
	}
	
	binLen = hexLen / 2;

	/* Allocate memory for output buffer. */
	*bin = (unsigned char*) calloc(1, sizeof(char) * binLen);
	if( !(*bin) ) {
		printf( "Memory allocation failed\n" );
		exit(0);
	}	

	for(i = 0; i < hexLen; i = i + 2) {

		/* Convert each hex character to its numeric value */
		temp1 = h2i( *(hex + i) );
		temp2 = h2i( *(hex + i + 1) );

		/* 
		 * Combines the numeric value of two hex characters 
		 * to obtain the numeric alue of the hex encoded byte. 
		 */
		*(*bin + j) = temp1*16 + temp2;
		j++;
	}

	return binLen;
}

/* 
 * Encodes sequnce of bytes 'bytes',
 * of length 'bytesLen', into hex encoded string 'hex',
 * Returns: length of 'hex' 
 * Caller is responsible of freeing 'hex'.
*/
size_t bytes_to_hex_string(uint8_t *bytes, size_t bytesLen, char **hex) {

	size_t i = 0;
	size_t hexLen = 0;

	hexLen = bytesLen * 2 + 1;
	*hex = (char *) calloc(1, hexLen);

	for (i = 0; i < bytesLen; i++) {

		*(*hex + i*2) = nibble_to_char(bytes[i] >> 4);
		*(*hex + (i*2+1)) = nibble_to_char(bytes[i] & 0x0f);
	}

	/* char buffer must be null-terminated */
    *(*hex + 2*i) = '\0';
	
	return hexLen;
}

size_t base64_encode(uint8_t *bytes, size_t bytesLen, char **b64) {

	size_t b64Len = 0;
	size_t mod = 0;
	size_t padLen = 0;
	size_t i = 0;
	size_t j = 0;

	/* 
	 * Compute the length of output by first culculating the number of padding bytes
	 * (must be a multiple of 3). Then compute the number of bytes needed
	 * to represent (4 bytes is needed for each 3 bytes of input (input length + padding length))
	 */
	mod = bytesLen % 3;
	padLen = mod ? (3 - mod) : 0;
	b64Len = 4*( (bytesLen + padLen) / 3);
	
	/* Can now allocate memory for output buffer */
	*b64 = (char*) malloc( sizeof(char) * b64Len );
	if( !(*b64) ) {
		printf( "Memory allocation failed\n" );
		exit(0);
	}

	while(i < bytesLen) {

		/* Add zero bytes if binlen is not a multiple of 3 */
		int b1 = (i < bytesLen) ? *(bytes + i) : 0;
		i++;
		int b2 = (i < bytesLen) ? *(bytes + i) : 0;
		i++;
		int b3 = (i < bytesLen) ? *(bytes + i) : 0;
		i++;

		/* b1 || b2 || b3 */
		int three_bytes = (b1 << 0x10) + (b2 << 0x08) + b3;

		/* Convert blocks of 6 bits to char */
		*(*b64 + j) = *(base64CharSet + ((three_bytes >> 18) & 0x3F));
		j++;
		*(*b64 + j) = *(base64CharSet + ((three_bytes >> 12) & 0x3F));
		j++;
		*(*b64 + j) = *(base64CharSet + ((three_bytes >> 6) & 0x3F));
		j++;
		*(*b64 + j) = *(base64CharSet + (three_bytes & 0x3F));
		j++;

	}

	//Add padding in the end
	for(i = 0; i < padLen; i++) {
		*(*b64 + (b64Len - 1 - i)) = '=';
	}

	return b64Len;
}

size_t base64_decode() {

	return 0;
}

/* Dumps hex content of a byte buffer */
void dump_bytes(uint8_t *bytes, size_t bytesLen) {

	size_t i;
	for (i = 0; i < bytesLen; i++) {

		if (i > 0 && !(i%8)) putchar(' ');
		if (i > 0 && !(i%64)) putchar('\n');
		printf("%02x", bytes[i]);
	}
	putchar('\n');

}

void dump_data(const void *s, size_t len, FILE *f) {

	size_t i, j;
	const u_char *p = (const u_char *)s;

	for (i = 0; i < len; i += 16) {

		/* Hex dump */
		fprintf(f, "%.4zu: ", i);
		for (j = i; j < i + 16; j++) {
			if (j < len)
				fprintf(f, "%02x ", p[j]);
			else
				fprintf(f, "   ");
		}

		/* ASCII dump */
		fprintf(f, " ");
		for (j = i; j < i + 16; j++) {
			if (j < len) {
				if  (isascii(p[j]) && isprint(p[j]))
					fprintf(f, "%c", p[j]);
				else
					fprintf(f, ".");
			}
		}
		fprintf(f, "\n");
	}
}


