#include <openssl/aes.h>
#include "openssl_aes.h"

int encrypt(const unsigned char *plaintext, int plaintext_len, const unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext) {
    AES_KEY aes_key;
    // 常用的有 128、192、 256 位。
    AES_set_encrypt_key(key, 128, &aes_key);
    AES_cbc_encrypt(plaintext, ciphertext, plaintext_len, &aes_key, iv, AES_ENCRYPT);
    return 0;
}

int decrypt(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key,
            unsigned char *iv, unsigned char *plaintext) {
    AES_KEY aes_key;
    // 常用的有 128、192、256 位。
    AES_set_decrypt_key(key, 128, &aes_key);
    AES_cbc_encrypt(ciphertext, plaintext, ciphertext_len, &aes_key, iv, AES_DECRYPT);
    return 0;
}

