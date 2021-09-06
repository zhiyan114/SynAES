// Example Usages
#include <iostream>
#include "SynAES.h"
int main() {
    SynAES * crypt = new SynAES("0123456789ABCDEF0123456789ABCDEF");
    std::cout << "Encryption: " << crypt->encrypt("YO SUP","0123456789AB").c_str() << std::endl;
    std::cout << "Decryption: " << crypt->decrypt("lyiAqsYTgCuWO0WcO7HKJ8IqZwwZWg==","0123456789AB").c_str() << std::endl;
    std::string PlaintxtData;
    std::cout << "Decryption (method 2) = Tag Validation: " << std::to_string(crypt->decrypt("lyiAqsYTgCuWO0WcO7HKJ8IqZwwZWg==","0123456789AB",&PlaintxtData)).c_str() << " | Data: " << PlaintxtData.c_str() << std::endl;
    std::string Pause;
    std::cin >> Pause;
}