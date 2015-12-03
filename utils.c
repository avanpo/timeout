#include <ctype.h>
#include <ncurses.h>
#include <time.h>

#include <openssl/aes.h>

int strncicmp(const char *a, const char *b, size_t n)
{
	int i, d;
	for (i = 0; i < n; ++i) {
		d = tolower(a[i]) - tolower(b[i]);
		if (d != 0) return d;
	}
	return 0;
}

void millisleep(int ms)
{
	struct timespec ts;
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (long)(ms % 1000) * 1000000L;

	nanosleep(&ts, NULL);
}

void print_str_slowly(const char *str)
{
	for (; *str; str++) {
		addch(*str);
		refresh();
		millisleep(100);
	}
}

size_t pkcs7_pad(unsigned char *plaintext, size_t length, int block_length)
{
	int i;
	int padding = (length % block_length == 0) ? 16 : block_length - length % block_length;

	for (i = 0; i < padding; ++i) {
		plaintext[length + i] = padding;
	}
	return length + padding;
}

size_t encrypt_AES_ECB(unsigned char *plaintext, unsigned char *ciphertext, size_t length, const unsigned char *key_str)
{
	AES_KEY key;
	AES_set_encrypt_key(key_str, 128, &key);

	size_t new_length = pkcs7_pad(plaintext, length, 16);

	int i;
	for (i = 0; i < new_length; i += 16) {
		AES_encrypt(&plaintext[i], &ciphertext[i], &key);
	}
	return new_length;
}
