
/* Frequency analysis attack on single byte XOR cipher */


#include "frequency_attack.h"
#include "crypto_utility.h"

int scores[256] = {0};
int sorted_scores[256] = {0};
char english_letter_frequency[] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 
	'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 
	'j', 'x', 'q', 'z'};
static const int english_letter_frequency_len = sizeof(english_letter_frequency);


void count(char *hex, size_t hexlen) {

	int a, b, i;

	for (i = 0; i < hexlen; i = i + 2) {

		a = h2i(hex[i]);
		b = h2i(hex[i + 1]);
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

	int i = 0, j = 0, index = 0;

	for (i = max;  i > -1; i--) {
		for (j = 0; j < 256; j++) {
			if (scores[j] == i) {
				sorted_scores[index] = j;
				index++;
			}
		}
	}
}

unsigned char * fixed_xor(unsigned char *p, unsigned char *q, size_t len) {

	int binlen = 0;

	unsigned char *res = (u_char *) malloc(sizeof(u_char) * len);

	int i;
	for (i = 0; i < len; i++) {
		res[i] = p[i] ^ q[i];
	}

	return res;
}

/* 
 * Output
 *		1: 'ch' is numerical/letter ascii
 *		0: 'ch' is not numerical/letter ascii
 */
int is_text_ascii(char ch) {

	if ('0' <= ch && ch <= '9') 
		return 1;
	if ('a' <= ch && ch <= 'z')
		return 1;
	else if ('A' <= ch && ch <= 'Z')
		return 1;
	else 
		return 0;


}

int score(char ch) {

	if (ch < 31)
		return -5;
	switch (ch) {
		case 'e':
		case 't':
		case 'a':
		case 'o':
		case 'i':
		case 'n':
		case 'E':
		case 'T':
		case 'A':
		case 'O':
		case 'I':
		case 'N':
		case ' ':
		return 5;
	}
	if (isalpha(ch)) 
		return 4;

	return 1;
}

int ascii_text_count(char *str, int strLen) {

	int i = 0, count = 0;

	for (i = 0; i < strLen; i++) {
		count = count + score(str[i]);
	}

	return count;
}


char ** produce_strings(unsigned char *str, int strLen, int depth_str_letters, int depth_english_letters) {

	unsigned char key = 0, x = 0, y = 0, index = 0;
	char **res = NULL;
	unsigned char *key_repeated = NULL;

	int i = 0, j = 0;

	res = (char **) malloc(sizeof(char*) * (depth_str_letters * depth_english_letters));
	for (i = 0; i < depth_english_letters * depth_str_letters; i++) {
		res[i] = (char *) malloc(sizeof(char) * strLen);
	}

	key_repeated = (unsigned char *) malloc(sizeof(char) * strLen);

	for (i = 0; i < depth_str_letters; i++) { // number of most frequent to try

		for (j = 0; j < depth_english_letters; j++) { //number of letter to try

			x = (unsigned char) sorted_scores[i];
			y = (unsigned char) english_letter_frequency[j];
			key = x ^ y;

			memset(key_repeated, key, strLen);

			res[index] = fixed_xor(key_repeated, str, strLen);
			index++;

		}
	}

	free(key_repeated);

	return res;
}

char * do_attack(char *hex) {

	//printf("%s\n", hex);

	int depth_str_letters = 10;
	int depth_english_letters = 10;

	//hex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	char *res;
	int i, max, j, max_count_index, max_count = 0, max_count_temp = 0;
	unsigned char *bin = NULL;
	char **strings = NULL;

	count(hex, strlen(hex));
	max = find_max();
	sort_scores(max);
	j = h2b(hex, strlen(hex), &bin);

	strings = produce_strings(bin, j, depth_str_letters, depth_english_letters);

	res = (char *) malloc(sizeof(char) * j);

	for (i = 0; i < depth_str_letters * depth_english_letters; i++) {
		max_count_temp = ascii_text_count(strings[i], j);
		if (max_count_temp > max_count) {
			max_count_index = i;
			max_count = max_count_temp;
		}
	}

	//dump_data(strings[max_count_index], j, stdout);	

	memcpy(res, strings[max_count_index], j);

	for (i = 0; i < 2 * 4; i++) {
		free(strings[i]);
	}
	free(strings);

	return res;
}

/*
int main(int argc, char *argv[]) {

	char hex[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	int i, max, j, max_count_index, max_count = 0, max_count_temp = 0;
	unsigned char *bin = NULL;
	char **strings = NULL;

	count(hex, strlen(hex));
	max = find_max();
	sort_scores(max);
	j = h2b(hex, strlen(hex), &bin);

	strings = produce_strings(bin, j, 2, 4);

	for (i = 0; i < 2 * 4; i++) {
		max_count_temp = ascii_text_count(strings[i], j);
		if (max_count_temp > max_count) {
			max_count_index = i;
			max_count = max_count_temp;
		}
	}

	dump_data(strings[max_count_index], j, stdout);

	return 0;
}
*/
