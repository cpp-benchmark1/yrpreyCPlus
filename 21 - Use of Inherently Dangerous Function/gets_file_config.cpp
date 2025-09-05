#include <iostream>
#include <fstream>
#include <cstring>

// Import the gets function
extern "C" char* gets(char*);

int main() {
    // Fixed size buffer
    char configBuffer[128];
    
    std::cout << "Enter configuration data: ";
    // SINK CWE 242
    char* result = gets(configBuffer);
    
    if (result == nullptr) {
        std::cout << "Failed to read configuration data" << std::endl;
        return 1;
    }
    
    std::cout << "Configuration data received: " << configBuffer << std::endl;
    
    // Save configuration data to config file
    const char* configFilePath = "config.txt";
    std::ofstream configFile(configFilePath);
    
    if (configFile.is_open()) {
        configFile << configBuffer;
        configFile.close();
        
        std::cout << "Configuration data saved to: " << configFilePath << std::endl;
    } else {
        std::cout << "Failed to open configuration file for writing" << std::endl;
        return 1;
    }
    
    return 0;
}