#include <openssl/aes.h>
#include <openssl/rand.h>
#include <iostream>
#include <string.h>
#include "openssl_aes.h"

void test_openssl_aes()
{
    // 测试OpenSSL的AES加密和解密功能
    const char *plaintext = "Hello, OpenSSL AES Encryption!";
    const char *key = "0123456789abcdef";
    char *iv = new char[16];
    memcpy(iv, "0123456789abcdef", 16);

    int paddedLength = strlen((const char *)plaintext);
    unsigned char *encryptedText = new unsigned char[paddedLength];
    int retval = ::encrypt((const unsigned char *)plaintext, int(strlen(plaintext)), (const unsigned char *)key, (unsigned char *)iv, encryptedText);

    if (retval != 0)
    {
        std::cout << "Encryption failed!" << std::endl;
        return;
    }

    // 显示加密后的数据
    std::cout << "Encrypted Text: ";
    for (int i = 0; i < paddedLength; ++i)
    {
        printf("%02x", encryptedText[i]);
    }
    std::cout << "\n";

    unsigned char decryptedText[paddedLength];

    memcpy(iv, "0123456789abcdef", 16);
    retval = ::decrypt(encryptedText, paddedLength, (const unsigned char *)key, (unsigned char *)iv, decryptedText);

    std::cout << decryptedText;
    std::cout << "\n";

    delete[] encryptedText;
    delete[] iv;
}

int test_aes()
{
    // 使用256位密钥
    const int keyLength = 256 / 8;
    unsigned char key[keyLength];

    // 生成随机密钥
    if (RAND_bytes(key, keyLength) != 1)
    {
        std::cerr << "Error generating random key." << std::endl;
        return 1;
    }

    // 显示生成的密钥（仅用于演示，实际应用中应该保密）
    std::cout << "Generated Key: ";
    for (int i = 0; i < keyLength; ++i)
    {
        printf("%02x", key[i]);
    }
    std::cout << std::endl;

    // 明文
    const char *plaintext = "Hello, OpenSSL AES Encryption!";

    // 使用 PKCS#7 填充方式
    int pad = AES_BLOCK_SIZE - (strlen(plaintext) % AES_BLOCK_SIZE);
    int paddedLength = strlen(plaintext) + pad;

    // 分配足够大的内存来存储填充后的明文
    unsigned char *paddedPlaintext = new unsigned char[paddedLength];
    memcpy(paddedPlaintext, plaintext, strlen(plaintext));
    memset(paddedPlaintext + strlen(plaintext), pad, pad);

    // 初始化 AES 加密上下文
    AES_KEY aesKey;
    if (AES_set_encrypt_key(key, keyLength * 8, &aesKey) != 0)
    {
        std::cerr << "Error setting encryption key." << std::endl;
        delete[] paddedPlaintext;
        return 1;
    }

    // 加密
    unsigned char encryptedText[paddedLength];
    AES_encrypt(paddedPlaintext, encryptedText, &aesKey);

    // 显示加密后的数据
    std::cout << "Encrypted Text: ";
    for (int i = 0; i < paddedLength; ++i)
    {
        printf("%02x", encryptedText[i]);
    }
    std::cout << std::endl;

    // 解密（为了演示，我们在同一个程序中进行加密和解密）
    AES_KEY decryptKey;
    if (AES_set_decrypt_key(key, keyLength * 8, &decryptKey) != 0)
    {
        std::cerr << "Error setting decryption key." << std::endl;
        delete[] paddedPlaintext;
        return 1;
    }

    // 解密
    unsigned char decryptedText[paddedLength];
    AES_decrypt(encryptedText, decryptedText, &decryptKey);

    // 去除填充
    int unpaddedLength = paddedLength - decryptedText[paddedLength - 1];
    decryptedText[unpaddedLength] = '\0';

    // 显示解密后的数据
    std::cout << "Decrypted Text: " << decryptedText << std::endl;

    // 释放内存
    delete[] paddedPlaintext;

    return 0;
}

int main()
{
    test_openssl_aes();
    return 0;
}
