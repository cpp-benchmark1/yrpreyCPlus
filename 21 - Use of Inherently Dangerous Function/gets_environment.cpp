#include <iostream>
#include <cstdlib>
#include <cstring>

// Import the gets function
extern "C" char* gets(char*);

int main() {
    char dataBuffer[64];
    
    std::cout << "Enter data to set as environment variable: ";
    // SINK CWE 242
    char* result = gets(dataBuffer);
    
    if (result == nullptr) {
        std::cout << "Failed to read data" << std::endl;
        return 1;
    }
    
    std::cout << "Data received: " << dataBuffer << std::endl;
    
    // Set environment variable
    const char* envVarName = "USER_DATA";
    int setResult = setenv(envVarName, dataBuffer, 1);
    
    if (setResult == 0) {
        std::cout << "Environment variable " << envVarName << " set successfully" << std::endl;
        
        const char* envValue = getenv(envVarName);
        if (envValue != nullptr) {
            std::cout << "Environment variable value: " << envValue << std::endl;
        }
    } else {
        std::cout << "Failed to set environment variable" << std::endl;
        return 1;
    }
    
    return 0;
}