#ifndef __openssl_aes_h__
#define __openssl_aes_h__

int encrypt(const unsigned char *plaintext, int plaintext_len, const unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext);

int decrypt(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key,
            unsigned char *iv, unsigned char *plaintext);

#endif // __openssl_aes_h__
