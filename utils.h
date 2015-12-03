#ifndef UTILS_H
#define UTILS_H

int strncicmp(const char *a, const char *b, size_t n);

void millisleep(int ms);

void print_str_slowly(const char *str);

size_t encrypt_AES_ECB(unsigned char *plaintext, unsigned char *ciphertext, size_t length, const unsigned char *key_str);

#endif
