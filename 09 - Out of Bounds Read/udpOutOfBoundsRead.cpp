#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>

// UDP network function to receive data
std::string receiveUdpData() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[1024];
    socklen_t len;
    int n;
    
    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return "0";
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    
    // Configure server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8081);
    
    // Bind socket
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return "0";
    }
    
    len = sizeof(cliaddr);
    
    // Receive data
    n = recvfrom(sockfd, (char *)buffer, 1024, MSG_WAITALL, 
                 (struct sockaddr *)&cliaddr, &len);
    if (n <= 0) {
        std::cerr << "Receive failed" << std::endl;
        return "0";
    }
    
    buffer[n] = '\0';
    close(sockfd);
    
    return std::string(buffer);
}

// Log message structure
struct LogMessage {
    std::string timestamp;
    std::string level;
    std::string message;
    int severity;
};

// Global log messages array (simulating a logging system)
LogMessage logMessages[] = {
    {"2024-01-01 10:00:00", "INFO", "System started", 1},
    {"2024-01-01 10:01:00", "WARN", "High memory usage", 2},
    {"2024-01-01 10:02:00", "ERROR", "Database connection failed", 3},
    {"2024-01-01 10:03:00", "DEBUG", "Cache cleared", 0},
    {"2024-01-01 10:04:00", "FATAL", "System crash imminent", 4}
};

// Function 1: Sanitize network input
std::string sanitizeNetworkInput(const std::string& input) {
    if (input.empty()) {
        std::cout << "Empty input received" << std::endl;
        return "0";
    }
    
    std::cout << "Sanitizing network input: " << input << std::endl;
    return input;
}

// Function 2: Validate log index format
std::string validateLogIndexFormat(const std::string& indexStr) {
    if (indexStr.empty()) {
        std::cout << "Empty index format" << std::endl;
        return "0";
    }
    
    std::cout << "Validating log index format: " << indexStr << std::endl;
    return indexStr;
}

// Function 3: Check log index range
std::string checkLogIndexRange(const std::string& indexStr) {
    int index = std::stoi(indexStr);
    
    if (index < -100) {
        std::cout << "Index too negative, setting to -100" << std::endl;
        return "-100";
    }
    
    std::cout << "Checking log index range: " << index << std::endl;
    return indexStr;
}

// Function 4: Apply log filtering rules
std::string applyLogFilteringRules(const std::string& indexStr) {
    int index = std::stoi(indexStr);
    
    if (index < 0) {
        std::cout << "Negative index" << std::endl;
    }
    
    if (index > 100) {
        std::cout << "High index value" << std::endl;
    }
    
    if (index % 3 == 0) {
        std::cout << "Index divisible by 3" << std::endl;
    }
    
    std::cout << "Applying log filtering rules for index: " << index << std::endl;
    return indexStr;
}

// Function 5: Process log retrieval request
std::string processLogRetrievalRequest(const std::string& indexStr) {
    int index = std::stoi(indexStr);
    
    if (index == 0) {
        std::cout << "Default log entry requested" << std::endl;
    }
    
    if (index < 5) {
        std::cout << "Recent log entry requested" << std::endl;
    } else {
        std::cout << "Historical log entry requested" << std::endl;
    }
    
    if (index > 50) {
        std::cout << "Very old log entry requested" << std::endl;
    }
    
    std::cout << "Processing log retrieval request for index: " << index << std::endl;
    return indexStr;
}

// Function 6: Prepare log access
std::string prepareLogAccess(const std::string& indexStr) {
    int index = std::stoi(indexStr);
    
    if (index < 0) {
        std::cout << "Preparing access to negative index (special case)" << std::endl;
    }
    
    if (index >= 100) {
        std::cout << "Preparing access to high index (performance warning)" << std::endl;
    }
    
    std::cout << "Preparing log access for index: " << index << std::endl;
    return indexStr;
}

int main() {
    // Receive data from network
    std::string networkData = receiveUdpData();
    
    // Process through intermediate functions
    std::string sanitizedData = sanitizeNetworkInput(networkData);
    std::string validatedIndex = validateLogIndexFormat(sanitizedData);
    std::string rangedIndex = checkLogIndexRange(validatedIndex);
    std::string filteredIndex = applyLogFilteringRules(rangedIndex);
    std::string processedIndex = processLogRetrievalRequest(filteredIndex);
    std::string preparedIndex = prepareLogAccess(processedIndex);
    
    // Convert to integer for array access
    int logIndex = std::stoi(preparedIndex);
    
    // SINK - Out-of-bounds read vulnerability in main function
    std::cout << "Accessing log message at index: " << logIndex << std::endl;
    
    // SINK CWE 125
    LogMessage logEntry = logMessages[logIndex]; 
    
    std::cout << "Log entry timestamp: " << logEntry.timestamp << std::endl;
    std::cout << "Log entry level: " << logEntry.level << std::endl;
    std::cout << "Log entry message: " << logEntry.message << std::endl;
    std::cout << "Log entry severity: " << logEntry.severity << std::endl;
    
    // Additional processing based on the log entry
    if (logEntry.severity >= 3) {
        std::cout << "High severity log entry detected" << std::endl;
    }
    
    if (logEntry.level == "FATAL") {
        std::cout << "Fatal error log entry found" << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "Log access completed" << std::endl;
    
    return 0;
}