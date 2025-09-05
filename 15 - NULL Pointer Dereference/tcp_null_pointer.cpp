#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>

// TCP network function to receive data
std::string receiveTcpData() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return "0";
    }
    
    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cerr << "Setsockopt failed" << std::endl;
        return "0";
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8092);
    
    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return "0";
    }
    
    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen failed" << std::endl;
        return "0";
    }
    
    // Accept connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        std::cerr << "Accept failed" << std::endl;
        return "0";
    }
    
    // Read data
    int valread = read(new_socket, buffer, 1024);
    if (valread <= 0) {
        std::cerr << "Read failed" << std::endl;
        return "0";
    }
    
    close(new_socket);
    close(server_fd);
    
    return std::string(buffer);
}

// Function 1: Parse configuration ID data
int* parseConfigIdData(const std::string& data) {
    if (data.empty()) {
        std::cout << "Empty configuration ID data received" << std::endl;
        return new int(0);
    }
    
    int* configId = new int(std::stoi(data));
    std::cout << "Parsing configuration ID data: " << data << std::endl;
    return configId;
}

// Function 2: Check configuration range
int* checkConfigRange(int* configId) {
    if (*configId < 0) {
        std::cout << "Negative configuration ID detected" << std::endl;
    }
    
    if (*configId > 1000) {
        std::cout << "High configuration ID detected" << std::endl;
    }
    
    std::cout << "Checking configuration range: " << *configId << std::endl;
    return configId;
}

// Function 3: Process configuration calculation
int* processConfigCalculation(int* configId) {
    if (*configId % 2 == 0) {
        std::cout << "Even configuration ID, processing normally" << std::endl;
    } else {
        std::cout << "Odd configuration ID, applying special processing" << std::endl;
    }
    
    if (*configId > 100) {
        std::cout << "Large configuration ID, using advanced calculation" << std::endl;
    }
    
    std::cout << "Processing configuration calculation: " << *configId << std::endl;
    return configId;
}

// Function 4: Access configuration value (SINK - NULL pointer dereference vulnerability)
int accessConfigValue(int* configId) {
    std::cout << "Accessing configuration value for ID: " << *configId << std::endl;
    
    // Set pointer to NULL if configuration ID is 0
    if (*configId == 0) {
        configId = nullptr;
        std::cout << "Configuration ID is 0, setting pointer to NULL" << std::endl;
    }
    
    // SINK CWE 476
    int value = *configId;
    
    std::cout << "Configuration value accessed: " << value << std::endl;
    return value;
}

void logConfigAccess(int configValue) {
    if (configValue == 0) {
        std::cout << "No configuration value to log" << std::endl;
        return;
    }
    
    std::cout << "Logging configuration access: " << configValue << std::endl;
    
    if (configValue > 50) {
        std::cout << "High configuration value detected" << std::endl;
    }
}

int main() {
    // Receive data from network
    std::string networkData = receiveTcpData();
    
    // Process through intermediate functions with conditional flow
    int* parsedConfigId = parseConfigIdData(networkData);
    
    // Conditional flow based on configuration ID
    int* rangedConfigId;
    if (*parsedConfigId % 2 == 0) {
        rangedConfigId = checkConfigRange(parsedConfigId);
    } else {
        std::cout << "Skipping range check for odd configuration ID" << std::endl;
        rangedConfigId = parsedConfigId;
    }
    
    int* calculatedConfigId;
    if (*rangedConfigId % 3 == 0) {
        calculatedConfigId = processConfigCalculation(rangedConfigId);
    } else {
        std::cout << "Skipping calculation for non-divisible configuration ID" << std::endl;
        calculatedConfigId = rangedConfigId;
    }
    
    // Access configuration value
    int configValue = accessConfigValue(calculatedConfigId);
    
    // Log the access
    logConfigAccess(configValue);
    
    // Clean up memory
    delete parsedConfigId;
    
    std::cout << std::endl;
    std::cout << "Configuration access completed" << std::endl;
    
    return 0;
}