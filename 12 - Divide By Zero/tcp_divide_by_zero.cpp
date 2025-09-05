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
    address.sin_port = htons(8086);
    
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

// Function 1: Parse thread count data
std::string parseThreadCountData(const std::string& data) {
    if (data.empty()) {
        std::cout << "Empty thread count data received" << std::endl;
        return "0";
    }
    
    std::cout << "Parsing thread count data: " << data << std::endl;
    return data;
}

// Function 2: Validate thread format
std::string validateThreadFormat(const std::string& threadStr) {
    if (threadStr.empty()) {
        std::cout << "Empty thread format" << std::endl;
        return "0";
    }
    
    std::cout << "Validating thread format: " << threadStr << std::endl;
    return threadStr;
}

// Function 3: Check thread range
std::string checkThreadRange(const std::string& threadStr) {
    int threadCount = std::stoi(threadStr);
    
    if (threadCount < 0) {
        std::cout << "Negative thread count detected" << std::endl;
    }
    
    if (threadCount > 100) {
        std::cout << "High thread count detected" << std::endl;
    }
    
    std::cout << "Checking thread range: " << threadCount << std::endl;
    return threadStr;
}

// Function 4: Apply thread adjustment
std::string applyThreadAdjustment(const std::string& threadStr) {
    int threadCount = std::stoi(threadStr);
    
    if (threadCount == 0) {
        std::cout << "Zero thread count, using default adjustment" << std::endl;
    }
    
    if (threadCount < 5) {
        std::cout << "Low thread count, applying small adjustment" << std::endl;
    } else {
        std::cout << "High thread count, applying large adjustment" << std::endl;
    }
    
    std::cout << "Applying thread adjustment: " << threadCount << std::endl;
    return threadStr;
}

// Function 5: Process thread calculation
std::string processThreadCalculation(const std::string& threadStr) {
    int threadCount = std::stoi(threadStr);
    
    if (threadCount % 2 == 0) {
        std::cout << "Even thread count, processing normally" << std::endl;
    } else {
        std::cout << "Odd thread count, applying special processing" << std::endl;
    }
    
    if (threadCount > 20) {
        std::cout << "Large thread count, using advanced calculation" << std::endl;
    }
    
    std::cout << "Processing thread calculation: " << threadCount << std::endl;
    return threadStr;
}

// Function 6: Calculate work distribution (SINK - Divide by zero vulnerability)
int calculateWorkDistribution(const std::string& threadStr) {
    int threadCount = std::stoi(threadStr);
    
    std::cout << "Calculating work distribution for thread count: " << threadCount << std::endl;
    
    int totalWork = 1000; 
    // SINK CWE 369
    int workPerThread = totalWork / threadCount;
    
    std::cout << "Total work units: " << totalWork << std::endl;
    std::cout << "Thread count: " << threadCount << std::endl;
    std::cout << "Work per thread calculated: " << workPerThread << std::endl;
    
    return workPerThread;
}

void logWorkDistribution(int workPerThread) {
    if (workPerThread <= 0) {
        std::cout << "Invalid work distribution, skipping log" << std::endl;
        return;
    }
    
    std::cout << "Logging work distribution: " << workPerThread << " units per thread" << std::endl;
    
    if (workPerThread > 100) {
        std::cout << "High work load per thread detected" << std::endl;
    }
}

int main() {
    // Receive data from network
    std::string networkData = receiveTcpData();
    
    // Process through intermediate functions
    std::string parsedThreads = parseThreadCountData(networkData);
    std::string validatedThreads = validateThreadFormat(parsedThreads);
    std::string rangedThreads = checkThreadRange(validatedThreads);
    std::string adjustedThreads = applyThreadAdjustment(rangedThreads);
    std::string calculatedThreads = processThreadCalculation(adjustedThreads);
    
    int workPerThread = calculateWorkDistribution(calculatedThreads);
    
    // Log the distribution
    logWorkDistribution(workPerThread);
    
    std::cout << std::endl;
    std::cout << "Work distribution calculation completed" << std::endl;
    
    return 0;
}