#ifndef ENCODING_H
#define ENCODING_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

size_t h2b(char *, size_t, uint8_t **);
size_t bytes_to_hex_string();

size_t base64_encode();
size_t base64_decode();

void print_bytes(uint8_t*, size_t);
void dump_data(const void*, size_t, FILE *);

static int h2i(char);

#endif /* ENCODING_H */