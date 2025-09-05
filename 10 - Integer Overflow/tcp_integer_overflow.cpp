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
    address.sin_port = htons(8082);
    
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

// Function 1: Parse configuration value
std::string parseConfigValue(const std::string& data) {
    if (data.empty()) {
        std::cout << "Empty configuration data received" << std::endl;
        return "0";
    }
    
    std::cout << "Parsing configuration value: " << data << std::endl;
    return data;
}

// Function 2: Validate configuration format
std::string validateConfigFormat(const std::string& valueStr) {
    if (valueStr.empty()) {
        std::cout << "Empty configuration format" << std::endl;
        return "0";
    }
    
    std::cout << "Validating configuration format: " << valueStr << std::endl;
    return valueStr;
}

// Function 3: Check configuration range
std::string checkConfigRange(const std::string& valueStr) {
    int value = std::stoi(valueStr);
    
    if (value < 0) {
        std::cout << "Negative configuration value detected" << std::endl;
    }
    
    if (value > 100) {
        std::cout << "High configuration value detected" << std::endl;
    }
    
    std::cout << "Checking configuration range: " << value << std::endl;
    return valueStr;
}

// Function 4: Apply configuration multiplier
std::string applyConfigMultiplier(const std::string& valueStr) {
    int value = std::stoi(valueStr);
    
    if (value == 0) {
        std::cout << "Zero configuration value, using default" << std::endl;
    }
    
    if (value < 10) {
        std::cout << "Low configuration value, applying small multiplier" << std::endl;
    } else {
        std::cout << "High configuration value, applying large multiplier" << std::endl;
    }
    
    std::cout << "Applying configuration multiplier: " << value << std::endl;
    return valueStr;
}

// Function 5: Process configuration calculation
std::string processConfigCalculation(const std::string& valueStr) {
    int value = std::stoi(valueStr);
    
    if (value % 2 == 0) {
        std::cout << "Even configuration value, processing normally" << std::endl;
    } else {
        std::cout << "Odd configuration value, applying special processing" << std::endl;
    }
    
    if (value > 50) {
        std::cout << "Large configuration value, using advanced calculation" << std::endl;
    }
    
    std::cout << "Processing configuration calculation: " << value << std::endl;
    return valueStr;
}

int calculateMemoryAllocation(const std::string& valueStr) {
    int value = std::stoi(valueStr);
    
    std::cout << "Calculating memory allocation for value: " << value << std::endl;
    
    int blockSize = 1024;
    // SINK CWE 190
    int totalSize = value * blockSize;
    
    std::cout << "Requested blocks: " << value << std::endl;
    std::cout << "Block size: " << blockSize << std::endl;
    std::cout << "Total size calculated: " << totalSize << std::endl;
    
    if (totalSize < 0) {
        std::cout << "WARNING: Integer overflow detected! Total size is negative: " << totalSize << std::endl;
    }
    
    return totalSize;
}

void logMemoryAllocation(int allocatedSize) {
    if (allocatedSize <= 0) {
        std::cout << "Invalid allocation size, skipping log" << std::endl;
        return;
    }
    
    std::cout << "Logging memory allocation: " << allocatedSize << " bytes" << std::endl;
    
    if (allocatedSize > 1000000) {
        std::cout << "Large memory allocation detected" << std::endl;
    }
}

int main() {
    
    // Receive data from network
    std::string networkData = receiveTcpData();
    
    // Process through intermediate functions
    std::string parsedValue = parseConfigValue(networkData);
    std::string validatedValue = validateConfigFormat(parsedValue);
    std::string rangedValue = checkConfigRange(validatedValue);
    std::string multipliedValue = applyConfigMultiplier(rangedValue);
    std::string calculatedValue = processConfigCalculation(multipliedValue);
    
    // Calculate memory allocation (vulnerability occurs here)
    int allocatedSize = calculateMemoryAllocation(calculatedValue);
    
    // Log the allocation
    logMemoryAllocation(allocatedSize);
    
    std::cout << std::endl;
    std::cout << "Memory allocation calculation completed" << std::endl;
    
    return 0;
}