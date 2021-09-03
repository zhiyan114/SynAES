# What is SynAES?
SynAES is a library that is aim to help a new developers who are interested in using Synapse X's Crypto function to create a secure communication between the server and the client.
# Languages that are written
* LUA (Synapse X's environment) duh and Script-Ware
* NodeJS
* Python
* PHP
* C#
* Java
* C++ (Incomplete, will be worked on soon)

You may request for more via issues tab or create a poll request to add your versions to it. (Prefer it to be written in a constructor format rather than function returning table format unless the language doesn't support it)


# AES Information
Key size should be 16, 24, or 32 characters long.

IV/Nonce should be 12 characters long.

# Usage Information
All data will be handled in string format (this includes key, iv, and data). The GMAC will be a size of 128 bit which will concatenated at the end of the ciphertext.

When performing encryption, Your key, IV, and data will be taken in which then it will return a base64 version of ciphertext and gmac that concatenated together.

When performing decryption, Your key, IV, and base64 encrypted data will be taken in which then it will return the original data that was encrypted.