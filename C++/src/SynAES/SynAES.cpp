#include "SynAES.h"
#include "base64.h"
#include <stdexcept>
#include <cstring>
#include <string.h>
#include <vector>

SynAES::SynAES(std::string MainKey) {
    std::copy(MainKey.begin(),MainKey.end(),key);
    key[MainKey.length()] = 0;
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
    EVP_CIPHER_CTX * ctx = EVP_CIPHER_CTX_new();
    
    EVP_EncryptInit_ex(ctx, CipherType, NULL, key, reinterpret_cast<unsigned char*>(IV.c_str()));
    unsigned char* CipherTxt = new unsigned char[Data.length()+16];
    int CipherSize;
    EVP_EncryptUpdate(ctx, CipherTxt, &CipherSize, reinterpret_cast<unsigned char*>(Data.c_str()), Data.length());
    EVP_EncryptFinal_ex(ctx, CipherTxt, &CipherSize);
    EVP_CIPHER_CTX_ctrl(ctx,EVP_CTRL_AEAD_GET_TAG, 16, &CipherTxt[Data.length()]);
    EVP_CIPHER_CTX_free(ctx);
    std::string ReturnData = base64_encode(CipherTxt,Data.length()+16);
    delete[] CipherTxt;
    return ReturnData;
}
std::string SynAES::decrypt(std::string Data, std::string IV) {
    std::vector<BYTE> MainDataAndTag = base64_decode(Data);
    const unsigned char* ConstDataTag = MainDataAndTag.data();
    char* MainData = new char[MainDataAndTag.size()-16];
    char* MainTag = new char[16];
    std::strncpy(MainData,reinterpret_cast<const char*>(ConstDataTag),MainDataAndTag.size()-16); //const_cast
    std::strncpy(MainTag,reinterpret_cast<const char*>(&ConstDataTag[MainDataAndTag.size()-16]),16);
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, CipherType, NULL, key, reinterpret_cast<unsigned char*>(IV.c_str()));
    unsigned char* PlainTxt = new unsigned char[MainDataAndTag.size()-16];
    int OutputLen;
    EVP_DecryptUpdate(ctx, PlainTxt, &OutputLen, reinterpret_cast<const unsigned char *>(MainData), MainDataAndTag.size()-16);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_TAG, 16, (void*)MainTag);
    int TagValid = EVP_DecryptFinal_ex(ctx, PlainTxt, &OutputLen);
    EVP_CIPHER_CTX_free(ctx);
    std::string ReturnData = std::string(reinterpret_cast<const char*>(PlainTxt),MainDataAndTag.size()-16);
    delete[] MainData;
    delete[] MainTag;
    delete[] PlainTxt;
    if(TagValid == 0) {
        throw std::runtime_error("Tag Validation Failed");
    }
    return ReturnData;
}
int SynAES::decrypt(std::string Data, std::string IV,std::string * PlainText) {
    std::vector<BYTE> MainDataAndTag = base64_decode(Data);
    const unsigned char* ConstDataTag = MainDataAndTag.data();
    char* MainData = new char[MainDataAndTag.size()-16];
    char* MainTag = new char[16];
    std::strncpy(MainData,reinterpret_cast<const char*>(ConstDataTag),MainDataAndTag.size()-16); //const_cast
    std::strncpy(MainTag,reinterpret_cast<const char*>(&ConstDataTag[MainDataAndTag.size()-16]),16);
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, CipherType, NULL, key, reinterpret_cast<unsigned char*>(IV.c_str()));
    unsigned char* PlainTxt = new unsigned char[MainDataAndTag.size()-16];
    int OutputLen;
    EVP_DecryptUpdate(ctx, PlainTxt, &OutputLen, reinterpret_cast<const unsigned char *>(MainData), MainDataAndTag.size()-16);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_TAG, 16, (void*)MainTag);
    int TagValid = EVP_DecryptFinal_ex(ctx, PlainTxt, &OutputLen);
    EVP_CIPHER_CTX_free(ctx);
    *PlainText = std::string(reinterpret_cast<const char*>(PlainTxt),MainDataAndTag.size()-16);
    delete[] MainData;
    delete[] MainTag;
    delete[] PlainTxt;
    //std::memcpy(PlainText,&StrPlainTxt,sizeof(StrPlainTxt));
    return TagValid;
}