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
    address.sin_port = htons(8084);
    
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

// Function 1: Parse lower limit value
std::string parseLowerLimitValue(const std::string& data) {
    if (data.empty()) {
        std::cout << "Empty lower limit data received" << std::endl;
        return "0";
    }
    
    std::cout << "Parsing lower limit value: " << data << std::endl;
    return data;
}

// Function 2: Validate limit format
std::string validateLimitFormat(const std::string& limitStr) {
    if (limitStr.empty()) {
        std::cout << "Empty limit format" << std::endl;
        return "0";
    }
    
    std::cout << "Validating limit format: " << limitStr << std::endl;
    return limitStr;
}

// Function 3: Check limit range
std::string checkLimitRange(const std::string& limitStr) {
    int limit = std::stoi(limitStr);
    
    if (limit < 0) {
        std::cout << "Negative limit detected" << std::endl;
    }
    
    if (limit > 1000) {
        std::cout << "High limit detected" << std::endl;
    }
    
    std::cout << "Checking limit range: " << limit << std::endl;
    return limitStr;
}

// Function 4: Apply limit adjustment
std::string applyLimitAdjustment(const std::string& limitStr) {
    int limit = std::stoi(limitStr);
    
    if (limit == 0) {
        std::cout << "Zero limit, using default adjustment" << std::endl;
    }
    
    if (limit < 50) {
        std::cout << "Low limit, applying small adjustment" << std::endl;
    } else {
        std::cout << "High limit, applying large adjustment" << std::endl;
    }
    
    std::cout << "Applying limit adjustment: " << limit << std::endl;
    return limitStr;
}

// Function 5: Process limit calculation
std::string processLimitCalculation(const std::string& limitStr) {
    int limit = std::stoi(limitStr);
    
    if (limit % 5 == 0) {
        std::cout << "Limit divisible by 5, processing normally" << std::endl;
    } else {
        std::cout << "Limit not divisible by 5, applying special processing" << std::endl;
    }
    
    if (limit > 200) {
        std::cout << "Large limit, using advanced calculation" << std::endl;
    }
    
    std::cout << "Processing limit calculation: " << limit << std::endl;
    return limitStr;
}

// Function 6: Calculate buffer size (SINK - Integer underflow vulnerability)
int calculateBufferSize(const std::string& limitStr) {
    int limit = std::stoi(limitStr);
    
    std::cout << "Calculating buffer size for limit: " << limit << std::endl;
    
    int maxBufferSize = 1000; 
    // SINK CWE 191
    int bufferSize = limit - maxBufferSize; 
    
    std::cout << "Maximum buffer size: " << maxBufferSize << std::endl;
    std::cout << "Limit value: " << limit << std::endl;
    std::cout << "Calculated buffer size: " << bufferSize << std::endl;
    
    if (bufferSize < 0) {
        std::cout << "WARNING: Integer underflow detected! Buffer size is negative: " << bufferSize << std::endl;
    }
    
    return bufferSize;
}

void logBufferAllocation(int bufferSize) {
    if (bufferSize <= 0) {
        std::cout << "Invalid buffer size, skipping log" << std::endl;
        return;
    }
    
    std::cout << "Logging buffer allocation: " << bufferSize << " bytes" << std::endl;
    
    if (bufferSize > 500) {
        std::cout << "Large buffer allocation detected" << std::endl;
    }
}

int main() {
    // Receive data from network
    std::string networkData = receiveTcpData();
    
    // Process through intermediate functions
    std::string parsedLimit = parseLowerLimitValue(networkData);
    std::string validatedLimit = validateLimitFormat(parsedLimit);
    std::string rangedLimit = checkLimitRange(validatedLimit);
    std::string adjustedLimit = applyLimitAdjustment(rangedLimit);
    std::string calculatedLimit = processLimitCalculation(adjustedLimit);
    
    // Calculate buffer size (vulnerability occurs here)
    int bufferSize = calculateBufferSize(calculatedLimit);
    
    // Log the allocation
    logBufferAllocation(bufferSize);
    
    std::cout << std::endl;
    std::cout << "Buffer size calculation completed" << std::endl;
    
    return 0;
}