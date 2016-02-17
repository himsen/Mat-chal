#include "encoding.h"
#include "base64.h"

void  hstring2base64(char* hex, int hexlen, char** b64, int** b64len) {

	unsigned char* bin;
	int* binlen;

	//Convert hex string to binary
	h2b(hex, hexlen, &bin, &binlen);

	//Base64 encode binary
	base64_encode(bin, *binlen, b64, b64len);

}