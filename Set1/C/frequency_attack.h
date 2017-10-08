#ifndef FREQUENCY_ATTACK_H
#define FREQUENCY_ATTACK_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

void count(char *hex, size_t hexlen);
int find_max();
void sort_scores(int max);
unsigned char * fixed_xor(unsigned char *p, unsigned char *q, size_t len);
char ** produce_strings(unsigned char *str, int strLen, 
	int depth_str_letters, int depth_english_letters);
int ascii_count(char *str, int strLen);
int is_english_text(char *str, int strLen);
char * do_attack(char *hex);

#endif /* FREQUENCY_ATTACK_H */
