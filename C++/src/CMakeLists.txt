include_directories(.)
add_executable(main_program
main.cpp
main.h
base64.cpp
base64.h
)
find_package(OpenSSL REQUIRED)
target_link_libraries(main_program OpenSSL::Crypto)