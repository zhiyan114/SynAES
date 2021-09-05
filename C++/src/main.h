#include <iostream>
#include <string>
#include <openssl/bio.h>
#include <openssl/evp.h>

class SynAES {
    public:
      SynAES(std::string Key);
      std::string encrypt(std::string Data, std::string IV);
      std::string decrypt(std::string Data, std::string IV);
    private:
      unsigned char key[32];
      const EVP_CIPHER* CipherType;
};