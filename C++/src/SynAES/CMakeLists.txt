add_library(SynAES SHARED
SynAES.cpp
SynAES.h
base64.cpp
base64.h
)
find_package(OpenSSL REQUIRED)
target_link_libraries(SynAES OpenSSL::Crypto)