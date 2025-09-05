#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <cstdint>

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
    address.sin_port = htons(8096);
    
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

// Function 1: Parse buffer size data
std::string parseBufferSizeData(const std::string& data) {
    if (data.empty()) {
        std::cout << "Empty buffer size data received" << std::endl;
        return "0";
    }
    
    std::cout << "Parsing buffer size data: " << data << std::endl;
    return data;
}

// Function 2: Validate buffer size format
std::string validateBufferSizeFormat(const std::string& sizeStr) {
    if (sizeStr.empty()) {
        std::cout << "Empty buffer size format" << std::endl;
        return "0";
    }
    
    std::cout << "Validating buffer size format: " << sizeStr << std::endl;
    return sizeStr;
}

// Function 3: Check buffer size range
std::string checkBufferSizeRange(const std::string& sizeStr) {
    size_t size = std::stoul(sizeStr);
    
    if (size == 0) {
        std::cout << "Zero buffer size detected" << std::endl;
    }
    
    if (size > 1000000) {
        std::cout << "Large buffer size detected" << std::endl;
    }
    
    std::cout << "Checking buffer size range: " << size << std::endl;
    return sizeStr;
}

// Function 4: Allocate configuration buffer
void* allocateConfigBuffer(const std::string& sizeStr) {
    size_t bufferSize = std::stoul(sizeStr);
    
    std::cout << "Allocating configuration buffer for size: " << bufferSize << std::endl;
    
    void* buffer = nullptr;
    size_t alignment = 16;  // 16-byte alignment
    
    // SINK CWE 789
    int result = posix_memalign(&buffer, alignment, bufferSize);
    
    if (result != 0) {
        std::cout << "Failed to allocate aligned buffer" << std::endl;
        return nullptr;
    }
    
    std::cout << "Successfully allocated configuration buffer at: " << buffer << std::endl;
    return buffer;
}

void logBufferAllocation(void* buffer, size_t size) {
    if (buffer == nullptr) {
        std::cout << "No buffer to log" << std::endl;
        return;
    }
    
    std::cout << "Logging buffer allocation: " << buffer << " with size: " << size << std::endl;
    
    if (size > 100000) {
        std::cout << "Large buffer allocation detected" << std::endl;
    }
}

int main() {
    // Receive data from network
    std::string networkData = receiveTcpData();
    
    // Process through intermediate functions with conditional flow
    std::string parsedSize = parseBufferSizeData(networkData);
    
    // Conditional flow based on buffer size
    std::string validatedSize;
    if (parsedSize.length() > 1) {
        validatedSize = validateBufferSizeFormat(parsedSize);
    } else {
        std::cout << "Skipping validation for single character size" << std::endl;
        validatedSize = parsedSize;
    }
    
    std::string finalSize;
    if (validatedSize != "0") {
        finalSize = checkBufferSizeRange(validatedSize);
    } else {
        std::cout << "Skipping range check for zero size" << std::endl;
        finalSize = validatedSize;
    }
    
    // Allocate configuration buffer
    void* configBuffer = allocateConfigBuffer(finalSize);
    
    // Log the allocation
    size_t bufferSize = std::stoul(finalSize);
    logBufferAllocation(configBuffer, bufferSize);
    
    // Clean up
    if (configBuffer != nullptr) {
        free(configBuffer);
        std::cout << "Buffer freed successfully" << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "Configuration buffer allocation completed" << std::endl;
    
    return 0;
}