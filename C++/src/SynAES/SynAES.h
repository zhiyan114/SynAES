#include <iostream>
#include <string>
#include <openssl/bio.h>
#include <openssl/evp.h>

#if defined(_MSC_VER)
    //  Microsoft 
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC
    #define EXPORT __attribute__((visibility("default")))
    #define IMPORT
#else
    //  do nothing and hope for the best?
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif
class EXPORT SynAES {
    public:
      SynAES(std::string Key);
      std::string encrypt(std::string Data, std::string IV);
      std::string decrypt(std::string Data, std::string IV);
      int decrypt(std::string Data, std::string IV, std::string * PlainText);
    private:
      unsigned char key[32];
      const EVP_CIPHER* CipherType;
};