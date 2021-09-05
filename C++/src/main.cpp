#include <main.h>
#include "base64.h"
#include <stdexcept>
#include <cstring>
#include <string.h>

SynAES::SynAES(std::string MainKey) {
    key = reinterpret_cast<const unsigned char*>(MainKey.c_str());
    switch(strlen(MainKey.c_str())) {
        case 16:
            CipherType = EVP_aes_128_gcm();
            break;
        case 24:
            CipherType = EVP_aes_192_gcm();
            break;
        case 32:
            CipherType = EVP_aes_256_gcm();
            break;
        default:
            throw std::invalid_argument("Invalid SynAES Key Length");
            break;
    }
}
std::string SynAES::encrypt(std::string Data, std::string IV) {
    const unsigned char* MainIV = reinterpret_cast<const unsigned char*>(IV.c_str());
    const unsigned char* MainData = reinterpret_cast<const unsigned char*>(Data.c_str());
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, CipherType, NULL, NULL, NULL);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_IVLEN, sizeof(MainIV), NULL);
    EVP_EncryptInit_ex(ctx, NULL, NULL, key, MainIV);
    
    unsigned char CipherTxt[1000];
    int CipherSize;
    EVP_EncryptUpdate(ctx, CipherTxt, &CipherSize, MainData, sizeof(MainData));
    EVP_EncryptFinal_ex(ctx, CipherTxt, &CipherSize);
    EVP_CIPHER_CTX_ctrl(ctx,EVP_CTRL_AEAD_GET_TAG, 16, CipherTxt);
    EVP_CIPHER_CTX_free(ctx);
    delete[] MainIV;
    delete[] MainData;
    return base64_encode(CipherTxt,sizeof(CipherTxt));
    
}
std::string SynAES::decrypt(std::string Data, std::string IV) {
    const unsigned char* MainIV = reinterpret_cast<const unsigned char*>(IV.c_str());
    const unsigned char* MainDataAndTag = const_cast<const unsigned char*>(base64_decode(Data).data());
    const unsigned char* MainData = new unsigned char[1000]; // 
    const unsigned char* MainTag = new unsigned char[1000];
    std::memcpy(const_cast<unsigned char*>(MainDataAndTag),&MainData,strlen((const char*)MainDataAndTag)-16);
    std::memcpy(const_cast<unsigned char*>(&MainDataAndTag[strlen((const char*)MainDataAndTag)-16]),MainTag,16);
    delete[] MainDataAndTag;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, CipherType, NULL, NULL, NULL);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_IVLEN, sizeof(MainIV), NULL);
    EVP_DecryptInit_ex(ctx, NULL, NULL, key, MainIV);
    unsigned char PlainTxt[sizeof(MainData)];
    int OutputLen;
    EVP_DecryptUpdate(ctx, PlainTxt, &OutputLen, MainData, sizeof(MainData));
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_TAG, 16, (void *)MainTag);
    int TagValid = EVP_DecryptFinal_ex(ctx, PlainTxt, &OutputLen);
    if(TagValid == 0) {
        throw std::runtime_error("Tag Validation Failed");
    }
    return std::string(reinterpret_cast<const char*>(PlainTxt));
}


// Example Usages
int main() {
    SynAES * crypt = new SynAES("0123456789ABCDEF0123456789ABCDEF");
    std::cout << crypt->encrypt("YO SUP","0123456789AB").c_str() << std::endl;
    std::cout << crypt->decrypt("lyiAqsYTgCuWO0WcO7HKJ8IqZwwZWg==","0123456789AB").c_str() << std::endl;
    std::string Pause;
    std::cin >> Pause;
}