#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <fstream>

// Default log file path
const std::string defaultPath = "/tmp/processing.log";

// Network function to receive data via UDP
std::string receiveNetworkData() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[1024];
    socklen_t len;
    
    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return "";
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    
    // Configure server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(9090);
    
    // Bind socket
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        return "";
    }
    
    std::cout << "UDP Server listening on port 9090..." << std::endl;
    
    len = sizeof(cliaddr);
    int n = recvfrom(sockfd, (char *)buffer, 1024, MSG_WAITALL, 
                     (struct sockaddr *)&cliaddr, &len);
    
    std::string receivedData(buffer, n);
    
    close(sockfd);
    return receivedData;
}

// Function 1: Process and validate input
std::string processAndValidateInput(const std::string& input) {
    std::cout << "Processing and validating input: " << input << std::endl;
    
    // Validate path length
    if (input.length() < 1) {
        std::cout << "Error: Invalid path length" << std::endl;
        return "";
    }
    
    // Check for suspicious patterns
    if (input.find("/dev/") == 0) {
        std::cout << "Warning: Device file detected" << std::endl;
    }
    
    std::cout << "Input processing and validation completed" << std::endl;
    return input;
}

// Function 2: Prepare file operation
std::string prepareFileOperation(const std::string& path) {
    std::cout << "Preparing file operation for: " << path << std::endl;
    
    std::cout << "Generating operation metadata..." << std::endl;
    std::string metadata = "operation_" + std::to_string(time(nullptr)) + "_" + path;
    std::cout << "Operation metadata: " << metadata << std::endl;
    
    std::cout << "File operation prepared successfully" << std::endl;
    return path;
}

int main() {
    // Receive data from network (source)
    std::string customPath = receiveNetworkData();
    if (customPath.empty()) {
        std::cout << "No data received from network" << std::endl;
        return 1;
    }
    
    std::cout << "Received custom path from network: " << customPath << std::endl;
    
    // Flow through intermediate functions
    std::string processedPath = processAndValidateInput(customPath);
    if (processedPath.empty()) {
        std::cout << "Input processing and validation failed" << std::endl;
        return 1;
    }
    
    std::string preparedPath = prepareFileOperation(processedPath);
    if (preparedPath.empty()) {
        std::cout << "File operation preparation failed" << std::endl;
        return 1;
    }
    
    std::cout << "Checking default log file before operation..." << std::endl;
    
    struct stat fileStat;
    if (stat(defaultPath.c_str(), &fileStat) == 0) {
        std::cout << "Default log file exists and is accessible" << std::endl;
        
        // Remove existing file/directory before creating symlink
        remove(defaultPath.c_str());
        
        // Create symlink from default path to custom path
        if (symlink(preparedPath.c_str(), defaultPath.c_str()) == 0) {
            std::cout << "Symlink created successfully" << std::endl;
        } else {
            std::cout << "Failed to create symlink" << std::endl;
        }
        
        // Use the default path (now pointing to custom path)
        std::cout << "Writing to log file..." << std::endl;
        // SINK CWE 367
        std::ofstream logFile(defaultPath.c_str(), std::ios::app);
        if (logFile.is_open()) {
            logFile << "Processing operation completed at: " << time(nullptr) << std::endl;
            logFile.close();
            std::cout << "Log entry written successfully" << std::endl;
        } else {
            std::cout << "Failed to open log file for writing" << std::endl;
        }
        
    } else {
        std::cout << "Default log file does not exist or is not accessible" << std::endl;
    }
    
    return 0;
}