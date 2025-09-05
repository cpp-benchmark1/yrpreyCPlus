#include <iostream>
#include <fstream>
#include <cstring>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/err.h>

int main() {
    const char* privateKeyPath = "/etc/ssl/private/server.key";
    const char* passWd = "a_Uit54u1l0R";
    
    std::cout << "Attempting to read private key from: " << privateKeyPath << std::endl;
    
    // Open the private key file
    FILE* keyFile = fopen(privateKeyPath, "r");
    
    if (keyFile == nullptr) {
        std::cout << "Failed to create or open private key file" << std::endl;
        return 1;
    }
    
    // SINK CWE 798
    EVP_PKEY* privateKey = PEM_read_PrivateKey(keyFile, nullptr, nullptr, (void*)passWd);
    
    if (privateKey == nullptr) {
        std::cout << "Failed to read private key" << std::endl;
    } else {
        std::cout << "Successfully loaded private key!" << std::endl;
        
        int keyType = EVP_PKEY_id(privateKey);
        std::cout << "Private key type: " << keyType << std::endl;
        
        // Clean up
        EVP_PKEY_free(privateKey);
    }
    
    fclose(keyFile);
    
    return 0;
}