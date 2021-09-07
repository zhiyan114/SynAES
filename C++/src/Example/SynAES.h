#include <iostream>
#include <string>
#include <openssl/bio.h>
#include <openssl/evp.h>

class SynAES {
    public:
      SynAES(std::string Key);
      std::string encrypt(std::string Data, std::string IV,int DataLen);
      std::string decrypt(std::string Data, std::string IV);
      int decrypt(std::string Data, std::string IV, std::string * PlainText);
    private:
      unsigned char key[32];
      const EVP_CIPHER* CipherType;
};