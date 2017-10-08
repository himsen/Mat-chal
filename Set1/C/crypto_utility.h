#ifndef CRYPTO_UTILITY_H
#define CRYPTO_UTILITY_H

/* 
 * Cryptography utility functions header
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int h2i(char hex);
char nibble_to_char(uint8_t nibble);
size_t h2b(char *hex, size_t hexLen, uint8_t **bin);
size_t bytes_to_hex_string(uint8_t *bytes, size_t bytesLen, char **hex);
size_t base64_encode(uint8_t *bytes, size_t bytesLen, char **b64);
size_t base64_decode();
void dump_bytes(uint8_t *bytes, size_t bytesLen);
void dump_data(const void *s, size_t len, FILE *f);

 #endif /* CRYPTO_UTILITY_H */
