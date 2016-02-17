#ifndef ENCODING_H
#define ENCODING_H

void h2b(char*, int, unsigned char**, int**);
void hc2b(char*, int, unsigned char**, int**);
void base64_encode(unsigned char*, int, char**, int**);
void base64_decode(unsigned char*, int, char**, int**);

int h2int(char);

#endif
