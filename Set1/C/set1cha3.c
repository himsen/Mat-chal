

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int scores[256] = {0};
int sorted_scores[256] = {0};
char english_letter_frequency[5] = {'e', 't', 'a', 'o', 'i'};
static const int english_letter_frequency_len = sizeof(english_letter_frequency);

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

int h2int (char hex) {

	if ('0' <= hex && hex <= '9')
		return hex - '0';
	else if ('a' <= hex && hex <= 'z')
		return hex - 'a' + 10;
	else if ('A' <= hex && hex <= 'Z')
		return hex - 'A' + 10;
	else 
		return -1;
}


void count(char *hex, size_t hexlen) {

	int a, b, i;

	for (i = 0; i < hexlen; i = i + 2) {

		a = h2int(hex[i]);
		b = h2int(hex[i + 1]);
		scores[a * 16 + b] += 1;
	}
}

int find_max() {

	int i;
	int max = 0;

	for (i = 0; i < 256; i++) {
		if (max < scores[i]) 
			max = scores[i];
	}

	return max;
}

void sort_scores(int max) {

	int i, j, index = 0;

	for (i = max;  i > -1; i--) {
		for (j = 0; j < 256; j++) {
			if (scores[j] == i) {
				sorted_scores[index] = j;
				index++;
			}
		}
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

unsigned char * fixed_xor(unsigned char *p, char *q, size_t len) {

	unsigned char *bin = NULL;
	int binlen = 0;

	h2b(q, len * 2, &bin, &binlen);

	printf("%c and %c\n", bin[0], bin[1]);

	u_char *res = (u_char *) malloc(sizeof(u_char) * len);

	int i;
	for (i = 0; i < len; i++) {
		res[i] = p[i] ^ bin[i];
	}

	free(bin);

	return res;

}

void try_decrypt(char *hex) {

	unsigned char key = 0;
	int i, j;
	unsigned char x, y;
	int bla = 0;

	unsigned char *res = NULL;

	int length = strlen(hex) / 2;

	unsigned char *key_repeated = (unsigned char *) malloc(sizeof(char) * length);

	for (i = 0; i < 2; i++) { // number of most frequent to try

		for (j = 0; j < english_letter_frequency_len; j++) { //number of letter to try

			x = (unsigned char) sorted_scores[i];
			y = (unsigned char) english_letter_frequency[j];
			key = x ^ y;

			printf("x = %c, y = %c, key = %c\n", x, y, key);

			memset(key_repeated, key, length);

			dump_data(key_repeated, length, stdout);

			res = fixed_xor(key_repeated, hex, length);

			dump_data(res, length, stdout);

			free(res);

		}
	}

	free(key_repeated);

}

int main(int argc, char* argv[]) {
	
	char hex[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	int i, max;
	//for (i = 0; i < 256; i++)
	//	printf("scores[%i] = %i\n", i, scores[i]);

	count(hex, strlen(hex));

	//for (i = 0; i < 256; i++)
	//	printf("scores[%i] = %i\n", i, scores[i]);

	max = find_max();

	//printf("max = %i\n", max);

	sort_scores(max);

	//for (i = 0; i < 256; i++)
	//	printf("sorted_scores[%i] = %i\n", i, sorted_scores[i]);

	try_decrypt(hex);

	return 0;
}
