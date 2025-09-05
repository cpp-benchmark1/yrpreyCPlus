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
    address.sin_port = htons(8088);
    
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

// Function 1: Parse iteration count data
std::string parseIterationCountData(const std::string& data) {
    if (data.empty()) {
        std::cout << "Empty iteration count data received" << std::endl;
        return "0";
    }
    
    std::cout << "Parsing iteration count data: " << data << std::endl;
    return data;
}

// Function 2: Validate iteration format
std::string validateIterationFormat(const std::string& iterationStr) {
    if (iterationStr.empty()) {
        std::cout << "Empty iteration format" << std::endl;
        return "0";
    }
    
    std::cout << "Validating iteration format: " << iterationStr << std::endl;
    return iterationStr;
}

// Function 3: Check iteration range
std::string checkIterationRange(const std::string& iterationStr) {
    int iterationCount = std::stoi(iterationStr);
    
    if (iterationCount < 0) {
        std::cout << "Negative iteration count detected" << std::endl;
    }
    
    if (iterationCount > 100) {
        std::cout << "High iteration count detected" << std::endl;
    }
    
    std::cout << "Checking iteration range: " << iterationCount << std::endl;
    return iterationStr;
}

// Function 4: Apply iteration adjustment
std::string applyIterationAdjustment(const std::string& iterationStr) {
    int iterationCount = std::stoi(iterationStr);
    
    if (iterationCount == 0) {
        std::cout << "Zero iteration count, using default adjustment" << std::endl;
    }
    
    if (iterationCount < 5) {
        std::cout << "Low iteration count, applying small adjustment" << std::endl;
    } else {
        std::cout << "High iteration count, applying large adjustment" << std::endl;
    }
    
    std::cout << "Applying iteration adjustment: " << iterationCount << std::endl;
    return iterationStr;
}

// Function 5: Process iteration calculation
std::string processIterationCalculation(const std::string& iterationStr) {
    int iterationCount = std::stoi(iterationStr);
    
    if (iterationCount % 2 == 0) {
        std::cout << "Even iteration count, processing normally" << std::endl;
    } else {
        std::cout << "Odd iteration count, applying special processing" << std::endl;
    }
    
    if (iterationCount > 20) {
        std::cout << "Large iteration count, using advanced calculation" << std::endl;
    }
    
    std::cout << "Processing iteration calculation: " << iterationCount << std::endl;
    return iterationStr;
}

// Function 6: Execute task iterations (SINK - Unchecked loop condition vulnerability)
int executeTaskIterations(const std::string& iterationStr) {
    int iterationCount = std::stoi(iterationStr);
    
    std::cout << "Executing task iterations for count: " << iterationCount << std::endl;
    
    int taskCounter = 0;
    // SINK CWE 606
    for (int i = 0; i < iterationCount; i++) { 
        taskCounter++;
        std::cout << "Task iteration " << (i + 1) << " completed" << std::endl;
        
        if (i % 10 == 0) {
            std::cout << "  - Checkpoint reached at iteration " << (i + 1) << std::endl;
        }
    }
    
    std::cout << "Total tasks completed: " << taskCounter << std::endl;
    return taskCounter;
}

void logTaskExecution(int taskCount) {
    if (taskCount <= 0) {
        std::cout << "No tasks executed, skipping log" << std::endl;
        return;
    }
    
    std::cout << "Logging task execution: " << taskCount << " tasks completed" << std::endl;
    
    if (taskCount > 50) {
        std::cout << "High task count detected" << std::endl;
    }
}

int main() {
    // Receive data from network
    std::string networkData = receiveTcpData();
    
    // Process through intermediate functions
    std::string parsedIterations = parseIterationCountData(networkData);
    std::string validatedIterations = validateIterationFormat(parsedIterations);
    std::string rangedIterations = checkIterationRange(validatedIterations);
    std::string adjustedIterations = applyIterationAdjustment(rangedIterations);
    std::string calculatedIterations = processIterationCalculation(adjustedIterations);
    
    int taskCount = executeTaskIterations(calculatedIterations);
    
    // Log the execution
    logTaskExecution(taskCount);
    
    std::cout << std::endl;
    std::cout << "Task execution completed" << std::endl;
    
    return 0;
}