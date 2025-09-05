#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// Function 1: Get environment variable data
std::string getEnvironmentData() {
    std::cout << "Retrieving environment variable data..." << std::endl;
    
    // Get sensitive data from environment variable
    const char* envData = getenv("SSH_CONFIG_DATA");
    if (envData == nullptr) {
        std::cout << "Environment variable SSH_CONFIG_DATA not found, using default" << std::endl;
        return "Host *\n    StrictHostKeyChecking no\n    UserKnownHostsFile /dev/null\n";
    }
    
    std::cout << "Environment data retrieved successfully" << std::endl;
    return std::string(envData);
}

// Function 2: Write configuration data
void writeConfigurationData(const std::string& data) {
    std::cout << "Writing configuration data to SSH config file..." << std::endl;
    
    const char* configPath = "/etc/ssh/ssh_config";
    
    // Open file with insecure permissions
    int fd = open(configPath, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd == -1) {
        std::cout << "Failed to create SSH config file" << std::endl;
        return;
    }
    
    // Write data to file
    ssize_t bytesWritten = write(fd, data.c_str(), data.length());
    if (bytesWritten == -1) {
        std::cout << "Failed to write data to SSH config file" << std::endl;
    } else {
        std::cout << "Successfully wrote " << bytesWritten << " bytes to SSH config file" << std::endl;
    }
    
    // Close file
    close(fd);
    
}

int main() {

    
    // Get data from environment variable
    std::string configData = getEnvironmentData();
    
    // Write configuration with insecure permissions
    writeConfigurationData(configData);
    
    
    return 0;
}