#include "encoding.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printBits(size_t const size, void const * const ptr)
{

    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for(i = 0; i < size; i++)
    {
        for(j = 7; j >= 0; j--)
        {
            byte = b[i] & (1<<j);
            byte >>= j;
            printf("%u", byte);
        }
    }

    puts("");

}


int main(int argc, char** argv) {

	/* base64_encode test start */
	
	//Test vectors from RFC4648.
	char* test0 = ""; //""
	int test0_len = 0;
	char* test0_expres = ""; 
	int test0_explen = 0;
	char* test1 = "66"; //"f"
	int test1_len = 2;
	char* test1_expres = "Zg==";
	int test1_explen = 4;
	char* test2 = "666f"; //"fo"
	int test2_len = 4;
	char* test2_expres = "Zm8="; 
	int test2_explen = 4;
	char* test3 = "666f6f"; //"foo"
	int test3_len = 6;
	char* test3_expres = "Zm9v";
	int test3_explen = 4;
	char* test4 = "666f6f62"; //"foob"
	int test4_len = 8;
	char* test4_expres = "Zm9vYg==";
	int test4_explen = 8;
	char* test5 = "666f6f6261"; //"fooba"
	int test5_len = 10;
	char* test5_expres = "Zm9vYmE=";
	int test5_explen = 8;
	char* test6 = "666f6f626172"; //"foobar"
	int test6_len = 12;
	char* test6_expres = "Zm9vYmFy";
	int test6_explen = 8;

	//Test vector from Matasano.
	char* test_matasano = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	int test_matasano_len = 96;
	char* test_matasano_expres = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
	int test_matasano_explen = 64;

	//Pointers to test vectors, test vector lengths, expected base64 encodings and expected base64 encoding lengths.
	char* test_vectors[] = {test0, test1, test2, test3, test4, test5, test6, test_matasano};
	int test_vectors_len[] = {test0_len, test1_len, test2_len, test3_len, test4_len, test5_len, test6_len, test_matasano_len};
	char* test_vectors_expres[] = {test0_expres, test1_expres, test2_expres, test3_expres, test4_expres, test5_expres, test6_expres, test_matasano_expres};
	int test_vectors_explen[] = {test0_explen, test1_explen, test2_explen, test3_explen, test4_explen, test5_explen, test6_explen, test_matasano_explen};

	//Temporary buffers to hold binary conversion.
	unsigned char* bin;
	int* binlen;

	//Temporary buffers to hold base64 conversion.
	char* b64;
	int* b64len;

	//Error flag
	int error_flag = 0;
	
	for(int i = 0; i < 8; i++) {

		//Convert test (hex encoded) string to binary and then base64 encode.
		h2b( *(test_vectors + i), *(test_vectors_len + i), &bin, &binlen );
		base64_encode(bin, *binlen, &b64, &b64len);

		//Test whether b64 encoding has the expected length.
		error_flag = (*b64len == *(test_vectors_explen + i)) ? 0 : 1;

		if( error_flag ) {
			printf("Test %d failed (Length of b64 encoding was not as expected).\n", i);
			printf("Expected length: %d.\nActual length: %d.\n", *(test_vectors_explen + i), *b64len);
			goto error;
		}

		//Test whether b64 encoding is as expected.
		error_flag = memcmp( b64, *(test_vectors_expres + i), *b64len);

		if( error_flag ) {
			printf("Test %d failed (base64 encoding was not as expected).\n", i);
			//We have to hack a little to make it easy to print out.
			char* b64ExpandBuffer = (char*) malloc( (sizeof(char) * (*b64len)) + 1 );
			char* b64expresExpandBuffer = (char*) malloc( (sizeof(char) * (*(test_vectors_explen + i))) + 1);
			memcpy( b64ExpandBuffer, b64, *b64len );
			*(b64ExpandBuffer + (*b64len)) = '\0';
			memcpy( b64expresExpandBuffer, *(test_vectors_expres + i), *(test_vectors_explen + i) );
			*(b64expresExpandBuffer + (*(test_vectors_explen + i))) = '\0';
			//Now inform user what the problem is.
			printf("Expected base64 encoding: %s.\nActual base64 encoding: %s.\n", b64expresExpandBuffer, b64ExpandBuffer);
			//Remember to free allocated memory.
			free(b64ExpandBuffer);
			free(b64expresExpandBuffer);
			goto error;
		}

		//Free temporary buffers for next test.
		free(bin);
		free(binlen);
		free(b64);
		free(b64len);

	}

	//If we reach this point, all tests has passed :).
	printf("All tests passed.\n");
	return 1;

	error:
		//Remember to free temporary buffers. 
		free(bin);
		free(binlen);
		free(b64);
		free(b64len);

		//If we reach this point, the test has failed :(.
		printf("Test failed.\n");
		return 0;

	/* h2b test end */

} 



